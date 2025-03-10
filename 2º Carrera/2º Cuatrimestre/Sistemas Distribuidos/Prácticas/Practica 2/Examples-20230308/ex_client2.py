import socket

HOST = 'localhost'    # The remote host
PORT = 50007          # The same port as used by the server

# Read the binary file
with open('file.pdf', 'rb') as f:
    data = f.read()
    print(len(data))

# Send the binary file to the server
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
s.sendall(data)

# Send the EOT character to the server
s.send(b'\xe2\x90\x84')

# Receive the response from the server
data = s.recv(1024)
print('Received', str(data))

# Close the socket
s.close()