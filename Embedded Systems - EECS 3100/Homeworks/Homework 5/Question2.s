;*******************************************************************
; main.s
; Author: Aiden Rader
; Date Created: 6/18/25
; Last Modified: 6/18/25
; Section Number: 041
; Instructor: Devinder Kaur
; Homework Number: 5
;
; Calculates a function f(x) where:
;     f(x) = -1 if x < 0
;     f(x) =  0 if x == 0
;     f(x) =  1 if x > 0
;
;*******************************************************************

	AREA    |.text|, CODE, READONLY, ALIGN=2
	THUMB
	EXPORT  Start

Start
loop
		BL init_func	; Branch to a setup function that sets up our variables

		CBZ r0, res_zero; If r0 = 0, goto zero branch
		CMP r0, r1		; Set the comparison from random int to 0
		BLT res_neg		; if less then 0 then goto neg branch
		CMP r0, r1
		BGT res_pos		; if greater then 0 then goto pos branch

		B loop			; Loop forever

init_func
		MOV r0, #0		; Init our x value at a specific number (i.e. x)
		MOV r1, #0		; Set a comparison variable (i.e. what x is equal to)
		BX LR

res_zero
		MOV r2, #0		; Set variable to 0
		B loop

res_pos
		MOV r2, #1		; Set variable to 1
		B loop

res_neg
		MOV r2, #-1		; Set variable to -1
		B loop

		ALIGN				; make sure the end of this section is aligned
		END					; end of file