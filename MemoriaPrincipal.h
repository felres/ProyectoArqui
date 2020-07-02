#ifndef MEMORIA_PRINCIPAL
#define MEMORIA_PRINCIPAL
class MemoriaPrincipal{
	
	#include <iostream>
	#include <fstream>
	#include <string>
    typedef struct Bloque{
        int palabra1;
        int palabra2;
        char estado;
        int id;
    }Bloque;
    
    struct inst_t{
    int byte[4];
	};
    
    private:
      int memoriaDatos[96]; //48 * 2
      int memoriaDatosWritingIndex = 0;
      int memoriaInstrucciones[640]; //80 * 8
      std::string nombreDelFolderContenedor = "HILILLOS-PRUEBA FINAL-CI0120";
    
    public:
      MemoriaPrincipal(int numeroDeHilos);
      ~MemoriaPrincipal();
      Bloque getData(int dir);
      Bloque getInst(int dir);
      bool storeDato(int dir, Bloque dato);
      int load_hilo(int hilo);
};
#endif
