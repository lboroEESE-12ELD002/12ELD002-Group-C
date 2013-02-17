#ifndef BUTTONS_H_
#define BUTTONS_H_

//Define programme modes
#define START_MODE				(0)
#define TIMING_MODE				(1)
#define STOP_MODE				(2)

// Port, pins and interrupt resources for buttons
#define BUTTONS_IN              (P2IN)
#define BUTTONS_OUT				(P2OUT)
#define BUTTONS_DIR             (P2DIR)
#define BUTTONS_REN				(P2REN)
#define BUTTONS_IE              (P2IE)
#define BUTTONS_IES             (P2IES)
#define BUTTONS_IFG             (P2IFG)
#define BUTTONS_IRQ_VECT2       (PORT2_VECTOR)

// Button ports
#define BUTTON_STAR_PIN        	(BIT2)
#define BUTTON_NUM_PIN         	(BIT1)
#define BUTTON_UP_PIN          	(BIT4)
#define BUTTON_DOWN_PIN        	(BIT0)
#define BUTTON_BACKLIGHT_PIN   	(BIT3)
#define ALL_BUTTONS			 	(BUTTON_STAR_PIN + BUTTON_NUM_PIN + BUTTON_UP_PIN + BUTTON_DOWN_PIN + BUTTON_BACKLIGHT_PIN)


// Macros for button press detection
#define BUTTON_STAR_IS_PRESSED		((BUTTONS_IN & BUTTON_STAR_PIN) == BUTTON_STAR_PIN)
#define BUTTON_NUM_IS_PRESSED		((BUTTONS_IN & BUTTON_NUM_PIN) == BUTTON_NUM_PIN)
#define BUTTON_UP_IS_PRESSED		((BUTTONS_IN & BUTTON_UP_PIN) == BUTTON_UP_PIN)
#define BUTTON_DOWN_IS_PRESSED		((BUTTONS_IN & BUTTON_DOWN_PIN) == BUTTON_DOWN_PIN)
#define BUTTON_BACKLIGHT_IS_PRESSED	((BUTTONS_IN & BUTTON_BACKLIGHT_PIN) == BUTTON_BACKLIGHT_PIN)
#define NO_BUTTON_IS_PRESSED		((BUTTONS_IN & ALL_BUTTONS) == 0)

// Macros for button release detection
#define BUTTON_STAR_IS_RELEASED			((BUTTONS_IN & BUTTON_STAR_PIN) == 0)
#define BUTTON_NUM_IS_RELEASED			((BUTTONS_IN & BUTTON_NUM_PIN) == 0)
#define BUTTON_UP_IS_RELEASED			(BUTTONS_IN & BUTTON_UP_PIN) == 0)
#define BUTTON_DOWN_IS_RELEASED			((BUTTONS_IN & BUTTON_DOWN_PIN) == 0)
#define BUTTON_BACKLIGHT_IS_RELEASED	((BUTTONS_IN & BUTTON_BACKLIGHT_PIN) == 0)

// Button debounce time (msec)
#define BUTTONS_DEBOUNCE_TIME_IN	(5u)
#define BUTTONS_DEBOUNCE_TIME_OUT	(250u)
#define BUTTONS_DEBOUNCE_TIME_LEFT	(50u)

// Detect if STAR / NUM button is held low continuously
#define LEFT_BUTTON_LONG_TIME		(2u)

// Leave set_value() function after some seconds of user inactivity
#define INACTIVITY_TIME			(30u)


// Set of button flags
typedef union
{
  struct
  {
  	// Manual button events
	unsigned short star    	: 1;    // Short STAR button press
    unsigned short num     	: 1;    // Short NUM button press
    unsigned short up      	: 1;    // Short UP button press
    unsigned short down      	: 1;    // Short DOWN button press
    unsigned short backlight  	: 1;    // Short BACKLIGHT button press
    unsigned short star_long   : 1;    // Long STAR button press
    unsigned short num_long   	: 1;    // Long NUM button press
  } flag;
  unsigned short all_flags;            // Shortcut to all display flags (for reset)
} s_button_flags;
extern volatile s_button_flags button;

struct struct_button
{
	unsigned  star_timeout;
	unsigned  num_timeout;
	signed repeats;
};
extern volatile struct struct_button sButton;

// Prototypes
void buttons_initiate(void);

#endif /*BUTTONS_H_*/
