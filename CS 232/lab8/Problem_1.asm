		AREA 	dj_code,CODE,READONLY
	
		;read N numbers
START	ADR		R0,source_array 
		LDR 	R1,=0x40000000
		LDRB	R2,[R0],#01
		STRB 	R2,[R1],#01
		
		;reading array
read	LDRB	R3,[R0],#01
		STRB	R3,[R1],#01
		SUBS	R2,R2,#01	
		BNE		read		
		;bubble sort
		LDR 	R0,=0x40000000
		LDRB	R1,[R0]
		SUBS 	R1,R1,#01
		;bubble sort loop
bubble	MOV		R2,R1
		MOV		R3,R0
		ADD		R3,R3,#01
		;till N-i'th element
loop	LDRB	R4,[R3],#01
		LDRB	R5,[R3]
		CMP		R4, R5
		BLE		noswap
		;swapping
		STRB	R4,[R3],#-01
		STRB	R5,[R3],#01
		;decrementing loop counters
noswap	SUBS	R2,R2,#01
		BNE		loop
		SUBS 	R1,R1,#01
		BNE		bubble
		
		
here 	B		here
		
source_array	DCB		0x09,0x04,0x02,0x03,0x09,0x06,0x07,0x01,0x05,0x08
		END