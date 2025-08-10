// Program written by: Aiden Rader
// Date Created: 6/3/2025
// Last Modified: 6/3/2025

#include <stdint.h>
// Constant declarations to access port registers using
// symbolic names instead of addresses; from the tm4c123gh6pm.h file
#define SYSCTL_RCGCGPIO_R   (*((volatile unsigned long *)0x400FE608))
#define GPIO_PORTA_DIR_R    (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_DEN_R    (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_AMSEL_R  (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_PCTL_R   (*((volatile unsigned long *)0x4000452C))
#define GPIO_PORTA_AFSEL_R  (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_DATA_R   (*((volatile unsigned long *)0x400043FC))
#define GPIO_PORTA_CR_R     (*((volatile unsigned long *)0x40004524))
#define GPIO_PORTA_PUR_R    (*((volatile unsigned long *)0x40004510))
#define GPIO_PORTA_PDR_R    (*((volatile unsigned long *)0x40004514))
#define GPIO_PORTA_LOCK_R   (*((volatile unsigned long *)0x40004520))

/* Note: GPIO_PORTA_DATA_R is = Port A Pin 7 */

// Function Prototypes
void initPortA(void);
unsigned long Read_PA7(void);

// Main Function
int main(void) {
	initPortA();

	// Forever Loop
	while(1) {
		volatile unsigned long state = Read_PA7();

		// Check if the button IS Pressed; Positive Logic
		if (state == 1) {
			// Do something...
		} else {
			// Do something else...
		}
	}
}

// Initialize PA7 as digital input with pull-up resistor
void initPortA(void) {
	volatile unsigned long delay;

	SYSCTL_RCGCGPIO_R |= 0x00000001; 		// 1. Activate clock for Port A
	delay = SYSCTL_RCGCGPIO_R;       		// 2. Allow time for clock to stabilize

	GPIO_PORTA_LOCK_R = 0x4C4F434B;
	GPIO_PORTA_CR_R |= 0x80;         	// 3. Allow changes to PA7 (Unlock aswell)

	GPIO_PORTA_AMSEL_R &= ~0x80;     	// 4. Disable analog function on PA7
	GPIO_PORTA_PCTL_R &= ~0xF0000000;	// 5. Configure PA7 as GPIO
	GPIO_PORTA_DIR_R &= ~0x80;       	// 6. Set PA7 as input (0)
	GPIO_PORTA_AFSEL_R &= ~0x80;     	// 7. Disable alternate functions on PA7
	GPIO_PORTA_PUR_R |= 0x80;        	// 8. Enable pull-up resistor on PA7 (for positive logic)
	GPIO_PORTA_PDR_R &= ~0x80;       	// 9. Ensure pull-down is disabled; hence NOT
	GPIO_PORTA_DEN_R |= 0x80;        	// 10. Enable digital function for PA7
}

// Return 1 if pressed, 0 if not
unsigned long Read_PA7(void) {
	return (GPIO_PORTA_DATA_R & 0x80) >> 7;
}
