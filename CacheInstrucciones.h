#ifndef CACHEINST   
#define CACHEINST
#include <memory>
#include "MemoriaPrincipal.h"
#define BLOCK_SIZE 8
#define WORD_SIZE 4

typedef int tag_t;
typedef int reg_t;

struct inst_t{
    int byte[4];
};

class CacheInstrucciones{
    private:
        struct bloque{
            inst_t word1;
            inst_t word2;
            tag_t tag; 
        };
        bloque memoria[4];
        MemoriaPrincipal *mp;
        tag_t get_tag(reg_t *);
        int find_tag(tag_t tag);
        int load_from_memory(tag_t );
    public: 
        CacheInstrucciones(MemoriaPrincipal *mp);
        inst_t lw(reg_t *);
};
#endif