import socket


#creamos la direccion, socket, buffer
direccion = ('locahost',8080)
buffer = 1024
cliente_udp_sock=socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

#enviamos el comnado al servidor
print('Introduce un comando:',
      '\n1. ls',
      '\n2. rm <nombre_fichero>',
      '\n3. write <nombre_fichero> <mensaje>',
      '\n4. cd <nombre_directorio>',
      '\5. mv <origen> <destino>',
      '\6. exit')
comando = input('\nIntroduce uno de esos comandos rellando los campos: ')

if comando == 'exit':
    cliente_udp_sock.close()
    print('Cliente finalizado')
    exit()
#enviamos al servidor el comando
cliente_udp_sock.sendto(comando.encode(),direccion)

#recibimos la respuesta del servidor despues de la ejecucion del comando
data, address = cliente_udp_sock.recvfrom(buffer)
respuesta = data.decode()
print (respuesta)

#cerramos el socket
cliente_udp_sock.close()
print('Cliente finalizado')
exit()

