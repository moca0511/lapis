EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 14
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
L Device:Q_Photo_NPN Q4
U 1 1 601D23CB
P 5550 3850
AR Path="/5FA82233/601D23CB" Ref="Q4"  Part="1" 
AR Path="/5FA821A9/601D23CB" Ref="Q1"  Part="1" 
AR Path="/5FA82246/601D23CB" Ref="Q3"  Part="1" 
AR Path="/5FA82203/601D23CB" Ref="Q2"  Part="1" 
F 0 "Q4" H 5740 3896 50  0000 L CNN
F 1 "LTR-4206E" H 5740 3805 50  0000 L CNN
F 2 "LED_THT:LED_D3.0mm_Horizontal_O1.27mm_Z2.0mm_IRBlack" H 5750 3950 50  0001 C CNN
F 3 "~" H 5550 3850 50  0001 C CNN
	1    5550 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 3650 5650 3400
$Comp
L power:GND #PWR0130
U 1 1 601D7E50
P 5650 4600
AR Path="/5FA82233/601D7E50" Ref="#PWR0130"  Part="1" 
AR Path="/5FA821A9/601D7E50" Ref="#PWR0115"  Part="1" 
AR Path="/5FA82246/601D7E50" Ref="#PWR0128"  Part="1" 
AR Path="/5FA82203/601D7E50" Ref="#PWR0117"  Part="1" 
F 0 "#PWR0130" H 5650 4350 50  0001 C CNN
F 1 "GND" H 5655 4427 50  0000 C CNN
F 2 "" H 5650 4600 50  0001 C CNN
F 3 "" H 5650 4600 50  0001 C CNN
	1    5650 4600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 601D7E56
P 5650 4400
AR Path="/5FA82233/601D7E56" Ref="R5"  Part="1" 
AR Path="/5FA821A9/601D7E56" Ref="R2"  Part="1" 
AR Path="/5FA82246/601D7E56" Ref="R4"  Part="1" 
AR Path="/5FA82203/601D7E56" Ref="R3"  Part="1" 
F 0 "R5" H 5720 4446 50  0000 L CNN
F 1 "1k" H 5720 4355 50  0000 L CNN
F 2 "Resistor_SMD:R_0201_0603Metric_Pad0.64x0.40mm_HandSolder" V 5580 4400 50  0001 C CNN
F 3 "~" H 5650 4400 50  0001 C CNN
	1    5650 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 4600 5650 4550
Wire Wire Line
	5650 4250 5650 4150
Wire Wire Line
	5650 4150 5850 4150
Connection ~ 5650 4150
Wire Wire Line
	5650 4150 5650 4050
Text HLabel 5850 4150 2    50   Output ~ 0
WALLSENSOR_ADC
$Comp
L power:+3.3V #PWR?
U 1 1 60612AF0
P 5650 3400
AR Path="/5FA81D59/60612AF0" Ref="#PWR?"  Part="1" 
AR Path="/5FA821A9/60612AF0" Ref="#PWR0114"  Part="1" 
AR Path="/5FA82203/60612AF0" Ref="#PWR0116"  Part="1" 
AR Path="/5FA82246/60612AF0" Ref="#PWR0125"  Part="1" 
AR Path="/5FA82233/60612AF0" Ref="#PWR0126"  Part="1" 
F 0 "#PWR0126" H 5650 3250 50  0001 C CNN
F 1 "+3.3V" H 5665 3573 50  0000 C CNN
F 2 "" H 5650 3400 50  0001 C CNN
F 3 "" H 5650 3400 50  0001 C CNN
	1    5650 3400
	1    0    0    -1  
$EndComp
$EndSCHEMATC
