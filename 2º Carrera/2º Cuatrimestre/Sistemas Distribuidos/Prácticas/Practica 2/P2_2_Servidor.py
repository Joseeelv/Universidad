#creamos el servidor
import argparse
import socket
import os
def main(Host, Port):
    print("---HOLA DE NUEVO---")
    #asignamos la direccion IP
    address=(Host,Port)
    
    #creamos el listener
    listener= socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    listener.bind(address)
    
    print("Esperando Clientes...")
    listener.listen()
    cliente,addr=listener.accept() #aceptamos al cliente
    print("Cliente aceptado con direccion" + str(addr))
    
    #comprobar que el archivo ya existe en el servidor
    data = cliente.recv(1024)
    print("Archivo recibido con nombre: ",data)
    #transferencia de archivos si este no existe
    # if os.path.exists(nombrearchivo) !=  :
    #     data = b''
    #     while True:
    #         chunk = cliente.recv(1024)
    #         print(len(chunk))
    #         print(chunk)
    #         find = chunk.find(b'\xe2\x90\x84')
    #         if find != -1:
    #             data += chunk[:find]
    #             break
    #         data += chunk

        #esribimos los datos en un nuevo archivo
    with open('output.pdf', 'wb') as f:
        f.write(data)
        #Enviamos confirmacion al cliente
        cliente.sendall(b'File received')

            
        
    
    #terminamos conexion cerrando cliente y el listener
    print("Terminando...")
    cliente.close()
    listener.close()

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--port', default=1025, help="listening port")
    parser.add_argument('--host', default='localhost', help="hostname")
    args = parser.parse_args()

    main(args.host, args.port)
