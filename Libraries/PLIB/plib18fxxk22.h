/*
 * File:   plib18fxxk22.h
 * Author: vsk HS-Ulm
 *
 * Created on 15. März 2016, 16:16
 */

// for documentation see: MPLAB_XC8_Peripheral_Libraries.pdf

/*
 * added legacy plib functions
 *
 * 15.03.2016   VSK
 * + OpenADC()          tested with uCQ_Base->BoardTest()
 * - #define BusyADC()          ADCON0bits.NOT_DONE
 * - #define ConvertADC()       ADCON0bits.GO = 1
 * - #define CloseADC()         ADCON0bits.ADON = 0; PIE1bits.ADIE = 0
 * - #define ReadADC()          ADRES
 * - #define SetChanADC(ch)     ADCON0 = (ADCON0 & 0b10000011) | (ch & 0b01111100)
 * - #define SelChanConvADC(ch) SetChanADC(ch); ADCON0bits.GO = 1;
 * -----------------------------------------------------------------------------
 * + OpenECapture1()    tested with uCQ_Base->TimeMeasure()
 * - OpenECompare2()
 * - OpenECompare3()
 * -----------------------------------------------------------------------------
 * - OpenTimer0()       not tested
 * - ReadTimer0()       not tested
 * - WriteTimer0()      not tested
 * + OpenTimer1()       tested with uCQ_Base->ClockMenu()
 * - ReadTimer1()       not tested
 * - WriteTimer1()      not tested
 * + OpenTimer2()       tested with uCQ_Base->BoardTest()
 * - #define CloseTimer2()      T2CONbits.TMR2ON = 0; PIE1bits.TMR2IE = 0
 * - #define WriteTimer2(value) TMR2 = (value)
 * - #define ReadTimer2()       TMR2
 * + OpenTimer5()       tested with uCQ_Base->BoardTest()
 * - ReadTimer5()       not tested
 * - WriteTimer5()      not tested
 * -----------------------------------------------------------------------------
 * + #define baud1USART(config) BAUDCON1 = config
 * + Open1USART()       tested with uCQ_Base->BoardTest()
 * - #define baud2USART(config) BAUDCON1 = config
 * - Open2USART()       not tested
 * -----------------------------------------------------------------------------
 * + OpenSPI1()         tested with uCQ-AddOnBoards
 * + ReadSPI1()           "
 * + WriteSPI1()          "
 * - allOtherSPI1       not tested
 * -----------------------------------------------------------------------------
 *  OpenI2C1()          not tested
 *  WriteI2C1()
 *  ReadI2C1()
 *  StopI2C1()
 *  StartI2C1()
 *  RestartI2C1()
 *  AckI2C1()
 *  NotAckI2C1()
 *  IdleI2C1()
 * -----------------------------------------------------------------------------
*
 *TODO
 * OpenECompare2()
 * OpenEPWM2()
 * SetOutputEPWM2()
 * SetDCEPWM2()
 */

/*############################################################*/
/*  old plib    configuration for device =  'PIC18FxxK22'     */
/*############################################################*/
/*
 ADC        #define ADC_V14     (_1 for 28pin device)
 ECC        #define ECC_V9      (_1 for 28pin device)
 CC         #define CC_V9       (_1 for 28pin device)
 EPWM       #define EPWM_V15    (_1 for 28pin device)
 PWM        #define PWM_V15     (_1 for 28pin device)
 PCPWM      **No configuration chosen for this peripheral**
 USART      #define EAUSART_V11
 SPI        #define SPI_V5
            #define SPI_IO_V11  (2xk22)
            #define SPI_IO_V12  (4xk22)
 I2C        #define I2C_V6
 TIMERS     #define TMR_V7_3
 EEPROM     #define EEP_V2
 PORT_B     #define PTB_V1
 ANCOMP     #define ANCOM_V8
 MWIRE      #define MWIRE_V5
 CTMU       #define CTMU_V1_1
 PPS        No configuration chosen for this peripheral
 RTCC       No configuration chosen for this peripheral
 DPSLP      No configuration chosen for this peripheral
 PMP        No configuration chosen for this peripheral
 FLASH      #define FLASH_V1_4
*/

#ifndef PLIB18FXXK22_H
#define PLIB18FXXK22_H

#include <xc.h>

#define NON_BLOCKING    // avoid blocking funktions by using TimeOuts
#ifndef I2C_TIMEOUT
    #define I2C_TIMEOUT 100
#endif

//extern uint16_t Plib_TO_cnt;

#ifndef USE_OR_MASKS
    //*************** A/D Conversion Clock Selection *****************************
    #define ADC_FOSC_2      0b10001111      //A/D conversion clock source is Fosc/2
    #define ADC_FOSC_4      0b11001111      //A/D conversion clock source is Fosc/4
    #define ADC_FOSC_8      0b10011111      //A/D conversion clock source is Fosc/8
    #define ADC_FOSC_16     0b11011111      //A/D conversion clock source is Fosc/16
    #define ADC_FOSC_32     0b10101111      //A/D conversion clock source is Fosc/32
    #define ADC_FOSC_64     0b11101111      //A/D conversion clock source is Fosc/64
    #define ADC_FOSC_RC     0b11111111      //A/D conversion clock source is Internal RC OSC

    //************** A/D Acquisition Time Selection *******************************
    #define ADC_0_TAD       0b11110001      //A/D Acquisition Time is 0 TAD
    #define ADC_2_TAD       0b11110011      //A/D Acquisition Time is 2 TAD
    #define ADC_4_TAD       0b11110101      //A/D Acquisition Time is 4 TAD
    #define ADC_6_TAD       0b11110111      //A/D Acquisition Time is 6 TAD
    #define ADC_8_TAD       0b11111001      //A/D Acquisition Time is 8 TAD
    #define ADC_12_TAD      0b11111011      //A/D Acquisition Time is 12 TAD
    #define ADC_16_TAD      0b11111101      //A/D Acquisition Time is 16 TAD
    #define ADC_20_TAD      0b11111111      //A/D Acquisition Time is 20 TAD

    //*************** ADC Interrupt Enable/Disable *****************************
    #define ADC_INT_ON      0b11111111      //A/D Interrupt Enable
    #define ADC_INT_OFF     0b01111111      //A/D Interrupt Disable

#else // USE_OR_MASKS
    //*************** A/D Conversion Clock Select ******************************
    #define ADC_FOSC_2      0b00000000      //A/D conversion clock source is Fosc/2
    #define ADC_FOSC_4      0b01000000      //A/D conversion clock source is Fosc/4
    #define ADC_FOSC_8      0b00010000      //A/D conversion clock source is Fosc/8
    #define ADC_FOSC_16     0b01010000      //A/D conversion clock source is Fosc/16
    #define ADC_FOSC_32     0b00100000      //A/D conversion clock source is Fosc/32
    #define ADC_FOSC_64     0b01100000      //A/D conversion clock source is Fosc/64
    #define ADC_FOSC_RC     0b01110000      //A/D conversion clock source is Internal RC OSC
    #define ADC_FOSC_MASK   (~ADC_FOSC_RC)  //Mask A/D conversion clock source bits

    //************** A/D Acquisition Time Selection ****************************
    #define ADC_0_TAD       0b00000000      //A/D Acquisition Time is 0 TAD
    #define ADC_2_TAD       0b00000010      //A/D Acquisition Time is 2 TAD
    #define ADC_4_TAD       0b00000100      //A/D Acquisition Time is 4 TAD
    #define ADC_6_TAD       0b00000110      //A/D Acquisition Time is 6 TAD
    #define ADC_8_TAD       0b00001000      //A/D Acquisition Time is 8 TAD
    #define ADC_12_TAD      0b00001010      //A/D Acquisition Time is 12 TAD
    #define ADC_16_TAD      0b00001100      //A/D Acquisition Time is 16 TAD
    #define ADC_20_TAD      0b00001110      //A/D Acquisition Time is 20 TAD
    #define ADC_TAD_MASK    (~ADC_20_TAD)   //Mask A/D Acquisition Time bits

    //*************** ADC Interrupt Enable/Disable *****************************
    #define ADC_INT_ON      0b10000000      //A/D Interrupt Enable
    #define ADC_INT_OFF     0b00000000      //A/D Interrupt Disable
    #define ADC_INT_MASK    (~ADC_INT_ON)   //Mask A/D Interrupt
