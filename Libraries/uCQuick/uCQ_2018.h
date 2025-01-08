//##############################################################################
//      filename:               uCQ_2018.h
//
//      meaningful pin-names (signals) and macro definitions
//      for demo projects on uCQ_2018 platform
//
//##############################################################################
//
//      Author:                 V.SchK
//      Company:                HS-Ulm
//
//      Revision:               3.0 (XC8 only)
//      Date:                   November 2019
//      Assembled using         MPLABX v5.00+ / XC8 v2.00++
//
//      todo	- add comments ;-)
//              -
//
//##############################################################################/*

#ifndef UCQ_2018_H
#define	UCQ_2018_H

#include <xc.h>         // XC8 compiler

#warning "##### please check which kind of ecoder is populated! #####"
#define ENCODER_TOGGLE   //
//                                 //    ___     ___     ___
//# ifdef ENCODER_TOGGLE           // __|   |___|   |___|   |__ (toggles)
//# else                           // __ ___ ___ ___ ___ ___ ___
//                                 //   |   |   |   |   |   |   (pulses)

//#define POTI_AT_A1

//----------------------------------------------------------internal clock freq.
#if defined(__18F25K22) | defined(__18F24K22) | defined(__18F26K22)
    #define IRCF_16MHZ  0b111
    #define IRCF_8MHZ   0b110
    #define IRCF_4MHZ   0b101
    #define IRCF_2MHZ   0b100
    #define IRCF_1MHZ   0b011
    #define IRCF_500KHZ 0b010
    #define IRCF_250KHZ 0b001
    #define IRCF_31KHZ  0b000
#endif

// ---------------------------------------------------------------pin directions
#define INPUT_PIN           1
#define OUTPUT_PIN          0
#define INPUT_REG           0xFF
#define OUTPUT_REG          0x00
#define DIGITAL_PIN          0
#define ANALOG_PIN           1
#define mALL_IO_DIGITAL()   ANSELA = ANSELB = ANSELC = 0x00

// -----------------------------------------------------------------push buttons
#define BTN_L               PORTBbits.RB2               // left button
#define BTN_L_TRI           TRISBbits.TRISB2
#define BTN_L_ANS           ANSELBbits.ANSB2
#define BTN_R               PORTBbits.RB4               // right button
#define BTN_R_TRI           TRISBbits.TRISB4
#define BTN_R_ANS           ANSELBbits.ANSB4

#define BTN_ACTIVATED       0
#define mGET_BTN_L()        (BTN_L == BTN_ACTIVATED)
#define mGET_BTN_R()        (BTN_R == BTN_ACTIVATED)
//#define mGET_BTN_ENC()      mGET_ENC_BTN()

// -------------------------------------------------------------------------LEDs
#define LED_1               LATBbits.LATB2
#define LED_1_TRI           TRISBbits.TRISB2
#define LED_2               LATBbits.LATB3
#define LED_2_TRI           TRISBbits.TRISB3
#define LED_3               LATBbits.LATB4
#define LED_3_TRI           TRISBbits.TRISB4
#define LED_4               LATBbits.LATB5
#define LED_4_TRI           TRISBbits.TRISB5

#define LED_ON              0
#define LED_OFF             1
#define mSET_LED_1_ON()     LED_1 = LED_ON
#define mSET_LED_1_OFF()    LED_1 = LED_OFF
#define mTOG_LED_1()        LED_1 ^= 1
#define mGET_LED_1()        (LED_1 ^ LED_OFF)
#define mSET_LED_2_ON()     LED_2 = LED_ON
#define mSET_LED_2_OFF()    LED_2 = LED_OFF
#define mTOG_LED_2()        LED_2 ^= 1
#define mGET_LED_2()        (LED_2 ^ LED_OFF)
#define mSET_LED_3_ON()     LED_3 = LED_ON
#define mSET_LED_3_OFF()    LED_3 = LED_OFF
#define mTOG_LED_3()        LED_3 ^= 1
#define mGET_LED_3()        (LED_3 ^ LED_OFF)
#define mSET_LED_4_ON()     LED_4 = LED_ON
#define mSET_LED_4_OFF()    LED_4 = LED_OFF
#define mTOG_LED_4()        LED_4 ^= 1
#define mGET_LED_4()        (LED_4 ^ LED_OFF)

#define mALL_LED_OFF()      LATB |= 0b00111100
#define mALL_LED_ON()       LATB &= 0b11000011
#define mALL_LED_OUTPUT()   TRISB  &= 0b11000011

// ---------------------------------------------------------------digital inputs
#define TTL_IN          PORTAbits.RA0
#define TTL_IN_TRI      TRISAbits.TRISA0
#define TTL_IN_ANS      ANSELAbits.ANSA0
#define ST_IN           PORTCbits.RC3
#define ST_IN_TRI       TRISCbits.TRISC3
#define ST_IN_ANS       ANSELCbits.ANSC3

// ---------------------------------------------------------------rotary encoder
#define ENC_BTN         PORTBbits.RB1
#define ENC_BTN_TRI     TRISBbits.TRISB1
#define ENC_BTN_ANS     ANSELBbits.ANSB1
#define mGET_ENC_BTN()  (ENC_BTN == BTN_ACTIVATED)

