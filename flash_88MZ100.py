#!/usr/bin/env python
###    Autor: Aaron Christophel ATCnetz.de    ###

import time
import serial.tools.list_ports

usedCom = "COM14"
usedBaud = 115200
serialPort = serial.Serial(usedCom, usedBaud, serial.EIGHTBITS, serial.PARITY_NONE, serial.STOPBITS_ONE)
print('Using port: {}'.format(usedCom))

bootloader_password = 0xffffffff
uart_ceck = 0x00

def to_byte(input,number=4):
    return input.to_bytes(number, byteorder = 'little')
    
def get_cmd(cmd,length=0,address=0):
    return_data = to_byte(cmd,1) + to_byte(0x00,1) + to_byte(length,1) + to_byte(bootloader_password) + to_byte(address)
    return bytearray([len(return_data)]) + return_data
    
def send_cmd(cmd):
    global uart_ceck
    uart_ceck ^= 0x40
    cmd[2] = uart_ceck
    print(' '.join(format(x, '02x') for x in cmd))
    serialPort.write(cmd)
    time.sleep(0.01)

def wait_for_prompt():
    while (True):
        if (serialPort.inWaiting()>0):
            data_str = serialPort.read(serialPort.inWaiting())
            print(' '.join(format(x, '02x') for x in data_str))
            for x in data_str:
                if x == 0x3A:
                    serialPort.write(to_byte(0x3A,1))
                    print("Halting boot")
                    return
                if x == 0x23:
                    print("Got it")
                    return
        time.sleep(0.01)

def uart_flush(): 
    time.sleep(0.4)# Flush serial data 
    while(serialPort.inWaiting()>0):
        data_str = serialPort.read(serialPort.inWaiting())
        print(' '.join(format(x, '02x') for x in data_str))

    
def enable_swd(state=1):
    return get_cmd(1,0,not state)
    
def read_memory(address,length):#max 256*4 bytes
    return get_cmd(2,int(length/4),address)

#Example: write_memory(0x00,bytearray([0x02, 0x07, 0x40, 0x34]))
def write_memory(address,data):#max 256*4 bytes
    return get_cmd(3,int(len(data)),0x100000+address)+data
    
def read_flash(address,length):
    return get_cmd(4,int(length/4),address)
    
def run_address(address):
    return get_cmd(5,0,address)
    
def reset_chip():
    return get_cmd(7)
    
def erase_flash():
    return run_address(0x666)

print("Waiting for boot promt, please reset the chip") 
wait_for_prompt()
uart_flush()

for x in range(5):
    send_cmd(read_memory(0x0,12)) 
    time.sleep(0.1)
    while(serialPort.inWaiting()>0):#Read the answer from device
        data_str = serialPort.read(serialPort.inWaiting())
        print(' '.join(format(x, '02x') for x in data_str))

serialPort.close()