#endif    // USE_OR_MASKS


#ifndef    USE_OR_MASKS
    //*************** A/D Result Format Select ***********************************
    #define ADC_RIGHT_JUST      0b11111111      // Right justify A/D result
    #define ADC_LEFT_JUST       0b01111111      // Left justify A/D result
#else // USE_OR_MASKS
    //*************** A/D Result Format Select ***********************************
    #define ADC_RIGHT_JUST      0b10000000      // Right justify A/D result
    #define ADC_LEFT_JUST       0b00000000      // Left justify A/D result
    #define ADC_RESULT_MASK     (~ADC_RIGHT_JUST)   //Mask ADC Result adjust bit
#endif // USE_OR_MASKS

#ifndef USE_OR_MASKS
    //************** Positive Voltage Reference Configuration *************************
    #define ADC_REF_VDD_VDD         0b11110011  // ADC voltage positive source VREF+ = AVDD
    #define ADC_REF_VDD_VREFPLUS    0b11110111  // ADC voltage positive source VREF+ = ext. source at VREF+
    #define ADC_REF_FVR_BUF         0b11111011  // ADC voltage positive source VREF+ = FVR BUF
    //************** Negetive Voltage Reference Configuration *************************
    #define ADC_REF_VDD_VSS         0b11111100  // ADC voltage negetive source VREF- = AVSS
    #define ADC_REF_VDD_VREFMINUS   0b11111101  // ADC voltage negetive source VREF- = ext. source at VREF-
#else //USE_OR_MASKS
    //************** Positive Voltage Reference Configuration *************************
    #define ADC_REF_VDD_VDD         0b00000000  // ADC voltage positive source VREF+ = AVDD
    #define ADC_REF_VDD_VREFPLUS    0b00000100  // ADC voltage positive source VREF+ = ext. source at VREF+
    #define ADC_REF_FVR_BUF         0b00001000  // ADC voltage positive source VREF+ = FVR BUF
    #define ADC_REF_POS_MASK        (~0b00001100)            //Mask ADC positive voltage source selection bits
    //************** Negetive Voltage Reference Configuration *************************
    #define ADC_REF_VDD_VSS         0b00000000  // ADC voltage negetive source VREF- = AVSS
    #define ADC_REF_VDD_VREFMINUS   0b00001001  // ADC voltage negetive source VREF- = ext. source at VREF-
    #define ADC_REF_NEG_MASK        (~0b00000011)   //Mask ADC negetive voltage source selection bits
#endif //USE_OR_MASKS

#ifndef USE_OR_MASKS
    //**************** Special Trigger Select bit ******************************
    #define ADC_TRIG_CTMU   0b11111111     //Special trigger from the CTMU
    #define ADC_TRIG_CCP5   0b01111111     //Special trigger from CCP5
#else //USE_OR_MASKS
    //**************** Special Trigger Select bit ******************************
    #define ADC_TRIG_CTMU   0b10000000     //Special trigger from the CTMU
    #define ADC_TRIG_CCP5   0b00000000     //Special trigger from CCP5
    #define ADC_TRIG_MASK   (~ADC_TRIG_CTMU)    //Mask ADC Special Trigger Select bit
#endif //USE_OR_MASKS

#ifndef USE_OR_MASKS
    #define ADC_CH0         0b10000011      //Select Channel 0
    #define ADC_CH1         0b10000111      //Select Channel 1
    #define ADC_CH2         0b10001011      //Select Channel 2
    #define ADC_CH3         0b10001111      //Select Channel 3
    #define ADC_CH4         0b10010011      //Select Channel 4
    #define ADC_CH8         0b10100011      //Select Channel 8
    #define ADC_CH9         0b10100111      //Select Channel 9
    #define ADC_CH10        0b10101011      //Select Channel 10
    #define ADC_CH11        0b10101111      //Select Channel  11
    #define ADC_CH12        0b10110011      //Select Channel 12
    #define ADC_CH13        0b10110111      //Select Channel 13
    #define ADC_CH14        0b10111011      //Select Channel 14
    #define ADC_CH15        0b10111111      //Select Channel 15
    #define ADC_CH16        0b11000011      //Select Channel 16
    #define ADC_CH17        0b11000111      //Select Channel  17
    #define ADC_CH18        0b11001011      //Select Channel 18
    #define ADC_CH19        0b11001111      //Select Channel 19

    #if defined (_18F43K22) || defined (_18F44K22) || defined (_18F45K22) || defined (_18F46K22)
        #define ADC_CH5     0b10010111      //Select Channel 5
        #define ADC_CH6     0b10011011      //Select Channel 6
        #define ADC_CH7     0b10011111      //Select Channel 7

        #define ADC_CH20    0b11010011      //Select Channel 20
        #define ADC_CH21    0b11010111      //Select Channel 21
        #define ADC_CH22    0b11011011      //Select Channel 22
        #define ADC_CH23    0b11011111      //Select Channel 23
        #define ADC_CH24    0b11100011      //Select Channel 24
        #define ADC_CH25    0b11100111      //Select Channel 25
        #define ADC_CH26    0b11101011      //Select Channel 26
        #define ADC_CH27    0b11101111      //Select Channel 27
    #endif

    #define ADC_CH_CTMU     0b11110111      //Select Channel 29 for CTMU
    #define ADC_CH_DAC      0b11111011      //Select Channel 30 for DAC
    #define ADC_CH_FRV      0b11111111      //Select Channel 31 for FRV

#else
    #define ADC_CH0         0b00000000      //Select Channel 0
    #define ADC_CH1         0b00000100      //Select Channel 1
    #define ADC_CH2         0b00001000      //Select Channel 2
    #define ADC_CH3         0b00001100      //Select Channel 3
    #define ADC_CH4         0b00010000      //Select Channel 4
    #define ADC_CH8         0b00100000      //Select Channel 8
    #define ADC_CH9         0b00100100      //Select Channel 9
    #define ADC_CH10        0b00101000      //Select Channel 10
    #define ADC_CH11        0b00101100      //Select Channel  11
    #define ADC_CH12        0b00110000      //Select Channel 12
    #define ADC_CH13        0b00110100      //Select Channel 13
    #define ADC_CH14        0b00111000      //Select Channel 14
    #define ADC_CH15        0b00111100      //Select Channel 15
    #define ADC_CH16        0b01000000      //Select Channel 16
    #define ADC_CH17        0b01000100      //Select Channel  17
    #define ADC_CH18        0b01001000      //Select Channel 18
    #define ADC_CH19        0b01001100      //Select Channel 19

    #if defined (_18F43K22) || defined (_18F44K22) || defined (_18F45K22) || defined (_18F46K22)
        #define ADC_CH5     0b00010100      //Select Channel 5
        #define ADC_CH6     0b00011000      //Select Channel 6
        #define ADC_CH7     0b00011100      //Select Channel 7
        #define ADC_CH20    0b01010000      //Select Channel 20
        #define ADC_CH21    0b01010100      //Select Channel 21
        #define ADC_CH22    0b01011000      //Select Channel 22
        #define ADC_CH23    0b01011100      //Select Channel 23
        #define ADC_CH24    0b01100000      //Select Channel 24
        #define ADC_CH25    0b01100100      //Select Channel 25
        #define ADC_CH26    0b01101000      //Select Channel 26
        #define ADC_CH27    0b01101100      //Select Channel 27
    #endif

    #define ADC_CH_CTMU     0b01110100      //Select Channel 29 for CTMU
    #define ADC_CH_DAC      0b01111000      //Select Channel 30 for DAC
    #define ADC_CH_FRV      0b01111100      //Select Channel 31 for FRV
    #define ADC_CH_MASK     (~0b01111100)   //Mask ADC channel selection bits
#endif


