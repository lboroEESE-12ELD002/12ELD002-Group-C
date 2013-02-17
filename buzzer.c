//ELD002 Group Project: Cybots
//Chronos System Software
//
//FILE DESCRIPTION
//buttons.c
//Contains functions for buttons.
//
//CONTAINS FUNCTIONS
//start_buzzer
//stop_buzzer
//timer0_A3_start
//timer0_A3_stop
//
//WRITTEN BY
//Chris Elmer

//INCLUDES
#include  "main.h" //Processor header.

// Global Variable section
struct buzzer sBuzzer;
unsigned short	timer0_A3_ticks;

//FUNCTIONS
//Start Buzzer
void start_buzzer(unsigned cycles, unsigned short on_time, unsigned short off_time)
{
	extern unsigned short timer0_A3_ticks;

	// Store new buzzer duration while buzzer is off
	if (sBuzzer.time == 0)
	{
		sBuzzer.time 	 = cycles;
		sBuzzer.on_time  = on_time;
		sBuzzer.off_time = off_time;

		// Need to init every time, because SimpliciTI claims same timer

		// Reset TA1R, set up mode, TA1 runs from 32768Hz ACLK
		TA1CTL = TACLR | MC_1 | TASSEL__ACLK;

		// Set PWM frequency
		TA1CCR0 = BUZZER_TIMER_STEPS;

		// Enable IRQ, set output mode "toggle"
		TA1CCTL0 = OUTMOD_4;

		// Allow buzzer PWM output on P2.7
		P2SEL |= BIT7;

		// Activate Timer0_A3 periodic interrupts
//		fptr_Timer0_A3_function = toggle_buzzer;  This needs to be put back in.
		Timer0_A3_Start(sBuzzer.on_time);

		// Preload timer advance variable
		timer0_A3_ticks = sBuzzer.off_time;

		// Start with buzzer output on
		sBuzzer.state 	 	= BUZZER_ON_OUTPUT_ENABLED;
	}
}

//Stop Buzzer
void stop_buzzer(void)
{
	// Stop PWM timer
	TA1CTL &= ~(BIT4 | BIT5);

	// Disable buzzer PWM output
	P2OUT &= ~BIT7;
	P2SEL &= ~BIT7;

	// Clear PWM timer interrupt
	TA1CCTL0 &= ~CCIE;

	// Disable periodic start/stop interrupts
	Timer0_A3_Stop();
}

//Timer0_A3_Start
void Timer0_A3_Start(unsigned short ticks)
{
	extern unsigned short timer0_A3_ticks;
	unsigned short value;

	// Store timer ticks in global variable
	timer0_A3_ticks = ticks;

	// Delay based on current counter value
	value = TA0R + ticks;

	// Update CCR
	TA0CCR3 = value;

	// Reset IRQ flag
	TA0CCTL3 &= ~CCIFG;

	// Enable timer interrupt
	TA0CCTL3 |= CCIE;
}


//Timer0_A3_stop
void Timer0_A3_Stop(void)
{
	// Clear timer interrupt
	TA0CCTL3 &= ~CCIE;
}

//Beep Function
//Controls periodic beep
void f_beep(void)
{
	extern unsigned volatile flash;
	extern unsigned volatile flash_counter;

	if ((flash_counter / 4) == 1)
	{
		start_buzzer(1, BUZZER_ON_TICKS, BUZZER_OFF_TICKS);
		if (flash == 1)
		{
			flash = 0;
			display_symbol(LCD_ICON_ALARM, SEG_OFF);
		}
		else
		{
			flash = 1;
			display_symbol(LCD_ICON_ALARM, SEG_ON);
		}
	}
}


