#include "MemoriaPrincipal.h"
MemoriaPrincipal::MemoriaPrincipal(int numeroDeHilos)
{
	// Llena  toda la memoria de '1' por default
	for(int i = 0; i < memoriaPrincipal.length; i++)
	{
		memoriaPrincipal[i] = 1;
	}
	
	// debe almacenar los hilos de alguna forma, pero deberia ser el que los lee?
}

MemoriaPrincipal::~MemoriaPrincipal(){}

/**
 * dirBloque: Direccion del numero de bloque que debe enviar al cache
 */
int getData(int dir)
{
	if(dir > 383)
	{
		printf("ERROR 1");
		return -1;
	}
	return memoriaDatos[dir/4];
}

int storeDato(int dir, int dato)
{
	if(dir > 383)
	{
		printf("ERROR 3");
		return -1;
	}
	memoriaDatos[dir/4] = dato;
	return dato;
}

/**
 * Ocupa corrimiento
 * Empieza en la 384 y llega hasta 1020.
 */
inst_t getInst(int dir)
{
	if(dir < 383)
	{
		printf("ERROR 2");
		return -1;
	}
	inst_t ins;
	for(int i = 0; i < 4; i++)
	{
		ins.byte[i] = memoriaInstrucciones[dir-384 + i];
	}
	return ins;
}