void OpenADC( unsigned char, unsigned char , unsigned char );
//char BusyADC (void);
#define BusyADC()       ADCON0bits.NOT_DONE
//void ConvertADC (void);
#define ConvertADC()    ADCON0bits.GO = 1
//void CloseADC(void);
#define CloseADC()      ADCON0bits.ADON = 0; PIE1bits.ADIE = 0
//int  ReadADC(void);
#define ReadADC()       ADRES
//void SetChanADC(unsigned char );
#define SetChanADC(ch)  ADCON0 = (ADCON0 & 0b10000011) | (ch & 0b01111100)
//void SelChanConvADC( unsigned char );
#define SelChanConvADC(ch)  SetChanADC(ch); ADCON0bits.GO = 1;

//##############################################################################
//##############################################################################
//##############################################################################
//##############################################################################
//##############################################################################

//***************** Capture Interrupt Enable/Diable ***********************************
#ifndef USE_OR_MASKS
    #define CAPTURE_INT_ON   0b11111111             /* Enable Capture interrupt */
    #define CAPTURE_INT_OFF  0b01111111             /* Disable Capture interrupt */
#else
    #define CAPTURE_INT_ON   0b10000000             /* Enable Capture interrupt */
    #define CAPTURE_INT_OFF  0b00000000             /* Disable Capture interrupt */
    #define CAPTURE_INT_MASK    (~CAPTURE_INT_ON)   //Mask Capture interrupt bit
#endif

//***************** Capture mode selection ********************************************
#ifndef USE_OR_MASKS
    #define CAP_EVERY_FALL_EDGE     0b10000100      /* Capture on every falling edge*/
    #define CAP_EVERY_RISE_EDGE     0b10000101      /* Capture on every rising edge*/
    #define CAP_EVERY_4_RISE_EDGE   0b10000110      /* Capture on every 4th rising edge*/
    #define CAP_EVERY_16_RISE_EDGE  0b10000111      /* Capture on every 16th rising edge  */
#else
    #define CAP_EVERY_FALL_EDGE     0b00000100      /* Capture on every falling edge*/
    #define CAP_EVERY_RISE_EDGE     0b00000101      /* Capture on every rising edge*/
    #define CAP_EVERY_4_RISE_EDGE   0b00000110      /* Capture on every 4th rising edge*/
    #define CAP_EVERY_16_RISE_EDGE  0b00000111      /* Capture on every 16th rising edge*/
    #define CAP_MODE_MASK           (0b11110000)    //Mask Capture mode selection bits
#endif

//***************** Capture mode selection ********************************************
#ifndef    USE_OR_MASKS
    #define ECAP_EVERY_FALL_EDGE     0b10000100     /* Capture on every falling edge*/
    #define ECAP_EVERY_RISE_EDGE     0b10000101     /* Capture on every rising edge*/
    #define ECAP_EVERY_4_RISE_EDGE   0b10000110     /* Capture on every 4th rising edge*/
    #define ECAP_EVERY_16_RISE_EDGE  0b10000111     /* Capture on every 16th rising edge*/
#else
    #define ECAP_EVERY_FALL_EDGE     0b00000100     /* Capture on every falling edge*/
    #define ECAP_EVERY_RISE_EDGE     0b00000101     /* Capture on every rising edge*/
    #define ECAP_EVERY_4_RISE_EDGE   0b00000110     /* Capture on every 4th rising edge*/
    #define ECAP_EVERY_16_RISE_EDGE  0b00000111     /* Capture on every 16th rising edge*/
    #define ECAP_MODE_MASK          (0b11110000)    //Mask Capture mode selection bits
#endif

#ifndef USE_OR_MASKS
    #define ECCP_1_SEL_TMR12        0b11001111      //ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
    #define ECCP_1_SEL_TMR34        0b11011111      //ECCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
    #define ECCP_1_SEL_TMR56        0b11101111      //ECCP selects TIMER5 for Capture & Compare and TIMER6 for PWM
    #define ECCP_2_SEL_TMR12        0b11001111      //ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
    #define ECCP_2_SEL_TMR34        0b11011111      //ECCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
    #define ECCP_2_SEL_TMR56        0b11101111      //ECCP selects TIMER5 for Capture & Compare and TIMER6 for PWM
    #define ECCP_3_SEL_TMR12        0b11001111      //ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
    #define ECCP_3_SEL_TMR34        0b11011111      //ECCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
    #define ECCP_3_SEL_TMR56        0b11101111      //ECCP selects TIMER5 for Capture & Compare and TIMER6 for PWM
    #define CCP_4_SEL_TMR12         0b11001111      //CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
    #define CCP_4_SEL_TMR34         0b11011111      //CCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
    #define CCP_4_SEL_TMR56         0b11101111      //CCP selects TIMER5 for Capture & Compare and TIMER6 for PWM
    #define CCP_5_SEL_TMR12         0b11001111      //CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
    #define CCP_5_SEL_TMR34         0b11011111      //CCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
    #define CCP_5_SEL_TMR56         0b11101111      //CCP selects TIMER5 for Capture & Compare and TIMER6 for PWM
#else
    #define ECCP_1_SEL_TMR12        0b00000000      //ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
    #define ECCP_1_SEL_TMR34        0b00010000      //ECCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
    #define ECCP_1_SEL_TMR56        0b00100000      //ECCP selects TIMER5 for Capture & Compare and TIMER6 for PWM
    #define ECCP_1_SEL_TMR_MASK     (~0b00110000)   //Maks ECCP TIMER Source selection bits
    #define ECCP_2_SEL_TMR12        0b00000000      //ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
    #define ECCP_2_SEL_TMR34        0b00010000      //ECCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
    #define ECCP_2_SEL_TMR56        0b00100000      //ECCP selects TIMER5 for Capture & Compare and TIMER6 for PWM
    #define ECCP_2_SEL_TMR_MASK     (~0b00110000)   //Maks ECCP TIMER Source selection bits
    #define ECCP_3_SEL_TMR12        0b00000000      //ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
    #define ECCP_3_SEL_TMR34        0b00010000      //ECCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
    #define ECCP_3_SEL_TMR56        0b00100000      //ECCP selects TIMER5 for Capture & Compare and TIMER6 for PWM
    #define ECCP_3_SEL_TMR_MASK     (~0b00110000)   //Maks ECCP TIMER Source selection bits
    #define CCP_4_SEL_TMR12         0b00000000      //CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
    #define CCP_4_SEL_TMR34         0b00010000      //CCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
    #define CCP_4_SEL_TMR56         0b00100000      //CCP selects TIMER5 for Capture & Compare and TIMER6 for PWM
    #define CCP_4_SEL_TMR_MASK      (~0b00110000)   //Maks CCP TIMER Source selection bits
    #define CCP_5_SEL_TMR12         0b00000000      //CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
    #define CCP_5_SEL_TMR34         0b00010000      //CCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
    #define CCP_5_SEL_TMR56         0b00100000      //CCP selects TIMER5 for Capture & Compare and TIMER6 for PWM
    #define CCP_5_SEL_TMR_MASK      (~0b00110000)   //Maks CCP TIMER Source selection bits
#endif

void OpenECapture1(unsigned char);
//unsigned int ReadECapture1 (void);
//void CloseECapture1 (void);

void OpenECapture2(unsigned char);
//unsigned int ReadECapture2 (void);
//void CloseECapture2 (void);

void OpenECapture3(unsigned char);
//unsigned int ReadECapture3 (void);
//void CloseECapture3 (void);

void OpenCapture4(unsigned char);
//unsigned int ReadCapture4 (void);
//void CloseCapture4 (void);

void OpenCapture5(unsigned char);
//unsigned int ReadCapture5 (void);
//void CloseCapture5 (void);


//##############################################################################


