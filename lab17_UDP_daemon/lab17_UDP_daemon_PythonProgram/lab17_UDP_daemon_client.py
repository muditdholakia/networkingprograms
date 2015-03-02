#!/usr/bin/env python
import socket
import sys

host = 'localhost'
port = 9500
size = 1024

sd = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

data = raw_input ("Enter Data")
sd.sendto(data,(host,port))
data,addr = sd.recvfrom(size)

print "Echo From Server :", data

sd.close()
