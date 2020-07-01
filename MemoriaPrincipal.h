#ifndef MEMORIA_PRINCIPAL
#define MEMORIA_PRINCIPAL
class MemoriaPrincipal{
    
    typedef struct Bloque{
        int palabra1;
        int palabra2;
        char estado;
        int id;
    }Bloque;
    
    private:
      int memoriaPrincipal[1024]
    
    public:
      MemoriaPrincipal(int numeroDeHilos);
      ~MemoriaPrincipal();
      Bloque getData(int dir);
      Bloque getInst(int dir);
      bool storeDato(int dir, Bloque dato);
};
#endif