#ifndef USE_OR_MASKS
    //*************** Compare unit enable/disable **********************************************
    #define COM_INT_ON   0b11111111  			/*Enable Compare unit interrupt */
    #define COM_INT_OFF  0b01111111 			/*Disable Compare unit interrupt */

    //************** CCPx Module Mode Selection **********************************************
    #define COM_TOGG_MATCH   0b11110010			/*Compare mode, toggle output on match */
    #define COM_HI_MATCH     0b11111000  		/*Compare mode: initialize CCPx pin low; on compare match, force CCPx pin high*/
    #define COM_LO_MATCH     0b11111001  		/*Compare mode: initialize CCPx pin high; on compare match, force CCPx pin low*/
    #define COM_UNCHG_MATCH  0b11111010  		/*Compare mode: generate software interrupt on compare match*/
    #define COM_TRIG_SEVNT	 0b11111011	 		/*Compare mode: Special Event Trigger; reset timer; start A/D conversion on CCPx match*/

    //**************ECCPx Module Mode Selection **********************************************
    #define ECOM_TOGG_MATCH   0b11110010  		/*Compare mode, toggle output on match */
    #define ECOM_HI_MATCH     0b11111000  		/*Compare mode: initialize ECCPx pin low; on compare match, force ECCPx pin high*/
    #define ECOM_LO_MATCH     0b11111001  		/*Compare mode: initialize ECCPx pin high; on compare match, force CCPx pin low*/
    #define ECOM_UNCHG_MATCH  0b11111010  		/*Compare mode: generate software interrupt on compare match*/
    #define ECOM_TRIG_SEVNT	  0b11111011  		/*Compare mode: Special Event Trigger; reset timer; start A/D conversion on ECCPx match*/
#else
    //*************** Compare unit enable/disable **********************************************
    #define COM_INT_ON   0b10000000  			/*Enable Compare unit interrupt */
    #define COM_INT_OFF  0b00000000  			/*Disable Compare unit interrupt */
    #define COM_INT_MASK	(~COM_INT_ON)		//Mask Compare unit interrupt enable/Diable bits

    //************** CCPx Module Mode Selection **********************************************
    #define COM_TOGG_MATCH   0b00000010			/*Compare mode, toggle output on match */
    #define COM_HI_MATCH     0b00001000  		/*Compare mode: initialize CCPx pin low; on compare match, force CCPx pin high*/
    #define COM_LO_MATCH     0b00001001  		/*Compare mode: initialize CCPx pin high; on compare match, force CCPx pin low*/
    #define COM_UNCHG_MATCH  0b00001010  		/*Compare mode: generate software interrupt on compare match*/
    #define COM_TRIG_SEVNT	 0b00001011	 		/*Compare mode: Special Event Trigger; reset timer; start A/D conversion on CCPx match*/
    #define COM_MODE_MASK	(0b11110000) 		//Mask  CCPx Module Mode Selection bits

    //**************ECCPx Module Mode Selection **********************************************
    #define ECOM_TOGG_MATCH   0b00000010  		/*Compare mode, toggle output on match */
    #define ECOM_HI_MATCH     0b00001000  		/*Compare mode: initialize ECCPx pin low; on compare match, force ECCPx pin high*/
    #define ECOM_LO_MATCH     0b00001001  		/*Compare mode: initialize ECCPx pin high; on compare match, force CCPx pin low*/
    #define ECOM_UNCHG_MATCH  0b00001010  		/*Compare mode: generate software interrupt on compare match*/
    #define ECOM_TRIG_SEVNT	  0b00001011  		/*Compare mode: Special Event Trigger; reset timer; start A/D conversion on ECCPx match*/
    #define ECOM_MODE_MASK	  (0b11110000)		//Mask  ECCPx Module Mode Selection bits
#endif //USE_OR_MASKS

#ifndef USE_OR_MASKS
    #define ECCP_1_SEL_TMR12		0b11001111  	//ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
    #define ECCP_1_SEL_TMR34		0b11011111  	//ECCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
    #define ECCP_1_SEL_TMR56		0b11101111  	//ECCP selects TIMER5 for Capture & Compare and TIMER6 for PWM

    #define ECCP_2_SEL_TMR12		0b11001111  	//ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
    #define ECCP_2_SEL_TMR34		0b11011111  	//ECCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
    #define ECCP_2_SEL_TMR56		0b11101111  	//ECCP selects TIMER5 for Capture & Compare and TIMER6 for PWM

    #define ECCP_3_SEL_TMR12		0b11001111  	//ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
    #define ECCP_3_SEL_TMR34		0b11011111  	//ECCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
    #define ECCP_3_SEL_TMR56		0b11101111  	//ECCP selects TIMER5 for Capture & Compare and TIMER6 for PWM

    #define CCP_4_SEL_TMR12			0b11001111  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
    #define CCP_4_SEL_TMR34			0b11011111  	//CCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
    #define CCP_4_SEL_TMR56			0b11101111  	//CCP selects TIMER5 for Capture & Compare and TIMER6 for PWM

    #define CCP_5_SEL_TMR12			0b11001111  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
    #define CCP_5_SEL_TMR34			0b11011111  	//CCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
    #define CCP_5_SEL_TMR56			0b11101111  	//CCP selects TIMER5 for Capture & Compare and TIMER6 for PWM

#else
    #define ECCP_1_SEL_TMR12	    0b00000000  	//ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
    #define ECCP_1_SEL_TMR34	    0b00010000  	//ECCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
    #define ECCP_1_SEL_TMR56	    0b00100000  	//ECCP selects TIMER5 for Capture & Compare and TIMER6 for PWM
    #define ECCP_1_SEL_TMR_MASK		(~0b00110000)  	//Maks ECCP TIMER Source selection bits

    #define ECCP_2_SEL_TMR12	    0b00000000  	//ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
    #define ECCP_2_SEL_TMR34	    0b00010000  	//ECCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
    #define ECCP_2_SEL_TMR56	    0b00100000  	//ECCP selects TIMER5 for Capture & Compare and TIMER6 for PWM
    #define ECCP_2_SEL_TMR_MASK		(~0b00110000)  	//Maks ECCP TIMER Source selection bits

    #define ECCP_3_SEL_TMR12	    0b00000000  	//ECCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
    #define ECCP_3_SEL_TMR34	    0b00010000  	//ECCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
    #define ECCP_3_SEL_TMR56	    0b00100000  	//ECCP selects TIMER5 for Capture & Compare and TIMER6 for PWM
    #define ECCP_3_SEL_TMR_MASK		(~0b00110000)  	//Maks ECCP TIMER Source selection bits

    #define CCP_4_SEL_TMR12	    	0b00000000  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
    #define CCP_4_SEL_TMR34	    	0b00010000  	//CCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
    #define CCP_4_SEL_TMR56	    	0b00100000  	//CCP selects TIMER5 for Capture & Compare and TIMER6 for PWM
    #define CCP_4_SEL_TMR_MASK		(~0b00110000)  	//Maks CCP TIMER Source selection bits

    #define CCP_5_SEL_TMR12	    	0b00000000  	//CCP selects TIMER1 for Capture & Compare and TIMER2 for PWM
    #define CCP_5_SEL_TMR34	    	0b00010000  	//CCP selects TIMER3 for Capture & Compare and TIMER4 for PWM
    #define CCP_5_SEL_TMR56	    	0b00100000  	//CCP selects TIMER5 for Capture & Compare and TIMER6 for PWM
    #define CCP_5_SEL_TMR_MASK		(~0b00110000)  	//Maks CCP TIMER Source selection bits
#endif

void OpenECompare1(unsigned char config,unsigned int period);
void CloseECompare1(void);

void OpenECompare2(unsigned char config,unsigned int period);
void CloseECompare2(void);

void OpenECompare3(unsigned char config,unsigned int period);
void CloseECompare3(void);

void OpenCompare4(unsigned char config,unsigned int period);
void CloseCompare4(void);

void OpenCompare5(unsigned char config,unsigned int period);
void CloseCompare5(void);




//##############################################################################
//##############################################################################
//##############################################################################
//##############################################################################
//##############################################################################

/* used to hold 16-bit timer value */
union Timers
{
  unsigned int lt;
  char bt[2];
};

/* Interrupt bit mask to be 'anded' with the other configuration masks and
 * passed as the 'config' parameter to the 'open' routines. */
#ifndef USE_OR_MASKS
    #define TIMER_INT_OFF   0b01111111  //Disable TIMER Interrupt
    #define TIMER_INT_ON    0b11111111  //Enable TIMER Interrupt
