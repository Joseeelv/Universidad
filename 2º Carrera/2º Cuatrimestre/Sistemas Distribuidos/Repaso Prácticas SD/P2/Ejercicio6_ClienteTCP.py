import socket
#creamos el socket tcp, direccion,buffer y conectamos al servidor
cliente_tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
direccion = ('locahost',8080)
buffer = 1024
cliente_tcp.connect(direccion)

#vamos a enviar el comando a realizar
while True:
    print('Introduce un comando:',
      '\n1. ls',
      '\n2. rm <nombre_fichero>',
      '\n3. write <nombre_fichero> <mensaje>',
      '\n4. cd <nombre_directorio>',
      '\5. mv <origen> <destino>',
      '\6. exit')
    comando = input('\nIntroduce uno de esos comandos rellando los campos: ')

    if comando.lower() == 'exit':
        print('Saliendo el programa, cerrando conexion')
        cliente_tcp.close()
        break
    #enviamos el comando al servidor
    cliente_tcp.send(comando.lower().encode())

    #recibimos los mensajes del servidor
    respuesta = cliente_tcp.recv(buffer).decode()
    
    print(respuesta)
    cliente_tcp.close()
    exit()