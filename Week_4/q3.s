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
	LDR R0, =SRC
	LDR R1, =DST1
	LDR R2, [R0]
DIV	CMP R2, #10				;COMPARES IT TO 10
	BCC LOOP				;GOES TO LOOP WHEN R2<10 AS CARRY IS INVERSE OF BORROW
	SUBS R2, #10
	ADD R3, #1				;QUOTIENT
	B DIV
LOOP	STRB R2, [R1], #1
	MOV R2, R3				;MOVING THE QUOTIENT TO THE NEW DIVISION LOOP
	MOV R3, #0
	CMP R2, #10
	BCS DIV
	STRB R2, [R1]
	;LDR R4, =DST
	;SUBS R4,R1,R4				;R4 STORES THE NUMBER OF BYTES TO BE PACKED
	BL UNP
STOP B STOP
UNP	LDR R0,=DST1
	LDR R5, =DST2
	MOV R2, #2				;HOLDS THE NUMBER OF BYTES TO BE PACKED
L1	LDRB R3, [R0], #1
	LDRB R4, [R0], #1
	LSL R4, #4
	ADD R3,R4
	STRB R3, [R5], #1
	SUBS R2, #1
	BNE L1
	BX LR
SRC DCD 0XAA
	AREA mydata, DATA, READWRITE
DST1 DCD 0
DST2 DCD 0
	END 