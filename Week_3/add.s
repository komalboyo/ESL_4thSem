	AREA RESET, DATA, READONLY
	EXPORT __Vectors
__Vectors
	DCD 0X10001000
	DCD Reset_Handler
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0, =VAL1
	LDR R1, =VAL2
	LDR R5, =DST
	LDR R2, [R0],#4
	LDR R3, [R1],#4
	ADDS R4, R2, R3
	STR R4, [R5],#4
	LDR R2, [R0]
	LDR R3, [R1]
	ADCS R4, R2, R3
	STR R4, [R5]
STOP B STOP
VAL1 DCD 0XFFFF1111, 0X12341111
VAL2 DCD 0XABCD1234, 0X12345678
	AREA mydata, DATA, READWRITE
DST DCD 0,0
	END