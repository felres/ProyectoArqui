#include <iostream>
#include <stdlib.h>
#include "CPU/CPU.h"

int printTitle()
{
	std::string a = " ___  ____  __  __  __  __  __      __    ____  _____  ____     ___  ____  __  __ ";
	std::string b = "/ __)(_  _)(  \\/  )(  )(  )(  )    /__\\  (  _ \\(  _  )(  _ \\   / __)(  _ \\(  )(  )";
	std::string c = "\\__ \\ _)(_  )    (  )(__)(  )(__  /(__)\\  )(_) ))(_)(  )   /  ( (__  )___/ )(__)( ";
	std::string d = "(___/(____)(_/\\/\\_)(______)(____)(__)(__)(____/(_____)(_)\\_)   \\___)(__)  (______)";
	
	std::cout << a << '\n' << b << '\n' << c << '\n' << d << std::endl << std::endl;
	return 0;
}

int main(int argc, char *argv[]){
    printTitle();

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
    cpu.load_memory(cant_hilos);
    cpu.cpu_init();
    cpu.printHilos();
    CD.imprimir();
    MP.printData();
}
