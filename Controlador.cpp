#include <iostream>
#include <stdlib.h>
#include "CacheDatos.h"
#include "CacheInstrucciones.h"
#include "MemoriaPrincipal.h"
#include "CPU.h"

int main(int argc, char *argv[]){
    if ( argc < 3 )
        std::cout << "Uso: <quantum> <#hilos>" << std::endl;
    int quantum = atoi(argv[1]);
    int cant_hilos = atoi(argv[2]);

    CacheInstrucciones CI;
    MemoriaPrincipal MP;
    CacheDatos CD(MP);
    CPU cpu(quantum);
    cpu.set_ptr( &CI, &MP, &CD);
    cpu.cpu_init();
    cpu.printHilos();
}