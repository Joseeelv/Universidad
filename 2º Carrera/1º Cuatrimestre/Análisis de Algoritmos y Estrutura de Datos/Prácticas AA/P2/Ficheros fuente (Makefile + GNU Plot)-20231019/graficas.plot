# Titulo de cada eje.
 
set xlabel "n (numero de elementos)"
set ylabel "t(n) (tiempo en segundos)"

# Estilo de presentacion (puntos interpolados linealmente).

set style data linespoints

# Representacion grafica.

set terminal x11 1
plot "prueba-1.tmp" title "Ordenacion por intercambio directo", \
     "prueba-2.tmp" title "Ordenacion por seleccion directa", \
     "prueba-3.tmp" title "Ordenacion por insercion directa"

# Pausa (hasta que se pulse [Intro]).

pause -1 "[Intro] para terminar\n"
