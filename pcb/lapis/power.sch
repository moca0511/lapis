EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 14
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
L power:+BATT #PWR?
U 1 1 5FA84D20
P 3900 2150
F 0 "#PWR?" H 3900 2000 50  0001 C CNN
F 1 "+BATT" H 3915 2323 50  0000 C CNN
F 2 "" H 3900 2150 50  0001 C CNN
F 3 "" H 3900 2150 50  0001 C CNN
	1    3900 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_PMOS_SGD Q?
U 1 1 5FA86E2F
P 3250 2300
F 0 "Q?" V 3592 2300 50  0000 C CNN
F 1 "Q_PMOS_SGD" V 3501 2300 50  0000 C CNN
F 2 "" H 3450 2400 50  0001 C CNN
F 3 "~" H 3250 2300 50  0001 C CNN
	1    3250 2300
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 5FA87C7C
P 2950 2500
F 0 "R?" V 2743 2500 50  0000 C CNN
F 1 "R" V 2834 2500 50  0000 C CNN
F 2 "" V 2880 2500 50  0001 C CNN
F 3 "~" H 2950 2500 50  0001 C CNN
	1    2950 2500
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_SPDT SW?
U 1 1 5FA8896F
P 3600 2800
F 0 "SW?" H 3600 3085 50  0000 C CNN
F 1 "SW_SPDT" H 3600 2994 50  0000 C CNN
F 2 "" H 3600 2800 50  0001 C CNN
F 3 "~" H 3600 2800 50  0001 C CNN
	1    3600 2800
	1    0    0    -1  
$EndComp
$EndSCHEMATC
