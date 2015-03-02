#!/usr/bin/env python
import socket
import csv
import sys
import os

HOST = 'localhost'    
PORT = 9500              
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
data = raw_input('Enter Data: ')
s.send(data)
data = s.recv(1024)
print "Received", data
s.close()
os._exit(0)
