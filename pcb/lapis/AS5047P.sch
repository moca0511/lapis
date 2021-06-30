EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 11 14
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
L lapis-rescue:AS5047P-ATSM-SamacSys_Parts IC2
U 1 1 5FB26737
P 3700 4050
AR Path="/5FA82269/5FB26737" Ref="IC2"  Part="1" 
AR Path="/5FA82159/5FB26737" Ref="IC1"  Part="1" 
F 0 "IC1" H 4300 4315 50  0000 C CNN
F 1 "AS5047P-ATSM" H 4300 4224 50  0000 C CNN
F 2 "SOP65P640X120-14N" H 4750 4150 50  0001 L CNN
F 3 "http://ams.com/eng/content/download/725051/1853902/379375" H 4750 4050 50  0001 L CNN
F 4 "Board Mount Hall Effect / Magnetic Sensors 14 bit core res Up to 28krpm" H 4750 3950 50  0001 L CNN "Description"
F 5 "1.2" H 4750 3850 50  0001 L CNN "Height"
F 6 "985-AS5047P-ATSM" H 4750 3750 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.co.uk/ProductDetail/ams/AS5047P-ATSM?qs=cGEy3R83DS8fzNOVLHtOgg%3D%3D" H 4750 3650 50  0001 L CNN "Mouser Price/Stock"
F 8 "ams" H 4750 3550 50  0001 L CNN "Manufacturer_Name"
F 9 "AS5047P-ATSM" H 4750 3450 50  0001 L CNN "Manufacturer_Part_Number"
	1    3700 4050
	1    0    0    -1  
$EndComp
NoConn ~ 4900 4650
NoConn ~ 3700 4650
NoConn ~ 3700 4550
NoConn ~ 4900 4550
NoConn ~ 4900 4450
NoConn ~ 4900 4050
$Comp
L Device:C C7
U 1 1 5FB3B10A
P 6650 4300
AR Path="/5FA82269/5FB3B10A" Ref="C7"  Part="1" 
AR Path="/5FA82159/5FB3B10A" Ref="C6"  Part="1" 
F 0 "C6" H 6765 4346 50  0000 L CNN
F 1 "0.1u" H 6765 4255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0201_0603Metric_Pad0.64x0.40mm_HandSolder" H 6688 4150 50  0001 C CNN
F 3 "~" H 6650 4300 50  0001 C CNN
	1    6650 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 4150 6650 3950
Wire Wire Line
	6650 4450 6650 4700
Wire Wire Line
	4900 4250 4950 4250
Wire Wire Line
	4900 4150 5000 4150
Wire Wire Line
	4900 4350 4950 4350
Wire Wire Line
	4950 4350 4950 4250
Connection ~ 4950 4250
Wire Wire Line
	4950 4250 5000 4250
Wire Wire Line
	3700 4450 3550 4450
Wire Wire Line
	3700 4050 3550 4050
Wire Wire Line
	3700 4150 3550 4150
Wire Wire Line
	3700 4250 3550 4250
Wire Wire Line
	3700 4350 3550 4350
Wire Wire Line
	8050 4600 7950 4600
Wire Wire Line
	8050 4700 7950 4700
Wire Wire Line
	9500 4600 9600 4600
Wire Wire Line
	9500 4700 9600 4700
Text HLabel 7950 4600 0    50   Input ~ 0
ENC_CS
Text HLabel 7950 4700 0    50   Input ~ 0
ENC_SCK
Text HLabel 9600 4700 2    50   Output ~ 0
ENC_MISO
Text HLabel 9600 4600 2    50   Input ~ 0
ENC_MOSI
Wire Wire Line
	8050 3600 7950 3600
Wire Wire Line
	8050 3700 7950 3700
Wire Wire Line
	8050 3800 7950 3800
Wire Wire Line
	9500 3600 9600 3600
Wire Wire Line
	9500 3700 9600 3700
Wire Wire Line
	9500 3800 9600 3800
$Comp
L power:+3.3V #PWR0161
U 1 1 60388650
P 7550 4250
AR Path="/5FA82269/60388650" Ref="#PWR0161"  Part="1" 
AR Path="/5FA82159/60388650" Ref="#PWR0159"  Part="1" 
F 0 "#PWR0161" H 7550 4100 50  0001 C CNN
F 1 "+3.3V" H 7565 4423 50  0000 C CNN
F 2 "" H 7550 4250 50  0001 C CNN
F 3 "" H 7550 4250 50  0001 C CNN
	1    7550 4250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0162
