import socket

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

host = '127.0.0.1'
port = 5001


server_socket.bind((host, port))

server_socket.listen(1)

print("Server is waiting for connection...")

client_socket, address = server_socket.accept()

print("Connected with:", address)

message = client_socket.recv(1024).decode()

print("Client says:", message)

response = "Hello Client, message received!"

client_socket.send(response.encode())

client_socket.close()
server_socket.close()