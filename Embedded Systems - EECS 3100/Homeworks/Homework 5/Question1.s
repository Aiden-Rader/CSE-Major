;*******************************************************************
; main.s
; Author: Aiden Rader
; Date Created: 6/18/25
; Last Modified: 6/18/25
; Section Number: 041
; Instructor: Devinder Kaur
; Homework Number: 5
;
; Define an array with 10 unsigned integers in assembly and write an
; assembly program that calculates the mean of these 10 integers (truncating the result to an integer).
; You must define the array in a data area.
;
;*******************************************************************

	AREA    |.text|, CODE, READONLY, ALIGN=2
	THUMB
	EXPORT  Start

; Define global(s)
ARRAY DCD 1,2,3,4,5,6,7,8,9,10	; Make an array of 10 unsigned integers, DCD will allocate one or more words of data

Start
loop	BL mean_of_ints  	; Branch to averaging function

mean_of_ints
		MOV r0, #0 			; Initialize sum to 0
		LDR r1, =ARRAY 		; Load the array into register 1
		MOV r2, #10			; Define the array size as 10 ints, this will be our decrement variable

loop_mean
		LDR r3, [r1], #4	; Load our memory address of r1 and move to next register/next int in array
		ADD r0, r0, r3		; Add last and current integer in the array to sum variable
		SUBS r2, r2, #1		; decrement loop variable by 1
		BNE loop_mean		; Loop the mean once again if not looped through all variables
		MOV r2, #10			; Re-define array size in size variable
		UDIV r0, r0, r2		; Divide the sum by the length of the array
		BX LR				; Exit the loop

		ALIGN				; make sure the end of this section is aligned
		END					; end of file
