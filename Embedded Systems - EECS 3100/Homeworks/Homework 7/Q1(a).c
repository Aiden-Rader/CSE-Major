/********************************************************************
 main.c
 Author: Aiden Rader
 Date Created: 7/2/2025
 Last Modified: 7/2/2025
 Section Number: 041
 Instructor: Devinder Kaur
 Homework Number: 7
	Question 1(a):
	Write a function in C that uses SysTick delay for 1 millisecond. Assume that the SysTick is already
	initialized with NVIC_ST_RELOAD=0x00FFFFFF; NVIC_ST_CTRL=0x05; Assume that the clock is
	running at 50 MHz, such that each bus cycle is 20 ns.
********************************************************************/

#include <stdint.h>
#include "tm4c123gh6pm.h"

// Define our functions
void SysTick_Init(void);
void SysTick_Wait(uint32_t delay);
void SysTick_Wait1ms(uint32_t delay);

int main(void)
{
	SysTick_Init();
	unsigned long int loops = 1000;
	while (1)
	{
		SysTick_Wait1ms(loops);
	}
}

// Init function for our SysTick Timer
void SysTick_Init(void)
{
	NVIC_ST_CTRL_R = 0;			   // 1) disable SysTick during setup
	NVIC_ST_RELOAD_R = 0x00FFFFFF; // 2) maximum reload value
	NVIC_ST_CURRENT_R = 0;		   // 3) any write to CURRENT clears it
	NVIC_ST_CTRL_R = 0x05;		   // 4) enable SysTick with core clock
}

void SysTick_Wait(uint32_t cycles)
{
	NVIC_ST_RELOAD_R = cycles - 1; // number of counts
	NVIC_ST_CURRENT_R = 0;		   // any value written to CURRENT clears
	while ((NVIC_ST_CTRL_R & 0x00010000) == 0)
	{	// wait for COUNT flag
		// which is bit 16
	}
}

// Call this routine to wait for loops * 1ms
void SysTick_Wait1ms(uint32_t loops)
{
	unsigned long i;

	// wait 1ms => 1,000,000ns / 20 ns per cycle = 50,000 cycles
	for (i = 0; i < loops; i++)
	{
		SysTick_Wait(50000);
	}
}
