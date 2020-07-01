#include "CacheInstrucciones.h"




CacheInstrucciones::CacheInstrucciones(MemoriaPrincipal *mp){
    this->mp = mp;
}

inst_t CacheInstrucciones::lw(reg_t *MAR){
    inst_t word; 
    tag_t tag = get_tag(MAR);
    int block_i = find_tag(tag);
    if(block_i == -1)
        block_i = load_from_memory(tag);
    if(*MAR % 8)
        return memoria[block_i].word2;
    return memoria[block_i].word1;
}

tag_t CacheInstrucciones::get_tag(reg_t * MAR){
    return (*MAR - (*MAR %BLOCK_SIZE))/BLOCK_SIZE;
}

int CacheInstrucciones::find_tag(tag_t tag){
    for(int b_i = 0; b_i < 4; ++b_i){
        if(memoria[b_i].tag == tag)
            return b_i;
    }
    return -1;
}

int CacheInstrucciones::load_from_memory(tag_t tag){
    int bloque_reemplazo = tag % 4;
    int dir = tag * 8;
    memoria[bloque_reemplazo].word1 = mp->getInst(dir);
    memoria[bloque_reemplazo].word2 = mp->getInst(dir+4);
    return bloque_reemplazo;
}