#else //!USE_OR_MASKS
    #define TIMER_INT_OFF   0b00000000  //Disable TIMER Interrupt
    #define TIMER_INT_ON    0b10000000  //Enable TIMER Interrupt
    #define TIMER_INT_MASK  (~TIMER_INT_ON)    //Mask Enable/Disable Timer Interrupt selection bit
#endif

/* ***** TIMER0 ***** */
/* TIMER0 configuration masks -- to be 'anded' together and passed to the
 * 'open' routine. */
#ifndef USE_OR_MASKS
    #define T0_16BIT        0b10111111  //Timer0 is configured as an 16-bit timer/counter
    #define T0_8BIT         0b11111111  //Timer0 is configured as an 8-bit timer/counter

    #define T0_SOURCE_INT   0b11011111  //Internal instruction cycle clock (CLKO) acts as source of clock
    #define T0_SOURCE_EXT   0b11111111  //Transition on TxCKI pin acts as source of clock

    #define T0_EDGE_RISE    0b11101111  //Increment on low-to-high transition on TxCKI pin
    #define T0_EDGE_FALL    0b11111111  //Increment on high-to-low transition on TxCKI pin

    #define T0_PS_1_1       0b11111111  //1:1 Prescale value (NO Prescaler)
    #define T0_PS_1_2       0b11110000  //1:2 Prescale value
    #define T0_PS_1_4       0b11110001  //1:4 Prescale value
    #define T0_PS_1_8       0b11110010  //1:8 Prescale value
    #define T0_PS_1_16      0b11110011  //1:16 Prescale value
    #define T0_PS_1_32      0b11110100  //1:32 Prescale value
    #define T0_PS_1_64      0b11110101  //1:64 Prescale value
    #define T0_PS_1_128     0b11110110  //1:128 Prescale value
    #define T0_PS_1_256     0b11110111  //1:256 Prescale value

#else //!USE_OR_MASKS
    #define T0_16BIT            0b00000000  //Timer0 is configured as an 16-bit timer/counter
    #define T0_8BIT             0b01000000  //Timer0 is configured as an 8-bit timer/counter
    #define T0_BIT_MASK         (~T0_8BIT)    //Mask Timer0 8-Bit/16-Bit Control bit

    #define T0_SOURCE_INT       0b00000000  //Internal instruction cycle clock (CLKO) acts as source of clock
    #define T0_SOURCE_EXT       0b00100000  //Transition on TxCKI pin acts as source of clock
    #define T0_SOURCE_MASK      (~T0_SOURCE_EXT)    //Mask Timer0 Clock Source Select bit

    #define T0_EDGE_RISE        0b00000000  //Increment on low-to-high transition on TxCKI pin
    #define T0_EDGE_FALL        0b00010000  //Increment on high-to-low transition on TxCKI pin
    #define T0_EDGE_MASK        (~T0_EDGE_FALL)        //Mask Timer0 Source Edge Select bit

    #define T0_PS_1_1           0b00001000  //1:1 Prescale value (NO Prescaler)
    #define    NO_T0_PS_MASK     (~T0_PS_1_1)        //Mask Timer0 Prescaler Assignment bit

    #define T0_PS_1_2           0b00000000  //1:2 Prescale value
    #define T0_PS_1_4           0b00000001  //1:4 Prescale value
    #define T0_PS_1_8           0b00000010  //1:8 Prescale value
    #define T0_PS_1_16          0b00000011  //1:16 Prescale value
    #define T0_PS_1_32          0b00000100  //1:32 Prescale value
    #define T0_PS_1_64          0b00000101  //1:64 Prescale value
    #define T0_PS_1_128         0b00000110  //1:128 Prescale value
    #define T0_PS_1_256         0b00000111  //1:256 Prescale value
    #define T0_PS_MASK          (~T0_PS_1_256)    //Mask Timer0 Prescaler Select bits
#endif//USE_OR_MASKS

void OpenTimer0(unsigned char);
//void CloseTimer0 (void);
#define CloseTimer0()   T0CONbits.TMR0ON = 0; T0CONbits.TMR0ON = 0
unsigned int ReadTimer0 (void);
void WriteTimer0(unsigned int);

/* ***** TIMER1 ***** */

/* TIMER1 configuration masks -- to be 'anded' together and passed to the
 * 'open' routine. */
#ifndef USE_OR_MASKS
    #define T1_SOURCE_PINOSC    0b11011111  // Clock source T1OSCEN = 0 Ext clock, T1OSCEN=1 Crystal osc
    #define T1_SOURCE_FOSC_4    0b10011111  //Clock source is instruction clock (FOSC/4)
    #define T1_SOURCE_FOSC      0b10111111  //Closck source is system clock (FOSC)

    #define T1_PS_1_1           0b11100111  // 1:1 prescale value
    #define T1_PS_1_2           0b11101111  // 1:2 prescale value
    #define T1_PS_1_4           0b11110111  // 1:4 prescale value
    #define T1_PS_1_8           0b11111111  // 1:8 prescale value

    #define T1_OSC1EN_OFF       0b11111011  // Timer 1 oscilator enable off
    #define T1_OSC1EN_ON        0b11111111  // Timer 1 oscilator enable on

    #define T1_SYNC_EXT_ON      0b11111101  // Synchronize external clock input
    #define T1_SYNC_EXT_OFF     0b11111111  // Do not synchronize external clock input

    #define T1_8BIT_RW          0b11111110  //Enables register read/write of Timer1 in two 8-bit operations
    #define T1_16BIT_RW         0b11111111  //Enables register read/write of Timer1 in one 16-bit operation
#else
    #define T1_SOURCE_PINOSC    0b01000000  // Clock source T1OSCEN = 0 Ext clock, T1OSCEN=1 Crystal osc
    #define T1_SOURCE_FOSC_4    0b00000000  //Clock source is instruction clock (FOSC/4)
    #define T1_SOURCE_FOSC      0b00100000  //Clock source is system clock (FOSC)
    #define T1_SOURCE_MASK      (~T1_SOURCE_FOSC)    //Mask Timer1 Clock Source Select bits

    #define T1_PS_1_1           0b00000000  // 1:1 prescale value
    #define T1_PS_1_2           0b00001000  // 1:2 prescale value
    #define T1_PS_1_4           0b00010000  // 1:4 prescale value
    #define T1_PS_1_8           0b00011000  // 1:8 prescale value
    #define T1_PS_MASK          (~T1_PS_1_8)    //Mask Timer1 Input Clock Prescale Select bits

    #define T1_OSC1EN_OFF       0b00000000  // Timer 1 oscilator enable off
    #define T1_OSC1EN_ON        0b00000100  // Timer 1 oscilator enable on
    #define T1_OSC_MASK         (~T1_OSC1EN_ON)  //Mask Timer1 Oscillator Enable bit

    #define T1_SYNC_EXT_ON      0b00000000  // Synchronize external clock input
    #define T1_SYNC_EXT_OFF     0b00000010  // Do not synchronize external clock input
    #define T1_SYNC_MASK        (~T1_SYNC_EXT_OFF)    // Mask Timer1 External Clock Input Synchronization Select bit

    #define T1_8BIT_RW          0b00000000  //Enables register read/write of Timer1 in two 8-bit operations
    #define T1_16BIT_RW         0b00000001  //Enables register read/write of Timer1 in one 16-bit operation
    #define T1_BIT_RW_MASK      (~T1_16BIT_RW)  // Mask Timer1 16-Bit Read/Write Mode Enable bit
#endif

void OpenTimer1(unsigned char, unsigned char);
//void CloseTimer1 (void);
#define CloseTimer1()   T1CONbits.TMR1ON = 0; PIE1bits.TMR1IE = 0
unsigned int ReadTimer1 (void);
void WriteTimer1(unsigned int);



/* TIMER2 configuration masks -- to be 'anded' together and passed to the
 * 'open' routine. */
