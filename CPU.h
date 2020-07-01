#ifndef CPU_64
#define CPU_64
#include <iostream>
#include <queue>
//#include "CacheDatos.h"
//#include "MemoriaPrincipal.h"
#include "CacheInstrucciones.h"
#include <memory>

typedef int reg_t;
typedef int reg_i; 

struct TCB;

class CacheDatos;
class MemoriaPrincipal;
class CPU{
    private:
        std::queue<TCB> roundRobbing_queue;
        int quantum; 
        int thread_fin;
        reg_t reloj; 
        reg_t burst; 
        reg_t reg[32];
        reg_t RL;
        reg_t PC;
        reg_t MAR;
        reg_t thread_id;
        inst_t IR;
        //CacheDatos * cd;
        CacheInstrucciones * CI;
        MemoriaPrincipal *mp;
        CacheDatos *CD;

        void decode_execute();
        void load_context();
        void store_context();
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


};
#endif