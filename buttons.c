//ELD002 Group Project: Cybots
//Chronos System Software
//
//FILE DESCRIPTION
//buttons.c
//Contains functions for buttons.
//
//CONTAINS FUNCTIONS
//buttons_initiate
//PORT2_ISR
//
//WRITTEN BY
//Chris Elmer

//INCLUDES
#include  "main.h" //Processor header.

// Defines section

// Macro for button IRQ
#define IRQ_TRIGGERED(flags, bit)		((flags & bit) == bit)

// Global Variable section
volatile s_button_flags button;
volatile struct struct_button sButton;
unsigned volatile programme_mode;	//START_MODE, TIMING_MODE or STOP_MODE
unsigned volatile button_presses;

//FUNCTIONS
//buttons_initiate
void buttons_initiate(void)
{
	extern unsigned volatile programme_mode;
	extern unsigned volatile button_presses;
	programme_mode = START_MODE;
	button_presses = 0;

	// Set button ports to input 
	BUTTONS_DIR &= ~ALL_BUTTONS; 

	// Enable internal pull-downs
	BUTTONS_OUT &= ~ALL_BUTTONS; 
	BUTTONS_REN |= ALL_BUTTONS; 

	// IRQ triggers on rising edge
	BUTTONS_IES &= ~ALL_BUTTONS;   

	// Reset IRQ flags
	BUTTONS_IFG &= ~ALL_BUTTONS;  

	// Enable button interrupts
	BUTTONS_IE |= ALL_BUTTONS;
}   

//ISR for buttons & accelerometer
#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR(void)
{
	extern volatile unsigned programme_mode;
	extern volatile unsigned  time_elapsed[2];
	extern volatile unsigned  counts_remaining;
	extern unsigned volatile beep_enable;
	extern unsigned volatile button_presses;

	unsigned int_flag;
	unsigned int_enable;

	// Remember interrupt enable bits
	int_enable = BUTTONS_IE;

	// Store valid button interrupt flag
	int_flag = BUTTONS_IFG & int_enable;

	// Debounce buttons
	if ((int_flag & ALL_BUTTONS) != 0)
	{
		// Disable PORT2 IRQ
		__disable_interrupt();
		BUTTONS_IE = 0x00;
		__enable_interrupt();
	}

	if (programme_mode == START_MODE)	//Until timing starts
	{
		if ((int_flag & BUTTON_STAR_PIN) == BUTTON_STAR_PIN)	//Toggle audable feedback.
  		{
			if (beep_enable == 1)
				beep_enable = 0;
			else if (beep_enable == 0)
				beep_enable = 1;
  		}
  		else if ((int_flag & BUTTON_NUM_PIN) == BUTTON_NUM_PIN)	//Start countdown
  		{
  			programme_mode = TIMING_MODE;
  			clock_start();
  			as_start();
  		}
		else if ((int_flag & BUTTON_UP_PIN) == BUTTON_UP_PIN)	//Change start point upward
		{
			if (counts_remaining >= 0)
			{
				counts_remaining = counts_remaining + 60;
				++ time_elapsed[0];
			}
		}
		else if ((int_flag & BUTTON_DOWN_PIN) == BUTTON_DOWN_PIN)	//Change start point downward
		{
			if (counts_remaining <= 600)
			{
				counts_remaining = counts_remaining - 60;
				-- time_elapsed[0];
			}
		}
	}
	else if (programme_mode == TIMING_MODE)	//Whilst timer is running
	{
		if ((int_flag & BUTTON_STAR_PIN) == BUTTON_STAR_PIN)	//Toggle audable feedback
  		{
			if (beep_enable == 1)
				beep_enable = 0;
			else if (beep_enable == 0)
				beep_enable = 1;
  		}
  		else if ((int_flag & BUTTON_NUM_PIN) == BUTTON_NUM_PIN)	//Clock speed reset
  		{
			if (button_presses > 9)
				stop_mode();
			else
			{
	  			change_period(0);	//Slow down counter
	  			++ button_presses;	//Log presses
			}
  		}
		else if ((int_flag & BUTTON_UP_PIN) == BUTTON_UP_PIN)	//Speed up counter.  Test for when accelerometer doesn't work
		{
			change_period(1);
		}
		else if ((int_flag & BUTTON_DOWN_PIN) == BUTTON_DOWN_PIN)	//Not yet implemented
		{

		}
	}
	else if (programme_mode == STOP_MODE)
	{
		if ((int_flag & BUTTON_STAR_PIN) == BUTTON_STAR_PIN)	//Toggle audable feedback
  		{
			if (beep_enable == 1)
				beep_enable = 0;
			else if (beep_enable == 0)
				beep_enable = 1;
  		}
  		else if ((int_flag & BUTTON_NUM_PIN) == BUTTON_NUM_PIN)	//Not yet implemented
  		{

  		}
		else if ((int_flag & BUTTON_UP_PIN) == BUTTON_UP_PIN)	//Not yet implemented
		{

		}
		else if ((int_flag & BUTTON_DOWN_PIN) == BUTTON_DOWN_PIN)	//Not yet implemented
		{

		}
	}

	// Reenable PORT2 IRQ
	__disable_interrupt();
	BUTTONS_IFG = 0x00;
	BUTTONS_IE  = int_enable;
	__enable_interrupt();
}
