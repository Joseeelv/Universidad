#include "alumnos.h"
#include "Saltos/saltos.h"




#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*Cabecera: void cargar_alumnos (Puntero a puntero de la estructura de alumos y puntero a entero de su tamaño)
Precondición: Estructuras inicializada y puntero a entero = 0
Postcondición: cargan los datos del documento txt en la estructura para ser utilizados por el programa
*/

void cargar_alumnos (alumnos **v_alumnos, int *n){

FILE *fichero;          //Creamos el objeto para guardar el contenido del fichero

    char linea[130];             //para copiar cada linea entera y luego ponerla en el struct
    char *token;

    *v_alumnos=NULL;           //nos aseguramos de vaciar la estructura para evitar problemas
    *n=0;

    fichero=fopen("Files/Alumnos/alumnos.txt","r");         //abrimos el fichero

    if (fichero==NULL){         //establecemos un mensaje de error para en caso de éste, poder localizarlo rápidamente

        puts("Error al abrir el fichero alumnos.txt.");

    }else{

        do{

            fgets(linea,130,fichero);           //copiamos una linea completa del fichero, dependiendo de la iteración del bucle

            if (strcmp(linea,"\0")){            //el valor de la condición es diferente de 0 hasta que se alcance el final de linea

                *v_alumnos=realloc((alumnos *)(*v_alumnos),((*n)+1)*sizeof(alumnos));           //modificamos el struct dinámicamente para hacer sitio a los datos que entran en cada iteración del bucle

                token=strtok(linea,"-");                        //copiamos en token la linea hasta el primer "-"
                (*v_alumnos)[*n].id=atoi(token);                //copiamos token en la estructura

                token=strtok(NULL,"-");                         //copiamos desde el anterior guión hasta el siguiente
                strcpy((*v_alumnos)[*n].nombre,token);          //y lo guardamos en su correspondiente apartado de la estructura

                token=strtok(NULL,"-");
                strcpy((*v_alumnos)[*n].direccion,token);

                token=strtok(NULL,"-");
                strcpy((*v_alumnos)[*n].localidad,token);

                token=strtok(NULL,"-");
                strcpy((*v_alumnos)[*n].curso,token);

                token=strtok(NULL,"\n");                        //copiamos lo que queda hasta el salto de línea
                strcpy((*v_alumnos)[*n].grupo,token);

                (*n)++;

            }

        }while(!feof(fichero));
    }

    fclose(fichero);            //cerramos el fichero
}

/*Cabecera: void guardar_alumno (Puntero a la estructura de alumnos y entero de su tamaño)
Precondición: Estructuras inicializada y entero >= 0
Postcondición: guarda los datos de la estructura en el documento txt para su próximo uso
*/

void guardar_alumnos(alumnos *v_alumnos, int tam){
    FILE *fich;
    int i;


    fich=fopen("Files/Alumnos/alumnos.txt","w");         //abrimos el fichero donde queremos guardar los datos de la estructura
    i = 0;
    if (fich==NULL)
            puts("No se ha podido modificar el fichero");
        else{
            while( i < tam-1 )
            {
                fprintf( fich, "%.6d-%s-%s-%s-%s-%s\n", v_alumnos[i].id,v_alumnos[i].nombre,v_alumnos[i].direccion,v_alumnos[i].localidad,v_alumnos[i].curso,v_alumnos[i].grupo);
                i++;
            }
            fprintf( fich, "%.6d-%s-%s-%s-%s-%s", v_alumnos[i].id,v_alumnos[i].nombre,v_alumnos[i].direccion,v_alumnos[i].localidad,v_alumnos[i].curso,v_alumnos[i].grupo);

    puts("Se ha guardado alumnos correctamente");

    }
}

/*Cabecera: void crear_alumno (Puntero a puntero de la estructura de alumnos y puntero a entero de su tamaño)
Precondición: Estructuras inicializada y puntero a entero > 0
Postcondición: añade un nuevo alumno a la estructura de alumnos
*/

