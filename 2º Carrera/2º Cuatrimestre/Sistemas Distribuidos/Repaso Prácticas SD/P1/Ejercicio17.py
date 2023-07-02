# Realizar un script en Python que combine todos los ficheros de texto (.txt) 
# existentes en el directorio de trabajo actual en un único fichero de texto, 
# llamado “union.txt”. Tanto los ficheros con una extensión distinta, 
# como los que se encuentren en subdirectorios, deberán ignorarse.

import os

def union():
    #obtnemos el directorio actual
    directorio = os.getcwd()
    print(f'Directorio: {directorio}')
    
    #creamos la lista union para introducir los ficheros.txt
    union=[]
    #vamos a obtner los ficheros que solo acaben en .txt
    for archivos in os.listdir(directorio):
        ruta_archivo = os.path.join(directorio,archivos)
        #comprobamos que el archivo termine en '.txt' ó esté en el directorio actual
        if archivos.endswith(".txt") or os.path.isfile(directorio):
            #si está, abrimos la ruta y guardamos el archivo en el archivo general
            with open(ruta_archivo,'r') as file:
                union.append(file.read())
    with open('union.txt','w') as union_file:
        union_file.write('\n'.join(union))
    tam_union = len(union)
    print (f'Se ha creado el archivo union.txt con un tamaño de {tam_union} ')
    
    
#llamamos a la funcion
union()