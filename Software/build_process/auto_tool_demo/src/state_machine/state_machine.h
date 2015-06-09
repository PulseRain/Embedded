#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H


enum FSM_State {
    STATE_INIT,
    STATE_PLAN,
    STATE_CONTROL,
    STATE_EXECUTE,
    STATE_CLOSE
};


extern enum FSM_State FSM(int input);

extern void FSM_Test();

#endif
