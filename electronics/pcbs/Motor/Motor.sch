EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:Motor-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Secondary Region V Bot PCB (Motor Control)"
Date "2018-03-21"
Rev "2"
Comp "IEEE RAS (UT)"
Comment1 "Rev2: Power the Uno with VBATT, not 5V Reg."
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 8950 2300 0    60   ~ 0
Vin
Text Label 8900 2500 0    60   ~ 0
A0
Text Label 8900 2600 0    60   ~ 0
A1
Text Label 8900 2700 0    60   ~ 0
A2
Text Label 8900 2800 0    60   ~ 0
A3
Text Label 8900 2900 0    60   ~ 0
A4(SDA)
Text Label 8900 3000 0    60   ~ 0
A5(SCL)
Text Label 10550 3000 0    60   ~ 0
0(Rx)
Text Label 10550 2800 0    60   ~ 0
2
Text Label 10550 2900 0    60   ~ 0
1(Tx)
Text Label 10550 2700 0    60   ~ 0
3(**)
Text Label 10550 2600 0    60   ~ 0
4
Text Label 10550 2500 0    60   ~ 0
5(**)
Text Label 10550 2400 0    60   ~ 0
6(**)
Text Label 10550 2300 0    60   ~ 0
7
Text Label 10550 2100 0    60   ~ 0
8
Text Label 10550 2000 0    60   ~ 0
9(**)
Text Label 10550 1900 0    60   ~ 0
10(**/SS)
Text Label 10550 1800 0    60   ~ 0
11(**/MOSI)
Text Label 10550 1700 0    60   ~ 0
12(MISO)
Text Label 10550 1600 0    60   ~ 0
13(SCK)
Text Label 10550 1400 0    60   ~ 0
AREF
NoConn ~ 9400 1600
Text Label 10550 1300 0    60   ~ 0
A4(SDA)
Text Label 10550 1200 0    60   ~ 0
A5(SCL)
Text Notes 10850 1000 0    60   ~ 0
Holes
Text Notes 8550 750  0    60   ~ 0
Shield for Arduino that uses\nthe same pin disposition\nlike "Uno" board Rev 3.
$Comp
L CONN_01X08 P1
U 1 1 56D70129
P 9600 1950
F 0 "P1" H 9600 2400 50  0000 C CNN
F 1 "Power" V 9700 1950 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x08" V 9750 1950 20  0000 C CNN
F 3 "" H 9600 1950 50  0000 C CNN
	1    9600 1950
	1    0    0    -1  
$EndComp
Text Label 8650 1800 0    60   ~ 0
Reset
$Comp
L GND #PWR01
U 1 1 56D70CC2
P 9300 3150
F 0 "#PWR01" H 9300 2900 50  0001 C CNN
F 1 "GND" H 9300 3000 50  0000 C CNN
F 2 "" H 9300 3150 50  0000 C CNN
F 3 "" H 9300 3150 50  0000 C CNN
	1    9300 3150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 56D70CFF
P 10300 3150
F 0 "#PWR02" H 10300 2900 50  0001 C CNN
F 1 "GND" H 10300 3000 50  0000 C CNN
F 2 "" H 10300 3150 50  0000 C CNN
F 3 "" H 10300 3150 50  0000 C CNN
	1    10300 3150
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X06 P2
U 1 1 56D70DD8
P 9600 2750
F 0 "P2" H 9600 3100 50  0000 C CNN
F 1 "Analog" V 9700 2750 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x06" V 9750 2800 20  0000 C CNN
F 3 "" H 9600 2750 50  0000 C CNN
	1    9600 2750
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 P5
U 1 1 56D71177
P 10800 650
F 0 "P5" V 10900 650 50  0000 C CNN
F 1 "CONN_01X01" V 10900 650 50  0001 C CNN
F 2 "Socket_Arduino_Uno:Arduino_1pin" H 10721 724 20  0000 C CNN
F 3 "" H 10800 650 50  0000 C CNN
	1    10800 650 
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X01 P6
U 1 1 56D71274
P 10900 650
F 0 "P6" V 11000 650 50  0000 C CNN
F 1 "CONN_01X01" V 11000 650 50  0001 C CNN
F 2 "Socket_Arduino_Uno:Arduino_1pin" H 10900 650 20  0001 C CNN
F 3 "" H 10900 650 50  0000 C CNN
	1    10900 650 
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X01 P7
U 1 1 56D712A8
P 11000 650
F 0 "P7" V 11100 650 50  0000 C CNN
F 1 "CONN_01X01" V 11100 650 50  0001 C CNN
F 2 "Socket_Arduino_Uno:Arduino_1pin" V 11000 650 20  0001 C CNN
F 3 "" H 11000 650 50  0000 C CNN
	1    11000 650 
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X01 P8
U 1 1 56D712DB
P 11100 650
F 0 "P8" V 11200 650 50  0000 C CNN
F 1 "CONN_01X01" V 11200 650 50  0001 C CNN
F 2 "Socket_Arduino_Uno:Arduino_1pin" H 11024 572 20  0000 C CNN
F 3 "" H 11100 650 50  0000 C CNN
	1    11100 650 
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X08 P4
U 1 1 56D7164F
P 10000 2650
F 0 "P4" H 10000 3100 50  0000 C CNN
F 1 "Digital" V 10100 2650 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x08" V 10150 2600 20  0000 C CNN
F 3 "" H 10000 2650 50  0000 C CNN
	1    10000 2650
	-1   0    0    -1  
