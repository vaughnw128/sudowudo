import socket
import base64
import datetime
import os
LISTEN_IP = "0.0.0.0"
PORT = 4444 # Set the port to listen on

server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_socket.bind((LISTEN_IP, PORT))

log_location = "/var/log/sudowudo.log"

print("=== STARTED SUDOWUDO LISTENER ===")
    
while True:
    message, address = server_socket.recvfrom(1024)
    if message != None:
        current = datetime.datetime.now()
        timestamp = current.strftime("%d-%m-%Y %H:%M:%S")
        outstring = f"{timestamp} -- {address[0]}:{address[1]} -- {base64.b64decode(message.decode()).decode()}"
        print(outstring)
        with open(log_location, "w") as f:
            f.write(f"{outstring}\n")