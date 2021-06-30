EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 13 14
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
L power:GND #PWR0171
U 1 1 6027EF91
P 5950 3400
F 0 "#PWR0171" H 5950 3150 50  0001 C CNN
F 1 "GND" H 5955 3227 50  0000 C CNN
F 2 "" H 5950 3400 50  0001 C CNN
F 3 "" H 5950 3400 50  0001 C CNN
	1    5950 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C32
U 1 1 6027F320
P 5950 3100
F 0 "C32" H 6065 3146 50  0000 L CNN
F 1 "10u" H 6065 3055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric_Pad0.74x0.62mm_HandSolder" H 5988 2950 50  0001 C CNN
F 3 "~" H 5950 3100 50  0001 C CNN
	1    5950 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 2000 7200 2300
Wire Wire Line
	7200 2000 7300 2000
Wire Wire Line
	7300 2000 7300 2300
Wire Wire Line
	7400 2000 7400 2300
Wire Wire Line
	7300 2000 7400 2000
Connection ~ 7300 2000
Wire Wire Line
	7100 1850 7100 2000
$Comp
L power:+3.3V #PWR0172
U 1 1 6027EDD9
P 7100 1850
F 0 "#PWR0172" H 7100 1700 50  0001 C CNN
F 1 "+3.3V" H 7115 2023 50  0000 C CNN
F 2 "" H 7100 1850 50  0001 C CNN
F 3 "" H 7100 1850 50  0001 C CNN
	1    7100 1850
	1    0    0    -1  
$EndComp
$Comp
L MCU_ST_STM32F4:STM32F411CEUx U1
U 1 1 6027E48E
P 7300 3800
F 0 "U1" H 7300 4800 50  0000 C CNN
F 1 "STM32F411CEUx" H 7350 4700 50  0000 C CNN
F 2 "Package_DFN_QFN:QFN-48-1EP_7x7mm_P0.5mm_EP5.6x5.6mm" H 6700 2300 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00115249.pdf" H 7300 3800 50  0001 C CNN
	1    7300 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 2000 7100 2000
Connection ~ 7200 2000
Connection ~ 7100 2000
Wire Wire Line
	7100 2000 7100 2300
Wire Wire Line
	4050 2350 4050 2500
$Comp
L power:+3.3V #PWR0173
U 1 1 60283FDF
P 4050 2350
F 0 "#PWR0173" H 4050 2200 50  0001 C CNN
F 1 "+3.3V" H 4065 2523 50  0000 C CNN
F 2 "" H 4050 2350 50  0001 C CNN
F 3 "" H 4050 2350 50  0001 C CNN
	1    4050 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C29
U 1 1 60283FE5
P 4050 2650
F 0 "C29" H 4165 2696 50  0000 L CNN
F 1 "0.1u" H 4165 2605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0201_0603Metric_Pad0.64x0.40mm_HandSolder" H 4088 2500 50  0001 C CNN
F 3 "~" H 4050 2650 50  0001 C CNN
	1    4050 2650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0174
U 1 1 60283FEB
P 4050 3050
F 0 "#PWR0174" H 4050 2800 50  0001 C CNN
F 1 "GND" H 4055 2877 50  0000 C CNN
F 2 "" H 4050 3050 50  0001 C CNN
F 3 "" H 4050 3050 50  0001 C CNN
	1    4050 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 2800 4050 3050
Wire Wire Line
	3700 2350 3700 2500
$Comp
L power:+3.3V #PWR0175
U 1 1 602843B7
P 3700 2350
F 0 "#PWR0175" H 3700 2200 50  0001 C CNN
F 1 "+3.3V" H 3715 2523 50  0000 C CNN
F 2 "" H 3700 2350 50  0001 C CNN
F 3 "" H 3700 2350 50  0001 C CNN
	1    3700 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C28
U 1 1 602843BD
P 3700 2650
F 0 "C28" H 3815 2696 50  0000 L CNN
F 1 "0.1u" H 3815 2605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0201_0603Metric_Pad0.64x0.40mm_HandSolder" H 3738 2500 50  0001 C CNN
F 3 "~" H 3700 2650 50  0001 C CNN
	1    3700 2650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0176
