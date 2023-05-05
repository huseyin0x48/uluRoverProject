import socket
import struct
import random
import time


udpIp = "192.168.1.83"
udpPort = 8081


sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

while True:

    randomValue = random.randrange(0,100)
    data = struct.pack('i', randomValue)

    sock.sendto(data, (udpIp, udpPort))

    time.sleep(1)
