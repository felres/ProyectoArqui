#ifndef CPU_64
#define CPU_64
#include <iostream>
#include <queue>
#include <memory>
#include "CacheDatos.h"
#include "CacheInstrucciones.h"

typedef int reg_t;
typedef int reg_i; 

struct TCB{
    reg_t PC;
    reg_t reg[32];
    int id; 
    int cant_ciclos; 
};

class CPU{
    private:
        std::queue<TCB> roundRobbing_queue;
        std::vector<TCB> hilos_terminados; 
        int quantum; 
        int thread_fin;
        int cant_ciclos = 0;
        int start_clock = 0;
        reg_t reloj = 0; 
        reg_t burst = 0; 
        reg_t reg[32];
        reg_t RL = -1;
        reg_t PC = 0;
        reg_t MAR = 0;
        reg_t thread_id = 0;
        inst_t IR;
        CacheInstrucciones *CI;
        MemoriaPrincipal *MP;
        CacheDatos *CD;

        void decode_execute();
        void load_context();
        void store_context();
        void store_terminated_context();
        void addi(reg_i, reg_i, int);
        void add(reg_i, reg_i, reg_i);
        void sub(reg_i, reg_i, reg_i);
        void mul(reg_i, reg_i, reg_i);
        void div(reg_i, reg_i, reg_i);
        void lw(reg_i, reg_i, int);
        void sw(reg_i, reg_i, int);
        void beq(reg_i, reg_i, int);
        void bne(reg_i, reg_i, int);
        void lr(reg_i, reg_i);
        void sc(reg_i, reg_i, int);
        void jal(reg_i, int);
        void jalr(reg_i, reg_i, int);


    public: 
        CPU(int);
        void cpu_init();
        void load_memory(int);
        void printHilos();
        void set_ptr(CacheInstrucciones *, MemoriaPrincipal *, CacheDatos *);


};
#endif