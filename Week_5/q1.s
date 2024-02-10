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
	LDR R0, =ARR
	LDR R5, [R0]
	LDR R9, =DST	
	STR R5, [R9]		;to store the ARR in DST
	LDRB R5, [R0, #4]
	STRB R5, [R9, #4]
	
	MOV R2, #4
	MOV R3, #0		;i=0
	
L3	MOV R4, R3		;stores min_index
	ADD R5, R3, #1	;j=i+1
	
L2	LDRB R6, [R9, R4]	;a[min]
	LDRB R7, [R9, R5]	;a[j]
	CMP R7, R6
	BHS L1
	MOV R4, R5
	
L1 	ADD R5, #1		;j=j+1
	CMP R5, #5
	BLT L2
	LDRB R6, [R9,R3]	;SWAPPING
	LDRB R7, [R9,R4]
	STRB R6, [R9,R4]
	STRB R7, [R9,R3]
	
	ADD R3, #1
	CMP R3, R2
	BLT L3
STOP B STOP
ARR DCB 1,5,2,8,3
	AREA mydata, DATA, READWRITE
DST DCB 0,0,0,0,0
	END