#!/usr/bin/python

# TCP Server Code
import sys
import time
host="127.0.0.1"                # Set the server address to variable host
port=4446                   # Sets the variable port to 4444
from socket import *                # Imports socket module
 
s=socket(AF_INET, SOCK_STREAM)
 
s.bind((host,port))                 # Binds the socket. Note that the input to
                                            # the bind function is a tuple
 
s.listen(1)                         # Sets socket to listening state with a  queue
                                            # of 1 connection
 
print ("Listening for connections.. ")
 
q,addr=s.accept()               # Accepts incoming request from client and returns
                                            # socket and address to variables q and addr
print "Got connection from..",addr                                            
 
q.send(time.strftime("%d/%m/%Y")+ time.strftime("%I:%M:%S"))                        # Sends data to client
 
s.close()
 
# End of code


