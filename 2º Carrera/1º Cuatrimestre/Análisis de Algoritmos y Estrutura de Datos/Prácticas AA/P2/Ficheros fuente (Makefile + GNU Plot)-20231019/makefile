# Compilador de C++ y opciones de compilacion.

CXX = c++
CXXFLAGS = -ansi -Wall -O$(OPTIMIZACION)

# Nivel de optimizacion (por omision, no se optimiza).

OPTIMIZACION = 0

# Modulos objeto y ejecutables.

OBJS = prueba-1.o prueba-2.o prueba-3.o ../Ejercicio1/ordenacion.o
EXES = prueba-1 prueba-2 prueba-3

# Ficheros de tiempo y de graficas.

TIEMPOS = prueba-1.tmp prueba-2.tmp prueba-3.tmp
GRAFICAS = prueba-1-2-3.eps

# Por omision, obtiene los ficheros de tiempo.

all: $(TIEMPOS)

# Obtencion de los ejecutables.

prueba-1: prueba-1.o ../Ejercicio1/ordenacion.o
	$(CXX) $(LDFLAGS) -o $@ $^

prueba-2: prueba-2.o ../Ejercicio1/ordenacion.o
	$(CXX) $(LDFLAGS) -o $@ $^

prueba-3: prueba-3.o ../Ejercicio1/ordenacion.o
	$(CXX) $(LDFLAGS) -o $@ $^

# Obtencion de los objetos.

$(OBJS): cronometro.h ../Ejercicio1/ordenacion.h

# Obtencion de los ficheros de tiempo.

prueba-1.tmp: prueba-1
	./$< | tee $@

prueba-2.tmp: prueba-2
	./$< | tee $@

prueba-3.tmp: prueba-3
	./$< | tee $@

# Obtencion de las graficas.

graficas:
	gnuplot graficas.plot

graficas-eps:
	gnuplot graficas-eps.plot

# Limpieza del directorio.

clean:
	$(RM) $(EXES) $(OBJS) *~

clean-all: clean
	$(RM) $(TIEMPOS) $(GRAFICAS)
