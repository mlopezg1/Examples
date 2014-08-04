from serial import Serial
from time import sleep

ser = Serial('/dev/ttyACM0',baudrate=115200)

sleep(1)

cmd = [0x7E,0x00,0xFF,0x0A,0xA3]

for i in cmd:
	ser.write(chr(i))

print "Finish!"