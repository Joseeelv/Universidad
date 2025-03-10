#9. Implemente la función get_file_info(filename) para que devuelva
#una tupla con el tamaño en bytes del fichero,cuyo nombre se indica 
#como parámetro filename, en la primera posición,y una lista con 
#las palabras acabadas con el carácter's' que contenga el fichero,
#en segunda posición. Por ejemplo,la invocación get_file_info('mifichero.txt'),
#suponiendo que 'mifichero.txt' contiene el texto“``La casa está pintada en muchos
#colores'',devolverá la tupla(39, ['muchos', 'colores']).
import os

def get_file_info(filename):
    palabras_S = [] #palabras terminada en S
    palabras_fichero = []
    tam=os.stat(filename).st_size
    
    if filename is None:
        raise TypeError("Fichero vacío")
    if type(filename) is not str:
        raise TypeError("El fichero no es una cadena")
    
    with open(filename) as f:
        for lineas in f:
            palabras_fichero.extend(lineas.split())
    
    for palabra in palabras_fichero:
        if palabra[-1] == 's':
            palabras_S.append(palabra)
    return (tam,palabras_S)
            
#main
fichero = os.path.basename("./mifichero.txt")
f=get_file_info(fichero)
print(f)