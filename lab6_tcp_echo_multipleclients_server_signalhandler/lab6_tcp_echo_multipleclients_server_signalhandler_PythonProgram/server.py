#!/usr/bin/env python
import socket
import csv
import sys
import os
import errno
import signal
import optparse

def _handle_child(signum, frame):
	pid, status = os.waitpid(-1,os.WNOHANG)
	return
		
HOST = 'localhost'                 
PORT = 9500              		   
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
signal.signal(signal.SIGCHLD, _handle_child)
s.bind((HOST, PORT))
ld = s.listen(5)

while True:
	conn,addr = s.accept()
	pid = os.fork()
	if (pid == 0):
	    #s.close()
    	    print 'In child process : ', addr
    	    data = conn.recv(1024)
    	    print 'Received data : ',data
            conn.send(data)
            conn.close()
            #os._exit(0)
        else:
            print 'In Parent Process'
        conn.close()
s.close()
sys.exit(0)
        
