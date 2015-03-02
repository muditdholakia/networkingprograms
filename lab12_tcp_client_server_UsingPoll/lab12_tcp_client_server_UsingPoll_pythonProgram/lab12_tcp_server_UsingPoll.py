import select
import socket
import sys

host = "localhost"
port = 10000
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((host,port))
server.listen(5)

TIMEOUT = 1000
READ_ONLY = select.POLLIN
poller = select.poll()
poller.register(server, READ_ONLY)
# Map file descriptors to socket objects
fd_to_socket = { server.fileno(): server,
               }
while True:

    events = poller.poll(TIMEOUT)

    for fd, flag in events:

        # Retrieve the actual socket from its file descriptor
        s = fd_to_socket[fd]
        if flag & select.POLLIN:
	
	            if s is server:
	                connection, client_address = s.accept()
	                print "new connection from", client_address
	                fd_to_socket[ connection.fileno() ] = connection
	                poller.register(connection, READ_ONLY)
              	    else:
                	data = s.recv(1024)
		        print "received data ", data
		        poller.unregister(s)
			s.close()
s.close()
os._exit(0)
			     