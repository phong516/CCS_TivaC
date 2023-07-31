/*$file${src::qf::qf_defer.c} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*
* Model: qpc.qm
* File:  ${src::qf::qf_defer.c}
*
* This code has been generated by QM 5.2.4 <www.state-machine.com/qm>.
* DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
*
* This code is covered by the following QP license:
* License #    : LicenseRef-QL-dual
* Issued to    : Any user of the QP/C real-time embedded framework
* Framework(s) : qpc
* Support ends : 2023-12-31
* License scope:
*
* Copyright (C) 2005 Quantum Leaps, LLC <state-machine.com>.
*
* SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-QL-commercial
*
* This software is dual-licensed under the terms of the open source GNU
* General Public License version 3 (or any later version), or alternatively,
* under the terms of one of the closed source Quantum Leaps commercial
* licenses.
*
* The terms of the open source GNU General Public License version 3
* can be found at: <www.gnu.org/licenses/gpl-3.0>
*
* The terms of the closed source Quantum Leaps commercial licenses
* can be found at: <www.state-machine.com/licensing>
*
* Redistributions in source code must retain this top-level comment block.
* Plagiarizing this software to sidestep the license obligations is illegal.
*
* Contact information:
* <www.state-machine.com/licensing>
* <info@state-machine.com>
*/
/*$endhead${src::qf::qf_defer.c} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*! @file
* @brief QActive_defer() and QActive_recall() implementation.
*/
#define QP_IMPL           /* this is QP implementation */
#include "qf_port.h"      /* QF port */
#include "qf_pkg.h"       /* QF package-scope interface */
#include "qassert.h"      /* QP embedded systems-friendly assertions */
#ifdef Q_SPY              /* QS software tracing enabled? */
    #include "qs_port.h"  /* QS port */
    #include "qs_pkg.h"   /* QS facilities for pre-defined trace records */
#else
    #include "qs_dummy.h" /* disable the QS software tracing */
#endif /* Q_SPY */

Q_DEFINE_THIS_MODULE("qf_defer")

/*$skip${QP_VERSION} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/* Check for the minimum required QP version */
#if (QP_VERSION < 700U) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8U))
#error qpc version 7.0.0 or higher required
#endif
/*$endskip${QP_VERSION} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/*$define${QF::QActive::defer} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/

/*${QF::QActive::defer} ....................................................*/
bool QActive_defer(QActive const * const me,
    QEQueue * const eq,
    QEvt const * const e)
{
    bool const status = QEQueue_post(eq, e, 0U, me->prio);
    QS_CRIT_STAT_

    QS_BEGIN_PRE_(QS_QF_ACTIVE_DEFER, me->prio)
        QS_TIME_PRE_();      /* time stamp */
        QS_OBJ_PRE_(me);     /* this active object */
        QS_OBJ_PRE_(eq);     /* the deferred queue */
        QS_SIG_PRE_(e->sig); /* the signal of the event */
        QS_2U8_PRE_(e->poolId_, e->refCtr_); /* pool Id & ref Count */
    QS_END_PRE_()

    return status;
}
/*$enddef${QF::QActive::defer} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*$define${QF::QActive::recall} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/

/*${QF::QActive::recall} ...................................................*/
bool QActive_recall(QActive * const me,
    QEQueue * const eq)
{
    QEvt const * const e = QEQueue_get(eq, me->prio);
    bool recalled;

    /* event available? */
    if (e != (QEvt *)0) {
        QF_CRIT_STAT_

        QACTIVE_POST_LIFO(me, e); /* post it to the front of the AO's queue */

        QF_CRIT_E_();

        /* is it a dynamic event? */
        if (e->poolId_ != 0U) {

            /* after posting to the AO's queue the event must be referenced
            * at least twice: once in the deferred event queue (eq->get()
            * did NOT decrement the reference counter) and once in the
            * AO's event queue.
            */
            Q_ASSERT_CRIT_(210, e->refCtr_ >= 2U);

            /* we need to decrement the reference counter once, to account
            * for removing the event from the deferred event queue.
            */
            QEvt_refCtr_dec_(e); /* decrement the reference counter */
        }

        QS_BEGIN_NOCRIT_PRE_(QS_QF_ACTIVE_RECALL, me->prio)
            QS_TIME_PRE_();      /* time stamp */
            QS_OBJ_PRE_(me);     /* this active object */
            QS_OBJ_PRE_(eq);     /* the deferred queue */
            QS_SIG_PRE_(e->sig); /* the signal of the event */
            QS_2U8_PRE_(e->poolId_, e->refCtr_); /* pool Id & ref Count */
        QS_END_NOCRIT_PRE_()

        QF_CRIT_X_();
        recalled = true;
    }
    else {
        QS_CRIT_STAT_

        QS_BEGIN_PRE_(QS_QF_ACTIVE_RECALL_ATTEMPT, me->prio)
            QS_TIME_PRE_();      /* time stamp */
            QS_OBJ_PRE_(me);     /* this active object */
            QS_OBJ_PRE_(eq);     /* the deferred queue */
        QS_END_PRE_()

        recalled = false;
    }
    return recalled;
}
/*$enddef${QF::QActive::recall} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*$define${QF::QActive::flushDeferred} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/

/*${QF::QActive::flushDeferred} ............................................*/
uint_fast16_t QActive_flushDeferred(QActive const * const me,
    QEQueue * const eq)
{
    uint_fast16_t n = 0U;
    for (QEvt const *e = QEQueue_get(eq, me->prio);
         e != (QEvt *)0;
         e = QEQueue_get(eq, me->prio))
    {
        ++n; /* count the flushed event */
    #if (QF_MAX_EPOOL > 0U)
        QF_gc(e); /* garbage collect */
    #endif
    }
    return n;
}
/*$enddef${QF::QActive::flushDeferred} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/