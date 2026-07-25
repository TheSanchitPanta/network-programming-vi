import socket

client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

host = "127.0.0.1"
port = 5001

message = "Hello Server"

client_socket.sendto(message.encode(), (host, port))

response, addr = client_socket.recvfrom(1024)

print("Server replied:", response.decode())

client_socket.close()