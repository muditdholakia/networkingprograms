import socket
hostname = 'www.yahoo.com'
addr = socket.gethostbyname(hostname)
print ('The address of ', hostname, 'is', addr )