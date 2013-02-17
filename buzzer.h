#ifndef BUZZER_H_
#define BUZZER_H_

// Buzzer states
#define BUZZER_OFF							(0u)
#define BUZZER_ON_OUTPUT_DISABLED			(1u)
#define BUZZER_ON_OUTPUT_ENABLED			(2u)

// Buzzer modes
#define BUZZER_MODE_SINGLE					(0u)
#define BUZZER_MODE_SINGLE_CONTINUOUS		(1u)
#define BUZZER_MODE_DOUBLE_CONTINUOUS		(2u)

// Buzzer output signal frequency = 32,768kHz/(BUZZER_TIMER_STEPS+1)/2 = 2.7kHz
#define BUZZER_TIMER_STEPS					(5u)

// Buzzer on time
#define BUZZER_ON_TICKS						(CONV_MS_TO_TICKS(20))

// Buzzer off time
#define BUZZER_OFF_TICKS					(CONV_MS_TO_TICKS(200))

//Timer
// Timer0_A3 periodic delay
extern unsigned short		timer0_A3_ticks;

// Global Variable section
struct buzzer
{
	// Keep output for "time" seconds
	unsigned time;

	// On/off duty
	unsigned short on_time;
	unsigned short off_time;

	// Current buzzer output state
	unsigned state;
};
extern struct buzzer sBuzzer;

//Prototypes Section
void start_buzzer(unsigned cycles, unsigned short on_time, unsigned short off_time);
void stop_buzzer(void);
void Timer0_A3_Start(unsigned short ticks);
void Timer0_A3_Stop(void);
void f_beep(void);

#endif /* BUZZER_H_ */
