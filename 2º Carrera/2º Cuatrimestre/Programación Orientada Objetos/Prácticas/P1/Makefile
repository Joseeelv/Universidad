#!/usr/bin/colormake

# Makefile para las prácticas P0 y P1
#
# ©2010-2020 Los profesores de POO
# ©2021      Gerardo Aburruzaga García - La Gran Unificación
# ©2022-2024 Francisco Palomo Lozano

# AP1_AP2_N es el nombre del directorio donde el alumno ha desarrollado las
# prácticas de POO. Dentro, aparecerán los de cada práctica, es decir, P0, P1,
# P2, P3 y P4, así como los directorios y ficheros suministrados por los
# profesores de la asignatura: Tests-auto, dsl-comprobaciones y luhn.cpp. Véanse
# las instrucciones de entrega en el enunciado de la práctica.

# La variable P indica el número de práctica. Por omisión, se toma su valor del
# nombre del directorio de la práctica actual, que debe ser P0, P1, P2, P3 o P4.
# 
# AP1_AP2_N debe ser de la forma: Apellido1_Apellido2_Nombre_de_pila, sin tildes
# ni diéresis, y cambiando «ñ» por «nn».

NA        := $(shell dirname ${PWD})
AP1_AP2_N := $(notdir ${NA})
P         := $(shell basename ${PWD})
D         := ${AP1_AP2_N}/$P

# Directorio con los ficheros del programa de pruebas unitarias automáticas.

DIRTESTS = ../Tests-auto

# Compilador de C++ y versión de la norma del lenguaje.
#
# c++	     Compilador de C++ predeterminado, si es que hay uno instalado
# g++ 	     Compilador de C++ de la GNU CC (GNU Compiler Collection)
# clang++    Compilador de C++ de Clang/LLVM
# icpc       Compilador de C++ de Intel

CXX = clang++
STD = c++17
override CXX += -std=${STD}

# Opciones para el preprocesador.
#
# -Idir   Directorio donde buscar cabeceras adicionales (#include "...")
# -Dmacro Define una macro del preprocesador (como con #define)

CPPFLAGS := -D$P -I${DIRTESTS} -I.

# Opciones para el compilador.
#
# En lugar de «-g», empleamos «-gdwarf-4». La cuestión es que, a partir de Clang
# 14, se genera por omisión Dwarf 5 y las versiones de Valgrind inferiores a la
# 3.20 solo pueden trabajar con Dwarf 4.

CXXFLAGS := -gdwarf-4 -Wall -Wextra -pedantic

# Opciones para el enlazador.

LDFLAGS =
LDLIBS  =

# Opciones para Valgrind.

VGFLAGS = --quiet --track-origins=yes --leak-check=full --show-leak-kinds=all --show-reachable=no

# Ficheros de código fuente que tiene que escribir el alumno, y sus objetos binarios.

SRCS = cadena.cpp fecha.cpp
HDRS = ${SRCS:.cpp=.hpp}
OBJS = ${SRCS:.cpp=.o}

# Ficheros correspondientes a las pruebas de consola.

MAIN_SRCS = test-fechacadena-consola.cpp
MAIN_OBJS = ${MAIN_SRCS:.cpp=.o}
MAIN_EXE  = ${MAIN_SRCS:.cpp=}

# Ficheros correspondientes a las pruebas unitarias.

TEST_SRCS = ${DIRTESTS}/test-caso0-cadena-auto.cpp \
            ${DIRTESTS}/test-caso0-fecha-auto.cpp \
            ${DIRTESTS}/test-auto.cpp
TEST_HDRS = ${DIRTESTS}/test-auto.hpp ${DIRTESTS}/fct.h
TEST_OBJS = ${TEST_SRCS:.cpp=.o}
TEST_EXE  = test-$P-auto

# Nombre del archivo comprimido que se entregará a los profesores de la asignatura.

NOMBRETAR = ../../${AP1_AP2_N}.tar.gz

# Objetivos falsos.

.PHONY: all tests test-consola test-auto check valgrind clean distclean dist help variables

# Objetivos silenciosos (no muestran sus acciones).

.SILENT: help variables

# En los programas de GNU se emplean los siguientes nombres para los objetivos:
#
# https://www.gnu.org/software/make/manual/make.html#Standard-Targets

# Construye los programas de prueba.

all: ${MAIN_EXE} ${TEST_EXE}
	@echo "Pruebe «make help» para más objetivos interesantes"

# Ejecuta los programas de prueba.

tests: test-consola test-auto

# Construye y ejecuta las pruebas de consola.

test-consola: ${MAIN_EXE}
	./$<

# Construye y ejecuta las pruebas unitarias automáticas.

test-auto: ${TEST_EXE}
	./$<

# Ejecuta las comprobaciones sobre el código fuente.

check:
	${MAKE} --no-print-directory --makefile=Make_check.mk $@

# Ejecuta las pruebas comprobando que no haya fugas de memoria.
#
# La opción --logger no corresponde a Valgrind, sino al marco de pruebas FCTX, y
# se define en "fct.h".
#
# Forzamos la recompilación de un fichero definiendo la macro VALGRIND para
# indicar que se ejecutará Valgrind sobre su código, pues contiene fragmentos
# que deben compilarse condicionalmente si este es el caso. Tras ello, se
# actualiza su marca de tiempo para que vuelva a recompilarse en otros objetivos
# si es necesario.