//-----------------AND OR MASK----------------------
#ifndef USE_OR_MASKS
    #define T2_POST_1_1     0b10000111  //Timer2 Postscaler 1:1
    #define T2_POST_1_2     0b10001111  //Timer2 Postscaler 1:2
    #define T2_POST_1_3     0b10010111  //Timer2 Postscaler 1:3
    #define T2_POST_1_4     0b10011111  //Timer2 Postscaler 1:4
    #define T2_POST_1_5     0b10100111  //Timer2 Postscaler 1:5
    #define T2_POST_1_6     0b10101111  //Timer2 Postscaler 1:6
    #define T2_POST_1_7     0b10110111  //Timer2 Postscaler 1:7
    #define T2_POST_1_8     0b10111111  //Timer2 Postscaler 1:8
    #define T2_POST_1_9     0b11000111  //Timer2 Postscaler 1:9
    #define T2_POST_1_10    0b11001111  //Timer2 Postscaler 1:10
    #define T2_POST_1_11    0b11010111  //Timer2 Postscaler 1:11
    #define T2_POST_1_12    0b11011111  //Timer2 Postscaler 1:12
    #define T2_POST_1_13    0b11100111  //Timer2 Postscaler 1:13
    #define T2_POST_1_14    0b11101111  //Timer2 Postscaler 1:14
    #define T2_POST_1_15    0b11110111  //Timer2 Postscaler 1:15
    #define T2_POST_1_16    0b11111111  //Timer2 Postscaler 1:16
    #define T2_PS_1_1       0b11111100  //Timer2 Prescale 1:1
    #define T2_PS_1_4       0b11111101  //Timer2 Prescale 1:4
    #define T2_PS_1_16      0b11111110  //Timer2 Prescale 1:16
#else //!USE_OR_MASKS
    #define T2_POST_1_1     0b00000000  //Timer2 Postscaler 1:1
    #define T2_POST_1_2     0b00001000  //Timer2 Postscaler 1:2
    #define T2_POST_1_3     0b00010000  //Timer2 Postscaler 1:3
    #define T2_POST_1_4     0b00011000  //Timer2 Postscaler 1:4
    #define T2_POST_1_5     0b00100000  //Timer2 Postscaler 1:5
    #define T2_POST_1_6     0b00101000  //Timer2 Postscaler 1:6
    #define T2_POST_1_7     0b00110000  //Timer2 Postscaler 1:7
    #define T2_POST_1_8     0b00111000  //Timer2 Postscaler 1:8
    #define T2_POST_1_9     0b01000000  //Timer2 Postscaler 1:9
    #define T2_POST_1_10    0b01001000  //Timer2 Postscaler 1:10
    #define T2_POST_1_11    0b01010000  //Timer2 Postscaler 1:11
    #define T2_POST_1_12    0b01011000  //Timer2 Postscaler 1:12
    #define T2_POST_1_13    0b01100000  //Timer2 Postscaler 1:13
    #define T2_POST_1_14    0b01101000  //Timer2 Postscaler 1:14
    #define T2_POST_1_15    0b01110000  //Timer2 Postscaler 1:15
    #define T2_POST_1_16    0b01111000  //Timer2 Postscaler 1:16
    #define T2_POST_MASK    (~T2_POST_1_16)    //Mask Timer2 Postscale Selection bits

    #define T2_PS_1_1       0b00000000  //Timer2 Prescale 1:1
    #define T2_PS_1_4       0b00000001  //Timer2 Prescale 1:4
    #define T2_PS_1_16      0b00000011  //Timer2 Prescale 1:16
    #define T2_PS_MASK      (~T2_PS_1_16)    //Mask Timer2 Input Clock Prescale Select bits
#endif //!USE_OR_MASKS

void OpenTimer2(unsigned char);
#define CloseTimer2()           T2CONbits.TMR2ON = 0; PIE1bits.TMR2IE = 0
#define WriteTimer2(value)      TMR2 = (value)
#define ReadTimer2()            TMR2





#ifndef USE_OR_MASKS
    #define T5_SOURCE_PINOSC    0b11011111  // Clock source SOSCEN = 0 Ext clock, SOSCEN=1 Crystal osc
    #define T5_SOURCE_FOSC_4    0b10011111  //Clock source is instruction clock (FOSC/4)
    #define T5_SOURCE_FOSC      0b10111111  //Closck source is system clock (FOSC)

    #define T5_PS_1_1           0b11100111  //Timer5 1:1 prescale value
    #define T5_PS_1_2           0b11101111  //Timer5 1:2 prescale value
    #define T5_PS_1_4           0b11110111  //Timer5 1:4 prescale value
    #define T5_PS_1_8           0b11111111  //Timer5 1:8 prescale value

    #define T5_OSC1EN_OFF       0b11111011  // Timer1  oscilator disabled which is used by Timer5
    #define T5_OSC1EN_ON        0b11111111  // Timer1  oscilator enabled which is used by Timer5

    #define T5_SYNC_EXT_ON      0b11111101  // Synchronize external clock input
    #define T5_SYNC_EXT_OFF     0b11111111  // Do not synchronize external clock input

    #define T5_8BIT_RW          0b11111110  //Enables register read/write of Timer5 in two 8-bit operations
    #define T5_16BIT_RW         0b11111111  //Enables register read/write of Timer5 in two 16-bit operations

#else
    #define T5_SOURCE_PINOSC    0b01000000  // Clock source SOSCEN = 0 Ext clock, SOSCEN=1 Crystal osc
    #define T5_SOURCE_FOSC_4    0b00000000  //Clock source is instruction clock (FOSC/4)
    #define T5_SOURCE_FOSC      0b00100000  //Closck source is system clock (FOSC)
    #define T5_SOURCE_MASK      (~T5_SOURCE_FOSC) //Mask Timer5 Clock Source Select bits

    #define T5_PS_1_1           0b00000000  //Timer5 1:1 prescale value
    #define T5_PS_1_2           0b00001000  //Timer5 1:2 prescale value
    #define T5_PS_1_4           0b00010000  //Timer5 1:4 prescale value
    #define T5_PS_1_8           0b00011000  //Timer5 1:8 prescale value
    #define T5_PS_MASK          (~T5_PS_1_8)    //Mask Timer5 Input Clock Prescale Select bits

    #define T5_OSC1EN_OFF       0b00000000  // Timer1  oscilator disabled which is used by Timer5
    #define T5_OSC1EN_ON        0b00000100  // Timer1  oscilator enabled which is used by Timer5
    #define T5_OSC_MASK         (~T5_OSC1EN_ON) //Mask Timer5 Oscillator Source Select bit

    #define T5_SYNC_EXT_ON      0b00000000  // Synchronize external clock input
    #define T5_SYNC_EXT_OFF     0b00000010  // Do not synchronize external clock input
    #define T5_SYNC_MASK        (~T5_SYNC_EXT_OFF)  // Mask Timer5 External Clock Input Synchronization Select bit

    #define T5_8BIT_RW          0b00000000  //Enables register read/write of Timer5 in two 8-bit operations
    #define T5_16BIT_RW         0b00000001  //Enables register read/write of Timer5 in two 16-bit operations
    #define T5_BIT_RW_MASK      (~T5_16BIT_RW)  // Mask Timer5 16-Bit Read/Write Mode Enable bit
#endif

void OpenTimer5(unsigned char , unsigned char);
//void CloseTimer5 (void);
#define CloseTimer5()   PIE5bits.TMR5IE = 0; PIE3bits.TMR5GIE=0; T5CONbits.TMR5ON = 0; PIR3bits.TMR5GIF=0;
unsigned int ReadTimer5 (void);
void WriteTimer5(unsigned int );

#ifndef USE_OR_MASKS
    #define TIMER_GATE_ON           0b11111111  //Timer1 counting is controlled by Timer1 gate function
    #define TIMER_GATE_OFF          0b01111111  //Timer1 counts regardless of Timer1 gate function
    #define TIMER_GATE_POL_HI       0b11111111  //Gate  is active-high
    #define TIMER_GATE_POL_LO       0b10111111  //Gate is active-low
    #define TIMER_GATE_TOGGLE_ON    0b11111111  //Gate Toggle mode is enabled
    #define TIMER_GATE_TOGGLE_OFF   0b11011111  //Gate Toggle mode is disabled
    #define TIMER_GATE_1SHOT_ON     0b11111111  //Gate one shot is enabled
    #define TIMER_GATE_1SHOT_OFF    0b11101111  //Gate one shot is disabled
    #define TIMER_GATE_SRC_T1GPIN   0b11111100  //Timer1 gate pin
    #define TIMER_GATE_SRC_T0       0b11111101  //Timer0 overflow output
    #define TIMER_GATE_SRC_T2       0b11111110  //Timer2 match PR2  output
    #define TIMER_GATE_INT_OFF      0b11111011  //Interrupts disabled
    #define TIMER_GATE_INT_ON       0b11111111  //Interrupts enabled
