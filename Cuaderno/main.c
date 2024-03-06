#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Files/Usuarios/usuarios.h"
#include "Files/Calificaciones/calificaciones.h"
#include "Files/Matriculas/matriculas.h"
#include "Files/Configuracion/Config.h"
#include "Files/Horario/Horario.h"
#include "Files/Alumnos/alumnos.h"
#include "Files/Materias/materias.h"

//DECLARACION DE FUNCIONES DEL MAIN
static void bienvenida();
static void despedida();
void menuAdmin(Usuario** usuarios, int* nUsuarios, alumnos** v_alumnos, int* n_alumnos, materias** v_materias, int* n_materias, Matricula** matriculas, int* nMatriculas, Horario** Horarios, int* nHorarios, Configuracion** Configuraciones, int* nConfiguraciones);
void menuAdminAlum(alumnos** v_alumnos, int* n_alumnos, Matricula** matriculas, int* nMatriculas);
void menuMatricula(Matricula** matriculas, int* nMatriculas);
void menuAdminMaterias(materias** v_materias, int* n_materias);
void menuAdminHorarios(Horario** Horarios, int* nHorarios);
void menuProfe(int id_prof, alumnos** v_alumnos, int* n_alumnos, materias** v_materias, int* n_materias, Calificacion** calificaciones, int* nCalificaciones, Matricula** matriculas, int* nMatriculas, Horario** Horarios, int* nHorarios, Configuracion** Configuraciones, int* nConfiguraciones);
void menuListaAlumnos(int id_mat, alumnos** v_alumnos, int* n_alumnos, materias** v_materias, int* n_materias, Calificacion** calificaciones, int* nCalificaciones, Matricula** matriculas, int* nMatriculas, Horario** Horarios, int* nHorarios, Configuracion** Configuraciones, int* nConfiguraciones);

int main(){
	
	int nUsuarios, nCalificaciones, nMatriculas, nConfiguraciones, nHorarios, n_alumnos, n_materias, opt;
	int id = 0;

	Usuario *usuarios;
	Calificacion *calificaciones;
	Matricula *matriculas;
	Configuracion *Configuraciones;
	Horario *Horarios;

	usuarios = getUsuarios(&nUsuarios);
	calificaciones = getCalificaciones(&nCalificaciones);
	matriculas = getMatriculas(&nMatriculas);
	Configuraciones = getConfiguracion(&nConfiguraciones);
	Horarios = getHorarios(&nHorarios);
	cargar_alumnos(&v_alumnos, &n_alumnos);
	cargar_materias(&v_materias, &n_materias);
	
	bienvenida();
	
	
	opt = login(&nUsuarios, &usuarios, &id);

	switch(opt){
		case 1:	system("cls");
				//MenuAdmin
				menuAdmin(&usuarios, &nUsuarios, &v_alumnos, &n_alumnos, &v_materias, &n_materias, &matriculas, &nMatriculas, &Horarios, &nHorarios, &Configuraciones, &nConfiguraciones);
			break;
		case 2:	system("cls");
				//MenuProfe
				menuProfe(id, &v_alumnos, &n_alumnos, &v_materias, &n_materias, &calificaciones, &nCalificaciones, &matriculas, &nMatriculas, &Horarios, &nHorarios, &Configuraciones, &nConfiguraciones);

			break;
	}


	setUsuarios(usuarios, nUsuarios);
	setCalificaciones(calificaciones, nCalificaciones);
	setMatriculas(matriculas, nMatriculas);
	setConfiguracion(Configuraciones, nConfiguraciones);
	setHorarios(Horarios, nHorarios);
	guardar_alumnos(v_alumnos, n_alumnos);
	guardar_materias(v_materias, n_materias);
	
	despedida();
	
	system("pause");
	return 0;
}

//Cabecera: static void bienvenida
//Precondicion: ninguna
//Postcondición: muestra el mensaje de bienvenida
static void bienvenida(){
	printf("-------------------------------------\n");
	printf("BIENVENIDO A TU CUARDERNO DIGITAL: \n");
	printf("-------------------------------------\n");
}


//Cabecera: static void despedida
//Precondicion: se debe colocar despues del set(cuando los datos actualizados se guardan en los ficheros)
//postcondicion: muestra el mensaje de despedida.
static void despedida(){
		printf("-------------------------------------\n");
		printf("SALIENDO DEL CUARDENO, GUARDANDO DATOS...");
		printf("\n-------------------------------------\n");
		printf("\nGuardado completado\n");
}


