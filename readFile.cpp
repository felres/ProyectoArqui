#include <iostream>
#include <fstream>
#include <string>

int[][] construirMatrizDelHilo(std::string nombreDelArchivo)
{
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
			std::cout << tp << "\n";
		}
		//siempre cerrar
		newfile.close();
	}
}

int main()
{
   std::string nombreDelFolderContenedor = "HILILLOS-PRUEBA FINAL-CI0120";
   std::string nombreDelArchivo = nombreDelFolderContenedor + "/" + "0.txt";
   construirMatrizDelHilo(nombreDelArchivo);
}
