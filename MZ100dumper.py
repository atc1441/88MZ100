#by ATC (atcnetz.de)
# This small tool dumps the memory content of the 88MZ100 via its SWD port and OPENOCD
#
# You need to have an open OPENOCD connecion so this tool can connect to it
#
# on register level it controlls the QSPI port of the Flash and reads the input byte one by one.

import sys
import telnetlib
import re
import time

    
def getHEX(block):
    tn = telnetlib.Telnet("127.0.0.1",4444,2)
    oldtime = time.time()
    tn.write("reset\n".encode("utf8")) # Reset MZ100
    time.sleep(3)
    tn.write("halt\n".encode("utf8")) # Stop CPU
    time.sleep(3)
    tn.write("mww 0x4A070020 0x7d000\n".encode("utf8")) # Set count to 512kb
    time.sleep(1)
    tn.write("mww 0x4A070014 "+str(block)+"\n".encode("utf8")) # Set Flash address
    time.sleep(1)
    tn.write("mww 0x4A070000 0x153\n".encode("utf8")) # SS Enable
    time.sleep(1)
    tn.write("mww 0x4A070004 0x8000\n".encode("utf8")) # Start Transfer
    time.sleep(1)
    count = 0
    while True:
        tn.write("mdb 0x4A07000c\n".encode("utf8")) # Read byte, adress increases on its own
        try:
            currentAnswer = tn.read_until("\n".encode("utf8"),2).decode("utf8")
        except E.timeout:
            print("Closing because of no good answer from OpenOCD")
            exit()   
        if currentAnswer[0:10] == '0x4a07000c':
            print "Current "+ str(count+block) + " "+currentAnswer[12:14]
            file = open("dump.txt","a+") 
            file.write(currentAnswer[12:14]) 
            file.close() 
            count = count + 1
            if count > 0x4fff:
                print "current block done"
                tn.close
                return
	tn.close
    return

def main():
    current_pos = 0
    while current_pos < 0x80000: # Read blocks until over 512kb
        getHEX(current_pos)
        current_pos = current_pos + 0x4fff # when choosing a bigger block size Telnet closes the connection

if __name__ == '__main__':
    main()