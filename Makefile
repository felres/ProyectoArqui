completeP: */*.cpp
	g++ Controlador.cpp $^ -o cpu -g

documentacion:
	firefox doc/html/index.html &
