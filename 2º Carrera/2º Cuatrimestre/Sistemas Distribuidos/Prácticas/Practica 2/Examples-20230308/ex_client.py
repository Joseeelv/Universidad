import argparse
import os
import socket


def main(host, port, filein):
    remote_addr = (host, port)

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(remote_addr)

    print("Sending the file")
    with open(filein, 'r') as infile:
        data = infile.read()
        size = len(data)
        print("File size if of " + str(size))
        s.send(str(size).encode("utf-8"))

        buffer = s.recv(512)
        # We can ignore the message, it is just a control message
        s.sendall(data.encode("utf-8"))

    infile.close()

    s.close()


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--port', default=1025, help="remote port")
    parser.add_argument('--host', default='localhost', help="remote hostname")
    parser.add_argument('--filein', default='filein.txt', help="file to be read")
    args = parser.parse_args()

    main(args.host, args.port, args.filein)
