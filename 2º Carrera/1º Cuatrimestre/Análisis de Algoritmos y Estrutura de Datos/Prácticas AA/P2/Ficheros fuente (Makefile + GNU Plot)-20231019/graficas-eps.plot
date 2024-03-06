# Codificacion ISO Latin-1 y terminal EPS.

set encoding iso_8859_1
set terminal postscript eps solid

# Titulo de cada eje.

set xlabel "n (numero de elementos)"
set ylabel "t(n) (tiempo en segundos)"

# Estilo de presentacion (puntos interpolados linealmente).

set style data linespoints

# Creacion de los ficheros EPS.

set output "prueba-1-2-3.eps"
plot "prueba-1.tmp" title "Ordenacion por intercambio directo", \
     "prueba-2.tmp" title "Ordenacion por seleccion directa", \
     "prueba-3.tmp" title "Ordenacion por insercion directa"
