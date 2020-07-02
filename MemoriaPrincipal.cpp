#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>


#include "MemoriaPrincipal.h"

struct inst_t{
int byte[4];
};
	
MemoriaPrincipal::MemoriaPrincipal()
{
	// Llena  toda la memoria de '1' por default
	for(int i = 0; i < MEMORIADATOS_LENGTH; i++)
	{
		memoriaDatos[i] = 1;
	}
}

MemoriaPrincipal::~MemoriaPrincipal(){}

/**
 * dirBloque: Direccion del numero de bloque que debe enviar al cache
 */
int MemoriaPrincipal::getData(int dir)
{
	if(dir > 383)
	{
		std::cerr << "ERROR 1" << std::endl;
		return -1;
	}
	return memoriaDatos[dir/4];
}

int MemoriaPrincipal::storeDato(int dir, int dato)
{
	if(dir > 383)
	{
		std::cerr << "ERROR 3" << std::endl;
		return -1;
	}
	memoriaDatos[dir/4] = dato;
	return dato;
}

/**
 * Ocupa corrimiento
 * Empieza en la 384 y llega hasta 1020.
 */
 /*
inst_t MemoriaPrincipal::getInst(int dir)
{
	if(dir < 383)
	{
		std::cerr << "ERROR 2" << std::endl;
		return -1;
	}
	inst_t ins;
	for(int i = 0; i < 4; i++)
	{
		ins.byte[i] = memoriaInstrucciones[dir-384 + i];
	}
	return ins;
}*/

int MemoriaPrincipal::printData()
{
	
	std::string sep = "\t";
	std::string str;
	str = "mem:" + sep + "+0" + sep + "+4" + sep + "+8" + sep + "+12" + sep + '\n';
	str += "-----------------------------------\n";
	for(int i = 0; i < MEMORIADATOS_LENGTH; i+=4)
	{
		str += "[" + std::to_string(i*4) + "]" + sep
			+ std::to_string(memoriaDatos[i]) + sep
			+ std::to_string(memoriaDatos[i+1]) + sep
			+ std::to_string(memoriaDatos[i+2]) + sep
			+ std::to_string(memoriaDatos[i+3]) + '\n';
	}
	std::cout << str << std::endl;
	return 0;
}

int MemoriaPrincipal::printInstructions()
{
	
	std::string sep = "\t";
	std::string str;
	str = "ins:" + sep + "+0" + sep + "+1" + sep + "+2" + sep + "+3" + sep + '\n';
	str += "-----------------------------------\n";
	for(int i = 0; i < MEMORIAINSTRUCCIONES_LENGTH; i+=4)
	{
		str += "[" + std::to_string(i) + "]" + sep
			+ std::to_string(memoriaInstrucciones[i]) + sep
			+ std::to_string(memoriaInstrucciones[i+1]) + sep
			+ std::to_string(memoriaInstrucciones[i+2]) + sep
			+ std::to_string(memoriaInstrucciones[i+3]) + '\n';
	}
	std::cout << str << std::endl;
	return 0;
}

int MemoriaPrincipal::load_hilo(int n)
{
	// Construir el string
	std::string nombreDelArchivo = nombreDelFolderContenedor + "/" + std::to_string(n) + ".txt";
	std::fstream newfile;
	// Abrir archivo para leer
	newfile.open(nombreDelArchivo,std::ios::in);
	if (newfile.is_open())
	{
		std::string tp;
		// Leer dato. Instertar hilo en string
		while(getline(newfile, tp))
		{
			// aca ocupo hacer tokenization de los numeros y ponerlos en la matriz
			// tp contiene la linea que queremos tokenizar
			char *token;
			// hacemos un string de c para poder usar strtok.
			// Le copiamos los contenidos de tp
			char* cstr = new char[tp.length()+1];
			std::strcpy(cstr, tp.c_str());
			///std::cerr << "Must tokenize: " << cstr << std::endl;
			// get the first token
			token = strtok(cstr, " ");
			// walk through other tokens
			while( token != NULL ) {
			  ///std::cerr << "#" << memoriaInstruccionesWritingIndex << " = " << token << std::endl;
			  memoriaInstrucciones[memoriaInstruccionesWritingIndex++] = std::stoi(token);
			  token = strtok(NULL, " ");
			}
		}
		//siempre cerrar
		newfile.close();
	}
	return 0;
}

