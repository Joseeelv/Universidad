# Realizar un script en Python que imprima por pantalla el directorio de trabajo actual,
# junto a la lista de ficheros existentes en dicho directorio. 
# Posteriormente, el mismo script permitirá al usuario renombrar un fichero. 
# Para ello solicitará al usuario el nombre del fichero que quiere renombrar y el nuevo nombre que quiere darle. 
# Se deben gestionar correctamente las posibles excepciones que puedan darse en la ejecución del script.

import os

#funcion que nos imprime la lista de ficheros del directorio actual
def imprimir_archivos():
    #obtenemos el directorio actual
    directorio = os.getcwd()
    #creamos la lista de los ficheros de un directorio
    print(f'Directorio actual: {directorio}')
    
    #obtenemos la lista de ficheros que contiene el directorio
    ficheros = os.listdir(directorio)
    print("Ficheros del directorio actual: ")
    for fichero in ficheros:
        print(fichero)
    
#funcion que nos permite renombrar un archivo
def renombrar_archivos():
    nombre_arch=str(input('Introduce el nombre del fichero a modificar: '))
    nombre_arch_modif=str(input('Introduce el nombre que le quieres poner: '))
    
    try:
        #renombramos el fichero
        os.rename(nombre_arch, nombre_arch_modif)
    except FileNotFoundError:
        print('El archivo introducido no existe')
    except FileExistsError:
        print('Ya existe un fichero con ese nombre')
    except Exception as e:
        print(f'Error al renombrar el fichero {str(e)}')
    except None:
        print('No has introducido ningun nombre')
imprimir_archivos()
renombrar_archivos()
