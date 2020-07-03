#include <iostream>
#include <stdlib.h>
#include "CPU.h"
#include "MemoriaPrincipal.h"
#include "CacheInstrucciones.h"
#include "CacheDatos.h"



int main(int argc, char *argv[]){
    if ( argc < 3 ){
        std::cout << "Uso: <quantum> <#hilos>" << std::endl;
        return 1;
    }
    int quantum = atoi(argv[1]);
    int cant_hilos = atoi(argv[2]);

    MemoriaPrincipal MP;
    CacheInstrucciones CI(&MP);
    CacheDatos CD(&MP);
    CPU cpu(quantum);
    cpu.set_ptr( &CI, &MP, &CD);
    cpu.cpu_init();
    cpu.printHilos();
    CD.imprimir();
    MP.printData();
}