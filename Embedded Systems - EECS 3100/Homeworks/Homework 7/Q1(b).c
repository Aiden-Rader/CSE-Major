/********************************************************************
 main.c
 Author: Aiden Rader
 Date Created: 7/2/2025
 Last Modified: 7/2/2025
 Section Number: 041
 Instructor: Devinder Kaur
 Homework Number: 7
   [DESC]
********************************************************************/

#include <stdint.h>
#include "tm4c123gh6pm.h"

// Define our functions
void SysTick_Init_100us(void);

int main(void)
{
	SysTick_Init_100us();


	while (1)
	{

	}
}

// Init function for our SysTick Timer with 100us interupts
void SysTick_Init_100us(void)
{
	NVIC_ST_CTRL_R = 0;			   	// disable SysTick during setup
	NVIC_ST_RELOAD_R = 8000 - 1; 	// maximum reload value
	NVIC_ST_CURRENT_R = 0;		   	// any write to CURRENT clears it
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) | 0x20000000; // set priority 1

	NVIC_ST_CTRL_R = 0x07; // enable SysTick with core clock AND interupts
	__enable_irq(); // Enable global interrupts
}
