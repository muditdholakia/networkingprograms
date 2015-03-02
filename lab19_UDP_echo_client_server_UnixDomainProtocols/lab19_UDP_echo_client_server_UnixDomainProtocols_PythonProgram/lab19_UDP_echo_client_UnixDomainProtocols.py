import socket
import sys
import os

# Create a UDS socket
sock = socket.socket(socket.AF_UNIX, socket.SOCK_DGRAM)

# Connect the socket to the port where the server is listening
server_address = '/tmp/UNDtestUDP'
print >>sys.stderr, 'connecting to %s' % server_address
client_address = '/tmp/UNDtestCli'
try:
	os.unlink(client_address)
except OSError:
    if os.path.exists(client_address):
        raise
sock.bind(client_address)
try:
    # Send data
    message = 'This is the message.  It will be repeated.'
    print >>sys.stderr, 'sending "%s"' % message
    sock.sendto(message,server_address)
    amount_received = 0
    amount_expected = len(message)
    while amount_received < amount_expected:
        data,server_address = sock.recvfrom(1024)
        amount_received += len(data)
        print >>sys.stderr, 'received "%s"' % data
finally:
    print >>sys.stderr, 'closing socket'
    sock.close()