$EndComp
Wire Notes Line
	8525 825  9925 825 
Wire Notes Line
	9925 825  9925 475 
Wire Wire Line
	9400 2300 8950 2300
Wire Wire Line
	9400 2100 9300 2100
Wire Wire Line
	9400 2200 9300 2200
Connection ~ 9300 2200
Wire Wire Line
	8950 2300 8950 1450
Wire Wire Line
	9400 2500 8900 2500
Wire Wire Line
	9400 2600 8900 2600
Wire Wire Line
	9400 2700 8900 2700
Wire Wire Line
	9400 2800 8900 2800
Wire Wire Line
	9400 2900 8900 2900
Wire Wire Line
	9400 3000 8900 3000
$Comp
L CONN_01X10 P3
U 1 1 56D721E0
P 10000 1650
F 0 "P3" H 10000 2200 50  0000 C CNN
F 1 "Digital" V 10100 1650 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x10" V 10150 1650 20  0000 C CNN
F 3 "" H 10000 1650 50  0000 C CNN
	1    10000 1650
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10200 2100 10550 2100
Wire Wire Line
	10200 2000 10550 2000
Wire Wire Line
	10200 1900 10550 1900
Wire Wire Line
	10200 1800 10550 1800
Wire Wire Line
	10200 1700 10550 1700
Wire Wire Line
	10200 1600 10550 1600
Wire Wire Line
	10200 1400 10550 1400
Wire Wire Line
	10200 1300 10550 1300
Wire Wire Line
	10200 1200 10550 1200
Wire Wire Line
	10200 3000 10550 3000
Wire Wire Line
	10200 2900 10550 2900
Wire Wire Line
	10200 2800 10550 2800
Wire Wire Line
	10200 2700 10550 2700
Wire Wire Line
	10200 2600 10550 2600
Wire Wire Line
	10200 2500 10550 2500
Wire Wire Line
	10200 2400 10550 2400
Wire Wire Line
	10200 2300 10550 2300
Wire Wire Line
	10200 1500 10300 1500
Wire Wire Line
	10300 1500 10300 3150
Wire Wire Line
	9300 2100 9300 3150
Wire Notes Line
	8500 500  8500 3450
Wire Notes Line
	8500 3450 11200 3450
Wire Wire Line
	9400 1800 8650 1800
Text Notes 9700 1600 0    60   ~ 0
1
Wire Notes Line
	11200 1000 10700 1000
$Comp
L Conn_01x04 J3
U 1 1 5AB1D428
P 7150 1250
F 0 "J3" H 7150 1450 50  0000 C CNN
F 1 "I2C Bus" H 7150 950 50  0000 C CNN
F 2 "Connectors_Samtec:SL-104-X-XX_1x04" H 7150 1250 50  0001 C CNN
F 3 "" H 7150 1250 50  0001 C CNN
	1    7150 1250
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR03
U 1 1 5AB1D782
P 6900 900
F 0 "#PWR03" H 6900 750 50  0001 C CNN
F 1 "+5V" H 6900 1040 50  0000 C CNN
F 2 "" H 6900 900 50  0000 C CNN
F 3 "" H 6900 900 50  0000 C CNN
	1    6900 900 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 5AB1D7A8