U 1 1 602843C3
P 3700 3050
F 0 "#PWR0176" H 3700 2800 50  0001 C CNN
F 1 "GND" H 3705 2877 50  0000 C CNN
F 2 "" H 3700 3050 50  0001 C CNN
F 3 "" H 3700 3050 50  0001 C CNN
	1    3700 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 2800 3700 3050
Wire Wire Line
	3350 2350 3350 2500
$Comp
L power:+3.3V #PWR0177
U 1 1 602847E0
P 3350 2350
F 0 "#PWR0177" H 3350 2200 50  0001 C CNN
F 1 "+3.3V" H 3365 2523 50  0000 C CNN
F 2 "" H 3350 2350 50  0001 C CNN
F 3 "" H 3350 2350 50  0001 C CNN
	1    3350 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C26
U 1 1 602847E6
P 3350 2650
F 0 "C26" H 3465 2696 50  0000 L CNN
F 1 "0.1u" H 3465 2605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0201_0603Metric_Pad0.64x0.40mm_HandSolder" H 3388 2500 50  0001 C CNN
F 3 "~" H 3350 2650 50  0001 C CNN
	1    3350 2650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0178
U 1 1 602847EC
P 3350 3050
F 0 "#PWR0178" H 3350 2800 50  0001 C CNN
F 1 "GND" H 3355 2877 50  0000 C CNN
F 2 "" H 3350 3050 50  0001 C CNN
F 3 "" H 3350 3050 50  0001 C CNN
	1    3350 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 2800 3350 3050
Wire Wire Line
	3000 2350 3000 2500
$Comp
L power:+3.3V #PWR0179
U 1 1 60284C69
P 3000 2350
F 0 "#PWR0179" H 3000 2200 50  0001 C CNN
F 1 "+3.3V" H 3015 2523 50  0000 C CNN
F 2 "" H 3000 2350 50  0001 C CNN
F 3 "" H 3000 2350 50  0001 C CNN
	1    3000 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C24
U 1 1 60284C6F
P 3000 2650
F 0 "C24" H 3115 2696 50  0000 L CNN
F 1 "10u" H 3115 2605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric_Pad0.74x0.62mm_HandSolder" H 3038 2500 50  0001 C CNN
F 3 "~" H 3000 2650 50  0001 C CNN
	1    3000 2650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0180
U 1 1 60284C75
P 3000 3050
F 0 "#PWR0180" H 3000 2800 50  0001 C CNN
F 1 "GND" H 3005 2877 50  0000 C CNN
F 2 "" H 3000 3050 50  0001 C CNN
F 3 "" H 3000 3050 50  0001 C CNN
	1    3000 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 2800 3000 3050
Wire Wire Line
	5950 2900 5950 2950
Wire Wire Line
	5950 3250 5950 3400
$Comp
L power:GND #PWR0181
U 1 1 60294F29
P 7100 5750
F 0 "#PWR0181" H 7100 5500 50  0001 C CNN
F 1 "GND" H 7105 5577 50  0000 C CNN
F 2 "" H 7100 5750 50  0001 C CNN
F 3 "" H 7100 5750 50  0001 C CNN
	1    7100 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 5400 7100 5650
Wire Wire Line
	7200 5400 7200 5650
Wire Wire Line
	7200 5650 7100 5650
Connection ~ 7100 5650
Wire Wire Line
	7100 5650 7100 5750
Wire Wire Line
	7300 5400 7300 5650
Wire Wire Line
	7300 5650 7200 5650
Connection ~ 7200 5650
Wire Wire Line
	7400 5400 7400 5650
Wire Wire Line
	7400 5650 7300 5650
Connection ~ 7300 5650
Wire Wire Line
	7500 5400 7500 5650
Wire Wire Line
	7500 5650 7400 5650
Connection ~ 7400 5650
Wire Wire Line
	7500 2300 7500 1850
Wire Wire Line
	3350 3800 3350 3950
$Comp
L Device:C C27
U 1 1 6029CC4B
P 3350 4100
F 0 "C27" H 3465 4146 50  0000 L CNN
F 1 "0.1u" H 3465 4055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0201_0603Metric_Pad0.64x0.40mm_HandSolder" H 3388 3950 50  0001 C CNN
F 3 "~" H 3350 4100 50  0001 C CNN
	1    3350 4100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0183
