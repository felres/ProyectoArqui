completeP: */*.cpp
	g++ Controlador.cpp $^ -o cpu -g

documentacion:
	firefox html/index.html &
