#ifndef CACHE_DATOS
#define CACHE_DATOS
using namespace std;
#include "../MemoriaPrincipal/MemoriaPrincipal.h"

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
      /**
  		* @brief    Optiene el numero de bloque de la direccion recibida
  		* @details  divide la direccion que recibe entre 8, y retorna
      *           el int resultado de esta division
  		* @param    direccion, la direccion de memoria que se desea averiuar el bloque
  		* @return   el numero del bloque que se averiguo
  		*/
      int getBloque(int);


      /**
      * @brief    Optiene la palabra a la que corresponde la direccion de memoria que se paso
      * @details  hace la operacion modulo a la direccion recibida, y se asigna un 0 si es
      *           0, y un 1 si es algo distinto de 0
      * @param    direccion, la direccion de memoria que se desea averiuar la palabra
      * @return   0 o 1, dependiendo del resultado de la operacion, 1 siendo palabra 2 y 0 palabra 1
      */
      int getPalabra(int);


      /**
      * @brief    Optiene el indice del vector Datos donde se encuentra el bloque recibido
      *           como parametro, de no encontrarse se devuelve un -1
      * @details  recorre el vector, para averiguar si el id es igual al parametro recibido,
      *           si lo es se retorna de direccion por la cual se iba iterando
      * @param    mp_bloque, el bloque que se desea saber si esta en cache y en que parte
      * @return   el indice en el que se encuentra el bloque buscado, o -1 si no se encontro
      */
      int getIndiceCache(int);


      /**
  		* @brief    Remplaza un bloque en memoria por el nuevo que se desea subir
  		* @details  Se averigua por medio de LRU el bloque que se va a remplazar, se guarda el bloque a memoria si
      *           este se encuentra modificado, y luego se cargan los nuevos datos que se encuentran en el objeto
      *           @ref MemoriaPrincipal, y se retorna el indice de donde se realizo el cambio
  		* @param    direccion, la direccion del bloque que se desea subir a la cache
  		* @param    reloj, el reloj del codigo, que se debe aumentar si la victima estaba modificada
  		* @return   indice donde quedo guardado el nuevo bloque dentro de la cache
  		*/
      int CambiarBloque(int,int &);


      /**
      * @brief    Averigua cual bloque en la cache se debe remplazar por LRU
      * @details  recorre el vector viendo cual el es primer bloque no usado que encuentra,
      *           luego de pasar por un bloque usado lo cambia a no usado
      * @return   indice del bloque que se debe remplazar
      */
      int LRU();
    public:
      /**
      * @brief Constructor.
      * @details Llena la cache con nulos, y asigna el objeto @ref MemoriaPrincipal.
      * @param MP, puntero al objeto @ref MemoriaPrincipal
      */
      CacheDatos(MemoriaPrincipal *);
      ~CacheDatos();


      /**
  		* @brief    Lee el dato que se encuentra en la direccion solicitada
  		* @details  Averigua que bloque y que palabra se desea leer, si esta en cache lo retorna,
      *           de no estar lo carga a cache y lo retorna
  		* @param    direccion, direccion de la palabra que se esea leer.
  		* @param    reloj, reloj, el reloj del codigo, que se debe aumentar si se cambia de bloque
  		* @return   el dato que se leyo
  		*/
      int lw(int,int &);


      /**
      * @brief    Guarda un dato en la palabra que se indica en la direccion
      * @details  Averigua que bloque y que palabra se desea hacer el cambio, si este esta en cache
      *           se escribe y se cambia a modificado si no lo estaba antes, y si no estaba se carga
      *           en cache el bloque y se escribe en el bloque recien cargado
      * @param    direccion, direccion de donde se desea guardar la palabra recibida
      * @param    word, palabra que se desea escribir en memoria
      * @param    reloj, reloj, el reloj del codigo, que se debe aumentar si se cambia de bloque
      */
      void sw(int,int,int &);


      /**
      * @brief    Lee el dato que se encuentra en la direccion solicitada
      * @details  Averigua que bloque y que palabra se desea leer, si esta en cache lo retorna,
      *           de no estar lo carga a cache y lo retorna, y hace RL = direccion
      * @param    direccion, direccion de la palabra que se esea leer.
      * @param    RL, direccion para coordinar memoria critica
      * @param    reloj, reloj, el reloj del codigo, que se debe aumentar si se cambia de bloque
      * @return    el dato que se leyo
      */
      int lr(int,int &,int &);


      /**
      * @brief
      * @details  si RL == direccion, Averigua que bloque y que palabra se desea hacer el cambio,
      *           si este esta en cache se escribe y se cambia a modificado si no lo estaba antes,
      *           y si no estaba se carga en cache el bloque y se escribe en el bloque recien cargado
      * @param    direccion, , direccion de donde se desea guardar la palabra recibida
      * @param    RL, direccion para coordinar memoria critica
      * @param    reloj, reloj, el reloj del codigo, que se debe aumentar si se cambia de bloque
      * @return   retorna si se tuvo exito a la hora de hacer la escritura, 1 es si, 0 es no
      */
      bool sc(int,int ,int &, int &);
      /**
      * @brief      imprime la cache y las estadisticas que se requiere
      */
      void imprimir();
};
#endif
