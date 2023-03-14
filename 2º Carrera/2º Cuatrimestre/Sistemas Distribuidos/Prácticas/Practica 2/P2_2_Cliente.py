#Creamos el cliente 
import argparse
import socket


#main del cliente
def main(host, port, filein):
    #leemos el archivo a enviar
    with open(filein, 'rb') as infile:
        data = infile.read()
        size = len(data)
        
    remote_addr = (host, port) #asignamos la direccion
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(remote_addr) #nos conectamos
    s.send(filein.encode("utf-8"))
    print("Conexión establecida")
    
    print("Enviando archivo con nombre ",filein)
    s.sendall(data)
    s.send(b'\xe2\x90\x84')

    print("El tamaño del archivo es de " + str(size)+ " bytes")
   

    #buffer = s.recv(512)
    s.sendall(data.encode("utf-8"))

    infile.close()
    s.close()


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--port', default=1025, help="remote port")
    parser.add_argument('--host', default='localhost', help="remote hostname")
    parser.add_argument('--filein', default='filein.pdf', help="file to be read")
    args = parser.parse_args()

    main(args.host, args.port, args.filein)
