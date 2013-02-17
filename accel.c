//ELD002 Group Project: Cybots
//Chronos System Software
//
//FILE DESCRIPTION
//accel.c
//Contains functions for accelerometer.
//
//CONTAINS FUNCTIONS
//check_accel
//
//WRITTEN BY
//Chris Elmer

//INCLUDES
#include  "main.h" //Processor header.

//FUNCTIONS
//Check Accel
//Changes clock speed if accleration is above threshold.
//Then waits 10 seconds before checking again.
//Called at 4Hz by interrupt.
void check_accel (void)
{
	extern unsigned volatile clock_speed;
	extern unsigned volatile accel_counter;
	const unsigned trigger = 100;	//TODO set trigger.  Out of 256.
	unsigned x;
	unsigned y;
	unsigned z;
	unsigned t;

	if (accel_counter == 0)
	{
		// Store X/Y/Z acceleration data
		x = as_read_register(0x06);
		y = as_read_register(0x07);
		z = as_read_register(0x08);

		if((x > trigger) || (y > trigger) || (z > trigger))
			t = 1;
		else
			t = 0;

		if (t == 1)
		{
			change_period(1);	//Speed up OR stop.
			accel_counter = 40;
		}
		else if (t == 0)
		{
			change_period(0);	//Slow down
			accel_counter = 40;
		}
	}
	else
		--accel_counter;
}
