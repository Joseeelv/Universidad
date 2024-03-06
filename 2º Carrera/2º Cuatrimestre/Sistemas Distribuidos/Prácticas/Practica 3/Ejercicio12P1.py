# Implemente una función copiar(origen,destino) que copie el contenido del fichero origen,
# en el fichero destino (usando open())

def copiar(origen,destino):
    try:
        with open('mi_fichero', 'r') as f_origen:
            with open('fichero_salida', 'r') as f_destino:
                contenido = f_origen.read()
                f_destino.write(contenido)
        print("Copia realizada con exito")
    
    except:
        raise IOError
    
copiar("fichero1.txt","fichero2.txt") #ejemplo                 