//cabecera void menuAdmin(Usuario** usuarios, int* nUsuarios, alumnos** v_alumnos, int* n_alumnos, materias** v_materias, int* n_materias, Matricula** matriculas, int* nMatriculas, Horario** Horarios, int* nHorarios, Configuracion** Configuraciones, int* nConfiguraciones)
//precondicion todas las estructuras del sistema inicializadas
//postcondicion devuelve todas las opciones disponibles para trabajar como administrador del sistema


void menuAdmin(Usuario** usuarios, int* nUsuarios, alumnos** v_alumnos, int* n_alumnos, materias** v_materias, int* n_materias, Matricula** matriculas, int* nMatriculas, Horario** Horarios, int* nHorarios, Configuracion** Configuraciones, int* nConfiguraciones){
	int opc;
	do{
		printf("--------------------\n");
		printf("MENU: ADMINISTRADOR.\n");
		printf("\t1.- Usuarios\n");
		printf("\t2.- Alumnos\n");
		printf("\t3.- Materias\n");
		printf("\t4.- Horarios\n");
		printf("\t5.- Salir del menu");
		
		printf("\nSeleccione una opcion: ");
		
		do{
			scanf("%d", &opc);
			fflush(stdin);
			
			switch(opc){
				case 1:
					system("cls");
					menuAdminUsuarios(&*usuarios, &*nUsuarios);
					system("pause");
					break;
				case 2:
					system("cls");
					menuAdminAlum(&*v_alumnos, &*n_alumnos, &*matriculas, &*nMatriculas);
					system("pause");
					break;
				case 3:
					system("cls");
					menuAdminMaterias(&*v_materias, &*n_materias);
					system("pause");
					break;
				case 4:
					system("cls");
					menuAdminHorarios(&*Horarios, &*nHorarios);
					system("pause");
					break;
				case 5://Salir del menu
					break;
				default:	printf("Error, intente de nuevo: ");
			}
			
		}while(opc<1 || opc>5);	
			
	}while(opc!=5);

	
	
}

//cabecera void menuAdminAlum(alumnos** v_alumnos, int* n_alumnos, Matricula** matriculas, int* nMatriculas)
//precondicion estructura de alumnos y matriculas inicializada
//postcondicion devuelve todas las opciones disponibles para trabajar con los alumnos y sus respectivas matriculas siendo administrador

void menuAdminAlum(alumnos** v_alumnos, int* n_alumnos, Matricula** matriculas, int* nMatriculas){
	int opc=0;
	do{
		printf("--------\n");
		printf("ALUMNOS.\n");
		printf("\t1.- Dar alta\n");
		printf("\t2.- Dar baja\n");
		printf("\t3.- Modificar alumno\n");
		printf("\t4.- Listar alumnos\n");
		printf("\t5.- Matriculas\n");
		printf("\t6.- Salir del menu");
		
		printf("\nSeleccione una opcion: ");
		
		do{
			scanf("%d", &opc);
			fflush(stdin);
			
			switch(opc){
				case 1:
					system("cls");
					crear_alumno(&*v_alumnos, &*n_alumnos);
					system("pause");
					break;
				case 2:
					system("cls");
					eliminar_alumno(&**v_alumnos, &*n_alumnos);
					system("pause");
					break;
				case 3:
					system("cls");
					mod_alumno(*v_alumnos, &*n_alumnos);
					system("pause");
					break;
				case 4:
					system("cls");
					listar_alumnos(*v_alumnos, &*n_alumnos);
					system("pause");
					break;
				case 5:
					system("cls");
					listar_alumnos(*v_alumnos, &*n_alumnos);
					menuMatricula(&*matriculas, &*nMatriculas);
					system("pause");
					break;
				case 6://Salir del menu
					break;
				default:	printf("Error, intente de nuevo: ");
			}
			
		}while(opc<1 || opc>6);	
		system("cls");
	}while(opc!=6);
}

//cabecera void menuMatricula(Matricula** matriculas, int* nMatriculas)
//precondicion estructura de matriculas inicializada
//postcondicion devuelve todas las opciones disponibles para trabajar con matriculas siendo administrador

