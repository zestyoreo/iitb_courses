		AREA	dj_code, CODE, READONLY
		
		;Storing data at required addresses
START	ADR		R0,source_array ;adjacency matrix
		LDR		R1,=0x40000000
		MOV		R2,#01  ;source vertex
		SUBS	R2,R2,#01
		STRB	R2,[R1]
		LDR		R1,=0x30000000
		MOV		R2,#09  ;total vertices
		STRB	R2,[R1]
		LDR		R1,=0x60000000
		MOV		R3,R2
loop1	MOV		R4,R2
loop2	LDRB	R5,[R0],#01
		STRB	R5,[R1],#01
		SUBS	R4,R4,#01
		BNE		loop2
		SUBS	R3,R3,#01
		BNE		loop1
		
		;reading meta data
		LDR		R0,=0x30000000
		LDRB	R1,[R0] ;N
		LDR		R0,=0x40000000
		LDRB	R2,[R0] ;source
		LDR		R0,=0x60000000	;matrix
		LDR		R3,=0x70000000 	;distance array
		LDR		R4,=0x50000000	;shortest tree path
		
		MOV		R5,#00
		MOV		R6,#0xFF
		MOV		R7,#0x00
loop3	STRB	R6,[R3,R5]
		STRB	R7,[R4,R5]
		ADD		R5,R5,#01
		CMP		R5,R1
		BLT		loop3
		
		MOV		R5,#00
		STRB	R5,[R3,R2]
		MOV		R5,#00
		ADD		R5,R5,#01
		;finding shortest distance
algo 	MOV		R6,#0xFF ;min index
		MOV		R7,#0xFF ;min dist
		MOV		R8,#00	 
		;min distance vertex
min		LDRB	R9,[R4,R8]
		CMP		R9,#00
		BNE		skip
		LDRB	R9,[R3,R8]
		CMP		R9,R7
		BGT		skip
		MOV		R7,R9
		MOV		R6,R8
skip	ADD		R8,R8,#01
		CMP		R8,R1
		BLT		min
		;mark as processed
		MOV		R7,#01
		STRB	R7,[R4,R6]
		;update shortest dist tree
		MOV		R7,#00
update	LDRB	R8,[R4,R7]
		CMP		R8,#00
		BNE		skipU
		LDRB	R8,[R3,R6]
		CMP		R8,#0xFF
		BEQ		skipU
		MUL		R9,R6,R1
		ADD		R9,R9,R7
		LDRB	R10,[R0,R9]
		CMP		R10,#00
		BLE		skipU
		ADD		R11,R10,R8
		LDRB	R12,[R3,R7]
		CMP		R11,R12
		BGE		skipU
		STRB	R11,[R3,R7]
skipU	ADD		R7,R7,#01
		CMP		R7,R1
		BLT		update
		ADD		R5,R5,#01
		CMP		R5,R1
		BLT		algo
		
here 	B		here

source_array	DCB		0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x08,0x00
				DCB		0x04,0x00,0x08,0x00,0x00,0x00,0x00,0x0B,0x00
				DCB		0x00,0x08,0x00,0x07,0x00,0x04,0x00,0x00,0x02
				DCB		0x00,0x00,0x07,0x00,0x09,0x0E,0x00,0x00,0x00
				DCB		0x00,0x00,0x00,0x09,0x00,0x0A,0x00,0x00,0x00
				DCB		0x00,0x00,0x04,0x0E,0x0A,0x00,0x02,0x00,0x00
				DCB		0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x01,0x06
				DCB		0x08,0x0B,0x00,0x00,0x00,0x00,0x01,0x00,0x07
				DCB		0x00,0x00,0x02,0x00,0x00,0x00,0x06,0x07,0x00

		END