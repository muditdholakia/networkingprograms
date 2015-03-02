#!/usr/bin/env python
import socket
import csv
import sys
import os
import errno
import signal
import socket
import optparse

def _handle_child(signum, frame):
	pid, status = os.waitpid(-1,os.WNOHANG)
	return
		
HOST = 'localhost'                 
PORT = 9000              		   
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
signal.signal(signal.SIGCHLD, _handle_child)
s.bind((HOST, PORT))
ld = s.listen(5)
if (os.fork()>0):
	os._exit(0)
os.setsid()
while True:
	conn,addr = s.accept()
	pid = os.fork()
	if (pid == 0):
	    #s.close()
    	    print 'enter name:', addr
    	    data = conn.recv(1024)
    	    print 'Hello',data
            conn.send(data)
            conn.close()
        else:
            print 'ERROR!'
        conn.close()
s.close()
sys.exit(0)
        