U 1 1 6029CC51
P 3350 4500
F 0 "#PWR0183" H 3350 4250 50  0001 C CNN
F 1 "GND" H 3355 4327 50  0000 C CNN
F 2 "" H 3350 4500 50  0001 C CNN
F 3 "" H 3350 4500 50  0001 C CNN
	1    3350 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 4250 3350 4500
Wire Wire Line
	3000 3800 3000 3950
$Comp
L Device:C C25
U 1 1 6029CC5F
P 3000 4100
F 0 "C25" H 3115 4146 50  0000 L CNN
F 1 "10u" H 3115 4055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric_Pad0.74x0.62mm_HandSolder" H 3038 3950 50  0001 C CNN
F 3 "~" H 3000 4100 50  0001 C CNN
	1    3000 4100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0184
U 1 1 6029CC65
P 3000 4500
F 0 "#PWR0184" H 3000 4250 50  0001 C CNN
F 1 "GND" H 3005 4327 50  0000 C CNN
F 2 "" H 3000 4500 50  0001 C CNN
F 3 "" H 3000 4500 50  0001 C CNN
	1    3000 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 4250 3000 4500
Wire Wire Line
	6600 3100 6550 3100
Wire Wire Line
	6600 3400 6550 3400
Wire Wire Line
	6600 3500 6550 3500
Wire Wire Line
	6600 3600 6550 3600
Wire Wire Line
	6600 4200 6550 4200
Wire Wire Line
	6600 4300 6550 4300
Wire Wire Line
	6600 4400 6550 4400
Wire Wire Line
	6600 4500 6550 4500
Wire Wire Line
	6600 4600 6550 4600
Wire Wire Line
	6600 4700 6550 4700
Wire Wire Line
	6600 4800 6550 4800
Wire Wire Line
	6600 4900 6550 4900
Wire Wire Line
	6600 5000 6550 5000
Wire Wire Line
	6600 5100 6550 5100
Wire Wire Line
	6600 5200 6550 5200
Wire Wire Line
	7900 3700 7950 3700
Wire Wire Line
	7900 3800 7950 3800
Wire Wire Line
	7900 3900 7950 3900
Wire Wire Line
	7900 4000 7950 4000
Wire Wire Line
	7900 4100 7950 4100
Wire Wire Line
	7900 4200 7950 4200
Wire Wire Line
	7900 4300 7950 4300
Wire Wire Line
	7900 4400 7950 4400
Wire Wire Line
	7900 4600 7950 4600
Wire Wire Line
	7900 4700 7950 4700
NoConn ~ 7900 4500
NoConn ~ 7900 4800
NoConn ~ 7900 4900
NoConn ~ 7900 5000
NoConn ~ 7900 5100
NoConn ~ 6600 4100
NoConn ~ 6600 4000
NoConn ~ 6600 3900
Text HLabel 6550 4200 0    50   Output ~ 0
LED_LSRF
Text HLabel 6550 4300 0    50   Output ~ 0
LED_LFRS
Text HLabel 6550 4400 0    50   Output ~ 0
MR_PWM
Text HLabel 6550 4500 0    50   Output ~ 0
MR_EN
Text HLabel 6550 4600 0    50   Output ~ 0
ML_PWM
Text HLabel 6550 4700 0    50   Output ~ 0
ML_EN
Text HLabel 6550 4800 0    50   Output ~ 0
ENC_SCK
Text HLabel 6550 4900 0    50   Output ~ 0
ENC_CS_R
Text HLabel 6550 5000 0    50   Output ~ 0
ENC_CS_L
Text HLabel 6550 5100 0    50   Input ~ 0
ENC_MISO
Text HLabel 6550 5200 0    50   Output ~ 0
ENC_MOSI
Text HLabel 7950 3700 2    50   Input ~ 0
WALLSENSOR_RS
Text HLabel 7950 3800 2    50   Input ~ 0
WALLSENSOR_RF
Text HLabel 7950 3900 2    50   Input ~ 0
WALLSENSOR_LF
Text HLabel 7950 4000 2    50   Input ~ 0
WALLSENSOR_LS
Text HLabel 7950 4100 2    50   Input ~ 0
BATTERY
Text HLabel 7950 4200 2    50   Output ~ 0
IMU_SCK
Text HLabel 7950 4300 2    50   Input ~ 0
IMU_MISO
Text HLabel 7950 4400 2    50   Output ~ 0
IMU_MOSI
Wire Wire Line
	5950 2900 6600 2900