valgrind: ${MAIN_EXE} ${TEST_EXE}
	valgrind ${VGFLAGS} ./${MAIN_EXE}
	${MAKE} --no-print-directory --assume-new=${DIRTESTS}/test-caso0-cadena-auto.cpp \
	        CPPFLAGS="${CPPFLAGS} -DVALGRIND" ${TEST_EXE}
	valgrind ${VGFLAGS} ./${TEST_EXE} --logger=minimal
	@touch ${DIRTESTS}/test-caso0-cadena-auto.cpp

# Construye el programa de pruebas de consola.

${MAIN_EXE}: ${MAIN_OBJS} ${OBJS}
	${CXX} -o $@ ${LDFLAGS} $^ ${LDLIBS}

# Construye el programa de pruebas unitarias automáticas.

${TEST_EXE}: ${TEST_OBJS} ${OBJS}
	${CXX} -o $@ ${LDFLAGS} $^ ${LDLIBS}

# Dependencias y compilación.

cadena.o: cadena.hpp
fecha.o: fecha.hpp
${MAIN_OBJS} ${TEST_OBJS}: ${HDRS}

# Por si hay que reconstruir las pruebas automáticas.

${TEST_OBJS}: ${TEST_HDRS}

# Limpia el directorio de la práctica.

clean:
	${RM} ${OBJS} ${MAIN_EXE} ${MAIN_OBJS} ${TEST_EXE} ${TEST_OBJS} *.d core *~ 
	${MAKE} --no-print-directory --makefile=Make_check.mk $@

# Limpia el directorio de la práctica y el de las pruebas unitarias, y elimina el archivo.

distclean: clean
	${RM} ${DIRTESTS}/*.d ${DIRTESTS}/*~
	${RM} ${NOMBRETAR}

# Archiva para su entrega (incondicionalmente, lo que es mejorable).

dist: distclean ${NOMBRETAR}

${NOMBRETAR}:
	@echo "Creando archivo en «${NOMBRETAR}» con el siguiente contenido:"
	@tar --create --verbose --gzip --file=${NOMBRETAR} --directory=../.. \
	     ${SRCS:%.cpp=$D/%.cpp} ${HDRS:%.hpp=$D/%.hpp}

# Muestra la ayuda.

help:
	echo "make [all]          -- Construye los programas de prueba"
	echo "make tests          -- Construye y ejecuta los programas de prueba"
	echo "make test-consola   -- Construye y ejecuta el programa de pruebas de consola"
	echo "make test-auto      -- Construye y ejecuta el programa de pruebas unitarias automáticas"
	echo "make check          -- Construye y ejecuta el programa de comprobaciones estáticas de código fuente"
	echo "make valgrind       -- Construye y ejecuta con valgrind los programas de prueba"
	echo "make clean          -- Limpia el directorio de la práctica"
	echo "make distclean      -- Limpia el directorio de la práctica más otros ficheros"
	echo "make dist           -- Archiva en «${NOMBRETAR}» lo que se debe entregar, tras limpiar"
	echo "make help           -- Muestra esta ayuda"
	echo "make variables      -- Muestra las variables más importantes definidas en este «makefile»"

# Muestra las principales variables y sus valores.

PRINT = printf '%-10s = %-44s\t \# %s\n'

variables:
	echo "# Principales variables definidas en el «makefile»"
	echo
	echo "# Directorios:"
	echo
	${PRINT} "AP1_AP2_N" "${AP1_AP2_N}" "Directorio con las prácticas de POO"
	${PRINT} "P"         "$P"           "Nombre de esta práctica y su directorio"
	${PRINT} "DIRTESTS"  "${DIRTESTS}"  "Directorio de los programas de pruebas unitarias automáticas"
	echo
	echo "# Traducción (preprocesado, compilación y enlazado):"
	echo
	${PRINT} "CXX"       "${CXX}"       "Compilador"
	${PRINT} "CPPFLAGS"  "${CPPFLAGS}"  "Opciones para el preprocesador"
	${PRINT} "CXXFLAGS"  "${CXXFLAGS}"  "Opciones para el compilador"
	${PRINT} "LDFLAGS"   "${LDFLAGS}"   "Opciones para el enlazador"
	${PRINT} "LDLIBS"    "${LDLIBS}"    "Opciones para el enlazador (bibliotecas a enlazar)"
	echo
	echo "# Ficheros:"
	echo
	${PRINT} "SRCS"      "${SRCS}"      "Fuentes a escribir"
	${PRINT} "HDRS"      "${HDRS}"      "Cabeceras a escribir"
	${PRINT} "MAIN_SRCS" "${MAIN_SRCS}" "Fuentes del programa de pruebas de consola"
	${PRINT} "MAIN_EXE"  "${MAIN_EXE}"  "Programa de pruebas de consola"
	${PRINT} "TEST_SRCS" "${TEST_SRCS}" "Fuentes del programa de pruebas unitarias automáticas"
	${PRINT} "TEST_HDRS" "${TEST_HDRS}" "Cabeceras del programa de pruebas unitarias automáticas"
	${PRINT} "TEST_EXE"  "${TEST_EXE}"  "Programa de pruebas unitarias automáticas"
	${PRINT} "NOMBRETAR" "${NOMBRETAR}" "El archivo comprimido con lo que hay que entregar"
