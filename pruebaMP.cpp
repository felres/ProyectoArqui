#include <iostream>
#include <fstream>
#include <string>
#include "MemoriaPrincipal.h"

int main()
{
   MemoriaPrincipal* foo = new MemoriaPrincipal();
   foo->load_hilo(0);
   foo->load_hilo(1);
   foo->load_hilo(2);
   foo->load_hilo(3);
   foo->load_hilo(4);
   foo->load_hilo(5);
   foo->load_hilo(6);
   foo->printInstructions();
}
