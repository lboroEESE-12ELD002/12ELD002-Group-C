#ifndef ACCEL_H_
#define ACCEL_H_

// Include section

// Prototypes section

// Defines section
#define DISPLAY_ACCEL_X		(0u)
#define DISPLAY_ACCEL_Y		(1u)
#define DISPLAY_ACCEL_Z		(2u)

#define ACCEL_MODE_OFF		(0u)
#define ACCEL_MODE_ON		(1u)

// Stop acceleration measurement after 60 minutes to save battery
#define ACCEL_MEASUREMENT_TIMEOUT		(60*60u)

// Extern section
extern void reset_acceleration(void);
extern void sx_acceleration(unsigned line);
extern void display_acceleration(unsigned line, unsigned update);
extern unsigned is_acceleration_measurement(void);
extern void do_acceleration_measurement(void);
void check_accel (void);

#endif /* ACCEL_H_ */
