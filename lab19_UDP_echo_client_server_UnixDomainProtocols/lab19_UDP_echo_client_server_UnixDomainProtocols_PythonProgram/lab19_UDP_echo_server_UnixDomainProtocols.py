#!/usr/bin/env python
import socket
import csv
import sys
import os
import errno
import signal
import optparse

server_address = '/tmp/UNDtestUDP'
try:
    os.unlink(server_address)
except OSError:
    if os.path.exists(server_address):
        raise

sock = socket.socket(socket.AF_UNIX, socket.SOCK_DGRAM)
print >>sys.stderr, 'starting up on %s' % server_address
sock.bind(server_address)

while True:
    
    print >>sys.stderr, 'waiting for a connection'
#    connection, client_address = sock.accept()
    try:
               while True:
       	            data,client_address = sock.recvfrom(1024)
		    if data:
	       		print >>sys.stderr, 'received "%s"' % data
   	                print >>sys.stderr, 'sending data back to the client'
        	        sock.sendto(data,client_address)
	            else:
		        break          
    finally:
                sock.close()
      
