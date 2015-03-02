import socket
if hasattr(socket, 'setdefaulttimeout'):
# Set the default timeout on sockets to 5 seconds
     socket.setdefaulttimeout(5)
print(socket.gethostbyaddr("69.59.196.211"))