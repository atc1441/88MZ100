# 88MZ100

4.2" E-Paper Price tag and its 88MZ100 SOC infos:

The Chip is QFN48 and has no known datasheet but here is some reversed pinout:
```
1 - OSC 32mhz in
2 - OSC 32mhz out
3 - GPIO 0 - Reset
4 - GPIO 1 - Something NFC Power
5 - GPIO 2 - EPD BS
6 - GPIO 3 - Test mode input
7 - GPIO 4 - UART TXD
8 - GPIO 5 - IO Wakeup
9 - GPIO 6 - UART RXD
10 - GPIO 7 - Something NFC i2c
11 - SOME VDD or VCC
12 - SOME VDD or VCC

13 - Antenna OUT
14 - NC
15 - SOME VDD or VCC
16 - GPIO 8 - 
17 - GPIO 9 - 
18 - GPIO 10 - 
19 - GPIO 11 - 
20 - GPIO 12 - SPI SDO / EPD MoSi
21 - GPIO 13 - SPI SDI
22 - GPIO 14 - SWD CLK
23 - GPIO 15 - SWD DIO
24 - GPIO 16 - 

25 - SOME VDD or VCC
26 - GPIO 17 - 
27 - GPIO 18 - 
28 - GPIO 19 - 
29 - GPIO 20 - 
30 - GPIO 21 - 
31 - GPIO 22 - SPI SCK / EPD Clock
32 - GPIO 23 - EPD CS
33 - GPIO 24 - EPD Reset
34 - GPIO 25 - 
35 - SOME VDD or VCC
36 - SOME VDD or VCC

37 - CF2 Capacitor
38 - CF1 Capacitor
39 - VCC 3.3V maybe VBAT
40 - SOME VDD or VCC
41 - SOME VDD or VCC
42 - SOME VDD or VCC
43 - GPIO 26 - EPD D/C
44 - GPIO 27 - EPD Busy
45 - GPIO 28 - Something NFC i2c
46 - GPIO 29 - Something NFC i2c
47 - GPIO 30 - 
48 - SOME VDD or VCC


GPIO Register

0x48070000 + OFFSET!!! = Gpio function 0=GPIO 6=SPI
0x4A040004 = GPIO mode Input/Output
0x4A040000 = GPIO set/clear
0x4A040050 = GPIO Read

Currently known memory regions:

0x00000000 - 0x0001ffff  ROM 128kb

0x00100000 - 0x00127fff  RAM 160kb
0x20100000 - 0x20127fff Just the same RAM 160kb as on 0x00100000

0x00000000 - 0x00800000 Internal SPI Flash 512kb <- only acessable via internal QSPI Hardware


Fimrware Header:

Little endian so its switched!

8 times uint32_t

0x20125030 = 00 00 00 00 = Just to check if Flash is empty
0x20125034 = 23 01 CC CC = CONFIG 1
0x20125038 = 44 C6 00 00 = Length of image counts after header
0x2012503C = 07 7F EE FF = CONFIG 2

0x20125040 = FF FF FF FF = Seems like security, DONT TOUCH THIS!!!
0x20125044 = 00 00 10 00 = RAM Loading point 0x100000
0x20125048 = 41 01 10 00 = Entry point 0x100141
0x2012504C = 4C 56 52 4D = Magic string MRVL

CONFIG 1:
Byte0 = 
Byte1 = UART Port 0 or 1
Byte2 = 
Byte3 = 
```
