//##############################################################################
//      filename:        main.c
//
//      main file for �C lecture projects
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

#include "uCQuick/uCQ_2018.h"
#include "SHT21/SHT21.h"
#include "LCD/GLCDnokia.h"
#include "SHT21_lib.h"

#define MILLION 1000*1000UL
#define _XTAL_FREQ 16*MILLION

#define TMR0_1S_OFFSET (65535 - 15625) // 15526 cycles = 1s (Fosc = 16MHz)
#define TMR0_1S_PS 0b111
#define TMR1_85MS_OFFSET (65535 - 42500)    // 42500 cycles = 85ms  (Fosc = 16MHz)
#define TMR1_29MS_OFFSET (65535 - 29*500)   //   500 cycles =  1ms  (Fosc = 16MHz)
#define TMR1_85MS_PS 0b11



static void __init(void);
static void __interrupt(high_priority) __isr(void);
static void decimal_to_glcd(float decimal, char* unit);

static char new_meas = 0;
static uint16_t retVal;
static unsigned char meas_counter = 0;

static SHT21_State sht21_state = {
    .await_rh_meas = 0,
    .current_state = HUMIDITY,
    .measurement_type = HUMIDITY,
    .new_meas = 0,
    .measurement = 0,
    .state_transition = 0,
};

// TODO: clear Display on state change.
// TODO: numeral to string conversion must be enhanced for |num| >= 100 case.

int main() {
    __init();
    
    while (1) {        
        if (sht21_state.new_meas) {
            sht21_state.new_meas = 0;
            sht21_print_measurement(&sht21_state);
        }
    }
}

static void __init() {
    OSCCONbits.IRCF = IRCF_16MHZ;

    GLCD_Init();
    GLCD_Text2Out(0, 0, " SHT_21 ");
    GLCD_Text2Out(1, 3, ".");
    // GLCD_Text2Out(1, 0, " ??.?? C");

    ANSELCbits.ANSC3 = ANSELCbits.ANSC4 = 0; // I2C pins
    TRISCbits.TRISC3 = TRISCbits.TRISC4 = 1;

    // Interrupts
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    // Timer 0
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
    // Timer 1
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
    // TM
    INTCON3bits.INT1F = 0;
    INTCON3bits.INT1E = 1;
    INTCON2bits.INTEDG1 = 1;

    // Timer 0: measuring timer - duration 1s (Fosc = 16MHz)
    T0CONbits.T08BIT = 0;
    T0CONbits.T0CS = 0;
    T0CONbits.PSA = 0;
    T0CONbits.T0PS = TMR0_1S_PS; // Prescaler = 256
    TMR0 = TMR0_1S_OFFSET;
    T0CONbits.TMR0ON = 1;

    // Timer 1: SHT21 I2C delay timer - duration 85ms (Fosc = 16MHz)
    T1CONbits.TMR1CS = 0b00; // Fosc/4
    T1CONbits.T1CKPS = TMR1_85MS_PS; // PS = 8
    T1CONbits.T1RD16 = 1; // 16 bit mode
    TMR1 = TMR1_85MS_OFFSET; // offset to count to 42500 (=85ms)

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
        
        start_measurement(&sht21_state);

        return;

    }

    if (PIE1bits.TMR1IE && PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0;
        T1CONbits.TMR1ON = 0;
        get_measurement(&sht21_state);
        if (TEMP_HUMIDITY == sht21_state.current_state && sht21_state.await_rh_meas){
            start_measurement(&sht21_state);
        }

        return;
    }

    if (INTCON3bits.INT1E && INTCON3bits.INT1IF) {
        INTCON3bits.INT1IF = 0;
        sht21_next_state(&sht21_state);

        return;
    }

    // catch unexpected interrupts
    while (1) {
        Nop();
    }
}
