# Implemente un script en Python, utilizando el módulo os, 
# que liste todos los ficheros del directorio actual junto a su tamaño en bytes.
# Por último, el script mostrará la suma total del tamaño de los ficheros del directorio. 
# Se deben incluir, además, los ficheros existentes en subdirectorios.

import os


def mostrar_tamaño(directorio):
    TamTot = 0 #inicializamos el total de bytes a 0 "tamaño"
    print(f'Directorio actual: {directorio}')
    tam_direct = os.path.getsize(directorio)
    for d_raiz, archivos, directorio in os.walk(directorio):
        for archivo in archivos:
            ruta_archivo = os.path.join(d_raiz,archivo)
            tamaño = os.path.getsize(ruta_archivo)
            print(f'Archivo: {ruta_archivo}, Tamaño: {tamaño} ')
            TamTot =+ tamaño
    print(f'Tamaño total del directorio {tam_direct} Bytes ; Tamaño total de la ruta: {TamTot} Bytes')



dir_actual = os.getcwd() #guardamos el directorio actual
mostrar_tamaño(dir_actual)