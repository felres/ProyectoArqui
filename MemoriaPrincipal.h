#ifndef MEMORIA_PRINCIPAL
#define MEMORIA_PRINCIPAL
class MemoriaPrincipal{
    
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
      int memoriaInstrucciones[640]; //80 * 8
    
    public:
      MemoriaPrincipal(int numeroDeHilos);
      ~MemoriaPrincipal();
      Bloque getData(int dir);
      Bloque getInst(int dir);
      bool storeDato(int dir, Bloque dato);
};
#endif
