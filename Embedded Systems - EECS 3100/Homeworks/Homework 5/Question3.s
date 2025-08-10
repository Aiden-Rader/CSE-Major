;*******************************************************************
; main.s
; Author: Aiden Rader
; Date Created: 6/18/25
; Last Modified: 6/18/25
; Section Number: 041
; Instructor: Devinder Kaur
; Homework Number: 5
;
; Translate C code into assembly, conditional statements.
;
;*******************************************************************

	AREA    |.text|, CODE, READONLY, ALIGN=2
	THUMB
	EXPORT  Start

Start
loop
		BL init_vars	; Branch to init function for our variables

		CMP r0, r1		; Compare a to b
		BGE check_b     ; If a >= b, skip to next check
		CMP r0, r2      ; Compare a to c
		BGE check_b     ; If a >= c, skip to next check
		MOV r3, r0      ; a < b && a < c; so min = a

		B 	loop		; loop forever

init_vars
		MOV r0,	#4		; a = 4
		MOV r1, #-3		; b = -3
		MOV r2, #0		; c = 0

		BX 	LR			; Back to start branch

check_b
		CMP r1, r0      ; Compare b to a
		BGE else_case   ; If b >= a, skip
		CMP r1, r2      ; Compare b to c
		BGE else_case   ; If b >= c, skip
		MOV r3, r1      ; b < a && b < c; so min = b

		B 	loop		; loop forever

else_case
		MOV r3, r2		; else; so min = c

		B 	loop		; loop forever

		ALIGN			; make sure the end of this section is aligned
		END				; end of file