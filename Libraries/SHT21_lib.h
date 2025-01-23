/* 
 * File:   SHT21_lib.h
 * Author: Sebastian Moosbauer
 * Comments: This lib is still under development
 * Revision history: v.01 - initial library
 */

#include <xc.h>
#include <stdbool.h>

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SHT21_LIB
#define	SHT21_LIB

/* An enum is a colletion of named variables representing an individual integer
 * value. If not implement otherwise, the first Name represents value 0, the
 * second represents value 2, and so on.
 * For more information on Enums have a look at:
 * https://www.tutorialspoint.com/cprogramming/c_enumeration_or_enum.htm
 * Or ask us in the lab! ;)
 */
typedef enum{
    TEMPERATURE,
    HUMIDITY,
    TEMP_HUMIDITY,
} State;

typedef struct {
    State current_state;
    State measurement_type;
    bool state_transition;
    float  measurement;
    // unsigned char new_meas;
    bool new_meas;
    bool new_temp_meas;
    bool new_rh_meas;
    bool await_rh_meas;
    
}SHT21;

// change to next state. Used if button is clicked
extern void sht21_next_state(SHT21* state);

// start measurement depending on the current state / measurement mode
extern void start_measurement(SHT21* state);
// get measurement depending on the current state / measurement mode and 
// start additional measurements if required
extern void get_measurement(SHT21* state);

// print the sensors measurement to LCD
extern void sht21_print_measurement(SHT21* state);

#endif	/* XC_HEADER_TEMPLATE_H */

