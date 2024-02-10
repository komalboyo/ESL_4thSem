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
	MOV R2, #10
	ADD R3, R0, #36
L1	LDR R4, [R3], #-4
	STR R4, [R1], #4
	SUBS R2, #1
	;ADDS R2, #1
	;CMP R2, #10
	BNE L1
STOP B STOP
SRC DCD 1,2,3,4,5,6,7,8,9,10
	AREA mydata, DATA, READWRITE
DST DCD 0
	END