P 6900 1500
F 0 "#PWR04" H 6900 1250 50  0001 C CNN
F 1 "GND" H 6900 1350 50  0000 C CNN
F 2 "" H 6900 1500 50  0000 C CNN
F 3 "" H 6900 1500 50  0000 C CNN
	1    6900 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 1450 6950 1450
Wire Wire Line
	6900 1450 6900 1500
Wire Wire Line
	6700 1250 6950 1250
Wire Wire Line
	6700 1350 6950 1350
Text Label 6800 1100 2    60   ~ 0
A4(SDA)
Text Label 6800 1500 2    60   ~ 0
A5(SCL)
Text Notes 6600 650  0    100  ~ 20
I2C Bus
$Comp
L GND #PWR05
U 1 1 5AB1DE16
P 10800 850
F 0 "#PWR05" H 10800 600 50  0001 C CNN
F 1 "GND" H 10800 700 50  0000 C CNN
F 2 "" H 10800 850 50  0000 C CNN
F 3 "" H 10800 850 50  0000 C CNN
	1    10800 850 
	1    0    0    -1  
$EndComp
Wire Notes Line
	10700 1000 10700 500 
Wire Wire Line
	10800 850  11100 850 
Connection ~ 10900 850 
Connection ~ 11000 850 
Wire Wire Line
	6800 1350 6800 1500
Wire Wire Line
	6800 1250 6800 1100
Connection ~ 6800 1250
Connection ~ 6800 1350
Text Label 6700 1250 2    60   ~ 0
I2C_Data
Text Label 6700 1350 2    60   ~ 0
I2C_Clk
$Comp
L Conn_01x04 J1
U 1 1 5AB1EC09
P 6700 2450
F 0 "J1" H 6700 2650 50  0000 C CNN
F 1 "Left Encoder" H 6800 2150 50  0000 C CNN
F 2 "Connectors_Samtec:SL-104-X-XX_1x04" H 6700 2450 50  0001 C CNN
F 3 "" H 6700 2450 50  0001 C CNN
	1    6700 2450
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR06
U 1 1 5AB1EC6E
P 6950 2300
F 0 "#PWR06" H 6950 2150 50  0001 C CNN
F 1 "+5V" H 6950 2440 50  0000 C CNN
F 2 "" H 6950 2300 50  0000 C CNN
F 3 "" H 6950 2300 50  0000 C CNN
	1    6950 2300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 5AB1ECAB
P 6950 2700
F 0 "#PWR07" H 6950 2450 50  0001 C CNN
F 1 "GND" H 6950 2550 50  0000 C CNN
F 2 "" H 6950 2700 50  0000 C CNN
F 3 "" H 6950 2700 50  0000 C CNN
	1    6950 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 2650 6950 2650
Wire Wire Line
	6950 2650 6950 2700
Wire Wire Line
	6950 2300 6950 2350
Wire Wire Line
	6950 2350 6900 2350
$Comp
L PWR_FLAG #FLG08
U 1 1 5AB1F15E
P 7900 1200
F 0 "#FLG08" H 7900 1275 50  0001 C CNN
F 1 "PWR_FLAG" V 7900 1300 50  0000 L CNN
F 2 "" H 7900 1200 50  0001 C CNN
F 3 "" H 7900 1200 50  0001 C CNN
	1    7900 1200
	0    1    1    0   
$EndComp
$Comp
L PWR_FLAG #FLG09
U 1 1 5AB1F541
P 8650 1050
F 0 "#FLG09" H 8650 1125 50  0001 C CNN
F 1 "PWR_FLAG" V 8650 1150 50  0000 L CNN
F 2 "" H 8650 1050 50  0001 C CNN
F 3 "" H 8650 1050 50  0001 C CNN
	1    8650 1050
	1    0    0    1   
$EndComp
Wire Wire Line
	6900 900  6900 1150
Wire Wire Line
	6900 1150 6950 1150
NoConn ~ 9400 1700
NoConn ~ 9400 1800
NoConn ~ 9400 2500
NoConn ~ 9400 2600
NoConn ~ 9400 2700
NoConn ~ 9400 2800
NoConn ~ 10200 1400
NoConn ~ 10200 1600
NoConn ~ 10200 1700
NoConn ~ 10200 1800
NoConn ~ 10200 1900
NoConn ~ 10200 2000
NoConn ~ 10200 2100
NoConn ~ 10200 2300
NoConn ~ 10200 2400
NoConn ~ 10200 2500
NoConn ~ 10200 2600
NoConn ~ 10200 2700
NoConn ~ 10200 2800
NoConn ~ 10200 2900
NoConn ~ 10200 3000
Wire Wire Line
	6900 2450 7050 2450
