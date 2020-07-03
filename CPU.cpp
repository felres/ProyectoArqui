#include "CPU.h"


CPU::CPU(int quantum){
    this->quantum = quantum; 
}

void CPU::cpu_init(){
    while(!roundRobbing_queue.empty()){
        thread_fin = 0;
        load_context();
        while(burst != quantum && !thread_fin){
            /* Fetch de instruccion */
            IR = CI->lw(&PC);
            /* Decodificacion y ejecucion de instruccion */
            decode_execute();
            /* Ciclo de instruccion */
            reloj += 1;
        }
        if(burst == quantum){
            /* Se acaba el tiempo de ejecucion */ 
            store_context();
        }else if(thread_fin){
            store_terminated_context();
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
    /* Load cant_ciclos */
    cant_ciclos = tcb.cant_ciclos;
    start_clock = reloj;
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
    /* Store cant_ciclos */
    tcb.cant_ciclos = cant_ciclos + (reloj - start_clock);
    /* Store PCB in queue */
    roundRobbing_queue.push(tcb);
}

void CPU::store_terminated_context()
{
     TCB tcb;
    /* Store PC */
    tcb.PC = PC;
    /* Store Registers */
    for(int r = 0; r < 32; ++r)
        tcb.reg[r] = reg[r];
    /* Store thread id */
    tcb.id = thread_id;
     /* Store cant_ciclos */
    tcb.cant_ciclos = cant_ciclos + (reloj - start_clock);
    /* Store PCB in queue */
    hilos_terminados.emplace_back(tcb);
}

void CPU::addi(reg_i x1, reg_i x2, int n){
    reg[x1] = reg[x2] + n;
}

void CPU::add(reg_i x1, reg_i x2, reg_i x3){
    reg[x1] = reg[x2] + reg[x3];
}

void CPU::sub(reg_i x1, reg_i x2, reg_i x3){
    reg[x1] = reg[x2] - reg[x3];
}

void CPU::mul(reg_i x1, reg_i x2, reg_i x3){
    reg[x1] = reg[x2] * reg[x3];
}   

void CPU::div(reg_i x1, reg_i x2, reg_i x3){
    reg[x1] = reg[x2] / reg[x3];
}

void CPU::lw(reg_i x1, reg_i x2, int n){
    reg[x1] = CD->lw(reg[x2] + n, reloj);
}

void CPU::sw(reg_i x2, reg_i x1, int n){
    CD->sw(reg[x2] + n, reg[x1], reloj);
}

void CPU::beq(reg_i x1, reg_i x2, int n){
    if(reg[x1] == reg[x2])
        PC += n * 4;
}

void CPU::bne(reg_i x1, reg_i x2, int n){
    if(reg[x1] != reg[x2])
        PC += n*4;
}

void CPU::lr(reg_i x1, reg_i x2){
    reg[x1] = CD->lr(reg[x2], RL, reloj);
}

void CPU::sc(reg_i x2, reg_i x1, int n){
    CD->sc(reg[x2] + n, reg[x1], RL, reloj);
}

void CPU::jal(reg_i x1, int n){
    reg[x1] = PC;
    PC += n;
}

void CPU::jalr(reg_i x1, reg_i x2, int n){
    reg[x1] = PC;
    PC += reg[x2] + n;
}

void CPU::decode_execute(){
    switch(IR.byte[0]){
        case 19:
            addi(IR.byte[1], IR.byte[2], IR.byte[3]);
        break; 
        case 71:
            add(IR.byte[1], IR.byte[2], IR.byte[3]);
        break;
        case 83:
            sub(IR.byte[1], IR.byte[2], IR.byte[3]);
        break;
        case 72:
            mul(IR.byte[1], IR.byte[2], IR.byte[3]);
        break;
        case 56:
            div(IR.byte[1], IR.byte[2], IR.byte[3]);
        break;
        case 5:
            lw(IR.byte[1], IR.byte[2], IR.byte[3]);
        break;
        case 37:
            sw(IR.byte[1], IR.byte[2], IR.byte[3]);
        break;
        case 99:
            beq(IR.byte[1], IR.byte[2], IR.byte[3]);
        break;
        case 100:
            bne(IR.byte[1], IR.byte[2], IR.byte[3]);
        break;
        case 51:
            lr(IR.byte[1], IR.byte[2]);
        break;
        case 52:
            sc(IR.byte[1], IR.byte[2], IR.byte[3]);
        break;
        case 111:
            jal(IR.byte[1], IR.byte[3]);
        break;
        case 103:
            jalr(IR.byte[1], IR.byte[2], IR.byte[3]);
        break;
        case 999:
            thread_fin = 1;
        break;
    }
}

void CPU::load_memory(int cant_hilos)
{
    for(int hilo = 0; hilo < cant_hilos; ++hilo){
        TCB tcb;
        tcb.id = hilo;
        tcb.PC = MP->load_hilo(hilo);
        for(reg_i r; r < 32; ++r)
            tcb.reg[r] = 0;
    }
}   

 void CPU::set_ptr(CacheInstrucciones *CI, MemoriaPrincipal *MP, CacheDatos *CD){
     this->CD = CD;
     this->MP = MP;
     this->CI = CI;
 }

void CPU::printHilos(){
    std::cout << "Datos de hilos: " << std::endl;
    for(auto hilo: hilos_terminados){
        std::cout << "\tHilo " << hilo.id << ":" << std::endl;
        std::cout << "\tRegistros:" << std::endl;
        for(reg_i r; r < 32; ++r)
            std::cout << "\tr" << r << " = " << hilo.reg[r] << " , ";
        std::cout << std::endl;
        std::cout << "\tCantidad de ciclos: " << hilo.cant_ciclos << std::endl;
    }
}