#!/usr/bin/env python

import select
import socket
import sys

host = ''
port = 50000
backlog = 5
size = 1024
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((host,port))
server.listen(backlog)
input = [server]
run = 1
while run:
    inputready,outputready,exceptready = select.select(input,[],[])

    for s in inputready:

        if s == server:
            client, address = server.accept()
            input.append(client)
            print "Connection received from", address

        else:
            data = s.recv(size)
            if data:
            	print "Client Message:" + data
                s.send(data)
            else:
                s.close()
                input.remove(s)
server.close()