void crear_alumno(alumnos **v_alumnos, int *n_alumnos){

        int i, flag=1, aux=1000000;

//        (*n_alumnos)++;
//        *v_alumnos=realloc((alumnos *)(*v_alumnos),((*n_alumnos))*sizeof(alumnos));                     //aumentamos el tamaño de la estructura para tener espacio para el nuevo alumno


        while (aux >= 1000000 || aux < 0){
        puts("Introduzca la id del alumno (6 digitos):");
        scanf("%d", &aux);}

        for (i=0; i<(*n_alumnos-1); i++){

            if (aux == ((*v_alumnos+i)->id)){
//                (*n_alumnos)--;
//                *v_alumnos=realloc((alumnos *)(*v_alumnos),((*n_alumnos))*sizeof(alumnos));
                i=*n_alumnos;
                flag = 0;
            }
        }


        if (flag!=0){

        (*n_alumnos)++;
        *v_alumnos=realloc((alumnos *)(*v_alumnos),((*n_alumnos))*sizeof(alumnos));         //aumentamos el tamaño de la estructura para tener espacio para el nuevo alumno


        ((*v_alumnos+(*n_alumnos)-1)->id) = aux;

        puts("Introduzca el nombre del alumno:");
        fflush(stdin);
        fgets((*v_alumnos+(*n_alumnos)-1)->nombre,20,stdin);
        quitar_saltos((*v_alumnos+(*n_alumnos)-1)->nombre);

        puts("Introduzca la direccion:");
        fflush(stdin);
        fgets((*v_alumnos+(*n_alumnos)-1)->direccion,30,stdin);
        quitar_saltos((*v_alumnos+(*n_alumnos)-1)->direccion);

        puts("Introduzca la localidad:");
        fflush(stdin);
        fgets((*v_alumnos+(*n_alumnos)-1)->localidad,30,stdin);
        quitar_saltos((*v_alumnos+(*n_alumnos)-1)->localidad);

        puts("Introduzca el curso:");
        fflush(stdin);
        fgets((*v_alumnos+(*n_alumnos)-1)->curso,30,stdin);
        quitar_saltos((*v_alumnos+(*n_alumnos)-1)->curso);

        puts("Introduzca el grupo:");
        fflush(stdin);
        fgets((*v_alumnos+(*n_alumnos)-1)->grupo,10,stdin);
        quitar_saltos((*v_alumnos+(*n_alumnos)-1)->grupo);
        }
        else puts("Ya existe un alumno con ese ID");
}

/*Cabecera: void listar_alumno (Puntero a la estructura de alumnos y puntero a entero de su tamaño)
Precondición: Estructuras inicializada y puntero a entero >= 0
Postcondición: imprime por pantalla los ID y los nombres de los alumnos
*/

void listar_alumnos(alumnos *v_alumnos, int *n_alumnos){
    int i;
    printf("\nALUMNOS:\n\n");
    for (i=0; i<*n_alumnos; i++)    //recorre el vector de usuarios y lo muestra en pantalla
        printf("%.6d-%s\n", v_alumnos[i].id, v_alumnos[i].nombre);
}

/*Cabecera: void aliminar_alumno (Puntero a la estructura de alumnos y puntero a entero de su tamaño)
Precondición: Estructuras inicializada y puntero a entero > 0
Postcondición: recoge el número de id de un alumno introducido por el usuario del programa
*/

void eliminar_alumno(alumnos *v_alumnos, int *n_alumnos){
    int idborrar=0;

    listar_alumnos(v_alumnos, n_alumnos);

    printf("Introduzca la id del usuario a eliminar: ");
    scanf("%d", &idborrar);

    eliminacion(&v_alumnos, n_alumnos, idborrar);           //Llamamos a la función que se encarga de eliminar el alumno que hemos elegido
}

/*Cabecera: void eliminacion (Puntero a puntero de la estructura de alumnos, puntero a entero de su tamaño y entero del numero de id a borrar)
Precondición: Estructuras inicializada y puntero a entero > 0
Postcondición: elimina un alumno de la estructura de alumnos
*/