void menuMatricula(Matricula** matriculas, int* nMatriculas){
	
	int id_alum, opc;
	
	printf("Introduzca el ID del alumno con el que desea ver sus matriculas: ");
	scanf("%d",&id_alum);
	fflush(stdin);
	printf("\n");
	
	listaMateriasAlumno(&**matriculas, *nMatriculas, id_alum);
	
	printf("\n\t1.-Modificar matricula.");
	printf("\n\t2.-Crear matricula.");
	printf("\n\t3.-Eliminar matricula.");
	printf("\n\t4.-Volver al menu.");
	
	printf("\n\nSeleccione una opcion: ");
	do{
		scanf("%d", &opc);
		fflush(stdin);
	
		switch(opc){
			case 1:
				modificarMatricula(&*matriculas, *nMatriculas, id_alum);
				system("pause");
				break;
			case 2:
				addMatricula(&*matriculas, &*nMatriculas, id_alum);
				system("pause");
				break;
			case 3:
				eliminarMatricula(&*matriculas, &*nMatriculas, id_alum);
				system("pause");
				break;
			case 4: break;
			default:
				printf("Vuelve a seleccionar una opcion: ");
		}
	}while(opc<1 || opc>4);
	system("cls");
}

//cabecera void menuAdminMaterias(materias** v_materias, int* n_materias)
//precondicion estructura de materias inicializada
//postcondicion devuelve todas las opciones disponibles para trabajar con materias siendo administrador

void menuAdminMaterias(materias** v_materias, int* n_materias){
	int opc=0;
	do{
		printf("--------\n");
		printf("MATERIAS.\n");
		printf("\t1.- Dar alta\n");
		printf("\t2.- Dar baja\n");
		printf("\t3.- Modificar materia\n");
		printf("\t4.- Listar materias\n");
		printf("\t5.- Salir del menu");
		
		printf("\nSeleccione una opcion: ");
		
		do{
			scanf("%d", &opc);
			fflush(stdin);
			
			switch(opc){
				case 1:
					system("cls");
					crear_materias(&*v_materias, &*n_materias);
					break;
				case 2:
					system("cls");
					eliminar_materias(&*v_materias, &*n_materias);
					break;
				case 3:
					system("cls");
					mod_materia(&**v_materias, &*n_materias);
					break;
				case 4:
					system("cls");
					listar_materias(*v_materias, &*n_materias);
					break;
				case 5://Salir del menu
					break;
				default:	printf("Error, intente de nuevo: ");
			}
			
		}while(opc<1 || opc>5);	
			
	}while(opc!=5);
}

//cabecera void menuAdminHorarios(Horario** Horarios, int* nHorarios)
//precondicion la estructura de horario inicializada
//postcondicion devulve todas las opciones disponibles para trabajar con los horarios siendo administrador

void menuAdminHorarios(Horario** Horarios, int* nHorarios){
	int opc=0, id_prof;
	do{
		printf("--------\n");
		printf("HORARIOS.\n");
		printf("\t1.- Anadir hora\n");
		printf("\t2.- Eliminar hora\n");
		printf("\t3.- Modificar hora\n");
		printf("\t4.- Listar horas\n");
		printf("\t5.- Salir del menu");
		
		printf("\nSeleccione una opcion: ");
		
		do{
			scanf("%d", &opc);
			fflush(stdin);
			
			if(opc!=5){
				printf("Introduzca la ID del profesor del cual quiere consultar su horario (3 digitos): ");
				scanf("%d",&id_prof);
			}
			
			switch(opc){
				case 1:
					system("cls");
					crearhorario(&*Horarios, &*nHorarios, id_prof);
					system("pause");
					break;
				case 2:
					system("cls");
					eliminarHorario(&*Horarios, &*nHorarios, id_prof);
					system("pause");
					break;
				case 3:
					system("cls");
					modificarHorarioProfe(&*Horarios, *nHorarios, id_prof);
					system("pause");
					break;
				case 4:
					system("cls");
					listarHorarioProfe(*Horarios, *nHorarios, id_prof);
					system("pause");
					break;
				case 5://Salir del menu
					break;
				default:	printf("Error, intente de nuevo: ");
			}
			
		}while(opc<1 || opc>5);	
			system("cls");
	}while(opc!=5);
}


//cabecera menuProfe(int id_prof, alumnos** v_alumnos, int* n_alumnos, materias** v_materias, int* n_materias, Calificacion** calificaciones, int* nCalificaciones, Matricula** matriculas, int* nMatriculas, Horario** Horarios, int* nHorarios, Configuracion** Configuraciones, int* nConfiguraciones)
//precondicion todas las estructuras inicializadas y el identificador del profesor localizado
//postcondicion muestra el menu con todas las funcionalidades disponibles para el perfil de profesor

