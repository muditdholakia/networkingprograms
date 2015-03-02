# TCP Client Code
import select
import os
 
host="127.0.0.1"            # Set the server address to variable host
 
port=4446               # Sets the variable port to 4444
 
from socket import *             # Imports socket module
 
s=socket(AF_INET, SOCK_STREAM)      # Creates a socket
 
s.connect((host,port))          # Connect to server address

input = [0,s]
inputready,outputready,exceptready = select.select(input,[],[])
for c in inputready:
	if c == 0:
		data=raw_input()
 		print "Entered data:" + data              
        elif c == s:
		msg= s.recv(1024)            # Receives data upto 1024 bytes and stores in variables msg
		print "Message from server : " + msg             
        else:
                print "unknown socket:", s

s.close()                            # Closes the socket
os._exit(0)
# End of codes