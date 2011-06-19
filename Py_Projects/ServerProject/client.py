#!/usr/bin/env python
'''
A simple echo client that handles some exceptions
'''

import socket
import sys

host = 'localhost'
port = 50001
size = 1024
s = None
try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))
except socket.error:
    if s:
        s.close()
    print('Could not open socket:', message)
    sys.exit(1)
data = 'uname -a'
ret = s.send(bytearray(data,'utf-8'))
if (ret is not len(data)):
    print(ret)
data = s.recv(size).decode()
s.close()
print('Received:')
print(data)

