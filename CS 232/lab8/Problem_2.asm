		AREA 	dj_code,CODE,READONLY
	
START	MOV		R1,#51
		MOV		R2,#187
		
		;reading registers R4 R5
		MOV		R4,R1
		MOV 	R5,R2
		
		;euclid algorithm start
euclid	CMP		R4,R5
		;ensuring R4 > R5
		BGE		noswap
		MOV		R0,R5
		MOV		R5,R4
		MOV		R4,R0
		;subtracting till R4 < R5
noswap	SUBS	R4,R4,R5
		CMP		R4,#00
		;if perfectly divisible, gcd is R5, else loop
		BEQ		found
		BGE		noswap
		ADD 	R4,R4,R5
		B		euclid

		;storing gcd in R3
found	MOV		R3, R5

here 	B		here
		END