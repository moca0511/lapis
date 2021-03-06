EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 14
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
L lapis-rescue:DRV8835DSSR-SamacSys_Parts IC3
U 1 1 5FB455F8
P 3300 3550
F 0 "IC3" H 4300 3815 50  0000 C CNN
F 1 "DRV8835DSSR" H 4300 3724 50  0000 C CNN
F 2 "DRV8835DSSR" H 5150 3650 50  0001 L CNN
F 3 "http://www.ti.com/general/docs/suppproductinfo.tsp?distId=26&gotoUrl=http%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fdrv8835" H 5150 3550 50  0001 L CNN
F 4 "Motor / Motion / Ignition Controllers & Drivers 1.5A Low Vlt Stepper Motor" H 5150 3450 50  0001 L CNN "Description"
F 5 "0.8" H 5150 3350 50  0001 L CNN "Height"
F 6 "" H 5150 3250 50  0001 L CNN "Mouser Part Number"
F 7 "" H 5150 3150 50  0001 L CNN "Mouser Price/Stock"
F 8 "Texas Instruments" H 5150 3050 50  0001 L CNN "Manufacturer_Name"
F 9 "DRV8835DSSR" H 5150 2950 50  0001 L CNN "Manufacturer_Part_Number"
	1    3300 3550
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0118
U 1 1 5FB4808E
P 5800 3400
F 0 "#PWR0118" H 5800 3250 50  0001 C CNN
F 1 "+3.3V" H 5815 3573 50  0000 C CNN
F 2 "" H 5800 3400 50  0001 C CNN
F 3 "" H 5800 3400 50  0001 C CNN
	1    5800 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 3400 5800 3850
Wire Wire Line
	5800 3850 5300 3850
Wire Wire Line
	5800 3850 5800 3950
Wire Wire Line
	5800 3950 5300 3950
Connection ~ 5800 3850
$Comp
L power:GND #PWR0119
U 1 1 5FB48773
P 5800 4500
F 0 "#PWR0119" H 5800 4250 50  0001 C CNN
F 1 "GND" H 5805 4327 50  0000 C CNN
F 2 "" H 5800 4500 50  0001 C CNN
F 3 "" H 5800 4500 50  0001 C CNN
	1    5800 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 4050 2850 4050
Wire Wire Line
	2850 4050 2850 4400
Wire Wire Line
	2850 4400 5800 4400
Wire Wire Line
	5800 4400 5800 4500
$Comp
L power:+BATT #PWR0120
U 1 1 5FB48FF7
P 2850 3400
F 0 "#PWR0120" H 2850 3250 50  0001 C CNN
F 1 "+BATT" H 2865 3573 50  0000 C CNN
F 2 "" H 2850 3400 50  0001 C CNN
F 3 "" H 2850 3400 50  0001 C CNN
	1    2850 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 3550 2850 3550
Wire Wire Line
	2850 3550 2850 3400
Wire Wire Line
	5300 3550 5350 3550
Wire Wire Line
	5300 3650 5350 3650
Wire Wire Line
	5300 3750 5350 3750
Wire Wire Line
	3300 4150 3250 4150
Wire Wire Line
	3300 3950 3250 3950
Wire Wire Line
	3300 3850 3250 3850
Wire Wire Line
	3300 3750 3250 3750
Wire Wire Line
	3300 3650 3250 3650
Text HLabel 5350 3550 2    50   Input ~ 0
MR_PWM
Text HLabel 5350 3750 2    50   Input ~ 0
ML_PWM
Text HLabel 5350 3650 2    50   Input ~ 0
ML_EN
Text HLabel 3250 4150 0    50   Input ~ 0
MR_EN
Text GLabel 3250 3650 0    50   Output ~ 0
ML1
Text GLabel 3250 3750 0    50   Output ~ 0
ML2
Text GLabel 3250 3850 0    50   Output ~ 0
MR1
Text GLabel 3250 3950 0    50   Output ~ 0
MR2
$Comp
L power:+BATT #PWR0121
U 1 1 5FB4A9ED
P 1800 3400
F 0 "#PWR0121" H 1800 3250 50  0001 C CNN
F 1 "+BATT" H 1815 3573 50  0000 C CNN
F 2 "" H 1800 3400 50  0001 C CNN
F 3 "" H 1800 3400 50  0001 C CNN
	1    1800 3400
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0122
U 1 1 5FB4AEED
P 2300 3400
F 0 "#PWR0122" H 2300 3250 50  0001 C CNN
F 1 "+3.3V" H 2315 3573 50  0000 C CNN
F 2 "" H 2300 3400 50  0001 C CNN
F 3 "" H 2300 3400 50  0001 C CNN
	1    2300 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C8
