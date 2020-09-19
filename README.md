# 88MZ100

4.2" E-Paper Price tag and its 88MZ100 SOC infos:

The Chip is QFN48 and has no known datasheet but here is some reversed pinout:
```
1 - OSC 32mhz in
2 - OSC 32mhz out
3 - Reset
4 - 
5 - GPIO 2 - EPD BS
6 - GPIO 3 - Test mode input
7 - 
8 - 
9 - 
10 - 
11 - 
12 - 

13 - Antenna OUT
14 - 
15 - 
16 - 
17 - 
18 - 
19 - 
20 - GPIO 12 - SPI SDO / EPD MoSi
21 - GPIO 13 - SPI SDI
22 - GPIO 14 - SWD CLK
23 - GPIO 15 - SWD DIO
24 - 

25 - 
26 - 
27 - 
28 - 
29 - 
30 - 
31 - GPIO 22 - SPI SCK / EPD Clock
32 - GPIO 23 - EPD CS
33 - 
34 - 
35 - 
36 - 

37 - 
38 - 
39 - 
40 - 
41 - 
42 - 
43 - GPIO 26 - EPD D/C
44 - GPIO 27 - EPD Busy
45 - GPIO 28 - EPD Reset
46 - 
47 - 
48 - 
GPIO Register

0x48070000 + OFFSET!!! = Gpio function 0=GPIO 6=SPI
0x4A040004 = GPIO mode Input/Output
0x4A040000 = GPIO set/clear
0x4A040050 = GPIO Read
```
