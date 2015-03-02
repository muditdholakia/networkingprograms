#!/usr/bin/env python
import socket
import sys

host = 'localhost'
port = 9500
size = 1024

sd = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sd.bind((host,port))

data,address = sd.recvfrom(size)
print "Client Data :", data
sd.sendto(data,address)

sd.close()
