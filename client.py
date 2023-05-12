#!/bin/python3

from socket import socket
import sys

class Client:
    def __init__(self):
        self._socket = socket()

    def connect(self):
        self._socket.connect(("localhost", 1027))

    def send(self, data):
        self._socket.send(data.encode())
        print("Message sent")

    def receive(self):
        return self._socket.recv(1024).decode()

    def resolve_calcul(self, calcul):
        calcul = calcul.replace(" ", "")
        calcul = calcul.replace("=", "")
        calcul = calcul.replace("?", "")
        print("calcul: {}".format(calcul))

        try:
            #print("{:.2f}".format(eval(calcul)))
            result = str(eval(calcul))
            print("the result is {}".format(result))
            self.send(result)
        except Exception as e:
            print("Error: {}".format(e))
            # close the socket
            sys.exit(1)

if __name__ == "__main__":
    client = Client()
    client.connect()
    client.resolve_calcul(client.receive())
    print(client.receive())
    sys.exit(0)

