#include <iostream>
#include <fstream>
#include <string>

int main()
{
   std::string nombreDelArchivo = "HILILLOS-PRUEBA FINAL-CI0120/0.txt";
   std::fstream newfile;
   
   // Abrir archivo para leer
   newfile.open(nombreDelArchivo,std::ios::in);
   
   if (newfile.is_open())
   {
      std::string tp;
      // Leer dato. Instertar hilo en string
      while(getline(newfile, tp))
      { 
         std::cout << tp << "\n";
      }
      //siempre cerrar
      newfile.close();
   }
}