U 1 1 5FB4B7E1
P 1800 3750
F 0 "C8" H 1915 3796 50  0000 L CNN
F 1 "100u" H 1915 3705 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 1838 3600 50  0001 C CNN
F 3 "~" H 1800 3750 50  0001 C CNN
	1    1800 3750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C9
U 1 1 5FB4BBFF
P 2300 3750
F 0 "C9" H 2415 3796 50  0000 L CNN
F 1 "0.1u" H 2415 3705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0201_0603Metric_Pad0.64x0.40mm_HandSolder" H 2338 3600 50  0001 C CNN
F 3 "~" H 2300 3750 50  0001 C CNN
	1    2300 3750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0123
U 1 1 5FB4C3A0
P 1800 4100
F 0 "#PWR0123" H 1800 3850 50  0001 C CNN
F 1 "GND" H 1805 3927 50  0000 C CNN
F 2 "" H 1800 4100 50  0001 C CNN
F 3 "" H 1800 4100 50  0001 C CNN
	1    1800 4100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0124
U 1 1 5FB4C7BC
P 2300 4100
F 0 "#PWR0124" H 2300 3850 50  0001 C CNN
F 1 "GND" H 2305 3927 50  0000 C CNN
F 2 "" H 2300 4100 50  0001 C CNN
F 3 "" H 2300 4100 50  0001 C CNN
	1    2300 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 3600 2300 3400
Wire Wire Line
	1800 3400 1800 3600
Wire Wire Line
	1800 3900 1800 4100
Wire Wire Line
	2300 3900 2300 4100
Text GLabel 7200 3200 0    50   Input ~ 0
ML1
Text GLabel 7200 3700 0    50   Input ~ 0
ML2
Text GLabel 9050 3200 0    50   Input ~ 0
MR1
Text GLabel 9050 3700 0    50   Input ~ 0
MR2
Wire Wire Line
	7200 3700 8050 3700
Wire Wire Line
	7200 3200 8050 3200
Wire Wire Line
	9050 3200 9900 3200
Wire Wire Line
	9050 3700 9900 3700
$Comp
L Connector_Generic:Conn_01x01 J11
U 1 1 604B4DDD
P 8250 3200
F 0 "J11" H 8330 3242 50  0000 L CNN
F 1 "Conn_01x01" H 8330 3151 50  0000 L CNN
F 2 "TestPoint:TestPoint_THTPad_D1.0mm_Drill0.5mm" H 8250 3200 50  0001 C CNN
F 3 "~" H 8250 3200 50  0001 C CNN
	1    8250 3200
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J12
U 1 1 604B6C17
P 8250 3700
F 0 "J12" H 8330 3742 50  0000 L CNN
F 1 "Conn_01x01" H 8330 3651 50  0000 L CNN
F 2 "TestPoint:TestPoint_THTPad_D1.0mm_Drill0.5mm" H 8250 3700 50  0001 C CNN
F 3 "~" H 8250 3700 50  0001 C CNN
	1    8250 3700
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J13
U 1 1 604B717B
P 10100 3200
F 0 "J13" H 10180 3242 50  0000 L CNN
F 1 "Conn_01x01" H 10180 3151 50  0000 L CNN
F 2 "TestPoint:TestPoint_THTPad_D1.0mm_Drill0.5mm" H 10100 3200 50  0001 C CNN
F 3 "~" H 10100 3200 50  0001 C CNN
	1    10100 3200
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J14
U 1 1 604B75B7
P 10100 3700
F 0 "J14" H 10180 3742 50  0000 L CNN
F 1 "Conn_01x01" H 10180 3651 50  0000 L CNN
F 2 "TestPoint:TestPoint_THTPad_D1.0mm_Drill0.5mm" H 10100 3700 50  0001 C CNN
F 3 "~" H 10100 3700 50  0001 C CNN
	1    10100 3700
	1    0    0    -1  
$EndComp
NoConn ~ 5300 4050
$EndSCHEMATC
