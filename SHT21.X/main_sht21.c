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

#include "uCQuick/uCQ_2018.h"
#include "SHT21/SHT21.h"
#include "LCD/GLCDnokia.h"
#define MILLION 1000*1000UL
#define _XTAL_FREQ 16*MILLION

#define TMR0_1S_OFFSET 65535 - 15625 // 15526 cycles = 1s (Fosc = 16MHz)
#define TMR0_1S_PS 0b111
#define TMR1_85MS_OFFSET 65535 - 42500 // 42500 cycles = 85ms  (Fosc = 16MHz)
#define TMR1_85MS_PS 0b11

static void __init(void);
static void __interrupt(high_priority) __isr(void);
static void decimal_to_glcd(float decimal);

static char new_meas = 0;
static uint16_t valT; //42°C as initial value
static uint16_t valRH;

int main() {
    __init();
    
    int8_t temp_int, temp_dec;
    float temperature;
    while (1) {
        if (new_meas) {
            new_meas = 0;
            temperature = SHT21_TEMP_FROM_VAL(valT);
            if (temperature >= -40 && temperature <= 125) {
                decimal_to_glcd(temperature);
            }else{
                GLCD_Text2Out(1, 0, " XX.XX C");
                GLCD_Text2Out(2, 0, " !!ERROR!!");
            }
        }
    }
}

static void __init() {
    OSCCONbits.IRCF = IRCF_16MHZ;

    GLCD_Init();
    GLCD_Text2Out(0, 0, " SHT_21 ");
    GLCD_Text2Out(1, 0, " ??.?? C");

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
        TMR0 += TMR0_1S_OFFSET;

        // send measure command to SHT21
        wrSHT21(CMD_TRIG_T);
        // start delay timer
        TMR1 = TMR1_85MS_OFFSET;
        T1CONbits.TMR1ON = 1;

        return;
    }
    
    if(PIE1bits.TMR1IE && PIR1bits.TMR1IF){
        // immediately read new value
        rdSHT21(&valT);
        
        PIR1bits.TMR1IF = 0;
        // set flag to indicate new measurement value
        new_meas = 1;
        // disable delay timer
        T1CONbits.TMR1ON = 0;
        
        return;
    }

    // catch unexpected interrupts
    while (1) {
        Nop();
    }
}

#define GLCD_MODE() {SSP1CON1bits.SSPEN = 0; TRISCbits.TRISC3 = 0;}
#define I2C_MODE() {TRISCbits.TRISC3 = 1; SSP1CON1bits.SSPEN = 1;}
static void decimal_to_glcd(float decimal){
    
    int8_t integer_part = (int8_t) decimal;
    int8_t decimal_part = (int8_t) ((decimal - integer_part)*100);
    
    GLCD_MODE();
    GLCD_Value2Out_00(1, 1, integer_part, 2);
    GLCD_Value2Out_00(1, 4, decimal_part, 2);
    I2C_MODE();
}
