#ifndef CACHEINST   
#define CACHEINST
#include <memory>
#include "../MemoriaPrincipal/MemoriaPrincipal.h"
#define BLOCK_SIZE 8
#define WORD_SIZE 4

typedef int tag_t;
typedef int reg_t;

class CacheInstrucciones{
    private:
        struct bloque{
            inst_t word1;
            inst_t word2;
            tag_t tag; 
        };
        bloque memoria[4];
        /// @brief Referencia a la @ref MemoriaPrincipal
        MemoriaPrincipal *mp;
        /**
         * @brief Devuelve el tag del bloque correspondiente a la dirección física dada.
         * @param MAR contiene dirección de memoria para obtener el tag. 
         * @return tag_t 
         */
        tag_t get_tag(reg_t *MAR);
        /**
         * @brief Busca tag de bloque en @ref memoria.
         * @details A partir de un tag dado, verifica si ese tag existe en @ref memoria, si existe
         * retorna el índice del bloque de cache donde se encuentra el tag, si no, retorna -1.
         * @param tag tag a buscar. 
         * @return int indice del bloque con el tag correspondiente. 
         */
        int find_tag(tag_t tag);
        /**
         * @brief Carga bloque de memoria a la cache a partir de un tag de bloque dado. 
         * @details Dado el tag del bloque, calcula la direccion fisica y carga la memoria principal 
         * a @ref Memoria las dos palabras correspondientes en el bloque de cache mediante mapeo directo. 
         * @param tag Tag del bloque a cargar. 
         * @return int Indice del bloque de cache donde se cargó el bloque correspondiente al @param tag. 
         */
        int load_from_memory(tag_t tag);
    public: 
        /**
         * @brief Construct a new Cache Instrucciones object
         * @param mp puntero a objeto @ref MemoriaPrincipal el cual utiliza el cpu para correr. 
         */
        CacheInstrucciones(MemoriaPrincipal *mp);
        /**
         * @brief Devuelve la instruccion pedide a partir de una direccion fisica.
         * @details A partir de la direccion dada, si existe dado bloque en cache, devule un @ref ins_t 
         * con los datos de la instruccion pedida, si no existe, carga primero la isntruccion de memoria principal
         * y luego la revuelve. 
         * @param MAR Direccion fisica de la instruccion.
         * @return inst_t Struct con los datos de la instruccion pedida.
         */
        inst_t lw(reg_t *MAR);
};
#endif
