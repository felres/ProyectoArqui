pruebaLectura: readFile.o
	g++ -g readFile.o -o test

readFile.o: readFile.cpp
	g++ -c -g readFile.cpp

pruebaMP: MemoriaPrincipal.h MemoriaPrincipal.cpp pruebaMP.cpp
	g++ MemoriaPrincipal.h MemoriaPrincipal.cpp pruebaMP.cpp -o test
