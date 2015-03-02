#!/usr/bin/env python

import socket, threading

class ClientThread(threading.Thread):

    def __init__(self,ip,port,clientsocket):
        threading.Thread.__init__(self)
        self.ip = ip
        self.port = port
        self.csocket = clientsocket
        print "[+] New thread started for "+ip+":"+str(port)

    def run(self):    
        print "Connection from : "+ip+":"+str(port)

        clientsock.send("nWelcome to the servernn")

        data = "dummydata"

        while len(data):
            data = self.csocket.recv(2048)
            print "Client(%s:%s) sent : %s"%(self.ip, str(self.port), data)
            self.csocket.send("You sent me : "+data)

        print "Client at "+self.ip+" disconnected..."

host = "127.0.0.1"
port = 9500

tcpsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
tcpsock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

tcpsock.bind((host,port))

while True:
    tcpsock.listen(4)
    print "nListening for incoming connections..."
    (clientsock, (ip, port)) = tcpsock.accept()

    #pass clientsock to the ClientThread thread object being created
    newthread = ClientThread(ip, port, clientsock)
    newthread.start()
