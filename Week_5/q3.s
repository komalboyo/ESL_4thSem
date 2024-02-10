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
	LDR R1, =8
	LDR R2, =7
	LDR R3, =1
	LDR R4, =2
	LDR R5, =4
	LDR R6, =9
	LDR R7, =5
	LDR R8, =3
	LDR R9, =6
	LDR R10, =10
	
	STMIA R13!, {R1-R10}
	
	MOV R3, #0
	MOV R4, #0
	MOV R0, R13
L3	MOV R1, R0
	MOV R2, R0
	SUB R2, #4
	ADD R4, R3, #1
L2	LDMDB R1, {R5}
	LDMDB R2, {R6}
	CMP R5, R6
	BHS L1
	MOV R1, R2
L1	SUB R2, #4
	ADD R4, #1
	CMP R4, #10
	BNE L2
	
	LDMDB R0!, {R7}
	LDMDB R1!, {R8}
	STM R0, {R8}
	STM R1, {R7}
	
	ADD R3, #1
	CMP R3, #9
	BNE L3
	
	LDMDB R13!, {R1-R10}
STOP B STOP
	AREA mydata, DATA, READWRITE
DST DCD 0
	END