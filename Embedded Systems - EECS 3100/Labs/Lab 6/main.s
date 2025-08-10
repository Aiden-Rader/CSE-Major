;*******************************************************************
; main.s
; Author: Alex Munn
; Date Created: 7/10/2025
; Last Modified: 7/11/2025
; Section Number: 042
; Instructor: Mehzabien Iqbal
; Lab number: 6
; Brief description of the program
;   If the switch is presses, the LED toggles at 8 Hz
; Hardware connections
;   PE1 is switch input  (1 means pressed, 0 means not pressed)
;   PE0 is LED output (1 activates external LED on protoboard) 
; Overall functionality is similar to Lab 5, with three changes:
;   1) Initialize SysTick with RELOAD 0x00FFFFFF 
;   2) Add a heartbeat to PF2 that toggles every time through loop 
;   3) Add debugging dump of input, output, and time
; Operation
;	1) Make PE0 an output and make PE1 an input. 
;	2) The system starts with the LED on (make PE0 =1). 
;   3) Wait about 62 ms
;   4) If the switch is pressed (PE1 is 1), then toggle the LED
;      once, else turn the LED on. 
;   5) Steps 3 and 4 are repeated over and over
;*******************************************************************

SWITCH                  EQU 0x40024004  ;PE0
LED                     EQU 0x40024008  ;PE1
SYSCTL_RCGCGPIO_R       EQU 0x400FE608
SYSCTL_RCGC2_GPIOE      EQU 0x00000010  ;port E Clock Gating Control
SYSCTL_RCGC2_GPIOF      EQU 0x00000020  ;port F Clock Gating Control
GPIO_PORTE_DATA_R       EQU 0x400243FC
GPIO_PORTE_DIR_R        EQU 0x40024400
GPIO_PORTE_AFSEL_R      EQU 0x40024420
GPIO_PORTE_PUR_R        EQU 0x40024510
GPIO_PORTE_DEN_R        EQU 0x4002451C
GPIO_PORTF_DATA_R       EQU 0x400253FC
GPIO_PORTF_DIR_R        EQU 0x40025400
GPIO_PORTF_AFSEL_R      EQU 0x40025420
GPIO_PORTF_PUR_R        EQU 0x40025510
GPIO_PORTF_DEN_R        EQU 0x4002551C
GPIO_PORTF_AMSEL_R      EQU 0x40025528
GPIO_PORTF_PCTL_R       EQU 0x4002552C
GPIO_PORTF_LOCK_R  	    EQU 0x40025520
GPIO_PORTF_CR_R         EQU 0x40025524
NVIC_ST_CTRL_R          EQU 0xE000E010
NVIC_ST_RELOAD_R        EQU 0xE000E014
NVIC_ST_CURRENT_R       EQU 0xE000E018
GPIO_PORTE_AMSEL_R      EQU 0x40024528
GPIO_PORTE_PCTL_R       EQU 0x4002452C
           
		   THUMB
           AREA    DATA, ALIGN=4
SIZE       EQU    50
;You MUST use these two buffers and two variables
;You MUST not change their names
DataBuffer SPACE  SIZE*4
TimeBuffer SPACE  SIZE*4
DataPt     SPACE  4
TimePt     SPACE  4
;These names MUST be exported
           EXPORT DataBuffer  
           EXPORT TimeBuffer  
           EXPORT DataPt [DATA,SIZE=4] 
           EXPORT TimePt [DATA,SIZE=4]
    
      ALIGN          
      AREA    |.text|, CODE, READONLY, ALIGN=2
      THUMB
      EXPORT  Start
      IMPORT  TExaS_Init
	  IMPORT  SysTick_Init
	  IMPORT  SysTick_Wait
	  IMPORT  SysTick_Wait10ms

init_PortE
	; Enable Clock for Port E
	LDR r0, =SYSCTL_RCGCGPIO_R
	LDR r1, [r0]
	ORR r1, r1, #0x10
	STR r1, [r0]
	
	; Set small delay
	NOP
	NOP
	
	; Turn off AMSEL for Port E
	LDR r0, =GPIO_PORTE_AMSEL_R
	LDR r1, [r0]
	AND r1, #0x00
	STR r1, [r0]
	
	; Set Direction (input/output)
	LDR r0, =GPIO_PORTE_DIR_R
	LDR r1, [r0]
	MOV r1, #0x01
	STR r1, [r0]
	
	; Turn off AFSEL for Port E
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
	
