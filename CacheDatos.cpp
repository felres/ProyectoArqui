#include "CacheDatos.h"

int CacheDatos::getBloque(int direccion){
    return (int)(direccion/8);
}
int CacheDatos::getPalabra(int direccion){
    int ret = 0;
    if(0 != direccion % 8){
        ret = 1;
    }
    return ret;
}
int CacheDatos::getIndiceCache(int mp_bloque){\
    int ind = -1;
    for(int i = 0; i < 4 && ind == -1; ++i){
        if(mp_bloque == Datos[i].id){
            ind = i;
        }
    }
    return ind
}
int CacheDatos::CambiarBloque(int direccion){
    int victima = LRU();
    int mp_bloque = getBloque(direccion);
    if(Datos[victima].estado != 'M'){
        Datos[victima].id = getBloque(direccion);
        Datos[victima].estado = 'C';
        Datos[victima].palabra1 = MP->getData(mp_bloque*8)
        Datos[victima].palabra1 = MP->getData(mp_bloque*8 + 4)
    }
    return ind
}

CacheDatos::CacheDatos(MemPrincipal * MP){
    this->MP = MP
    for(int i = 0; i < 4; ++i){
        Datos[i].palabra1 = 0;
        Datos[i].palabra2 = 0;
        Datos[i].estado = i;
        Datos[i].id = -1;
    }
}
CacheDatos::~CacheDatos(){}
int CacheDatos::lw(int direccion,int & reloj){
    int ret = 0;
    int mp_bloque = getBloque(direccion);
    //Se guarda cual es el identificador de el bloque que se quiere optener
    int palabra = getPalabra(direccion)
    //se guarda si se busca la palabra 1 o la 2 del bloque
    int indice_Cache = getIndiceCache(mp_bloque);
    //optiene el indice del bloque dentro de la cache, si no esta se retorna -1
    if(indice_Cache != -1){
    //El bloque se encuentra en memoria
        if(palabra = 1){
            ret = Datos[indice_Cache].palabra1;
        }else{
            ret = Datos[indice_Cache].palabra2;
        }
    }else{
    //El bloque no se encuentra en memoria
        indice_Cache = CambiarBloque(direccion);
        //Recupera el bloque de MP, y da el indice donde se guardo
        if(palabra = 1){
            ret = Datos[indice_Cache].palabra1;
        }else{
            ret = Datos[indice_Cache].palabra2;
        }
    }
    return ret;
}

// mp_bloque = getBlo(Dir)
//     cache_bloque = getBloqueCache(mp_bloque)
//     If(EstaEnCache(bloque) && datosNOModificados(bloque)){
//     //El bloque esta en la//cache y no está modificado
//             datos[cache_bloque][getPalabra(dir)] = word
// //Cambia el valor del dato de la cache por el recibido
//             C -> M
// //Cambia de compartido a Modificado
//     }else{
//         if(!datosNOModificados(bloque)){
//         //El bloque esta en la cache modificado
//                datos[cache_bloque][getPalabra(dir)] = word
//         //Cambia el valor
//         }else{ //Bloque no está en la cache
//         CambiarBloque(dir,reloj);
// //Pide bloque a memoria
//     datos[cache_bloque][getPalabra(dir)] = word
//     //Cambia el valor
// }

void CacheDatos::sw(int direccion,int word,int & reloj){
    int mp_bloque = getBloque(direccion);
    //Se guarda cual es el identificador de el bloque que se quiere optener
    int palabra = getPalabra(direccion)
    //se guarda si se busca la palabra 1 o la 2 del bloque
    int indice_Cache = getIndiceCache(mp_bloque);
    //optiene el indice del bloque dentro de la cache, si no esta se retorna -1
    if(indice_Cache != -1 && Datos[indice_Cache] != M){
    //El bloque esta en la cache, y el bloque no esta modificado
        Datos[indice_Cache].estado = M;
        //Deja el estado en modificado
        if(palabra = 1){
            Datos[indice_Cache].palabra1 = word;
        }else{
            Datos[indice_Cache].palabra2 = word;
        }
    }else{
        if(indice_Cache != -1 && Datos[indice_Cache] == M){
        //bloque en cache pero no modificado
            if(palabra = 1){
                Datos[indice_Cache].palabra1 = word;
            }else{
                Datos[indice_Cache].palabra2 = word;
            }
        }else{
        //Bloque no en cache
            indice_Cache = CambiarBloque(direccion);
            //Recupera el bloque de MP, y da el indice donde se guardo
            Datos[indice_Cache] = M;
            if(palabra = 1){
                Datos[indice_Cache].palabra1 = word;
            }else{
                Datos[indice_Cache].palabra2 = word;
            }
        }
    }
}
// mp_bloque = getBloqueMP(dir)
//     If(esta mp_bloque y no invalidado)
//         retorne dato[cache_bloque][getPalabra(dir)%2]
//     else:
//         LRUBlock = getLRUBlock()
// if( datp[LRUBlock] está Modificado)
//      MP->storeDato(getBlockDir(dato[LRUBlock].tag)
// data[LRUBlock].pal1 = MP->getData(mp_bloque*8)
// data[LRUBlock].pal2 = MP->getData(mp_bloque*8+4)
// data[LRUBlock].tag = mp_bloque
// retorne dato[LRUBlock][getPalabra(dir)%2]
// RL = dir
//
//
//     if(EstaEnBloqueyValido(bloque)){//El bloque esta en la cache y no está
//      //modificado
//                        return datos[getPal
//         datos[getBlo(Dir)][getPalabra(dir)] = word
//     }else{
//         bloque = getBloque()
//         datos[bloque][0]
//     }

