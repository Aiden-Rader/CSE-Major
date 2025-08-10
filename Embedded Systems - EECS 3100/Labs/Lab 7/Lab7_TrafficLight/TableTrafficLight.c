/*******************************************************************
 * TableTrafficLight.c
 * Instructor: Divinder Kaur
 * Runs on LM4F120/TM4C123
 * Index implementation of a Moore finite state machine to operate a traffic light.  
 * Authors: Daniel Valvano,
 *					Jonathan Valvano,
 * 					Thomas Royko
 * Student: Aiden Rader, Alex Munn
 * Section: 042
 * Date:    07/17/2025
 *
 * east/west red light connected to PB5
 * east/west yellow light connected to PB4
 * east/west green light connected to PB3
 * north/south facing red light connected to PB2
 * north/south facing yellow light connected to PB1
 * north/south facing green light connected to PB0
 * pedestrian detector connected to PE2 (1=pedestrian present)
 * north/south car detector connected to PE1 (1=car present)
 * east/west car detector connected to PE0 (1=car present)
 * "walk" light connected to PF3 (built-in green LED)
 * "don't walk" light connected to PF1 (built-in red LED)
 *******************************************************************/

#include "TExaS.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "SysTick.h"

// Label input/output ports
#define LIGHT                   (*((volatile uint32_t *)0x400050FC))
#define SENSOR                  (*((volatile uint32_t *)0x4002401C))

// Define digital input/output ports
#define GPIO_PORTB_DIR_R        (*((volatile uint32_t *)0x40005400))
#define GPIO_PORTB_AFSEL_R      (*((volatile uint32_t *)0x40005420))
#define GPIO_PORTB_DEN_R        (*((volatile uint32_t *)0x4000551C))
#define GPIO_PORTB_AMSEL_R      (*((volatile uint32_t *)0x40005528))
#define GPIO_PORTB_PCTL_R       (*((volatile uint32_t *)0x4000552C))
#define GPIO_PORTE_DIR_R        (*((volatile uint32_t *)0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile uint32_t *)0x40024420))
#define GPIO_PORTE_DEN_R        (*((volatile uint32_t *)0x4002451C))
#define GPIO_PORTE_AMSEL_R      (*((volatile uint32_t *)0x40024528))
#define GPIO_PORTE_PCTL_R       (*((volatile uint32_t *)0x4002452C))
#define SYSCTL_RCGCGPIO_R       (*((volatile uint32_t *)0x400FE608))
#define SYSCTL_PRGPIO_R         (*((volatile uint32_t *)0x400FEA08))

struct State {
  uint32_t Out;      // 6-bit output
	uint32_t Walk_Out;  // Lowest 3 bits
  uint32_t Time;     // 10 ms
  uint8_t Next[9];
}; // depends on 2-bit input
typedef const struct State STyp;
	
#define goN       0
#define waitN     1
#define goE       2
#define waitE     3
#define walk      4
#define wait_walk 5

// Define FSM as global	(LOWERED VALS)
STyp FSM[6]={
 {0x21, 0x02, 300,{goN,waitN,goN,waitN,waitN,waitN,waitN,waitN}},  // goN
 {0x22, 0x02, 50,{goE,goE,goE,goE,walk,walk,walk,walk}},  // WaitN
 {0x0C, 0x02, 300,{goE,goE,waitE,waitE,waitE,waitE,waitE,waitE}},  // goE
 {0x14, 0x02, 50,{goN,goN,goN,goN,walk,walk,walk,walk}},  // WaitE
 {0x24, 0x0E, 150,{wait_walk,wait_walk,wait_walk,wait_walk,wait_walk,wait_walk,wait_walk,wait_walk}},  // Walk
 {0x24, 0x0A, 50,{goN,goE,goN,goN,goN,goE,goN,goN}}  //Wait_Walk
};

// Local function prototypes
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Init_GPIO_PortsEB(void);
void PortF_Init(void);

 
int main(void){
  uint8_t n; // state number
  uint32_t Input;
	EnableInterrupts();

	// Call various initialization functions
  TExaS_Init(SW_PIN_PE210, LED_PIN_PB543210, ScopeOff);// initialize 80 MHz system clock
  SysTick_Init();                   // initialize SysTick timer
  Init_GPIO_PortsEB();
	PortF_Init();

	// Establish initial state of traffic lights
  n = goN;                          // initial state: Green north; Red east
  
	while(1){
    LIGHT = FSM[n].Out;             // set lights to current state's Out value
		GPIO_PORTF_DATA_R = FSM[n].Walk_Out;
    SysTick_Wait10ms(FSM[n].Time);  // wait 10 ms * current state's Time value
    Input = SENSOR;                 // get new input from car detectors
    n = FSM[n].Next[Input];         // transition to next state
  }
}

void Init_GPIO_PortsEB(void) {
	volatile uint32_t delay;
  SYSCTL_RCGC2_R |= 0x00000032;  // activate clock for Port E
  delay = SYSCTL_RCGC2_R;        // allow time for clock to start

  GPIO_PORTB_DIR_R |= 0x3F;         // make PB5-0 out
  GPIO_PORTB_AFSEL_R &= ~0x3F;      // disable alt funct on PB5-0
  GPIO_PORTB_DEN_R = 0x3F;         // enable digital I/O on PB5-0
                                    // configure PB5-0 as GPIO
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFF000000)+0x00000000;
  GPIO_PORTB_AMSEL_R &= ~0x3F;      // disable analog functionality on PB5-0

  GPIO_PORTE_DIR_R &= ~0x07;        // make PE2-0 in
  GPIO_PORTE_AFSEL_R &= ~0x07;      // disable alt funct on PE2-0
  GPIO_PORTE_DEN_R |= 0x07;         // enable digital I/O on PE2-0
                                    // configure PE2-0 as GPIO
  GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R&0xFFFFF000)+0x00000000;
  GPIO_PORTE_AMSEL_R &= ~0x07;      // disable analog functionality on PE1-0
}

void PortF_Init(void){ 
	volatile unsigned long delay;

  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0

  // only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 in, PF3-1 out (important)
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital I/O on PF4-0

}
