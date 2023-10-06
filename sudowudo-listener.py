import socket
import base64

LISTEN_IP = "0.0.0.0"
PORT = 4444 # Set the port to listen on

server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_socket.bind((LISTEN_IP, PORT))

print("=== STARTED SUDOWUDO LISTENER ===")

while True:
    message, address = server_socket.recvfrom(1024)
    print(f"{address[0]}:{address[1]} -- {base64.b64decode(message.decode()).decode()}")