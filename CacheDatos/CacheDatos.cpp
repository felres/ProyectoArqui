#include "CacheDatos.h"
/*
*
*
*/
int CacheDatos::LRU(){
    int victima = -1;
    while(victima == -1){
    //Mientras no se haya seleccionado una victima
        if(Datos[indiceLRU].usado == 0){
        //Si el indice no se ha usado recientemente, seleccionar como victima
            victima = indiceLRU;
        }else{
        //Si se ha usado recientemente, cambiar su estado
            Datos[indiceLRU].usado = 0;
        }
        ++indiceLRU;
        indiceLRU = indiceLRU % 4;
        //Aumenta el puntero, y lo hace circular
    }
    return victima;
}

int CacheDatos::getBloque(int direccion){
    //Devuelve el bloque al que pertenece la direccion en Memoria Principal
    return (int)(direccion/8);
}
int CacheDatos::getPalabra(int direccion){
    int ret = 0;
    //Decide si el modulo es 0, es la palabra 1, sino es la palabra 2
    if(0 != direccion % 8){
        ret = 1;
    }
    return ret;
}
int CacheDatos::getIndiceCache(int mp_bloque){\
    int ind = -1;
    for(int i = 0; i < 4 && ind == -1; ++i){
    //Recorre la cache para encontrar si pertenece el bloque, y Devuelve el indice, de no estar devuelve -1
        if(mp_bloque == Datos[i].id){
            ind = i;
        }
    }
    return ind;
}
int CacheDatos::CambiarBloque(int direccion, int & reloj){
    ++cantFallos;
    int victima = LRU();
    //Decide en que bloque se van a poner los nuevos datos
    int mp_bloque = getBloque(direccion);
    //Se guarda cual es el identificador de el bloque que se quiere optener
    if(Datos[victima].estado == 'M'){
    //Se encuentra modificado, se guardan los datos en memoria
        reloj += 44;
        MP->storeDato((Datos[victima].id)*8,Datos[victima].palabra1);
        MP->storeDato(((Datos[victima].id)*8) + 4,Datos[victima].palabra2);
    }
    Datos[victima].id = getBloque(direccion);
    Datos[victima].estado = 'C';
    Datos[victima].palabra1 = MP->getData(mp_bloque*8);
    Datos[victima].palabra2 = MP->getData(mp_bloque*8 + 4);
    Datos[victima].usado = 1;
    //Cambia el bloque victima por el que se pidio
    return victima;
}

CacheDatos::CacheDatos(MemoriaPrincipal * MP){
    this->MP = MP;
    for(int i = 0; i < 4; ++i){
        Datos[i].palabra1 = 0;
        Datos[i].palabra2 = 0;
        Datos[i].estado = i;
        Datos[i].id = -1;
        Datos[i].usado = 0;
    }
    indiceLRU = 0;
    cantFallos = 0;
    cantSoli = 0;
    cantFallosLw = 0;
    cantSoliLw = 0;
    cantFallosSw = 0;
    cantSoliSw = 0;
}

CacheDatos::~CacheDatos(){}
int CacheDatos::lw(int direccion,int & reloj){
    int ret = 0;
    ++cantSoli;
    ++cantSoliLw;
    int mp_bloque = getBloque(direccion);
    //Se guarda cual es el identificador de el bloque que se quiere optener
    int palabra = getPalabra(direccion);
    //se guarda si se busca la palabra 1 o la 2 del bloque
    int indice_Cache = getIndiceCache(mp_bloque);
    //optiene el indice del bloque dentro de la cache, si no esta se retorna -1
    if(indice_Cache != -1){
    //El bloque se encuentra en memoria
        Datos[indice_Cache].usado = 1;
        if(palabra = 1){
            ret = Datos[indice_Cache].palabra1;
        }else{
            ret = Datos[indice_Cache].palabra2;
        }
    }else{
    //El bloque no se encuentra en memoria
        ++cantFallosLw;
        indice_Cache = CambiarBloque(direccion,reloj);
        reloj += 44;
        //Recupera el bloque de MP, y da el indice donde se guardo
        if(palabra = 1){
            ret = Datos[indice_Cache].palabra1;
        }else{
            ret = Datos[indice_Cache].palabra2;
        }
    }
    return ret;
}

