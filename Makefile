completeP: Controlador.cpp inst_t.h CacheDatos.h CacheDatos.cpp CacheInstrucciones.h CacheInstrucciones.cpp CPU.h CPU.cpp MemoriaPrincipal.h MemoriaPrincipal.cpp
	g++ Controlador.cpp inst_t.h CacheDatos.h CacheDatos.cpp CacheInstrucciones.h CacheInstrucciones.cpp CPU.h CPU.cpp MemoriaPrincipal.h MemoriaPrincipal.cpp -o test

pruebaMP: MemoriaPrincipal.h MemoriaPrincipal.cpp pruebaMP.cpp
	g++ MemoriaPrincipal.h MemoriaPrincipal.cpp pruebaMP.cpp -o test
