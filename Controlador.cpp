#include <iostream>
#include <stdlib.h>
#include "CPU.h"
#include "MemoriaPrincipal.h"
#include "CacheInstrucciones.h"
#include "CacheDatos.h"



int main(int argc, char *argv[]){
    std::cout << " ___  ____  __  __  __  __  __      __    ____  _____  ____     ___  ____  __  __\n";
    std::cout << "/ __)(_  _)(  \/  )(  )(  )(  )    /__\  (  _ \(  _  )(  _ \   / __)(  _ \(  )(  )\n";
    std::cout << "\__ \ _)(_  )    (  )(__)(  )(__  /(__)\  )(_) ))(_)(  )   /  ( (__  )___/ )(__)( \n";
	std::cout << "(___/(____)(_/\/\_)(______)(____)(__)(__)(____/(_____)(_)\_)   \___)(__)  (______)\n";

    if ( argc < 3 )
    {
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
