import socket

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

host = '127.0.0.1'
port = 5001

client_socket.connect((host, port))

message = "Hello Server"

client_socket.send(message.encode())

response = client_socket.recv(1024).decode()

print("Server replied:", response)

client_socket.close()