/*
 * File:   SHT21_lib.c
 * Author: basti
 *
 * Created on January 12, 2025, 8:01 PM
 */

#include "SHT21_lib.h"

#include "SHT21/SHT21.h"
#include "LCD/GLCDnokia.h"

#define TMR1_85MS_OFFSET 23035 //(65535 - 85*500)    // 500 cycles =  1ms  (Fosc = 16MHz)
#define TMR1_29MS_OFFSET 51035 //(65535 - 29*500)
#define GLCD_MODE() {SSP1CON1bits.SSPEN = 0; TRISCbits.TRISC3 = 0;}
#define I2C_MODE() {TRISCbits.TRISC3 = 1; SSP1CON1bits.SSPEN = 1;}

void sht21_next_state(SHT21_State* state) {
    state->current_state++;
    if (TEMP_HUMIDITY < state->current_state) {
        state->current_state = TEMPERATURE;
    }
    state->measurement_type = state->current_state;
    if (TEMP_HUMIDITY == state->measurement_type)
        state->measurement_type = TEMPERATURE;

    state->state_transition = 1;
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

extern void start_measurement(SHT21_State* state) {
    if (HUMIDITY == state->current_state) {
        start_rh_meas();
        state->measurement_type = HUMIDITY;
    } else if (TEMPERATURE == state->current_state) {
        start_temp_meas();
        state->measurement_type = TEMPERATURE;
    } else if (TEMP_HUMIDITY == state->current_state) {
        if (state->await_rh_meas) {
            start_rh_meas();
            state->measurement_type = HUMIDITY;
            state->await_rh_meas = 0;
        } else {
            start_temp_meas();
            state->measurement_type = TEMPERATURE;
            state->await_rh_meas = 1;
        }
    }

    T1CONbits.TMR1ON = 1;
}

extern void get_measurement(SHT21_State* state) {
    // immediately read new value

    uint16_t temp = 0;
    rdSHT21(&temp);

    // set flag to indicate new measurement value
    state->new_meas = 1;
    // disable delay timer
    T1CONbits.TMR1ON = 0;

    if (TEMPERATURE == state->measurement_type) {
        state->measurement = SHT21_TEMP_FROM_VAL(temp);
        return;
    }

    state->measurement = SHT21_RH_FROM_VAL(temp);
}

static void print_measurement(float measurement, char* unit) {
    unsigned char col = 2;
    static char text[] = "  00.00 ";
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

    Nop();
    GLCD_MODE();
    GLCD_Text2Out(1, 0, text);
    GLCD_Text2Out(1, 7, unit);
    I2C_MODE();
    Nop();
}

void sht21_print_measurement(SHT21_State* state) {
    if (TEMP_HUMIDITY == state->current_state) {
        static State internal_measurement_type = HUMIDITY;
        internal_measurement_type = HUMIDITY == internal_measurement_type ? TEMPERATURE : HUMIDITY;
        unsigned char col = TEMPERATURE == internal_measurement_type ? 1 : 8;

        int8_t integer_part = (int8_t) state->measurement;
        int8_t decimal_part = (int8_t) ((state->measurement - integer_part)*100);


        static unsigned char text[] = " 00.00  00.00";
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

        text[col++] = (unsigned char) (integer_part / 10) + 48;
        text[col++] = (unsigned char) (integer_part % 10) + 48;
        ++col;
        text[col++] = (unsigned char) (decimal_part / 10) + 48;
        text[col++] = (unsigned char) (decimal_part % 10) + 48;

        GLCD_MODE();
        if (state->state_transition) {
            state->state_transition = 0;
            GLCD_Clear();
            GLCD_Text2Out(0, 1, "SHT21");
            GLCD_TextOut(2, 0, " TEMP   HUM ");
        }
        GLCD_TextOut(3, 0, &text);
        I2C_MODE();

        return;
    }

    char* unit = TEMPERATURE == state->current_state ? "C" : "RH";
    print_measurement(state->measurement, unit);
}

