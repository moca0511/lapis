EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 14 15
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:Conn_01x06_Male J15
U 1 1 61A622DC
P 4700 4150
F 0 "J15" H 4808 4531 50  0000 C CNN
F 1 "Conn_01x06_Male" H 4808 4440 50  0000 C CNN
F 2 "Connector_PinHeader_1.27mm:PinHeader_1x06_P1.27mm_Vertical" H 4700 4150 50  0001 C CNN
F 3 "~" H 4700 4150 50  0001 C CNN
	1    4700 4150
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Female J17
U 1 1 61A627C7
P 6700 4550
F 0 "J17" H 6728 4526 50  0000 L CNN
F 1 "Conn_01x04_Female" H 6728 4435 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 6700 4550 50  0001 C CNN
F 3 "~" H 6700 4550 50  0001 C CNN
	1    6700 4550
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Female J16
U 1 1 61A62B2F
P 6700 3700
F 0 "J16" H 6728 3676 50  0000 L CNN
F 1 "Conn_01x04_Female" H 6728 3585 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 6700 3700 50  0001 C CNN
F 3 "~" H 6700 3700 50  0001 C CNN
	1    6700 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 3950 5000 3950
Wire Wire Line
	4900 4050 5000 4050
Wire Wire Line
	4900 4150 5000 4150
Wire Wire Line
	4900 4250 5000 4250
Wire Wire Line
	4900 4350 5000 4350
Wire Wire Line
	4900 4450 5000 4450
Wire Wire Line
	6500 4450 6350 4450
Wire Wire Line
	6500 4550 6350 4550
Wire Wire Line
	6500 4650 6350 4650
Wire Wire Line
	6500 4750 6350 4750
Wire Wire Line
	6500 3600 6400 3600
Wire Wire Line
	6500 3700 6400 3700
Wire Wire Line
	6500 3800 6400 3800
Wire Wire Line
	6500 3900 6400 3900
Text GLabel 5000 4450 2    50   Input ~ 0
VCC
Text GLabel 5000 4350 2    50   Input ~ 0
SWDIO
Text GLabel 5000 4250 2    50   Input ~ 0
SWCLK
Text GLabel 5000 4150 2    50   Input ~ 0
RX
Text GLabel 5000 4050 2    50   Input ~ 0
TX
Text GLabel 5000 3950 2    50   Input ~ 0
GND
Text GLabel 6350 4750 0    50   Input ~ 0
VCC
Text GLabel 6400 3900 0    50   Input ~ 0
VCC
Text GLabel 6350 4650 0    50   Input ~ 0
GND
Text GLabel 6400 3700 0    50   Input ~ 0
GND
Text GLabel 6350 4550 0    50   Input ~ 0
RX
Text GLabel 6350 4450 0    50   Input ~ 0
TX
Text GLabel 6400 3600 0    50   Input ~ 0
SWDIO
Text GLabel 6400 3800 0    50   Input ~ 0
SWCLK
$EndSCHEMATC