void eliminacion(alumnos **v_alumnos, int *n_alumnos, int idborrar){
    int i=0, error=1;

    while(i<*n_alumnos)
    {
        if((idborrar == ((*v_alumnos+i)->id)))
        {
            while(i<*n_alumnos-1) //bucle para sobreescribir datos en el alumno a borrar, se reasignan las id para mantener el orden
            {
                ((*v_alumnos+i)->id = (*v_alumnos+i+1)->id);
                strcpy((*v_alumnos+i)->nombre,(*v_alumnos+i+1)->nombre);
                strcpy((*v_alumnos+i)->direccion,(*v_alumnos+i+1)->direccion);
                strcpy((*v_alumnos+i)->localidad,(*v_alumnos+i+1)->localidad);
                strcpy((*v_alumnos+i)->curso,(*v_alumnos+i+1)->curso);
                strcpy((*v_alumnos+i)->grupo,(*v_alumnos+i+1)->grupo);
                i++;
            }
            (*n_alumnos)--;                                                                      //decrementa en 1 el número de alumnos
            *v_alumnos=realloc((alumnos *)(*v_alumnos),((*n_alumnos))*sizeof(alumnos));      //disminuye el tamaño del vector de forma dinamica
            error = 0;
            puts("Alumno eliminado corretamente.");
        }
        else i++;
    }
    if (error == 1){
        puts ("No existe ningun alumno con ese ID");
    }

}

/*Cabecera: void mod_alumno (Puntero a la estructura de alumnos y puntero a entero de su tamaño)
Precondición: Estructuras inicializada y puntero a entero >= 0
Postcondición: modifica los datos del alumno elegido en la estructura de alumnos
*/

void mod_alumno(alumnos *v_alumnos, int *n_alumnos){          //el admin introduce la id del alumno que desea modificar e introduce los nuevos datos
    int idmod, i, flag=1;
    listar_alumnos(v_alumnos, n_alumnos);
    printf("Introduzca la id del alumno a modificar: ");
    scanf("%d", &idmod);


    for (i=0; i<*n_alumnos; i++){
        if((idmod)== v_alumnos[i].id){

                flag=0;

                puts("Introduzca el nombre del alumno:");
                fflush(stdin);
                fgets(v_alumnos[i].nombre,21,stdin);
                quitar_saltos(v_alumnos[i].nombre);

                puts("Introduzca la direccion del alumno:");
                fflush(stdin);
                fgets(v_alumnos[i].direccion,31,stdin);
                quitar_saltos(v_alumnos[i].direccion);

                puts("Introduzca la localidad:");
                fflush(stdin);
                fgets(v_alumnos[i].localidad,31,stdin);
                quitar_saltos(v_alumnos[i].localidad);

                puts("Introduzca el curso del alumno:");
                fflush(stdin);
                fgets(v_alumnos[i].curso,31,stdin);
                quitar_saltos(v_alumnos[i].curso);

                puts("Introduzca el grupo:");
                fflush(stdin);
                fgets(v_alumnos[i].grupo,11,stdin);
                quitar_saltos(v_alumnos[i].grupo);

            }
    }
    if (flag==1) puts("No existe ningun alumno con ese id");

}

/*Cabecera: void datos_alumno (Puntero a puntero de la estructura de alumnos, puntero a entero de su tamaño y entero del numero de id del alumno a mostrar)
Precondición: Estructuras inicializada y puntero a entero > 0
Postcondición: muestra los datos del alumno que se pida
*/

void datos_alumno(alumnos *v_alumnos, int *n_alumnos, int id){
    int i;
    for (i=0; i<(*n_alumnos); i++){

            if (v_alumnos[i].id == id){
                printf("ID: %.6d \nNombre: %s \nDireccion: %s \nLocalidad: %s \nCurso y grupo: %s %s", v_alumnos[i].id, v_alumnos[i].nombre, v_alumnos[i].direccion, v_alumnos[i].localidad, v_alumnos[i].curso, v_alumnos[i].grupo);
            }
        }
}