Wire Wire Line
	6600 3200 6550 3200
Wire Wire Line
	6600 2700 6550 2700
Wire Wire Line
	6600 2500 5550 2500
Wire Wire Line
	5550 2500 5550 2950
$Comp
L Device:C C31
U 1 1 603084B7
P 5550 3100
F 0 "C31" H 5665 3146 50  0000 L CNN
F 1 "0.1u" H 5665 3055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0201_0603Metric_Pad0.64x0.40mm_HandSolder" H 5588 2950 50  0001 C CNN
F 3 "~" H 5550 3100 50  0001 C CNN
	1    5550 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 3400 5550 3250
$Comp
L power:GND #PWR0187
U 1 1 6030B435
P 5550 3400
F 0 "#PWR0187" H 5550 3150 50  0001 C CNN
F 1 "GND" H 5555 3227 50  0000 C CNN
F 2 "" H 5550 3400 50  0001 C CNN
F 3 "" H 5550 3400 50  0001 C CNN
	1    5550 3400
	1    0    0    -1  
$EndComp
Text HLabel 6550 3800 0    50   Output ~ 0
IMU_CS
Wire Wire Line
	6600 3800 6550 3800
Text HLabel 6550 2700 0    50   Input ~ 0
SW
Text HLabel 6550 3100 0    50   Output ~ 0
LED0
Text HLabel 6550 3200 0    50   Input ~ 0
SW
Text HLabel 6550 3400 0    50   Output ~ 0
LED3
Text HLabel 6550 3500 0    50   Output ~ 0
LED2
Text HLabel 6550 3600 0    50   Output ~ 0
LED1
Text HLabel 7950 4600 2    50   Output ~ 0
TX
Text HLabel 7950 4700 2    50   Input ~ 0
RX
Wire Wire Line
	4450 2800 4450 3050
$Comp
L power:GND #PWR0188
U 1 1 6028359D
P 4450 3050
F 0 "#PWR0188" H 4450 2800 50  0001 C CNN
F 1 "GND" H 4455 2877 50  0000 C CNN
F 2 "" H 4450 3050 50  0001 C CNN
F 3 "" H 4450 3050 50  0001 C CNN
	1    4450 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C30
U 1 1 60282CB5
P 4450 2650
F 0 "C30" H 4565 2696 50  0000 L CNN
F 1 "0.1u" H 4565 2605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0201_0603Metric_Pad0.64x0.40mm_HandSolder" H 4488 2500 50  0001 C CNN
F 3 "~" H 4450 2650 50  0001 C CNN
	1    4450 2650
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0189
U 1 1 60282A15
P 4450 2350
F 0 "#PWR0189" H 4450 2200 50  0001 C CNN
F 1 "+3.3V" H 4465 2523 50  0000 C CNN
F 2 "" H 4450 2350 50  0001 C CNN
F 3 "" H 4450 2350 50  0001 C CNN
	1    4450 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 2350 4450 2500
$Comp
L power:+3.3V #PWR0129
U 1 1 6060E33D
P 3350 3800
F 0 "#PWR0129" H 3350 3650 50  0001 C CNN
F 1 "+3.3V" H 3365 3973 50  0000 C CNN
F 2 "" H 3350 3800 50  0001 C CNN
F 3 "" H 3350 3800 50  0001 C CNN
	1    3350 3800
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0135
U 1 1 6060F828
P 3000 3800
F 0 "#PWR0135" H 3000 3650 50  0001 C CNN
F 1 "+3.3V" H 3015 3973 50  0000 C CNN
F 2 "" H 3000 3800 50  0001 C CNN
F 3 "" H 3000 3800 50  0001 C CNN
	1    3000 3800
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0137
U 1 1 60610CD6
P 7500 1850
F 0 "#PWR0137" H 7500 1700 50  0001 C CNN
F 1 "+3.3V" H 7515 2023 50  0000 C CNN
F 2 "" H 7500 1850 50  0001 C CNN
F 3 "" H 7500 1850 50  0001 C CNN
	1    7500 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 5200 7950 5200
Text HLabel 7950 5200 2    50   Output ~ 0
SPEAKER
$EndSCHEMATC