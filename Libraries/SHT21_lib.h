/* 
 * File:   SHT21_lib.h
 * Author: Sebastian Moosbauer
 * Comments: This lib is still under development
 * Revision history: v.01 - initial library
 */

#include <xc.h>

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SHT21_LIB
#define	SHT21_LIB

typedef enum{
    TEMPERATURE,
    HUMIDITY,
    TEMP_HUMIDITY,
} State;

typedef struct {
    State current_state;
    State measurement_type;
    unsigned char state_transition;
    float  measurement;
    unsigned char new_meas;
    unsigned char new_temp_meas;
    unsigned char new_rh_meas;
    unsigned char await_rh_meas;
    
}SHT21_State;

extern void sht21_next_state(SHT21_State* state);

extern void start_measurement(SHT21_State* state);
extern void get_measurement(SHT21_State* state);

extern void sht21_print_measurement(SHT21_State* state);

#endif	/* XC_HEADER_TEMPLATE_H */

