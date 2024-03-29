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
	LDR R1, =DST
	LDR R2,[R0]
	SUB R2,#2		;COUNTER DECREMENTED BY 2
	MOV R3, #1
	MOV R4, #1
	STR R3, [R1],#4
	STR R4,[R1],#4
L1	ADD R5,R4,R3
	STR R5,[R1],#4
	MOV R3, R4
	MOV R4,R5
	SUBS R2,#1
	BCS L1
STOP B STOP
N DCD 10
	AREA mydata, DATA, READWRITE
DST DCD 0
	END
