# Imprima por pantalla el listado de directorios de inicio de los usuarios que hay en el sistema 
# (p. ej., /home/root , /home/osboxes, . . . ). 
# Pista: hay un fichero con esta información. 
# También existe una función muy interesante en Python llamada split, 
# que convierte de string a lista.

def imprimir():
    with open('/etc/passwd', 'r') as directorios:
        contenido = directorios.readlines()
    
    for directorios in contenido:
        campos = directorios.split(':') #ponemos el string a una lista
        if len(campos) >= 6:
            usuario = campos[0] #el usuario va en la primera posicion de cada lista
            dir_ini = campos[5].strip() #despues va el directorio principal
            print(f'User:{usuario}, directorio:{dir_ini}')
        else:
            print("No hay campos suficientes es este directorio")
        

imprimir()