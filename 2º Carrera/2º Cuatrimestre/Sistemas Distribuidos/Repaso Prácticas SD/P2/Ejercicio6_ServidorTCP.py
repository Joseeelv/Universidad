import socket, os

#creamos el socket tcp,direccion,buffer,bindeamos y escuchamos
serv_tcp = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
addr= ('localhost', 8080)
buffer = 1024
serv_tcp.bind(addr)
serv_tcp.listen()

#directorio actual
directorio = os.gtcwd()

print('Esperando clientes..')
#aceptamos la conexion con el cliente
cliente, cliente_addr = serv_tcp.accept()
print(f'Conexion establecida existosa con cliente {cliente}')


#recibimos el comando procedente del cliente
comando = cliente.recv(buffer).decode()
print(f'Comando introducido: {comando}')
while True:
    if comando.lower() == 'exit':
        #enviamos la repuesta al cliente
        cliente.send(f'Se ha seleccionado la opcion {exit}\n Cerrando conexion con el cliente...'.encode())
        #cerramos los sockets
        break
    
    elif comando == 'ls':
        #mostramos la lista de los ficheros del directorio actual
        archivos = os.listdir(directorio)
        print('\n'.join(archivos))
        
    elif comando.startswith('rm'):
        #vamos a obtener el nombre del fichero a eliminar
        nombre_fichero = comando.split(' ')[1]
        ruta = os.path.join(directorio,nombre_fichero)
        #comprobamos que la ruta existe
        if os.path.exists(ruta):
            os.remove(ruta)
        
        cliente.send(f'Archivo {nombre_fichero} elimiado correctamente'.encode())
        
    elif comando.startswith('write'):
        #obtenemos el nombre del fichero a crear y el mensaje
        nombre = comando.split(' ')[1]
        mensaje =comando.split(' ')[2]
        ruta = os.path.join(directorio,nombre)
        
        #comrobamso que la ruta existe
        if os.path.exists(ruta):
            with open(ruta,'w') as fichero:
                fichero.write(mensaje)
        cliente.send(f'Archivo con nombre: {nombre}, creado correctamente con mensaje {mensaje}'.encode())
        
    elif comando.startswith('cd'):
        #vamos a obtener el directorio a donde queremos movernos
        directorio_destino = comando.split(' ')[1]
        ruta = os.path.join(directorio,directorio_destino)
        
        #comprobamos que la ruta existe
        if not os.path.exists(ruta):
            cliente.send(f'No existe el directorio {directorio_destino}')
        else:
            directorio = ruta #cambiamos el directorio actual por la ruta calculada
            
    elif comando.starwith('mv'):
        origen = comando.split(' ')[1]
        destindo = comando.split(' ')[2]
        
        ruta_origen = os.path.join(directorio,origen)
        ruta_destino = os.path.join(directorio, destindo)
        
        #comprobamos que existe las rutas
        if os.path.exists(ruta_origen) and os.path.isfile(ruta_origen) and os.path.exists(ruta_destino) and os.path.isdir(ruta_destino):
            os.rename(ruta_origen, os.path.join(ruta_destino,ruta_origen))
        cliente.send(f'Archivo movido correctamente '.encode())    
            
#cerramos conexion
cliente.close()
serv_tcp.close()
exit()