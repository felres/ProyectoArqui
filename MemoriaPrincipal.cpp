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

int MemoriaPrincipal::storeDato(int dir, int dato)
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
inst_t MemoriaPrincipal::getInst(int dir)
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

int MemoriaPrincipal::printData()
{
	std::string sep = '\t';
	std::string str;
	str = "mem:" + sep + "+0" + sep + "+1" + sep + "+2" + sep + "+3" + sep + '\n';
	for(int i = 0; i < memoriaDatos.length; i+=4)
	{
		str += "[" + i + "]" + sep
			+ memoriaDatos[i] + sep
			+ memoriaDatos[i+1] + sep
			+ memoriaDatos[i+2] + sep
			+ memoriaDatos[i+3] + '\n';
	}
	printf(str);
	return 0;
}

int MemoriaPrincipal::load_hilo(int n)
{
	// Construir el string
	std::string nombreDelArchivo = nombreDelFolderContenedor + "/" + itoa(n) + ".txt";
	std::fstream newfile;
	// Abrir archivo para leer
	newfile.open(nombreDelArchivo,std::ios::in);
	if (newfile.is_open())
	{
		std::string tp;
		// Leer dato. Instertar hilo en string
		while(getline(newfile, tp))
		{
			/// aca ocupo hacer tokenization de los numeros y ponerlos en la matriz
			// tp contiene la linea que queremos tokenizar
			char *token;
			// get the first token
			token = strtok(str, s);
			// walk through other tokens
			while( token != NULL ) {
			  memoriaDatos[memoriaDatosWritingIndex++] = stoi(token);
			  token = strtok(NULL, s);
			}
		}
		//siempre cerrar
		newfile.close();
	}
}

