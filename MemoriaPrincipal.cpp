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
int[] getData(int dirBloque)
{
	int dirDeMeoria = dirBloque * 8;
	int bloque[8];
	for(int i = 0; i < 8; i++)
	{
		bloque[i] = memoriaPrincipal[dirDeMemoria + i];
	}
	return bloque;
}

int[] getInst(int dirBloque)
{
}

bool storeDato(int dirBloque, int[] dato)
{
	bool exitoso = true;
}
