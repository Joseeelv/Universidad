#include "materias.h"
#include "Saltos/saltos.h"




#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*Cabecera: void cargar_materias (Puntero a puntero de la estructura de materias y puntero a entero de su tamaño)
Precondición: Estructuras inicializada en el header
Postcondición: cargan los datos del documento txt en la estructura para ser utilizados por el programa
*/

void cargar_materias (materias **v_materias, int *n){

FILE *fichero;          //Creamos el objeto para guardar el contenido del fichero

    char linea[130];             //para copiar cada linea entera y luego ponerla en el struct
    char *token;

    *v_materias=NULL;           //nos aseguramos de vaciar la estructura para evitar problemas
    *n=0;

    fichero=fopen("Files/Materias/materias.txt","r");         //abrimos el fichero

    if (fichero==NULL){         //establecemos un mensaje de error para en caso de éste, poder localizarlo rápidamente

        puts("Error al abrir el fichero materias.txt.");

    }else{

        do{

            fgets(linea,130,fichero);           //copiamos una linea completa del fichero, dependiendo de la iteración del bucle

            if (strcmp(linea,"\0")){            //el valor de la condición es diferente de 0 hasta que se alcance el final de linea

                *v_materias=realloc((materias *)(*v_materias),((*n)+1)*sizeof(materias));           //modificamos el struct dinámicamente para hacer sitio a los datos que entran en cada iteración del bucle

                token=strtok(linea,"-");
                (*v_materias)[*n].id=atoi(token);

                token=strtok(NULL,"-");
                strcpy((*v_materias)[*n].nombre,token);

                token=strtok(NULL,"\n");
                strcpy((*v_materias)[*n].abreviatura,token);



                (*n)++;

            }

        }while(!feof(fichero));
    }

    fclose(fichero);
}

/*Cabecera: void guardar_materias (Puntero a punteros de la estructura de materias y puntero a entero de su tamaño)
Precondición: Estructuras inicializada
Postcondición: guarda los datos de la estructura en el documento txt para su próximo uso
*/

void guardar_materias(materias *v_materias, int tam){
    FILE *fich;
    int i;


    fich=fopen("Files/Materias/materias.txt","w");
    i = 0;
    if (fich==NULL)
            puts("No se ha podido modificar el fichero");
        else{
            while( i < tam-1 )
            {
                fprintf( fich, "%.4d-%s-%s\n", v_materias[i].id,v_materias[i].nombre,v_materias[i].abreviatura);
                i++;
            }
            fprintf( fich, "%.4d-%s-%s", v_materias[i].id,v_materias[i].nombre,v_materias[i].abreviatura);

    //puts("Se ha guardado materias correctamente");

    }
}

/*Cabecera: void crear_materias (Puntero a puntero de la estructura de materias y puntero a entero de su tamaño)
Precondición: Estructuras inicializada y puntero a entero > 0
Postcondición: añade una nuevo materia a la estructura de materias
*/

void crear_materias(materias **v_materias, int *n_materias){


        (*n_materias)++;
        *v_materias=realloc((materias *)(*v_materias),((*n_materias))*sizeof(materias));

        (*v_materias+(*n_materias)-1)->id = *n_materias;


        puts("Introduzca el nombre de la materia:");
        fflush(stdin);
        fgets((*v_materias+(*n_materias)-1)->nombre,51,stdin);
        quitar_saltos((*v_materias+(*n_materias)-1)->nombre);

        puts("Introduzca la abreviatura:");
        fflush(stdin);
        fgets((*v_materias+(*n_materias)-1)->abreviatura,4,stdin);
        quitar_saltos((*v_materias+(*n_materias)-1)->abreviatura);


}

/*Cabecera: void listar_materias (Puntero a la estructura de materias y puntero a entero de su tamaño)
Precondición: Estructuras inicializada y puntero a entero >= 0
Postcondición: imprime por pantalla los ID y los nombres de las materias
*/

void listar_materias(materias *v_materias, int *n_materias){
    int i;
    printf("\nMATERIAS:\n\n");
    for (i=0; i<*n_materias; i++)    //recorre el vector de usuarios y lo muestra en pantalla
        printf("%.4d-%s\n", v_materias[i].id, v_materias[i].nombre);
}

/*Cabecera: void aliminar_materias (Puntero a la estructura de materias y puntero a entero de su tamaño)
Precondición: Estructuras inicializada y puntero a entero > 0
Postcondición: recoge el número de id de una materia introducido por el usuario del programa
*/

void eliminar_materias(materias **v_materias, int *n_materias){
    int idborrar=0, i=0, error=1;

    listar_materias(*v_materias, n_materias);

    printf("Introduzca la id de la materia a eliminar: ");
    scanf("%i", &idborrar);



    while(i<*n_materias)
    {
        if(((*v_materias+i)->id)== idborrar)
        {
            while(i<*n_materias-1) //bucle para sobreescribir datos en el alumno a borrar, se reasignan las id para mantener el orden
            {
                ((*v_materias+i)->id = (*v_materias+i+1)->id);
                strcpy((*v_materias+i)->nombre,(*v_materias+i+1)->nombre);
                strcpy((*v_materias+i)->abreviatura,(*v_materias+i+1)->abreviatura);
                i++;
            }
            (*n_materias)--;                                                                      //decrementa en 1 el número de materias
            *v_materias=realloc((materias *)(*v_materias),((*n_materias))*sizeof(materias));      //disminuye el tamaño del vector de forma dinamica
            error = 0;
            puts("Materia eliminada corretamente.");
        }
        else i++;
    }
    if (error == 1){
        puts ("No existe ninguna materia con ese ID");
    }
}

void mod_materia(materias *v_materias, int *n_materias){          //el admin introduce la id del equipo que desea modificar e introduce los nuevos datos
    int idmod, i, flag=1;
    listar_materias(v_materias, n_materias);
    printf("Introduzca la id de la materia a modificar: ");
    scanf("%d", &idmod);


    for (i=0; i<*n_materias; i++){
        if((idmod)== v_materias[i].id){

                flag=0;

                puts("Introduzca el nombre de la materia:");
                fflush(stdin);
                fgets(v_materias[i].nombre,51,stdin);
                quitar_saltos(v_materias[i].nombre);

                puts("Introduzca la abreviatura de la materia:");
                fflush(stdin);
                fgets(v_materias[i].abreviatura,4,stdin);
                quitar_saltos(v_materias[i].abreviatura);

            }
    }
    if (flag==1) puts("No existe ninguna materia con ese id");

}
