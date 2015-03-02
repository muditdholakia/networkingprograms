#!/usr/bin/env python
import socket
import sys

host = 'localhost'
port = 9500
size = 1024

sd = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sd.connect((host,port))
data = raw_input ("Enter Data: ")
sd.send(data)
data = sd.recv(1024)
sd.close()
print "Received", data

sd.close()