init_PortF
	; Enable Clock for Port F
	LDR r0, =SYSCTL_RCGCGPIO_R
	LDR r1, [r0]
	ORR r1, r1, #0x20
	STR r1, [r0]
	
	; Set small delay
	NOP
	NOP
	
	; Unlock Port F
	LDR r0, =GPIO_PORTF_LOCK_R
	AND r1, #0
	ORR r1, #0x4C000000
	ORR r1, #0x004F0000
	ORR r1, #0x00004300
	ORR r1, #0x0000004B
	STR r1, [r0]
	
	; Allow changes to Port F
	LDR r0, =GPIO_PORTF_CR_R
	LDR r1, [r0]
	MOV r1, #0x04
	STR r1, [r0]
	
	; Turn off AMSEL for Port F
	LDR r0, =GPIO_PORTF_AMSEL_R
	LDR r1, [r0]
	AND r1, #0x00
	STR r1, [r0]
	
	; Set Direction (input/output)
	LDR r0, =GPIO_PORTF_DIR_R
	LDR r1, [r0]
	MOV r1, #0x04
	STR r1, [r0]
	
	; Turn off AFSEL for Port E
	LDR r0, =GPIO_PORTF_AFSEL_R
	LDR r1, [r0]
	AND r1, #0x00
	STR r1, [r0]
	
	; Digital Enable for PE0 & PE1
	LDR r0, =GPIO_PORTF_DEN_R
	LDR r1, [r0]
	ORR r1, r1, #0x04
	STR r1, [r0]
	
	; Set the GPIO Mode
	LDR r0, =GPIO_PORTF_DATA_R
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

Start BL   TExaS_Init  ; running at 80 MHz, scope voltmeter on PD3
      BL   init_PortE  ; initialize Port E
      BL   init_PortF  ; initialize Port F
      BL   Debug_Init; initialize debugging dump, including SysTick

      CPSIE  I    ; TExaS voltmeter, scope runs on interrupts
loop  BL   Debug_Capture
    BL  heartbeat  ;heartbeat
    BL  delay  ; Delay
      ;input PE1 test output PE0
	LDR R0, =GPIO_PORTE_DATA_R
	LDR R1, [r0]
	AND R1, #0x02
	CMP R1, #0x02
	BNE switch_off
	BL  LED_Toggle
	B    loop
	  
switch_off
	BL LED_On
	B    loop
	
delay
	MOV  r4, #0x00130000
delay_loop
	SUBS r4, r4, #1
	BNE delay_loop
	BX LR
	
heartbeat
	LDR r2, =GPIO_PORTF_DATA_R
	LDR r3, [r2]
	EOR r3, #0x04
	STR r3, [r2]
	BX LR

;------------Debug_Init------------
; Initializes the debugging instrument
; Note: push/pop an even number of registers so C compiler is happy
Debug_Init
	PUSH {LR, r0, r1, r2, r3, r4}
	
	; initialize buffers to 0
	LDR r0, =SIZE
	LDR r1, =DataBuffer
	LDR r2, =TimeBuffer
	MOV r3, #0xFFFFFFFF
Debug_Init_Loop
	STR r3, [r1]
	STR r3, [r2]
	ADD r1, r1, #4
	ADD r2, r2, #4
	SUBS r0, r0, #1
	BNE Debug_Init_Loop
	
	LDR r0, =DataPt
	LDR r1, =DataBuffer
	STR r1, [r0] ; initialize data pointer
	
	LDR r0, =TimePt
	LDR r1, =TimeBuffer
	STR r1, [r0] ; initialize time pointer
	
	; init SysTick
	BL SysTick_Init

	POP {LR, r0, r1, r2, r3, r4}
	BX LR

;------------Debug_Capture------------
; Dump Port E and time into buffers
; Note: push/pop an even number of registers so C compiler is happy
Debug_Capture
	PUSH {r0, r1, r2, r3}

	LDR r0, =DataPt
	LDR r2, [r0]
	LDR r1, =DataBuffer
	LDR r3, =SIZE
	LSL r3, r3, #2 ; multiply size by 4 bytes
	ADD r1, r1, r3
	CMP r2, r1
	BHS Debug_Capture_Return ; return if data pointer past end of buffer
	; no need to check time pointer since it is incremented simultaneously
	
	LDR r0, =GPIO_PORTE_DATA_R
	LDR r1, [r0] ; get port E data
	LDR r0, =NVIC_ST_CURRENT_R
	LDR r3, [r0] ; get timer value
	
	AND r1, r1, #0x03 ; mask to bits 1 and 0
	MOV r2, r1 ; copy data
	LSL r2, r2, #3 ; shift bit 1 to bit 4
	AND r2, r2, #0x10 ; mask
	AND r1, r1, #0x01 ; mask
	ORR r1, r1, r2 ; combine back into one register
	
	LDR r0, =DataPt
	LDR r2, [r0]
	STR r1, [r2] ; store data into buffer
	ADD r2, r2, #4 ; increment pointer
	STR r2, [r0] ; store new pointer
	
	LDR r0, =TimePt
	LDR r2, [r0]
	STR r3, [r2] ; store data into buffer
	ADD r2, r2, #4 ; increment pointer
	STR r2, [r0] ; store new pointer

Debug_Capture_Return
	POP {r0, r1, r2, r3}
    BX LR


    ALIGN      ; make sure the end of this section is aligned
    END        ; end of file
        