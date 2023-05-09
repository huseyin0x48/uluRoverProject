import socket

UDP_IP_ADDRESS = "192.168.1.94" #Paketlerin alınacağı IP adresi girilmeli.
UDP_PORT_NO = 8081 #Paketlerin alınacağı port girilmeli.

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP_ADDRESS, UDP_PORT_NO))

while True:
    data, addr = sock.recvfrom(4)
    value = int.from_bytes(data, byteorder="big")
    print("Alınan değer: ", value)
