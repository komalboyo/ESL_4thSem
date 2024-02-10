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
	LDR R0, =N
	LDR R1, [R0]
	LDR R2, =DST
	MLA R4,R1, R1,R1
	LSR R4, R4, #1
	STR R4,[R2]
STOP B STOP
N DCD 10
	AREA mydata, DATA, READWRITE
DST DCD 0
	END