void CacheDatos::sw(int direccion,int word,int & reloj){
    ++cantSoli;
    ++cantSoliSw;
    int mp_bloque = getBloque(direccion);
    //Se guarda cual es el identificador de el bloque que se quiere optener
    int palabra = getPalabra(direccion);
    //se guarda si se busca la palabra 1 o la 2 del bloque
    int indice_Cache = getIndiceCache(mp_bloque);
    //optiene el indice del bloque dentro de la cache, si no esta se retorna -1
    if(indice_Cache != -1 && Datos[indice_Cache].estado != 'M'){
    //El bloque esta en la cache, y el bloque no esta modificado
        Datos[indice_Cache].estado = 'M';
        //Deja el estado en modificado
        Datos[indice_Cache].usado = 1;
        if(palabra = 1){
            Datos[indice_Cache].palabra1 = word;
        }else{
            Datos[indice_Cache].palabra2 = word;
        }
    }else{
        if(indice_Cache != -1 && Datos[indice_Cache].estado == 'M'){
        //bloque en cache pero modificado
            Datos[indice_Cache].usado = 1;
            if(palabra == 0){
                Datos[indice_Cache].palabra1 = word;
            }else{
                Datos[indice_Cache].palabra2 = word;
            }
        }else{
        //Bloque no en cache
            ++cantFallosSw;
            indice_Cache = CambiarBloque(direccion,reloj);
            reloj += 44;
            //Recupera el bloque de MP, y da el indice donde se guardo
            Datos[indice_Cache].estado = 'M';
            if(palabra == 0){
                Datos[indice_Cache].palabra1 = word;
            }else{
                Datos[indice_Cache].palabra2 = word;
            }
        }
    }
}

int CacheDatos::lr(int direccion,int & RL,int & reloj){
    ++cantSoli;
    ++cantSoliLw;
    int ret = 0;
    int mp_bloque = getBloque(direccion);
    //Se guarda cual es el identificador de el bloque que se quiere optener
    int palabra = getPalabra(direccion);
    //se guarda si se busca la palabra 1 o la 2 del bloque
    int indice_Cache = getIndiceCache(mp_bloque);
    //optiene el indice del bloque dentro de la cache, si no esta se retorna -1
    RL = direccion;
    if(indice_Cache != -1){
    //El bloque se encuentra en memoria
        Datos[indice_Cache].usado = 1;
        if(palabra == 0){
            ret = Datos[indice_Cache].palabra1;
        }else{
            ret = Datos[indice_Cache].palabra2;
        }
    }else{
    //El bloque no se encuentra en memoria
        ++cantSoliLw;
        indice_Cache = CambiarBloque(direccion,reloj);
        reloj += 44;
        //Recupera el bloque de MP, y da el indice donde se guardo
        if(palabra == 0){
            ret = Datos[indice_Cache].palabra1;
        }else{
            ret = Datos[indice_Cache].palabra2;
        }
    }
    return ret;
}

bool CacheDatos::sc(int direccion,int word,int & RL, int & reloj){
    bool exito = 0;
    ++cantSoli;
    ++cantSoliSw;
    if(direccion == RL){
        exito = 1;
        int mp_bloque = getBloque(direccion);
        //Se guarda cual es el identificador de el bloque que se quiere optener
        int palabra = getPalabra(direccion);
        //se guarda si se busca la palabra 1 o la 2 del bloque
        int indice_Cache = getIndiceCache(mp_bloque);
        //optiene el indice del bloque dentro de la cache, si no esta se retorna -1
        if(indice_Cache != -1 && Datos[indice_Cache].estado != 'M'){
        //El bloque esta en la cache, y el bloque no esta modificado
            Datos[indice_Cache].estado = 'M';
            //Deja el estado en modificado
            if(palabra == 0){
                Datos[indice_Cache].palabra1 = word;
            }else{
                Datos[indice_Cache].palabra2 = word;
            }
            Datos[indice_Cache].usado = 1;
        }else{
            if(indice_Cache != -1 && Datos[indice_Cache].estado == 'M'){
            //bloque en cache pero modificado
                Datos[indice_Cache].usado = 1;
                if(palabra == 0){
                    Datos[indice_Cache].palabra1 = word;
                }else{
                    Datos[indice_Cache].palabra2 = word;
                }
            }else{
            //Bloque no en cache
                ++cantFallosSw;
                indice_Cache = CambiarBloque(direccion,reloj);
                reloj += 44;
                //Recupera el bloque de MP, y da el indice donde se guardo
                Datos[indice_Cache].estado = 'M';
                if(palabra == 0){
                    Datos[indice_Cache].palabra1 = word;
                }else{
                    Datos[indice_Cache].palabra2 = word;
                }
            }
        }
    }
    return exito;
}

void CacheDatos::imprimir(){
    cout << "Cache de Datos:" << endl;
    for(int i = 0; i < 4; ++i){
        cout << "\tBloque = " << Datos[i].id << endl;
        cout << "\t\tPalabra 1 = " << Datos[i].palabra1 << endl;
        cout << "\t\tPalabra 2 = " << Datos[i].palabra2 << endl;
        cout << "\t\tEstado = " << Datos[i].estado << endl;
    }
    if(cantSoli){
        cout << "\tTasa de fallos: " << (double) cantFallos/cantSoli<< endl;
    }
    if(cantSoliLw){
        cout << "\tTasa de Fallos lw: " << (double) cantFallosLw/cantSoliLw << endl;
    }else{
        cout << "\tTasa de Fallos lw: No" << endl;
    }
    if(cantSoliSw){
        cout << "\tTasa de Fallos sw: " << (double) cantFallosSw/cantSoliSw << endl;
    }else{
        cout << "\tTasa de Fallos sw: NO" << endl;
    }
}
