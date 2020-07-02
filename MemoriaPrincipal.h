#ifndef MEMORIA_PRINCIPAL
#define MEMORIA_PRINCIPAL
#include <iostream>
#include <fstream>
#include <string>
class MemoriaPrincipal{
    
    struct inst_t{
    int byte[4];
	};
    
    private:
      int memoriaDatos[96]; //48 * 2
      int memoriaDatosWritingIndex = 0;
      int memoriaInstrucciones[640]; //80 * 8
      std::string nombreDelFolderContenedor = "HILILLOS-PRUEBA FINAL-CI0120";
    
    public:
      MemoriaPrincipal();
      ~MemoriaPrincipal();
      int getData(int dir);
      //inst_t getInst(int dir);
      int storeDato(int dir, int dato);
      int load_hilo(int n);
      int printData();
};
#endif
