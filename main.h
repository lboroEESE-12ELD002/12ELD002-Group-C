#ifndef MAIN_H_
#define MAIN_H_

#include "cc430x613x.h" //Processor header.
#include "cc430f6137.h"

// Macro section
// Conversion from usec to ACLK timer ticks
#define CONV_US_TO_TICKS(usec)         			(((usec) * 32768) / 1000000)
// Conversion from msec to ACLK timer ticks
#define CONV_MS_TO_TICKS(msec)         			(((msec) * 32768) / 1000)

//Peripheral headers
#include "buttons.h"
#include "buzzer.h"
#include "clock.h"
#include "LCD.h"
#include "vti_as.h"
#include "accel.h"

//Prototypes
void app_initiate (void);

#endif /*MAIN_H_*/