#define ENCBTN_IR_FLAG      INTCON3bits.INT1IF
#define ENCBTN_IR           INTCON3bits.INT1IE && INTCON3bits.INT1IF
#define mENCBTN_IR_EN()     INTCON3bits.INT1IE = 1
#define mENCBTN_IR_DIS()    INTCON3bits.INT1IE = 0
#define mENCBTN_IR_CLR()    INTCON3bits.INT1IF = 0


#define ENC_INT         PORTBbits.INT0          // A -> interrupt pin int_0/b_0
#define ENC_INT_TRI     TRISBbits.TRISB0
#define ENC_INT_ANS     ANSELBbits.ANSB0
#define ENC_DIR         PORTAbits.RA2           // B -> direction pin a_2
#define ENC_DIR_TRI     TRISAbits.TRISA2
#define ENC_DIR_ANS     ANSELAbits.ANSA2
//#define ENC_DIR         PORTEbits.RE3         // alternative selection (JP4)
//#define ENC_DIR_TRI     TRISEbits.TRISE3

#define ENC_A           PORTBbits.RB0
#define ENC_A_TRI       ENC_INT_TRI
#define ENC_A_ANS       ENC_INT_ANS
#define ENC_B           ENC_DIR
#define ENC_B_TRI       ENC_DIR_TRI
#define ENC_B_ANS       ENC_DIR_ANS


#define ENC_IR_FLAG     INTCONbits.INT0IF
#define ENC_IR          INTCONbits.INT0IE && INTCONbits.INT0IF
#define mENC_IR_DIS()   INTCONbits.INT0IE = 0
                                //    ___     ___     ___
#ifdef ENCODER_TOGGLE           // __|   |___|   |___|   |__ (toggles)
    #define ENC_DIR_UP          !INTCON2bits.INTEDG0
    #define ENC_DIR_DOWN        INTCON2bits.INTEDG0
    #define mENC_IR_EN()        INTCON2bits.INTEDG0 = !ENC_INT; \
                                INTCONbits.INT0IE = 1
    #define mENC_IR_RST()       INTCON2bits.INTEDG0 ^= 1; INTCONbits.INT0IF = 0
//    #define ENCODER_PANASONIC   // compatibility with old code

#else                           // __ ___ ___ ___ ___ ___ ___
    #define ENC_DIR_UP      1   //   |   |   |   |   |   |   (pulses)
    #define ENC_DIR_DOWN    0
    #define mENC_IR_EN()    INTCON2bits.INTEDG0 = 0; INTCONbits.INT0IE = 1
    #define mENC_IR_RST()   INTCONbits.INT0IF = 0
#endif

// ----------------------------------------------------------analog input (poti)
#if defined(POTI_AT_A1)
  #define POTI_TRI        TRISAbits.TRISA1
  #define POTI_ANS        ANSELAbits.ANSA1
  #define ADC_POTI        ADC_CH1
#else
  #define POTI_TRI        TRISAbits.TRISA0
  #define POTI_ANS        ANSELAbits.ANSA0
  #define ADC_POTI        ADC_CH0
#endif

#define ADC_IR          PIE1bits.ADIE && PIR1bits.ADIF
#define mADC_IR_EN()    PIE1bits.ADIE = 1
#define mADC_IR_DIS()   PIE1bits.ADIE = 0
#define mADC_IR_CLR()   PIR1bits.ADIF = 0

// ----------------------------------------------------------------------speaker
#define SPEAKER         LATCbits.LATC2
#define SPEAKER_TRI     TRISCbits.TRISC2
#define mTOG_SPEAKER()  SPEAKER = !SPEAKER

// ------------------------------------------------------------------------RS232
#define TX_PIN          LATCbits.LATC6
#define RX_PIN          PORTCbits.RC7
#define TX_TRI          TRISCbits.TRISC6
#define RX_TRI          TRISCbits.TRISC7
#define RX_ANS          ANSELCbits.ANSC7
#define TX_FREE         PIR1bits.TX1IF

// ------------------------------------------------------------BOOTLOADER (TEST)
#if defined(__18F24K22)
    #define BOOTLOADER_1310 0x3D0C
#elif defined(__18F25K22)
    #define BOOTLOADER_1310 0x7D0C
#elif defined(__18F26K22)
    #define BOOTLOADER_1310 0xFD0C
#endif

#define BOOTLOADER_TEST()  ENC_BTN_ANS = DIGITAL_IN;            \
        if(mGET_ENC_BTN()){ _asm goto BOOTLOADER_1310 _endasm }



// ------------------------------------------------------------debug help signal
#define dbgSIGNAL       SPEAKER
#define dbgSIGNAL_TRI   SPEAKER_TRI
#define dbgPULSE()      mTOG_SPEAKER();mTOG_SPEAKER()

//#define mENCBTN_DEBUG_STOP()
//#define SOFT_BREAK()

#endif	/* UCQ_2018_H */
