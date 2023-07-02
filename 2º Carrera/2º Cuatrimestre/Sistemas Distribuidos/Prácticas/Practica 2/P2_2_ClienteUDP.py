import socket
import os

# Dirección del servidor
direccion_servidor = ('localhost', 9999)

# Creación del socket con UDP
clt_udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Enviamos el nombre del archivo al servidor
file = "filein.pdf"
clt_udp.sendto(file.encode(), direccion_servidor)

# Comprobamos la respuesta del servidor
respuesta, _ = clt_udp.recvfrom(1024)
respuesta = respuesta.decode()

# Comprobamos si el archivo existe o no en el servidor
if respuesta == "existe":
    # Preguntamos si se desea sobreescribir el archivo
    overwrite = input("El archivo ya se encuentra en el servidor. ¿Desea sobreescribirlo? (s/n): ")
    if overwrite == "n":
        clt_udp.close()
        exit()

# Leemos y enviamos el archivo al servidor
with open(file, "rb") as archivo:
    while True:
        datos = archivo.read(1024)
        if not datos:
            break
        clt_udp.sendto(datos, direccion_servidor)

# Esperamos la respuesta del servidor de que todo ha ido bien
respuesta, _ = clt_udp.recvfrom(1024)
respuesta = respuesta.decode()
print(respuesta)

clt_udp.close()  # Cerramos el socket UDP