void menuProfe(int id_prof, alumnos** v_alumnos, int* n_alumnos, materias** v_materias, int* n_materias, Calificacion** calificaciones, int* nCalificaciones, Matricula** matriculas, int* nMatriculas, Horario** Horarios, int* nHorarios, Configuracion** Configuraciones, int* nConfiguraciones){
	int i, dia, opc, aux, opc1, cont=0;
	
	do{	
			printf("En que dia quiere trabajar?(1 al 5): ");
			scanf("%d", &dia);
			fflush(stdin);
		
			printf("\nLISTADO DE GRUPOS Y MATERIAS:\n");
				
			for(i=0;i<*nHorarios;i++){
				if((*Horarios)[i].id_prof == id_prof && (*Horarios)[i].dia == dia){
					printf("\t%d-%s\n", i+1, (*Horarios)[i].grupo);
				}
			}		

			printf("Selecione con que grupo desea trabajar: ");
		
			scanf("%d",&opc);
			
			system("cls");
			
			do{
				printf("GRUPO %s MATERIA %s\n", (*Horarios)[opc-1].grupo, (*v_materias)[opc-1].abreviatura);
				printf("\t1.-Lista de alumnos.\n");
				printf("\t2.-Cambiar de grupo.\n");
			
				printf("Seleccione una opcion: ");
				scanf("%d", &aux);
				fflush(stdin);
				printf("\n");
				
				switch(aux){
					case 1:
						//menuListaAlumnos
						system("cls");
						menuListaAlumnos((*v_materias)[opc-1].id, &*v_alumnos, &*n_alumnos, &*v_materias, &*n_materias, &*calificaciones, &*nCalificaciones, &*matriculas, &*nMatriculas, &*Horarios, &*nHorarios, &*Configuraciones, &*nConfiguraciones);
						system("pause");
						break;
					case 2:
						//Salimos de este grupo
					break;
					default:	break;
				}	
			}while(aux!=2);
			printf("Desea continuar?(Pulse 1 si asi lo desea): ");
			scanf("%d", &opc1);
			fflush(stdin);
						
	}while(opc1==1);
}

//cabecera menuListaAlumnos(int id_mat, alumnos** v_alumnos, int* n_alumnos, materias** v_materias, int* n_materias, Calificacion** calificaciones, int* nCalificaciones, Matricula** matriculas, int* nMatriculas, Horario** Horarios, int* nHorarios, Configuracion** Configuraciones, int* nConfiguraciones)
//precondicion todas las estructuras inicializadas y la id de la materia localizada
//postcondicion devuelve un menu con todas las opciones para trabajar con los alumnos desde el perfil de profesor

void menuListaAlumnos(int id_mat, alumnos** v_alumnos, int* n_alumnos, materias** v_materias, int* n_materias, Calificacion** calificaciones, int* nCalificaciones, Matricula** matriculas, int* nMatriculas, Horario** Horarios, int* nHorarios, Configuracion** Configuraciones, int* nConfiguraciones){
	int i, j, id_alum, aux, opc, opc1=0;
		
	do{
		for(i=0;i<*nMatriculas;i++){
			if((*matriculas)[i].id_mat==id_mat){
				id_alum = (*matriculas)[i].id_alum;
				for(j=0;j<*n_alumnos;j++){
					if((*v_alumnos)[j].id == id_alum){
						printf("%.6d - %s\n", (*v_alumnos)[j].id, (*v_alumnos)[j].nombre);
					}
				}
			}
		}
		
		printf("\n\t1.-Ficha del alumno.\n");
		printf("\t2.-Calificaciones del alumno.\n");
		printf("\t3-.Volver.\n");
	
		printf("Seleccione una opcion: ");
		scanf("%d",&opc);
		fflush(stdin);
		
		if(opc!=3){
			printf("\nIntroduzca la ID del alumno con el que quiere trabajar (6 digitos): ");
			scanf("%d", &aux);
			fflush(stdin);
		}
		
		switch(opc){
			case 1:
				//DatosAlumno
				datos_alumno(&**v_alumnos, &*n_alumnos, id_alum);
				printf("\nDesea modificar estos datos? (Escriba 1 si asi lo desea): ");
				fflush(stdin);
				scanf("%d", &opc1);
				fflush(stdin);
				
				if(opc1 == 1)	mod_alumno(&**v_alumnos, &*n_alumnos);
				break;
			case 2:
				//CalificacionesAlumno
				menuProfeCalificaciones(&*calificaciones, &*nCalificaciones, id_alum, id_mat);
				break;
			case 3:
				break;
			default:	break;
		}
		system("cls");
	}while(opc!=3);
	
	
	
}



















