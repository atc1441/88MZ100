#!/usr/bin/env python
###    Edited: Aaron Christophel ATCnetz.de    ###

# This is used to controll the E-Paper stock firwmare, there are not many good cmds known, most of them are for radio testing and display testimages
import sys
import time
import serial.tools.list_ports

ports = serial.tools.list_ports.comports()

usedCom = ports[0].device  # select the first available comport
usedBaud = 115200
resetTime = 1
print('Using port: {}'.format(usedCom))

serialPort = serial.Serial(usedCom, usedBaud, serial.EIGHTBITS, serial.PARITY_NONE, serial.STOPBITS_ONE)


send_bytes = b"C" + bytearray([0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00])

sendArray = bytearray([0x02]) + bytearray(b'CAFE') + bytearray([len(send_bytes)]) + send_bytes + bytearray([0x03])
crc_byte = 0
for c in sendArray: crc_byte += c
sendArray = sendArray + bytearray([crc_byte & 0xff])
print(' '.join(format(x, '02x') for x in sendArray))

serialPort.write(sendArray)


#print(serialPort.read())
    

serialPort.close()