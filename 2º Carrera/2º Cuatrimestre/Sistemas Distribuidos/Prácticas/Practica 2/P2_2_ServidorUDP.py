import socket

# Creamos el socket UDP
ser_udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Establecemos la dirección del servidor
ser_dir = ("localhost", 9999)

# Bindeamos el socket a la dirección del servidor
ser_udp.bind(ser_dir)

# Esperamos la conexión de un cliente
print("Esperando clientes...")
datos, cliente_dir = ser_udp.recvfrom(1024)
archivo = datos.decode()
print("Conexión establecida con el cliente:", cliente_dir)

try:
    # Abrimos el archivo para ver su contenido
    with open(archivo, "rb") as f:
        # Comprobamos que el archivo existe
        ser_udp.sendto("existe".encode(), cliente_dir)
        # Vemos si se quiere sobrescribir el archivo
        respuesta, _ = ser_udp.recvfrom(1024)
        respuesta = respuesta.decode()
        if respuesta == "n":
            ser_udp.close()  # Si no se quiere sobrescribir, cerramos la conexión
            exit()

except FileNotFoundError:
    # Comprobamos que el archivo no existe
    ser_udp.sendto("OK".encode(), cliente_dir)

# Creamos el archivo que almacenará el contenido
with open(archivo, "wb") as f:
    while True:
        # Recibimos el archivo
        datos, _ = ser_udp.recvfrom(1024)
        if not datos:
            break
        f.write(datos)  # Escribimos los datos

# Enviamos la confirmación al cliente de que todo ha ido bien
ser_udp.sendto("Archivo recibido correctamente".encode(), cliente_dir)

# Cerramos la conexión
ser_udp.close()