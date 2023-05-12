#!/bin/python3

from socket import socket
import random
import select

HOST = 'localhost'
PORT = 4242

class Server:
    def __init__(self):
        self.sock = socket()
        self.sock.bind((HOST, PORT))
        self.sock.listen()

    def generate_calcul(self):
        digits = [str(i) for i in range(1, 10)]
        op = ['+', '-', '*', '/']
        calcul = ""
        calcul += digits[random.randint(1, 8)]
        for i in range(5):
            calcul += op[random.randint(0, 3)]
            calcul += digits[random.randint(0, 8)]
        return calcul


    def _check_if_number(self, result):
        for char in result:
            if char not in "0123456789.-":
                return False
        return True

    def run(self):
        while True:
            try:
                read_socket, _, _ = select.select([self.sock], [], [], 2)
                print("Waiting for a client")
                for socks in read_socket:
                    client_socket, _ = socks.accept()
                    print("New client connected")
                    calcul = self.generate_calcul()
                    client_socket.send(calcul.encode())
                    result = client_socket.recv(1024).decode()
                    true_result = eval(calcul)

                    if not self._check_if_number(result):
                        print("Client sent a non number")
                        client_socket.send("You must send a number".encode())
                        client_socket.close()
                        continue
                    result = float(result)

                    print("{} = {}".format(calcul, true_result))
                    print("result of the client: {}".format(result))
                    if (result == true_result):
                        client_socket.send("Here's the flag: EPICTF{y0u_4r3_4_m4th3m4t1c14n}".encode())
                    else:
                        print("wrong result")
                        self.sock.close()
            except KeyboardInterrupt:
                print("Server closed")
                self.sock.close()
                exit(0)



if __name__ == "__main__":
    server = Server()
    server.run()

