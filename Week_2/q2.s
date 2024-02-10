	AREA RESET, DATA, READONLY
	EXPORT __Vectors
__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0, =SRC
	LDR R1, =DST
	LDR R2, [R0]
	STR R2, [R1]
STOP B STOP
	AREA mydata1, DATA, READONLY
SRC DCD 100
	AREA mydata2, DATA, READWRITE
DST DCD 0
	END