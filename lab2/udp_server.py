import socket

server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

host = "127.0.0.1"
port = 5001

server_socket.bind((host, port))

print("UDP Server is running...")

data, addr = server_socket.recvfrom(1024)

print("Client:", data.decode())

server_socket.sendto("Hello Client".encode(), addr)

server_socket.close()