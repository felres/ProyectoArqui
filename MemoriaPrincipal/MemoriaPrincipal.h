#ifndef MEMORIA_PRINCIPAL
#define MEMORIA_PRINCIPAL
#include <iostream>
#include <fstream>
#include "../CacheInstrucciones/inst_t.h"
#include <string>
#define MEMORIADATOS_LENGTH 96
#define MEMORIAINSTRUCCIONES_LENGTH 640


class MemoriaPrincipal{
    private:
      int memoriaDatos[MEMORIADATOS_LENGTH]; //48 * 2
      int memoriaInstrucciones[MEMORIAINSTRUCCIONES_LENGTH]; //80 * 8
      int memoriaInstruccionesWritingIndex = 0;
      std::string nombreDelFolderContenedor = "HILILLOS-PRUEBA FINAL-CI0120";
    
    public:
      MemoriaPrincipal();
      ~MemoriaPrincipal();
      int getData(int dir);
      inst_t getInst(int dir);
      int storeDato(int dir, int dato);
      int load_hilo(int n);
      int printData();
      int printInstructions();
};
#endif
