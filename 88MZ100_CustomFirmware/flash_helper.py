
#!/usr/bin/python

import sys
import os

def bytes_to_int(bytes):
    result = 0
    for b in range(3,-1,-1):
        result = result * 256 + int(bytes[b])
    return result

project_file = sys.argv[1] + '.bin'

in_file = open(project_file, "rb")
data = bytearray(in_file.read(8)[4:8])
in_file.close()
project_entry_point = hex(bytes_to_int(data))

print("Entry point of firmware: " + project_entry_point)

os.system('openocd -d0 -c "source [find openocd.cfg]"; -c "load_image ' + sys.argv[1] + '.bin 0x100000"; -c "resume ' + str(project_entry_point) + '"; -c "shutdown";')