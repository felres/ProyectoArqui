#ifndef CACHE_DATOS
#define CACHE_DATOS
using namespace std;
#include "MemoriaPrincipal.h"

class CacheDatos{
    typedef struct Bloque{
        int palabra1;
        int palabra2;
        char estado;
        int id;
        int usado;
    }Bloque;
    private:
      int cantFallos;
      int cantSoli;
      int cantFallosLw;
      int cantSoliLw;
      int cantFallosSw;
      int cantSoliSw;
      int indiceLRU;
      Bloque Datos[4];
      MemoriaPrincipal * MP;
      int getBloque(int);
      int getPalabra(int);
      int getIndiceCache(int);
      int CambiarBloque(int);
      int LRU();
    public:
      CacheDatos(MemoriaPrincipal *);
      ~CacheDatos();
      int lw(int,int &);
      void sw(int,int,int &);
      int lr(int,int &,int &);
      bool sc(int,int ,int &, int &);
      void imprimir();
};
#endif