#else
    #define TIMER_GATE_ON           0b10000000  //Timer1 counting is controlled by Timer1 gate function
    #define TIMER_GATE_OFF          0b00000000  //Timer1 is always counting
    #define TIMER_GATE_MASK         (~TIMER_GATE_ON)    //Mask Timer1 Gate Enable bit

    #define TIMER_GATE_POL_HI       0b01000000  //Gate  is active-high
    #define TIMER_GATE_POL_LO       0b00000000  //Gate is active-low
    #define TIMER_GATE_POL_MASK     (~TIMER_GATE_POL_HI)    //Mask Timer1 Gate Polarity bit

    #define TIMER_GATE_TOGGLE_ON    0b00100000  //Gate Toggle mode is enabled
    #define TIMER_GATE_TOGGLE_OFF   0b00000000  //Gate Toggle mode is disabled
    #define TIMER_GATE_TOGGLE_MASK  (~TIMER_GATE_TOGGLE_ON)    //Mask Timer1 Gate Toggle Mode bit

    #define TIMER_GATE_1SHOT_ON     0b00010000  //Gate one shot is enabled
    #define TIMER_GATE_1SHOT_OFF    0b00000000  //Gate one shot is disabled
    #define TIMER_GATE_1SHOT_MASK   (~TIMER_GATE_1SHOT_MASK)    //Mask Timer1 Gate Single Pulse Mode bit

    #define TIMER_GATE_SRC_T1GPIN   0b00000000  //Timer1 gate pin
    #define TIMER_GATE_SRC_T0       0b00000001  //Timer0 overflow output
    #define TIMER_GATE_SRC_T2       0b00000010  //Timer2 match PR2  output
    #define TIMER_GATE_SRC_MASK     (~TIMER_GATE_SRC_T2)     //Mask Timer1 Gate Source Select bits

    #define TIMER_GATE_INT_OFF      0b00000000  //Interrupts disabled
    #define TIMER_GATE_INT_ON       0b00000100  //Interrupts enabled
    #define TIMER_GATE_INT_MASK     (~TIMER_GATE_INT_ON)     //Mask Timer1 Gate Interrupt bit
#endif

//##############################################################################
//##############################################################################
//##############################################################################
//##############################################################################
//##############################################################################

/* Configuration bit masks to be 'anded' together and passed as the 'config'
 * parameter to the 'open' routine. */
//-----------AND OR MASK-------------------------------------------------
#ifndef USE_OR_MASKS
    #define USART_TX_INT_ON   0b11111111  // Transmit interrupt on
    #define USART_TX_INT_OFF  0b01111111  // Transmit interrupt off
    #define USART_RX_INT_ON   0b11111111  // Receive interrupt on
    #define USART_RX_INT_OFF  0b10111111  // Receive interrupt off
    #define USART_BRGH_HIGH   0b11111111  // High baud rate
    #define USART_BRGH_LOW    0b11101111  // Low baud rate
    #define USART_CONT_RX     0b11111111  // Continuous reception
    #define USART_SINGLE_RX   0b11110111  // Single reception
    #define USART_SYNC_MASTER 0b11111111  // Synchrounous master mode
    #define USART_SYNC_SLAVE  0b11111011  // Synchrounous slave mode
    #define USART_NINE_BIT    0b11111111  // 9-bit data
    #define USART_EIGHT_BIT   0b11111101  // 8-bit data
    #define USART_SYNCH_MODE  0b11111111  // Synchronous mode
    #define USART_ASYNCH_MODE 0b11111110  // Asynchronous mode
    #define USART_ADDEN_ON    0b11111111  // Enables address detection
    #define USART_ADDEN_OFF   0b11011111  // Disables address detection
//------------AND MASK------------------------------------------------
#else
    #define USART_TX_INT_ON     0b10000000  // Transmit interrupt on
    #define USART_TX_INT_OFF    0b00000000  // Transmit interrupt off
    #define USART_TX_INT_MASK   (~USART_TX_INT_ON)    //Mask Trnasmit Interrupt select bit

    #define USART_RX_INT_ON     0b01000000  // Receive interrupt on
    #define USART_RX_INT_OFF    0b00000000  // Receive interrupt off
    #define USART_RX_INT_MASK   (~USART_RX_INT_ON)    //Mask Receive Interrupt select bit

    #define USART_ADDEN_ON      0b00100000  // Enables address detection
    #define USART_ADDEN_OFF     0b00000000  // Disables address detection
    #define USART_ADDEN_MASK    (~USART_ADDEN_ON)    //Mask address detection select bit

    #define USART_BRGH_HIGH     0b00010000  // High baud rate
    #define USART_BRGH_LOW      0b00000000  // Low baud rate
    #define USART_BRGH_MASK     (~USART_BRGH_HIGH)    //Mask baud rate select bit

    #define USART_CONT_RX       0b00001000  // Continuous reception
    #define USART_SINGLE_RX     0b00000000  // Single reception
    #define USART_CONT_RX_MASK  (~USART_CONT_RX)     //Mask Continuous Reception select bit

    #define USART_SYNC_MASTER   0b00000100  // Synchrounous master mode
    #define USART_SYNC_SLAVE    0b00000000  // Synchrounous slave mode
    #define USART_SYNC_MASK     (~USART_SYNC_MASTER)    //Mask usart mode select bit

    #define USART_NINE_BIT      0b00000010  // 9-bit data
    #define USART_EIGHT_BIT     0b00000000  // 8-bit data
    #define USART_BIT_MASK      (~USART_NINE_BIT)        //Mask 9 bit transmit  select bit

    #define USART_SYNCH_MODE    0b00000001  // Synchronous mode
    #define USART_ASYNCH_MODE   0b00000000  // Asynchronous mode
    #define USART_MODE_MASK     (~USART_SYNCH_MODE)     //Mask sync/async mode select bit
#endif

/* The baud configuration bit masks to be 'anded' together and passed to
 * the 'baud' routine. */
//--------------AND OR MASK------------------------------
#ifndef USE_OR_MASKS
    #define BAUD_IDLE_CLK_HIGH  0b11111111  // idle state for clock is a high level
    #define BAUD_IDLE_CLK_LOW   0b11101111  // idle state for clock is a low level
    #define BAUD_16_BIT_RATE    0b11111111  // 16-bit baud generation rate
    #define BAUD_8_BIT_RATE     0b11110111  // 8-bit baud generation rate
    #define BAUD_WAKEUP_ON      0b11111111  // RX pin monitored
    #define BAUD_WAKEUP_OFF     0b11111101  // RX pin not monitored
    #define BAUD_AUTO_ON        0b11111111  // auto baud rate measurement enabled
    #define BAUD_AUTO_OFF       0b11111110  // auto baud rate measurement disabled
//-----------------AND MASK-------------------------------
#else
    #define BAUD_IDLE_CLK_HIGH  0b00010000  // idle state for clock is a high level
    #define BAUD_IDLE_CLK_LOW   0b00000000  // idle state for clock is a low level
    #define BAUD_IDLE_CLK_MASK  (~BAUD_IDLE_CLK_HIGH) //Mask Idle Clock State bit

    #define BAUD_16_BIT_RATE    0b00001000  // 16-bit baud generation rate
    #define BAUD_8_BIT_RATE     0b00000000  // 8-bit baud generation rate
    #define BAUD_BIT_RATE       (~BAUD_16_BIT_RATE) //Mask 16 bit baud rate select bit

    #define BAUD_WAKEUP_ON      0b00000010  // RX pin monitored
    #define BAUD_WAKEUP_OFF     0b00000000  // RX pin not monitored
    #define BAUD_WAKEUP_MASK    (~BAUD_WAKEUP_ON)   //Mask Wake-up Enable bit

    #define BAUD_AUTO_ON        0b00000001  // auto baud rate measurement enabled
    #define BAUD_AUTO_OFF       0b00000000  // auto baud rate measurement disabled
    #define BAUD_AUTO_MASK      (~BAUD_AUTO_ON)     //Mask Auto-Baud Detect Enable bit