Wire Wire Line
	6900 2550 7050 2550
Text Label 7050 2550 0    60   ~ 0
L_ENC_B
Text Label 7050 2450 0    60   ~ 0
L_ENC_A
$Comp
L Conn_01x04 J2
U 1 1 5AB20117
P 7650 2450
F 0 "J2" H 7650 2650 50  0000 C CNN
F 1 "Right Encoder" H 7750 2150 50  0000 C CNN
F 2 "Connectors_Samtec:SL-104-X-XX_1x04" H 7650 2450 50  0001 C CNN
F 3 "" H 7650 2450 50  0001 C CNN
	1    7650 2450
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR010
U 1 1 5AB2011D
P 7900 2300
F 0 "#PWR010" H 7900 2150 50  0001 C CNN
F 1 "+5V" H 7900 2440 50  0000 C CNN
F 2 "" H 7900 2300 50  0000 C CNN
F 3 "" H 7900 2300 50  0000 C CNN
	1    7900 2300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 5AB20123
P 7900 2700
F 0 "#PWR011" H 7900 2450 50  0001 C CNN
F 1 "GND" H 7900 2550 50  0000 C CNN
F 2 "" H 7900 2700 50  0000 C CNN
F 3 "" H 7900 2700 50  0000 C CNN
	1    7900 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 2650 7900 2650
Wire Wire Line
	7900 2650 7900 2700
Wire Wire Line
	7900 2300 7900 2350
Wire Wire Line
	7900 2350 7850 2350
Wire Wire Line
	7850 2450 8000 2450
Wire Wire Line
	7850 2550 8000 2550
Text Label 8000 2550 0    60   ~ 0
R_ENC_B
Text Label 8000 2450 0    60   ~ 0
R_ENC_A
Text Notes 7050 1950 0    100  ~ 20
Encoders
$Comp
L Arduino_Nano U1
U 1 1 5AB21616
P 2150 1500
F 0 "U1" H 2150 1700 60  0000 C CNN
F 1 "Left Nano" H 2150 1600 60  0000 C CNN
F 2 "Arduino_Nano:Arduino_Nano" H 1400 500 60  0001 C CNN
F 3 "" H 1400 500 60  0001 C CNN
	1    2150 1500
	1    0    0    -1  
$EndComp
$Comp
L Arduino_Nano U1
U 2 1 5AB2168D
P 1950 2600
F 0 "U1" H 1950 2800 60  0000 C CNN
F 1 "Left Nano" H 1950 2700 60  0000 C CNN
F 2 "Arduino_Nano:Arduino_Nano" H 1200 1600 60  0001 C CNN
F 3 "" H 1200 1600 60  0001 C CNN
	2    1950 2600
	1    0    0    -1  
$EndComp
$Comp
L Arduino_Nano U1
U 3 1 5AB21A72
P 2000 4350
F 0 "U1" H 2000 4550 60  0000 C CNN
F 1 "Left Nano" H 2000 4450 60  0000 C CNN
F 2 "Arduino_Nano:Arduino_Nano" H 1250 3350 60  0001 C CNN
F 3 "" H 1250 3350 60  0001 C CNN
	3    2000 4350
	1    0    0    -1  
$EndComp
$Comp
L Arduino_Nano U2
U 1 1 5AB21CBD
P 3950 1500
F 0 "U2" H 3950 1700 60  0000 C CNN
F 1 "Right Nano" H 3950 1600 60  0000 C CNN
F 2 "Arduino_Nano:Arduino_Nano" H 3200 500 60  0001 C CNN
F 3 "" H 3200 500 60  0001 C CNN
	1    3950 1500
	1    0    0    -1  
$EndComp
$Comp
L Arduino_Nano U2
U 2 1 5AB21CC3
P 3750 2600
F 0 "U2" H 3750 2800 60  0000 C CNN
F 1 "Right Nano" H 3750 2700 60  0000 C CNN
F 2 "Arduino_Nano:Arduino_Nano" H 3000 1600 60  0001 C CNN
F 3 "" H 3000 1600 60  0001 C CNN
	2    3750 2600
	1    0    0    -1  
