pruebaLectura: readFile.o
	g++ -g readFile.o -o test

readFile.o: readFile.cpp
	g++ -c -g readFile.cpp