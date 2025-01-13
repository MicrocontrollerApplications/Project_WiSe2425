/*
 * File:   SHT21_lib.c
 * Author: basti
 *
 * Created on January 12, 2025, 8:01 PM
 */

#include "SHT21_lib.h"

#include "SHT21/SHT21.h"
#include "LCD/GLCDnokia.h"

#define TMR1_85MS_OFFSET (65535 - 85*500)    // 500 cycles =  1ms  (Fosc = 16MHz)
#define TMR1_29MS_OFFSET (65535 - 29*500)
#define GLCD_MODE() {SSP1CON1bits.SSPEN = 0; TRISCbits.TRISC3 = 0;}
#define I2C_MODE() {TRISCbits.TRISC3 = 1; SSP1CON1bits.SSPEN = 1;}

void sht21_next_state(SHT21* sht21) {
    // increase state (i.e. move to next one)
    sht21->current_state++;
    /* the states are stored as enums. Enums are more or less simply named
     * variables representing an integer. See SHT21_lib.h line 15 for more
     * information .
     */
    if (TEMP_HUMIDITY < sht21->current_state) {
        sht21->current_state = TEMPERATURE;
    }
    sht21->measurement_type = sht21->current_state;
    if (TEMP_HUMIDITY == sht21->measurement_type)
        sht21->measurement_type = TEMPERATURE;

    sht21->state_transition = 1;
}

static void start_temp_meas(void) {
    // send measure command to SHT21
    wrSHT21(CMD_TRIG_T);
    // start delay timer
    TMR1 = TMR1_85MS_OFFSET;
}

static void start_rh_meas(void) {
    // send measure command to SHT21
    wrSHT21(CMD_TRIG_RH);
    // start delay timer
    TMR1 = TMR1_29MS_OFFSET;
}

extern void start_measurement(SHT21* sht21) {
    if (HUMIDITY == sht21->current_state) {
        start_rh_meas();
        sht21->measurement_type = HUMIDITY;
    } else if (TEMPERATURE == sht21->current_state) {
        start_temp_meas();
        sht21->measurement_type = TEMPERATURE;
    } else if (TEMP_HUMIDITY == sht21->current_state) {
        // Is temperature already measured and we're waiting for an RH measure?
        if (sht21->await_rh_meas) {
            start_rh_meas();
            sht21->measurement_type = HUMIDITY;
            sht21->await_rh_meas = 0;
        }// Currently, there's only on other measurement than RH -> temperature
        else {
            start_temp_meas();
            sht21->measurement_type = TEMPERATURE;
            sht21->await_rh_meas = 1;
        }
    }

    T1CONbits.TMR1ON = 1;
}

extern void get_measurement(SHT21* sht21) {
    // immediately read new value

    uint16_t temp = 0;
    rdSHT21(&temp);

    // set flag to indicate new measurement value
    sht21->new_meas = 1;
    // disable delay timer
    T1CONbits.TMR1ON = 0;

    if (TEMPERATURE == sht21->measurement_type) {
        sht21->measurement = SHT21_TEMP_FROM_VAL(temp);
    } else if (HUMIDITY == sht21->measurement_type) {
        sht21->measurement = SHT21_RH_FROM_VAL(temp);
    }

    if (TEMP_HUMIDITY == sht21->current_state) {
        sht21->new_temp_meas = 1;
        if (HUMIDITY == sht21->measurement_type) {
            sht21->new_temp_meas = 0;
            sht21->new_rh_meas = 1;
        }
    }
}

// Helper functions for sht21_print_measurement
static void print_measurement(float measurement, char* unit);
static void print_temp_hum_measurement(SHT21* sht21);

void sht21_print_measurement(SHT21* sht21) {
    // If state of SHT21 changed, we should reset the Display.
    if (sht21->state_transition) {
        sht21->state_transition = 0;
        GLCD_MODE();
        GLCD_Clear2Row(1);
        if (TEMP_HUMIDITY == sht21->current_state) {
            GLCD_TextOut(2, 0, " TEMP   HUM ");
        }
        I2C_MODE();
    }

    if (TEMP_HUMIDITY == sht21->current_state) {
        print_temp_hum_measurement(sht21);
        return;
    }

    char* unit;
    if (TEMPERATURE == sht21->measurement_type) {
        unit = "C";
    } else if (HUMIDITY == sht21->measurement_type) {
        unit = "RH";
    }
    print_measurement(sht21->measurement, unit);
}

static void print_measurement(float measurement, char* unit) {
    unsigned char col = 2;
    static char text[] = "  00.00 ";
    text[0] = ' ';
    text[1] = ' ';
    if (measurement < 0) {
        text[1] = '-';
        measurement *= -1;
    }
    if (measurement >= 100) {
        // move sign one char to the left
        text[0] = text[1];
        // get hundred place and convert to character ("letter of value")
        text[1] = (char) (measurement / 100) + 48;
        // reduce measurement by 100 for further processing
        measurement -= 100;
    }
    int8_t integer_part = (int8_t) measurement;
    int8_t decimal_part = (int8_t) ((measurement - integer_part)*100);

    text[col++] = (char) (integer_part / 10) + 48;
    text[col++] = (char) (integer_part % 10) + 48;
    ++col;
    text[col++] = (char) (decimal_part / 10) + 48;
    text[col++] = (char) (decimal_part % 10) + 48;

    GLCD_MODE();
    GLCD_Text2Out(1, 0, text);
    GLCD_Text2Out(1, 7, unit);
    I2C_MODE();
}

static void print_temp_hum_measurement(SHT21* sht21) {
    unsigned char col;
    if (sht21->new_temp_meas) {
        col = 1;
        sht21->new_temp_meas = 0;
    }
    if (sht21->new_rh_meas) {
        col = 8;
        sht21->new_rh_meas = 0;
    }

    int8_t integer_part = (int8_t) sht21->measurement;
    int8_t decimal_part = (int8_t) ((sht21->measurement - integer_part)*100);


    static char text[] = " 00.00  00.00";
    // if awaiting rh measurement, current measurement must be temperature
    text[col - 1] = ' ';
    if (integer_part < 0) {
        text[1] = '-';
        integer_part *= -1;
    }
    if (integer_part >= 100) {
        // move sign one char to the left
        text[0] = text[1];
        // get hundred place and convert to character ("letter of value")
        text[1] = (char) (integer_part / 100) + 48;
        // reduce measurement by 100 for further processing
        integer_part -= 100;
    }

    text[col++] = (char) (integer_part / 10) + 48;
    text[col++] = (char) (integer_part % 10) + 48;
    ++col;
    text[col++] = (char) (decimal_part / 10) + 48;
    text[col++] = (char) (decimal_part % 10) + 48;

    /* Ask us for what is going on here. Below macros GLCD_MODE() and I2C_Mode()
     * are not part of the exercise!
     */
    GLCD_MODE();
    GLCD_TextOut(3, 0, text);
    I2C_MODE();
}