$EndComp
$Comp
L Arduino_Nano U2
U 3 1 5AB21CC9
P 3800 4350
F 0 "U2" H 3800 4550 60  0000 C CNN
F 1 "Right Nano" H 3800 4450 60  0000 C CNN
F 2 "Arduino_Nano:Arduino_Nano" H 3050 3350 60  0001 C CNN
F 3 "" H 3050 3350 60  0001 C CNN
	3    3800 4350
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR012
U 1 1 5AB21F5F
P 1600 1600
F 0 "#PWR012" H 1600 1450 50  0001 C CNN
F 1 "+5V" H 1600 1740 50  0000 C CNN
F 2 "" H 1600 1600 50  0000 C CNN
F 3 "" H 1600 1600 50  0000 C CNN
	1    1600 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 1600 1600 1650
Wire Wire Line
	1600 1650 1750 1650
$Comp
L +5V #PWR013
U 1 1 5AB2201B
P 3400 1600
F 0 "#PWR013" H 3400 1450 50  0001 C CNN
F 1 "+5V" H 3400 1740 50  0000 C CNN
F 2 "" H 3400 1600 50  0000 C CNN
F 3 "" H 3400 1600 50  0000 C CNN
	1    3400 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 1600 3400 1650
Wire Wire Line
	3400 1650 3550 1650
NoConn ~ 1750 1550
NoConn ~ 3550 1550
NoConn ~ 3550 1750
NoConn ~ 1750 1750
NoConn ~ 1750 2100
NoConn ~ 1750 2200
NoConn ~ 3550 2100
NoConn ~ 3550 2200
$Comp
L GND #PWR014
U 1 1 5AB22193
P 1600 2000
F 0 "#PWR014" H 1600 1750 50  0001 C CNN
F 1 "GND" H 1600 1850 50  0000 C CNN
F 2 "" H 1600 2000 50  0000 C CNN
F 3 "" H 1600 2000 50  0000 C CNN
	1    1600 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 1850 1600 2000
Wire Wire Line
	1600 1950 1750 1950
Wire Wire Line
	1750 1850 1600 1850
Connection ~ 1600 1950
$Comp
L GND #PWR015
U 1 1 5AB222A5
P 3400 2000
F 0 "#PWR015" H 3400 1750 50  0001 C CNN
F 1 "GND" H 3400 1850 50  0000 C CNN
F 2 "" H 3400 2000 50  0000 C CNN
F 3 "" H 3400 2000 50  0000 C CNN
	1    3400 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 1850 3400 2000
Wire Wire Line
	3400 1950 3550 1950
Wire Wire Line
	3550 1850 3400 1850
Connection ~ 3400 1950
Text Notes 1750 850  0    120  ~ 24
Arduino Nanos
Text Notes 1750 1150 0    60   Italic 0
Note: Because the 5V we receive is regulated,\nwe can pipe it straight into the 5V port of\nthe nanos. We don't need to go through VIN.
NoConn ~ 1350 2650
NoConn ~ 1350 2750
NoConn ~ 1350 3050
NoConn ~ 1350 3150
NoConn ~ 1350 3250
NoConn ~ 1350 3350
NoConn ~ 1350 3450
NoConn ~ 1350 3550
NoConn ~ 1350 3650
NoConn ~ 1350 3750
NoConn ~ 1350 3850
NoConn ~ 1350 3950
NoConn ~ 1450 4400
NoConn ~ 1450 4500
NoConn ~ 1450 4600
NoConn ~ 1450 4700
NoConn ~ 1450 4800
NoConn ~ 1450 5100
NoConn ~ 1450 5200
NoConn ~ 3250 5200
NoConn ~ 3250 5100
NoConn ~ 3250 4800
NoConn ~ 3250 4700
NoConn ~ 3250 4600
NoConn ~ 3250 4500
NoConn ~ 3250 4400
NoConn ~ 3150 3950
NoConn ~ 3150 3850
NoConn ~ 3150 3750
NoConn ~ 3150 3650
NoConn ~ 3150 3550
NoConn ~ 3150 3450
NoConn ~ 3150 3350
NoConn ~ 3150 3250
NoConn ~ 3150 3150
NoConn ~ 3150 3050
NoConn ~ 3150 2750
NoConn ~ 3150 2650
Text Label 1200 2850 2    60   ~ 0
L_ENC_A
Text Label 1200 2950 2    60   ~ 0
L_ENC_B
Wire Wire Line
	1200 2850 1350 2850
