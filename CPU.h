#ifndef CPU_64
#define CPU_64
#include <iostream>
#include <queue>
//#include "CacheDatos.h"
#include "MemoriaPrincipal.h"
#include "CacheInstrucciones.h"
#include <memory>

typedef int reg_t;

struct TCB;

class CPU{
    private:
        std::queue<TCB> roundRobbing_queue;
        int quantum; 
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

        void load_context();
        void store_context();

    public: 
        CPU(int);
        void cpu_init();


};
#endif