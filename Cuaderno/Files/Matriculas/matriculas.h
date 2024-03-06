#include <stdio.h>
#ifndef _MATRICULAS_
#define _MATRICULAS

typedef struct{
	int id_mat;
	int id_alum;
}Matricula;

Matricula* getMatriculas (int *arraySize);
void setMatriculas(Matricula* data, int i);

void listarMatriculas(Matricula *data, int arraySize);
void imprimeMatricula(Matricula m);
void listaMateriasAlumno(Matricula *data, int arraySize, int id_alum);

void addMatricula(Matricula** matriculas, int* nMatriculas, int id_alum);
void modificarMatricula(Matricula** data, int nMatriculas, int id_alum);
void eliminarMatricula(Matricula** data, int* nMatriculas, int id_alum);
void cambiarMateria(int id, Matricula** data);

#endif