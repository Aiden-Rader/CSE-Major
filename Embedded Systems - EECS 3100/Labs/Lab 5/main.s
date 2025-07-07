;*******************************************************************
; main.s
; Author: Alex Munn, Aiden Rader
; Date Created: 11/18/2016
; Last Modified: 7/3/2025
; Section Number: 043
; Instructor: Devinder Kaur
; Lab number: 5
; Brief description of the program
;   If the switch is presses, the LED toggles at 8 Hz
; Hardware connections
;  PE1 is switch input  (1 means pressed, 0 means not pressed)
;  PE0 is LED output (1 activates external LED on protoboard) 
; Overall functionality is similar to Lab 4, with six changes:
;   1) the pin to which we connect the switch is moved to PE1, 
;   2) you will have to remove the PUR initialization because
;      pull up is no longer needed. 
;   3) the pin to which we connect the LED is moved to PE0, 
;   4) the switch is changed from negative to positive logic, and 
;   5) you should increase the delay so it flashes about 8 Hz.
;   6) the LED should be on when the switch is not pressed
; Operation
;   1) Make PE0 an output and make PE1 an input. 
;   2) The system starts with the LED on (make PE0 =1). 
;   3) Wait about 62 ms
;   4) If the switch is pressed (PE1 is 1), then toggle the LED
;      once, else turn the LED on. 
;   5) Steps 3 and 4 are repeated over and over
;*******************************************************************

GPIO_PORTE_DATA_R       EQU   0x400243FC
GPIO_PORTE_DIR_R        EQU   0x40024400
GPIO_PORTE_AFSEL_R      EQU   0x40024420
GPIO_PORTE_DEN_R        EQU   0x4002451C
GPIO_PORTE_AMSEL_R      EQU   0x40024528
GPIO_PORTE_PCTL_R       EQU   0x4002452C
SYSCTL_RCGCGPIO_R       EQU   0x400FE608


       IMPORT  TExaS_Init

       AREA    |.text|, CODE, READONLY, ALIGN=2
       THUMB
       EXPORT  Start

init_PortE
	; Enable Clock for Port E
	LDR r0, =SYSCTL_RCGCGPIO_R
	LDR r1, [r0]
	ORR r1, r1, #0x10
	STR r1, [r0]
	
	; Set small delay
	NOP
	NOP
	
	; Turn off AMSEL for Port F
	LDR r0, =GPIO_PORTE_AMSEL_R
	LDR r1, [r0]
	AND r1, #0x00
	STR r1, [r0]
	
	; Set Direction (input/output)
	LDR r0, =GPIO_PORTE_DIR_R
	LDR r1, [r0]
	MOV r1, #0x01
	STR r1, [r0]
	
	; Turn off AFSEL for Port F
	LDR r0, =GPIO_PORTE_AFSEL_R
	LDR r1, [r0]
	AND r1, #0x00
	STR r1, [r0]
	
	; Digital Enable for PE0 & PE1
	LDR r0, =GPIO_PORTE_DEN_R
	LDR r1, [r0]
	ORR r1, r1, #0x03
	STR r1, [r0]
	
	; Set the GPIO Mode
	LDR r0, =GPIO_PORTE_DATA_R
    LDR r1, [r0]
	AND r1, #0xFFFFFFFF
	STR r1, [r0]
	
	BX LR  ; Return from function
	
LED_Off
     LDR R0, =GPIO_PORTE_DATA_R
	 LDR R1, [r0]
	 AND R1, #0xFFFFFFFE
	 STR R1, [R0]
	 BX  LR
LED_On
     LDR R0, =GPIO_PORTE_DATA_R
	 LDR R1, [r0]
	 ORR R1, #0x01
	 STR R1, [R0]
	 BX  LR
LED_Toggle
     LDR R0, =GPIO_PORTE_DATA_R
	 LDR R1, [r0]
	 EOR R1, #0x01
	 STR R1, [R0]
	 BX  LR

Start
	; TExaS_Init sets bus clock at 80 MHz
	BL  TExaS_Init ; voltmeter, scope on PD3
	; you initialize PE1 PE0	 

	BL init_PortE

	CPSIE  I    ; TExaS voltmeter, scope runs on interrupts

loop
	; you input output delay
	LDR R0, =GPIO_PORTE_DATA_R
	LDR R1, [r0]
	AND R1, #0x02
	CMP R1, #0x02
	BNE switch_off
	BL  LED_Toggle
	BL  delay
	B   loop
	
switch_off
	BL LED_On
	B    loop
	
delay
	MOV  r4, #0x00130000
delay_loop
	SUBS r4, r4, #1
	BNE delay_loop
	BX LR

	ALIGN      ; make sure the end of this section is aligned
	END        ; end of file
       