# Realice un script en Python que mueva al directorio actual, todos los archivos contenidos en subdirectorios del mismo.
# Tenga en cuenta que un directorio puede contener a su vez otros directorios y 
# que la longitud en la jerarquía del árbol no está definida y por tanto, 
# el script debe funcionar para todos los casos.

import os
import shutil

def mover_dirs(directorio):
    for d_raiz, directorios,archivos in os.walk(directorio):
        for archivo in archivos:
            #almacenamos las rutas de origen y destino de los archivos
            ruta_archivo_origen= os.path.join(d_raiz,archivo)
            ruta_archivo_destino = os.path.join(directorio,archivo)
            #movemos los archivos del origen al destino "directorio actual"
            shutil.move(ruta_archivo_origen,ruta_archivo_destino)
    print(f'Archivos movidos correctamente de {ruta_archivo_origen} a {ruta_archivo_destino}')

dir_act = os.getcwd()
mover_dirs(dir_act)            
    
    
    
    
    
    
mover_dirs(dir_act)