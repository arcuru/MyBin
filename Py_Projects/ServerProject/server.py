#!/usr/bin/env python
'''
A simple echo server that handles some exceptions
'''

import socket
import subprocess
from multiprocessing import Process

def data_handler(data, client):
	print("Command")
	print(data)
	# Break data into list of arguments
	args = data.split(' ')
	try:
		proc = subprocess.Popen(args, stdout=subprocess.PIPE,
			stderr=subprocess.PIPE)
		so, se = proc.communicate()
		print("Result:")
		print(so.decode())
		if data:
			client.send(bytearray(so.decode(),'utf-8'))
		client.close()
	except:
		print("Error in processing")
		client.send(bytearray("Error in processing",'utf-8'))
		client.close()

host = ''
port = 50003
backlog = 5
size = 1024
s = None
proc_list = []
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
	# Break off child process to deal with this command
	proc_list.append(Process(target=data_handler, args=(data,client)))
	proc_list[-1].start()
	count = 0
	for x in proc_list:
		if x.is_alive():
			count += 1
		else:
			proc_list.remove(x)