int CacheDatos::lr(int direccion,int & RL,int & reloj){
    int mp_bloque = getBloque(direccion);
    //Se guarda cual es el identificador de el bloque que se quiere optener
    int palabra = getPalabra(direccion)
    //se guarda si se busca la palabra 1 o la 2 del bloque
    int indice_Cache = getIndiceCache(mp_bloque);
    //optiene el indice del bloque dentro de la cache, si no esta se retorna -1
    RL = direccion
    if(indice_Cache != -1){
    //El bloque se encuentra en memoria
        if(palabra = 1){
            ret = Datos[indice_Cache].palabra1;
        }else{
            ret = Datos[indice_Cache].palabra2;
        }
    }else{
    //El bloque no se encuentra en memoria
        indice_Cache = CambiarBloque(direccion);
        //Recupera el bloque de MP, y da el indice donde se guardo
        if(palabra = 1){
            ret = Datos[indice_Cache].palabra1;
        }else{
            ret = Datos[indice_Cache].palabra2;
        }
    }
}
// if dir == RL:
// // El condicional es correcto
//         exito = true
//         mp_bloque = getBlo(Dir)
//         cache_bloque = getBloqueCache(mp_bloque)
//         If(EstaEnCache(bloque) && datoNoModificado(bloque)):
//         //bloque en cache y Compartido
//             ret = datos[cache_bloque][getPalabra(Dir)]
//             Modificado(cache_bloque)
//         else:
//         -if(!datoNoModificado(bloque)):
//         //En cache modificado
//             ret = datos[cache_bloque][getPalabra(Dir)]
//         -else:
//         //no en cache
//             CambiarBloque(dir,reloj);
//     datos[cache_bloque][palabra] = word
//     else:
//         exito = false
//     return exito

bool CacheDatos::sc(int direccion,int word,int RL, int & reloj){
    bool exito = False;
    if(direccion == RL){
        exito = True;
        int mp_bloque = getBloque(direccion);
        //Se guarda cual es el identificador de el bloque que se quiere optener
        int palabra = getPalabra(direccion)
        //se guarda si se busca la palabra 1 o la 2 del bloque
        int indice_Cache = getIndiceCache(mp_bloque);
        //optiene el indice del bloque dentro de la cache, si no esta se retorna -1
        if(indice_Cache != -1 && Datos[indice_Cache] != M){
        //El bloque esta en la cache, y el bloque no esta modificado
            Datos[indice_Cache].estado = M;
            //Deja el estado en modificado
            if(palabra = 1){
                Datos[indice_Cache].palabra1 = word;
            }else{
                Datos[indice_Cache].palabra2 = word;
            }
        }else{
            if(indice_Cache != -1 && Datos[indice_Cache] == M){
            //bloque en cache pero no modificado
                if(palabra = 1){
                    Datos[indice_Cache].palabra1 = word;
                }else{
                    Datos[indice_Cache].palabra2 = word;
                }
            }else{
            //Bloque no en cache
                indice_Cache = CambiarBloque(direccion);
                //Recupera el bloque de MP, y da el indice donde se guardo
                Datos[indice_Cache] = M;
                if(palabra = 1){
                    Datos[indice_Cache].palabra1 = word;
                }else{
                    Datos[indice_Cache].palabra2 = word;
                }
            }
        }
    }
    return exito;
}