U 1 1 60388A97
P 10300 5150
AR Path="/5FA82269/60388A97" Ref="#PWR0162"  Part="1" 
AR Path="/5FA82159/60388A97" Ref="#PWR0160"  Part="1" 
F 0 "#PWR0162" H 10300 4900 50  0001 C CNN
F 1 "GND" H 10305 4977 50  0000 C CNN
F 2 "" H 10300 5150 50  0001 C CNN
F 3 "" H 10300 5150 50  0001 C CNN
	1    10300 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 4250 7550 4500
Wire Wire Line
	7550 4500 8050 4500
Wire Wire Line
	10300 4500 10300 5150
Wire Wire Line
	9500 4500 10300 4500
Text GLabel 7950 3600 0    50   Output ~ 0
ENC_VCC_
Text GLabel 7950 3700 0    50   Output ~ 0
ENC_CS_
Text GLabel 7950 3800 0    50   Output ~ 0
ENC_SCK_
Text GLabel 9600 3600 2    50   Output ~ 0
ENC_GND_
Text GLabel 9600 3700 2    50   Output ~ 0
ENC_MOSI_
Text GLabel 9600 3800 2    50   Input ~ 0
ENC_MISO_
Text GLabel 5000 4150 2    50   Output ~ 0
ENC_GND_
$Comp
L Connector_Generic:Conn_01x03 J6
U 1 1 6038B21F
P 8250 3700
AR Path="/5FA82269/6038B21F" Ref="J6"  Part="1" 
AR Path="/5FA82159/6038B21F" Ref="J1"  Part="1" 
F 0 "J1" H 8330 3742 50  0000 L CNN
F 1 "Conn_01x03" H 8330 3651 50  0000 L CNN
F 2 "SamacSys_Parts:ENC_connector" H 8250 3700 50  0001 C CNN
F 3 "~" H 8250 3700 50  0001 C CNN
	1    8250 3700
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J8
U 1 1 6038CA33
P 9300 3700
AR Path="/5FA82269/6038CA33" Ref="J8"  Part="1" 
AR Path="/5FA82159/6038CA33" Ref="J4"  Part="1" 
F 0 "J4" H 9380 3742 50  0000 L CNN
F 1 "Conn_01x03" H 9380 3651 50  0000 L CNN
F 2 "SamacSys_Parts:ENC_connector" H 9300 3700 50  0001 C CNN
F 3 "~" H 9300 3700 50  0001 C CNN
	1    9300 3700
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J7
U 1 1 6038E26F
P 8250 4600
AR Path="/5FA82269/6038E26F" Ref="J7"  Part="1" 
AR Path="/5FA82159/6038E26F" Ref="J2"  Part="1" 
F 0 "J2" H 8330 4642 50  0000 L CNN
F 1 "Conn_01x03" H 8330 4551 50  0000 L CNN
F 2 "SamacSys_Parts:ENC_connector" H 8250 4600 50  0001 C CNN
F 3 "~" H 8250 4600 50  0001 C CNN
	1    8250 4600
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J9
U 1 1 6038E8C0
P 9300 4600
AR Path="/5FA82269/6038E8C0" Ref="J9"  Part="1" 
AR Path="/5FA82159/6038E8C0" Ref="J5"  Part="1" 
F 0 "J5" H 9380 4642 50  0000 L CNN
F 1 "Conn_01x03" H 9380 4551 50  0000 L CNN
F 2 "SamacSys_Parts:ENC_connector" H 9300 4600 50  0001 C CNN
F 3 "~" H 9300 4600 50  0001 C CNN
	1    9300 4600
	-1   0    0    1   
$EndComp
Text GLabel 6650 3950 0    50   Output ~ 0
ENC_VCC_
Text GLabel 6650 4700 0    50   Output ~ 0
ENC_GND_
Text GLabel 5000 4250 2    50   Output ~ 0
ENC_VCC_
Text GLabel 3550 4050 0    50   Output ~ 0
ENC_CS_
Text GLabel 3550 4150 0    50   Output ~ 0
ENC_SCK_
Text GLabel 3550 4250 0    50   Output ~ 0
ENC_MISO_
Text GLabel 3550 4350 0    50   Output ~ 0
ENC_MOSI_
Text GLabel 3550 4450 0    50   Output ~ 0
ENC_GND_
$EndSCHEMATC
