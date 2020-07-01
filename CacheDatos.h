#ifndef CACHE_DATOS
#define CACHE_DATOS
class CacheDatos{
    typedef struct Bloque{
        int palabra1;
        int palabra2;
        char estado;
        int id;
        bool usado;
    }Bloque;
    private:
      int indiceLRU;
      Bloque Datos[4] MemPrincipal * MP;
      int getBloque(int);
      int getPalabra(int);
      int getIndiceCache(int);
      int CambiarBloque(int);
    public:
      CacheDatos(MemPrincipal *);
      ~CacheDatos();
      int lw(int,int &);
      void sw(int,int,int &);
      int lr(int,int &,int &);
      bool sc(int,int ,int &, int &);
};
#endif