#endif

/*Macros for backward compatibility*/
#ifndef USE_OR_MASKS
    #define BAUD_IDLE_RX_PIN_STATE_HIGH     0b11011111  // idle state for RX pin is high level
    #define BAUD_IDLE_RX_PIN_STATE_LOW      0b11111111  // idle state for RX pin is low level
    #define BAUD_IDLE_TX_PIN_STATE_HIGH     0b11101111  // idle state for TX pin is high level
    #define BAUD_IDLE_TX_PIN_STATE_LOW      0b11111111  // idle state for TX pin is low level
#else
    #define BAUD_IDLE_RX_PIN_STATE_HIGH     0b00000000  // idle state for RX pin is high level
    #define BAUD_IDLE_RX_PIN_STATE_LOW      0b00100000  // idle state for RX pin is low level
    #define BAUD_IDLE_TX_PIN_STATE_HIGH     0b00000000  // idle state for TX pin is high level
    #define BAUD_IDLE_TX_PIN_STATE_LOW      0b00010000  // idle state for TX pin is low level
    #define BAUD_IDLE_TX_RX_PIN_STATE_MASK  (~0b00110000)   //Mask idle tx rx pin state select bit
#endif

#define baud1USART(config)  BAUDCON1 = config
void Open1USART(unsigned char, unsigned int);
#define DataRdy1USART()     (PIR1bits.RC1IF)
#define Busy1USART()        (!TXSTA1bits.TRMT)
#define Close1USART()       RCSTA1&=0b01001111; TXSTA1bits.TXEN=0; PIE1&=0b11001111

#define baud2USART(config)  BAUDCON2 = config
void Open2USART(unsigned char, unsigned int );
#define DataRdy2USART( )    (PIR3bits.RC2IF)
#define Busy2USART()        (!TXSTA2bits.TRMT)
#define Close2USART()       RCSTA2&=0b01001111; TXSTA1bits.TXEN=0; PIE1&=0b11001111



//##############################################################################
//##############################################################################
//##############################################################################
//##############################################################################
//##############################################################################
/* SSPSTAT REGISTER */
// Master SPI mode only
#define   SMPEND        0b10000000           // Input data sample at end of data out
#define   SMPMID        0b00000000           // Input data sample at middle of data out


#define   MODE_00       0b00000000              // Setting for SPI bus Mode 0,0
//CKE           0x40                   // SSPSTAT register
//CKP           0x00                   // SSPCON1 register

#define   MODE_01       0b00000001              // Setting for SPI bus Mode 0,1
//CKE           0x00                   // SSPSTAT register
//CKP           0x00                   // SSPCON1 register

#define   MODE_10       0b00000010              // Setting for SPI bus Mode 1,0
//CKE           0x40                   // SSPSTAT register
//CKP           0x10                   // SSPCON1 register

#define   MODE_11       0b00000011              // Setting for SPI bus Mode 1,1
//CKE           0x00                   // SSPSTAT register
//CKP           0x10                   // SSPCON1 register

/* SSPCON1 REGISTER */
#define   SSPENB        0b00100000           // Enable serial port and configures SCK, SDO, SDI

#define   SPI_FOSC_4    0b00000000              // SPI Master mode, clock = Fosc/4
#define   SPI_FOSC_16   0b00000001              // SPI Master mode, clock = Fosc/16
#define   SPI_FOSC_64   0b00000010              // SPI Master mode, clock = Fosc/64
#define   SPI_FOSC_TMR2 0b00000011              // SPI Master mode, clock = TMR2 output/2
#define   SLV_SSON      0b00000100              // SPI Slave mode, /SS pin control enabled
#define   SLV_SSOFF     0b00000101              // SPI Slave mode, /SS pin control disabled
//************************************************************************************************//

#define CloseSPI    CloseSPI1
#define DataRdySPI  DataRdySPI1
#define ReadSPI     ReadSPI1
#define getcSPI1    ReadSPI1
#define getcSPI     getcSPI1
#define OpenSPI     OpenSPI1
#define WriteSPI    WriteSPI1
#define putcSPI1    WriteSPI1
#define putcSPI     putcSPI1
#define getsSPI     getsSPI1
#define putsSPI     putsSPI1

#define EnableIntSPI1                   (PIE1bits.SSP1IE = 1)
#define DisableIntSPI1                  (PIE1bits.SSP1IE = 0)
#define SetPriorityIntSPI1(priority)    (IPR1bits.SSP1IP = priority)
#define SPI1_Clear_Intr_Status_Bit      (PIR1bits.SSP1IF = 0)
#define SPI1_Intr_Status                (PIR1bits.SSP1IF)
#define SPI1_Clear_Recv_OV              (SSP1CONbits.SSPOV = 0)
#define CloseSPI1()                     (SSP1CON1 &=0xDF)
#define DataRdySPI1()                   (SSP1STATbits.BF)

void OpenSPI1(  unsigned char sync_mode,
                unsigned char bus_mode,
                unsigned char smp_phase );
signed char WriteSPI1(  unsigned char data_out );
void getsSPI1(  unsigned char *rdptr,  unsigned char length );
void putsSPI1(  unsigned char *wrptr );
unsigned char ReadSPI1( void );

//##############################################################################
//##############################################################################
//#############################       I2C        ###############################
//##############################################################################
//##############################################################################

/* SSPCON1 REGISTER */
//#define   SSPENB    			0b00100000  	/* Enable serial port and configures SCK, SDO, SDI*/
#define   SLAVE_7   			0b00000110     	/* I2C Slave mode, 7-bit address*/
#define   SLAVE_10  			0b00000111    	/* I2C Slave mode, 10-bit address*/
#define   MASTER    			0b00001000     	/* I2C Master mode */
#define   MASTER_FIRMW			0b00001011		//I2C Firmware Controlled Master mode (slave Idle)
#define   SLAVE_7_STSP_INT 		0b00001110		//I2C Slave mode, 7-bit address with Start and Stop bit interrupts enabled
#define   SLAVE_10_STSP_INT 	0b00001111		//I2C Slave mode, 10-bit address with Start and Stop bit interrupts enabled

/* SSPSTAT REGISTER */
#define   SLEW_OFF  			0b10000000  	/* Slew rate disabled for 100kHz mode */
#define   SLEW_ON   			0b00000000  	/* Slew rate enabled for 400kHz mode  */


void OpenI2C1(unsigned char sync_mode, unsigned char slew);
signed char WriteI2C1(unsigned char data_out);
unsigned char ReadI2C1(void);
//void StopI2C1();
//void StartI2C1();
//void RestartI2C1();
#ifdef NON_BLOCKING
    void AckI2C1(void);
    void NotAckI2C1(void);
#endif
//void IdleI2C1();

#define StopI2C1()      { SSP1CON2bits.PEN = 1;  while (SSP1CON2bits.PEN); }
#define StartI2C1()     { SSP1CON2bits.SEN = 1; while (SSP1CON2bits.SEN); }
#define RestartI2C1()   { SSP1CON2bits.RSEN = 1; while (SSP1CON2bits.RSEN); }
#ifndef NON_BLOCKING
    #define AckI2C1()   { SSP1CON2bits.ACKDT = 0; SSP1CON2bits.ACKEN = 1; \
                            while (SSPCON2bits.ACKEN); }
    #define NotAckI2C1(){ SSP1CON2bits.ACKDT = 1; SSP1CON2bits.ACKEN = 1; \
                            while (SSP1CON2bits.ACKEN); }
#endif
#define IdleI2C1()      { while ((SSP1CON2 & 0x1F) | (SSP1STATbits.R_W)); }
//#define IdleI2C1() {while((SSP1CON2 & 0x1F )|( SSP1STATbits.R_W ))continue;}

#endif  /* PLIB18FXXK22_H */
