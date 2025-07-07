;*******************************************************************
; main.s
; Author: Aiden Rader, Alex Munn, Salahedeen Hamdah
; Date Created: 11/18/2016
; Last Modified: 6/12/2016
; Section Number: 043
; Instructor: Divinder Kaur
; Lab number: 4
;   Brief description of the program
; The overall objective of this system is an interactive alarm
; Hardware connections
;   PF4 is switch input  (1 = switch not pressed, 0 = switch pressed)
;   PF3 is LED output    (1 activates green LED) 
; The specific operation of this system 
;   1) Make PF3 an output and make PF4 an input (enable PUR for PF4). 
;   2) The system starts with the LED OFF (make PF3 =0). 
;   3) Delay for about 100 ms
;   4) If the switch is pressed (PF4 is 0),
;      then toggle the LED once, else turn the LED OFF. 
;   5) Repeat steps 3 and 4 over and over
;*******************************************************************

GPIO_PORTF_DATA_R       EQU   0x400253FC
GPIO_PORTF_DIR_R        EQU   0x40025400
GPIO_PORTF_AFSEL_R      EQU   0x40025420
GPIO_PORTF_PUR_R        EQU   0x40025510
GPIO_PORTF_DEN_R        EQU   0x4002551C
GPIO_PORTF_AMSEL_R      EQU   0x40025528
GPIO_PORTF_PCTL_R       EQU   0x4002552C
SYSCTL_RCGCGPIO_R       EQU   0x400FE608
GPIO_PORTF_LOCK_R  	    EQU   0x40025520
GPIO_PORTF_CR_R         EQU   0x40025524
	
LED_ON					EQU   0x00000008
LED_OFF					EQU   0x00000000

		AREA    |.text|, CODE, READONLY, ALIGN=2
		THUMB
		EXPORT  Start
			
init_PortF
	; Enable Clock for Port F
	LDR r0, =SYSCTL_RCGCGPIO_R
	LDR r1, [r0]
	ORR r1, r1, #0x20
	STR r1, [r0]
	
	; Set small delay
	NOP
	NOP
	
	; Commit for Port F
	LDR r0, =GPIO_PORTF_CR_R
	LDR r1, [r0]
	AND r1, #0x18
	STR r1, [r0]
	
	; Turn off AMSEL for Port F
	LDR r0, =GPIO_PORTF_AMSEL_R
	LDR r1, [r0]
	AND r1, #0x00
	STR r1, [r0]
	
	; Set Direction (input/output)
	LDR r0, =GPIO_PORTF_DIR_R
	LDR r1, [r0]
	MOV r1, #0x08
	STR r1, [r0]
	
	; Turn off AFSEL for Port F
	LDR r0, =GPIO_PORTF_AFSEL_R
	LDR r1, [r0]
	AND r1, #0x00
	STR r1, [r0]
	
	; Digital Enable for PF3 & PF4
	LDR r0, =GPIO_PORTF_DEN_R
	LDR r1, [r0]
	ORR r1, r1, #0x18
	STR r1, [r0]
	
	; Enable the Pull-Up Resistor
	LDR r0, =GPIO_PORTF_PUR_R
	LDR r1, [r0]
	MOV r1, #0x10
	STR r1, [r0]
	
	; Set the GPIO Mode
	LDR r0, =GPIO_PORTF_DATA_R
    LDR r1, [r0]
	AND r1, #0xFFFFFFF7
	STR r1, [r0]
	
	BX LR  ; Return from function
	
LED_Off
     LDR R0, =GPIO_PORTF_DATA_R
	 LDR R1, [r0]
	 AND R1, #0xFFFFFFF7
	 STR R1, [R0]
	 BX  LR
LED_On
     LDR R0, =GPIO_PORTF_DATA_R
	 LDR R1, [r0]
	 ORR R1, #0x08
	 STR R1, [R0]
	 BX  LR
LED_Toggle
     LDR R0, =GPIO_PORTF_DATA_R
	 LDR R1, [r0]
	 EOR R1, #0x08
	 STR R1, [R0]
	 BX  LR
			
Start
	BL init_PortF
	BL LED_Off

loop  
	LDR R0, =GPIO_PORTF_DATA_R
	LDR R1, [r0]
	AND R1, #0x10
	CMP R1, #0x10
	BEQ switch_off
	BL  LED_Toggle
	BL  delay
	B   loop
switch_off
	BL LED_Off
	B    loop
		
delay
	MOV  r4, #0x00062000
delay_loop
	SUBS r4, r4, #1
	BNE delay_loop
	BX LR

	ALIGN      ; make sure the end of this section is aligned
	END        ; end of file
       