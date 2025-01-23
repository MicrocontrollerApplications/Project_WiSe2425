//##############################################################################
//      filename:        main.c
//
//      main file for µC lecture projects
//
//##############################################################################
//
//  Author:             S. Moosbauer
//  Company:            THU
//
//  Revision:           1.0 (XC8 compatible)
//  Date:               December 2024
//  Assembled using     XC8 2.50
//
//  todo    - enjoy learning! ;) 
//          -
//
//##############################################################################

#include <xc.h>
#include <stdbool.h>

#include "uCQuick/uCQ_2018.h"
#include "SHT21/SHT21.h"
#include "LCD/GLCDnokia.h"
#include "SHT21_lib.h"

#define MILLION 1000*1000UL
#define _XTAL_FREQ 16*MILLION

#define TMR0_1S_OFFSET (65535 - 15625) // 15526 cycles = 1s (Fosc = 16MHz)

static void __init(void);
static void __interrupt(high_priority) __isr(void);

// Initialize SHT21 object
static SHT21 sht21_sensor = {
    .current_state = TEMPERATURE,
    .measurement_type = TEMPERATURE,
    .state_transition = false,
    .measurement = 0,
    .new_meas = false,
    .new_temp_meas = false,
    .new_rh_meas = false,
    .await_rh_meas = false,
};

int main() {
    __init();
    
    while (1) {        
        if (sht21_sensor.new_meas) {
            sht21_sensor.new_meas = 0;
            sht21_print_measurement(&sht21_sensor);
        }
    }
}

static void __init() {
    /*
     * ATTENTION
     * Below line is relevant! Which Fosc do we use?
     */
    OSCCONbits.IRCF = IRCF_16MHZ;

    GLCD_Init();
    GLCD_Text2Out(0, 0, " SHT_21 ");

    /*
     * ATTENTION
     * Exercise 4
     * What is done below and why? Check the serial communication first! ;)
     */
    ANSELCbits.ANSC3 = 0;
    ANSELCbits.ANSC4 = 0; 
    TRISCbits.TRISC3 = 0;
    TRISCbits.TRISC4 = 1;

    // Interrupts
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    // TM
    INTCON3bits.INT1F = 0;
    INTCON3bits.INT1E = 1;
    INTCON2bits.INTEDG1 = 1;
    
    /*
     * ATTENTION
     * Exercise 3.1
     * Configure timer below!
     * HINT: have a look at TMR0_1S_OFFSET could it be useful?
     */
    // Timer 0
    
    
    // Timer 1
    
    

    // Timer 0 config: measuring timer - duration 1s
    

    // Timer 1: SHT21 delay timer
    
    

    SSP1ADD = 39; // I2C baudrate 100kHz
    initSHT21(MODE_RH12_T14_BIT | DIS_OC_HEATER | DIS_OTP_RELOAD);
}

static void __interrupt(high_priority) __isr() {
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
        INTCONbits.TMR0IF = 0;
        // offset Timer 0
        // TMR0 = TMR0 + TMR0_1S_OFFSET; // does not work? ~3s intervals
        T0CONbits.TMR0ON = 0;
        TMR0 = TMR0_1S_OFFSET;
        T0CONbits.TMR0ON = 1;
        
        start_measurement(&sht21_sensor);

        return;

    }

    if (PIE1bits.TMR1IE && PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0;
        T1CONbits.TMR1ON = 0;
        get_measurement(&sht21_sensor);
        if (TEMP_HUMIDITY == sht21_sensor.current_state && sht21_sensor.await_rh_meas){
            start_measurement(&sht21_sensor);
        }

        return;
    }

    if (INTCON3bits.INT1E && INTCON3bits.INT1IF) {
        INTCON3bits.INT1IF = 0;
        sht21_next_state(&sht21_sensor);

        return;
    }

    // catch unexpected interrupts
    while (1) {
        Nop();
    }
}
