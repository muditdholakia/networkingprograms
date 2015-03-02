#!/usr/bin/env python
import socket
import csv
import sys
import os
import errno
import signal
import optparse

server_address = '/tmp/UNDtest'
def _handle_child(signum, frame):
	pid, status = os.waitpid(-1,os.WNOHANG)
	return

try:
    os.unlink(server_address)
except OSError:
    if os.path.exists(server_address):
        raise

sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
signal.signal(signal.SIGCHLD, _handle_child)

print >>sys.stderr, 'starting up on %s' % server_address
sock.bind(server_address)


sock.listen(1)

while True:
    
    print >>sys.stderr, 'waiting for a connection'
    connection, client_address = sock.accept()
    pid = os.fork()
    if (pid == 0):
	    try:
               while True:
       	            data = connection.recv(1024)
		    if data:
	       		print >>sys.stderr, 'received "%s"' % data
   	                print >>sys.stderr, 'sending data back to the client'
        	        connection.sendall(data)
	            else:
		        break          
    	    finally:
                connection.close()
      
