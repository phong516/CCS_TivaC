/*$file${.::dpp.h} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*
* Model: dpp-comp.qm
* File:  ${.::dpp.h}
*
* This code has been generated by QM 5.2.4 <www.state-machine.com/qm>.
* DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
*
* SPDX-License-Identifier: GPL-3.0-or-later
*
* This generated code is open source software: you can redistribute it under
* the terms of the GNU General Public License as published by the Free
* Software Foundation.
*
* This code is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* NOTE:
* Alternatively, this generated code may be distributed under the terms
* of Quantum Leaps commercial licenses, which expressly supersede the GNU
* General Public License and are specifically designed for licensees
* interested in retaining the proprietary status of their code.
*
* Contact information:
* <www.state-machine.com/licensing>
* <info@state-machine.com>
*/
/*$endhead${.::dpp.h} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#ifndef DPP_H
#define DPP_H

enum DPPSignals {
    EAT_SIG = Q_USER_SIG, /* published by Table to let a philosopher eat */
    DONE_SIG,       /* published by Philosopher when done eating */
    PAUSE_SIG,      /* published by BSP to pause serving forks */
    SERVE_SIG,      /* published by BSP to serve re-start serving forks */
    TEST_SIG,       /* published by BSP to test the application */
    MAX_PUB_SIG,    /* the last published signal */

    HUNGRY_SIG,     /* posted direclty to Table from hungry Philo */
    TIMEOUT_SIG,    /* used by Philosophers for time events */
    MAX_SIG         /* the last signal */
};

enum {
    N_PHILO = 5 /* number of Philos */
};

/*$declare${Cont::TableEvt} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/

/*${Cont::TableEvt} ........................................................*/
typedef struct {
/* protected: */
    QEvt super;

/* public: */
    uint8_t philoNum;
} TableEvt;
/*$enddecl${Cont::TableEvt} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*$declare${Cont::Table_ctor} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/

/*${Cont::Table_ctor} ......................................................*/
void Table_ctor(void);
/*$enddecl${Cont::Table_ctor} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*$declare${Cont::AO_Table} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/

/*${Cont::AO_Table} ........................................................*/
extern QActive * const AO_Table;
/*$enddecl${Cont::AO_Table} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/*$declare${Comp::CompTimeEvt} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/

/*${Comp::CompTimeEvt} .....................................................*/
typedef struct {
/* protected: */
    QTimeEvt super;

/* public: */
    uint16_t compNum;
} CompTimeEvt;

/* public: */
void CompTimeEvt_ctor(CompTimeEvt * const me,
    QActive * act,
    uint16_t num,
    enum_t const sig,
    uint_fast8_t const tickRate);
/*$enddecl${Comp::CompTimeEvt} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*$declare${Comp::SM_Philo[N_PHILO]} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/

/*${Comp::SM_Philo[N_PHILO]} ...............................................*/
extern QHsm * const SM_Philo[N_PHILO];
/*$enddecl${Comp::SM_Philo[N_PHILO]} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*$declare${Comp::Philo_ctor} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/

/*${Comp::Philo_ctor} ......................................................*/
void Philo_ctor(uint8_t n);
/*$enddecl${Comp::Philo_ctor} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

#endif /* DPP_H */