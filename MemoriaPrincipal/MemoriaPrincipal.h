#ifndef MEMORIA_PRINCIPAL
#define MEMORIA_PRINCIPAL
#include <iostream>
#include <fstream>
#include "../CacheInstrucciones/inst_t.h"
#include <string>
#define MEMORIADATOS_LENGTH 96
#define MEMORIAINSTRUCCIONES_LENGTH 640


class MemoriaPrincipal{
    private:
		int memoriaDatos[MEMORIADATOS_LENGTH]; //48 * 2
		int memoriaInstrucciones[MEMORIAINSTRUCCIONES_LENGTH]; //80 * 8
		int memoriaInstruccionesWritingIndex = 0;
		std::string nombreDelFolderContenedor = "HILILLOS-PRUEBA FINAL-CI0120";
		
    public:
		/**
		* @brief Constructor.
		* @details Llena la memoria de datos con 1s.
		*/
		MemoriaPrincipal();
		~MemoriaPrincipal();

		/**
		* @brief Envia el dato requerido por la instancia del @ref CacheDatos.
		* @details El @ref CacheDatos envia la direccion de memoria que necesita
		* y el metodo lo encuentra en su vector y lo retorna.
		* @param Direccion en memoria virtual que necesita el objeto @ref CacheDatos.
		* @return Exitoso: El int que se refiere a la direccion de memoria
		* en la @ref MemoriaPrincipal. Sino, retorna -1.
		*/
		int getData(int dir);

		/**
		* @brief Retorna la instruccion requerida por la instancia de @ref
		* CacheInstrucciones.
		* @details En este caso para calcular el lugar correcto se debe hacer
		* un corrimiento teniendo en cuenta 
		* @param La direccion que requiere el metodo para buscar en su vector.
		* La direccion de memoria que se envia se encuentra entre 384 y 1020.
		* @return Exitoso: La estructura de datos con los cuatro ints que se
		* refieren a la instruccion que se pide. Sino, retorna la estruct
		* con el primer dato en -1.
		*/
		inst_t getInst(int dir);

		/**
		* @brief Guardar el dato del acche en la memoria principal. 
		* @details Se hace un calculo de donde es que la palabra (int)
		* enviada se necesita guardar.
		* @param La direccion de memoria donde se debe almacenar el dato. 
		* @param El dato que se quiere almacenar en memoria.
		* @return Exitoso: Se retorna el dato almacenado. Sino retorna -1.
		*/
		int storeDato(int dir, int dato);

		/**
		* @brief Lee el archivo de instrucciones del hilillo especificado.
		* @details Se asume que la ruta del archivo a leer es de tipo `.txt`
		* y se encuentra en un subfolder de nombre @ref nombreDelFolderContenedor.
		* El metodo abre el archivo y carga sus datos en el vector de
		* instrucciones @ref memoriaInstrucciones. Para saber donde debe
		* escribir la proxima vez que se llame este metodo, lleva el indice
		* en la variable @ref memoriaInstruccionesWritingIndex. Este metodo
		* usa funciones de c como @ref strtok().
		* @param El numero que se refiere al archivo de instrucciones del hilillo.
		* Empieza en 0 con `0.txt`. 
		* @return La direccion de memoria donde empiezan las instrucciones
		* del hilillo. 
		*/
		int load_hilo(int n);

		/**
		* @brief Imprime una tabla de la memoria de datos virtual.
		* @details Cuando se necesita imprimir el resultado de este @ref CPU
		* virtual, se llama a este metodo publico.
		*/
		int printData();

		/**
		* @brief Imprimir una tabla de la memoria virtual de instrucciones.
		* @details Esto se uso principalmente en el caso de debugeo.
		*/
		int printInstructions();
};
#endif
