#include "CPU.h"


struct TCB{
    int PC;
    int reg[32];
    int id; 
};

CPU::CPU(int quantum){
    this->quantum = quantum; 
}

void CPU::cpu_init(){
    while(!roundRobbing_queue.empty()){
        int thread_fin = 0;
        load_context();
        while(burst != quantum && !thread_fin){
            IR = CI->lw(&PC);
            /* Hace instruccion */
            reloj += 1;
        }
        if(burst == quantum){
            store_context();
        }
    }
}

void CPU::load_context(){
    /* Load PCB from queue */
    TCB tcb = roundRobbing_queue.front();
    roundRobbing_queue.pop();
    /* Load registers */
    for(int r = 0; r < 32; ++r)
        reg[r] = tcb.reg[r];
    /* Load PC */
    PC = tcb.PC;
    /* Load thread id */
    thread_id = tcb.id;
    burst = 0;
}

void CPU::store_context(){
    TCB tcb;
    /* Store PC */
    tcb.PC = PC;
    /* Store Registers */
    for(int r = 0; r < 32; ++r)
        tcb.reg[r] = reg[r];
    /* Store thread id */
    tcb.id = thread_id;
    /* Store PCB in queue */
    roundRobbing_queue.push(tcb);
}