Wire Wire Line
	1350 2950 1200 2950
Text Label 3000 2850 2    60   ~ 0
R_ENC_A
Wire Wire Line
	3000 2850 3150 2850
Text Label 3000 2950 2    60   ~ 0
R_ENC_B
Wire Wire Line
	3000 2950 3150 2950
Text Label 1300 4900 2    60   ~ 0
I2C_Data
Text Label 1300 5000 2    60   ~ 0
I2C_Clk
Text Label 3100 4900 2    60   ~ 0
I2C_Data
Text Label 3100 5000 2    60   ~ 0
I2C_Clk
Wire Wire Line
	1300 4900 1450 4900
Wire Wire Line
	1450 5000 1300 5000
Wire Wire Line
	3100 5000 3250 5000
Wire Wire Line
	3100 4900 3250 4900
NoConn ~ 9400 1900
$Comp
L Screw_Terminal_01x02 J4
U 1 1 5AB2D752
P 7600 1100
F 0 "J4" H 7600 1200 50  0000 C CNN
F 1 "Battery" H 7600 900 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_bornier-2_P5.08mm" H 7600 1100 50  0001 C CNN
F 3 "" H 7600 1100 50  0001 C CNN
	1    7600 1100
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 5AB2D843
P 7850 1250
F 0 "#PWR016" H 7850 1000 50  0001 C CNN
F 1 "GND" H 7850 1100 50  0000 C CNN
F 2 "" H 7850 1250 50  0000 C CNN
F 3 "" H 7850 1250 50  0000 C CNN
	1    7850 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 1200 7900 1200
Wire Wire Line
	7850 1200 7850 1250
$Comp
L +BATT #PWR017
U 1 1 5AB2D94A
P 7850 1050
F 0 "#PWR017" H 7850 900 50  0001 C CNN
F 1 "+BATT" H 7850 1190 50  0000 C CNN
F 2 "" H 7850 1050 50  0001 C CNN
F 3 "" H 7850 1050 50  0001 C CNN
	1    7850 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 1050 7850 1100
Wire Wire Line
	7800 1100 7900 1100
$Comp
L +BATT #PWR018
U 1 1 5AB2DA26
P 8950 1450
F 0 "#PWR018" H 8950 1300 50  0001 C CNN
F 1 "+BATT" H 8950 1590 50  0000 C CNN
F 2 "" H 8950 1450 50  0001 C CNN
F 3 "" H 8950 1450 50  0001 C CNN
	1    8950 1450
	1    0    0    -1  
$EndComp
Connection ~ 7850 1200
$Comp
L PWR_FLAG #FLG019
U 1 1 5AB2DBD3
P 7900 1100
F 0 "#FLG019" H 7900 1175 50  0001 C CNN
F 1 "PWR_FLAG" V 7900 1200 50  0000 L CNN
F 2 "" H 7900 1100 50  0001 C CNN
F 3 "" H 7900 1100 50  0001 C CNN
	1    7900 1100
	0    1    1    0   
$EndComp
Connection ~ 7850 1100
Text Notes 7700 650  0    100  ~ 20
Power
$Comp
L +5V #PWR020
U 1 1 5AB2DD83
P 8650 1050
F 0 "#PWR020" H 8650 900 50  0001 C CNN
F 1 "+5V" H 8650 1190 50  0000 C CNN
F 2 "" H 8650 1050 50  0000 C CNN
F 3 "" H 8650 1050 50  0000 C CNN
	1    8650 1050
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR021
U 1 1 5AB2E2F0
P 9150 1450
F 0 "#PWR021" H 9150 1300 50  0001 C CNN
F 1 "+5V" H 9150 1590 50  0000 C CNN
F 2 "" H 9150 1450 50  0000 C CNN
F 3 "" H 9150 1450 50  0000 C CNN
	1    9150 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 2000 9150 2000
Wire Wire Line
	9150 2000 9150 1450
Wire Notes Line
	7350 500  7350 1750
Wire Notes Line
	6250 1750 8500 1750
Wire Notes Line
	6250 500  6250 2950
Wire Notes Line
	6250 2950 8500 2950
$EndSCHEMATC
