import argparse
import socket

def main(host, port):
    address = (host, port)

    s_listener = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s_listener.bind(address)

    print("Waiting for clients...")
    s_listener.listen()
    s_client, addr = s_listener.accept()

    print("Client connected in address " + str(addr))

    buffer = s_client.recv(512)
    size = int(buffer.decode("utf-8"))
    print("File size is of " + str(size))
    s_client.send("OK".encode("utf-8"))

    print("Receiving file...")
    string = ""
    while len(string) < size:
        buffer = s_client.recv(1024)
        string = string + buffer.decode("utf-8")
        print("Received a total of " + str(len(string)) + " bytes")

    print("I am done. Finishing...")
    s_client.close()
    s_listener.close()


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--port', default=1025, help="listening port")
    parser.add_argument('--host', default='localhost', help="hostname")
    args = parser.parse_args()

    main(args.host, args.port)
