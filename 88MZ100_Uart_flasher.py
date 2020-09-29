#!/usr/bin/python

###    Autor: Aaron Christophel ATCnetz.de    ###

## arg1 = COMPORT  arg2 = read or write arg3 = filename to read or write

import sys
import os
import time
import serial.tools.list_ports

if(len(sys.argv)!=4):
    print("Example: COM1 read file.bin, or COM1 write file.bin")
    print("Not the right arguments but here are the... please wait...")
    ports_list = "possible UART ports: "
    for port in serial.tools.list_ports.comports():
        ports_list += port.device + " "
    print(ports_list)
    exit()
    
usedCom = sys.argv[1] #"COM14"
read_or_write = sys.argv[2]
file = sys.argv[3]
usedBaud = 115200
serialPort = serial.Serial(usedCom, usedBaud, serial.EIGHTBITS, serial.PARITY_NONE, serial.STOPBITS_ONE, timeout=1)
print('Using port: {}'.format(usedCom))

bootloader_password = 0xffffffff
uart_ceck = 0x00

def bytes_to_int(bytes):
    result = 0
    for b in range(3,-1,-1):
        result = result * 256 + int(bytes[b])
    return result
    
def to_byte(input,number=4):
    return input.to_bytes(number, byteorder = 'little')
    
def get_cmd(cmd,length=0,address=0,plus_size=0):
    return_data = to_byte(cmd,1) + to_byte(0x00,1) + to_byte(length,1) + to_byte(bootloader_password) + to_byte(address)
    return bytearray([len(return_data)+plus_size]) + return_data
    
def send_cmd(cmd):
    global uart_ceck
    uart_ceck ^= 0x40
    cmd[2] = uart_ceck
    #print(' '.join(format(x, '02x') for x in cmd))
    serialPort.write(cmd)

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
    time.sleep(1)# Flush serial data 
    while(serialPort.inWaiting()>0):
        data_str = serialPort.read(serialPort.inWaiting())
        print(' '.join(format(x, '02x') for x in data_str))

def uart_receive_handler(expected_len):
    data_str = serialPort.read(expected_len)   
    print("Answer: " + ' '.join(format(x, '02x') for x in data_str))
    if(data_str[0]!=len(data_str)-1):
        print("Error while receiving")
        exit()
    return data_str
    
def enable_swd(state=1):
    return get_cmd(1,0,not state)
    
def read_memory(address,length):#max 128bytes
    return get_cmd(2,int(length/4),address)

#Example: write_memory(0x00,bytearray([0x02, 0x07, 0x40, 0x34]))
def write_memory(address,data):#max 128bytes
    return get_cmd(3,int(len(data)/4),0x100000+address,len(data))+data
    
def read_flash(address,length):
    return get_cmd(4,int(length/4),address)
    
def run_address(address):
    return get_cmd(5,0,address)
    
def reset_chip():
    return get_cmd(7)
    
def erase_flash():
    return run_address(0x666)

def flash_file(filename):
    print("Opening file " + filename)
    in_file = open(filename, "rb")
    data = bytearray(in_file.read())
    filesize = len(data)
    in_file.close()
    print("file size: "+str(filesize))
    entry_point = bytes_to_int(data[4:8])
    print("entry point: "+ hex(entry_point))
    
    block_size = 80 # bytes per sending
    cur_address = 0
    while(filesize-cur_address>0):
        if(filesize-cur_address>block_size):
            cur_size = block_size
        else:
            cur_size = filesize-cur_address
        cur_data = data[cur_address:cur_address+cur_size]
        print("Current address: " + hex(cur_address))
        send_cmd(write_memory(cur_address,cur_data))
        cur_address+=cur_size
        uart_receive_handler(4)
    print("Running fimrware from: " + hex(entry_point))
    send_cmd(run_address(entry_point))

def dump_flash(filename):
    block_size = 128 # bytes per request
    for x in range(int(0x80000/block_size)):
        send_cmd(read_flash(x*block_size,block_size)) 
        current_block_dump = uart_receive_handler(4+block_size)
        file = open(filename,"ab+") 
        file.write((''.join(chr(i) for i in current_block_dump[4:])).encode('charmap')) 
        file.close() 

print("Waiting for boot promt, please reset the chip") 
wait_for_prompt()
uart_flush()
            
if(read_or_write=='read'):
    dump_flash('read_' + file)
elif(read_or_write=='write'):
    flash_file(file)

serialPort.close()