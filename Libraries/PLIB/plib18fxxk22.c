/*
 * File:   plib18fxxk22.c
 * Author: vsk THU
 *
 * Created on 15. März 2016, 16:16
 */

#pragma warning disable  520    // function never called
#pragma warning disable  373    // implicit signed to unsigned conversion
#pragma warning disable 1498    // pointer in expression may have no targets
//#pragma warning disable 

//#warning "###################################################################"
#warning "##### please view limitations for plib functions! #####"
//#warning "##### Some plib functions are not tested yet! #####"
//#warning "##### OpenECompareX() does not yet configure the pin as output! #####"
//#warning "##### PWMccpPWM() Ensure #pragma config CCP2MX = PORTB3! #####"
//#wARNING "##### some SPI1() functions not testet yet! #####"
//#warning "###################################################################"

#include "plib18fxxk22.h"

uint16_t Plib_TO_Cnt;    // used to avoid blocking functions

void OpenADC(unsigned char config, unsigned char config2, unsigned char config3) {
    ADCON0 = 0;
    ADCON1 = 0;
    ADCON2 = 0;

    ADCON0 = (config2) & 0b01111100; // GET CHANNELS

    ADCON1 = config3; // Vref+/- & Trigger & Negetive channel select

    ADCON2 = (config & 0b10000000) |        // RESULT
            ((config >> 4) & 0b00000111) |  // CONV CLK
            ((config << 2) & 0b00111000);   // ACQ TIME

    if (config2 & 0b10000000) // ADC INT.
    {
        PIR1bits.ADIF = 0;
        PIE1bits.ADIE = 1;
        INTCONbits.PEIE = 1;
    }
    ADCON0bits.ADON = 1;
}

//##############################################################################
//##############################################################################
//###############################   E_CAPTURE_COMPARE  #########################
//##############################################################################
//##############################################################################
void OpenECapture1(unsigned char config)
{
    TRISCbits.TRISC2 = 1;       //CP1_TRIS = 1;
    ANSELCbits.ANSC2 = 0;

    CCPTMRS0   &= 0b11111100;
    CCPTMRS0 |= ((config&0b00110000)>>4);

    CCP1CON = config & 0x0F;

    if(config&0x80)
    {
        PIR1bits.CCP1IF = 0;    // Clear the interrupt flag
        PIE1bits.CCP1IE = 1;    // Enable the interrupt
    }
}

//##############################################################################
void OpenECompare2(unsigned char config, unsigned int period)
{
//    while(1){;}

//#ifndef _OMNI_CODE_
//  unsigned char TBLPTR_U, TBLPTR_L;
//
//_asm
//movff TBLPTRU, TBLPTR_U
//movff TBLPTRL, TBLPTR_L
//_endasm
//#endif
//
//    if (((*(unsigned char far rom *) 0x300005) & 0b00000001))
//        if ((CCP2CON & 0x0f) != 0x0a)
//            TRISCbits.TRISC1 = 0;
//        else if (((*(unsigned char far rom *) 0x300005) & 0b00000100))
//            if ((CCP2CON & 0x0f) != 0x0a)
//                TRISBbits.TRISB3 = 0;

    CCPR2L = (unsigned char)period; // load ECAxL
    CCPR2H = (period >> 8); // load ECAxH

    CCP2CON = config & 0x0F; // Configure capture

    CCPTMRS0 &= 0b11100111;
    CCPTMRS0 |= ((config & 0b00110000) >> 1);

    if (config & 0x80) {
        PIR2bits.CCP2IF = 0; // Clear the interrupt flag
        PIE2bits.CCP2IE = 1; // Enable the interrupt
    }

//#ifndef _OMNI_CODE_
//_asm
//movff TBLPTR_U, TBLPTRU
//movff TBLPTR_L, TBLPTRL
//_endasm
//#endif

}

void OpenECompare3(unsigned char config,unsigned int period)
{
    CCPR3L = (unsigned char)period;            // load ECAxL
    CCPR3H = (period >> 8);     // load ECAxH

    CCP3CON = config & 0x0F;    // Configure capture

    CCPTMRS0 &= 0b00111111;     //configure timer source for CCP
    CCPTMRS0 |= ((config & 0b00110000) << 2);

    if (config & 0x80) {
        PIR4bits.CCP3IF = 0;    // Clear the interrupt flag
        PIE4bits.CCP3IE = 1;    // Enable the interrupt
    }
}

//##############################################################################
//##############################################################################
//###############################      TIMER       #############################
//##############################################################################
//##############################################################################

void OpenTimer0(unsigned char config) {
    T0CON = (0x7f & config);    // Configure timer, but don't start it yet
    TMR0H = 0;                  // Reset Timer0 to 0x0000
    TMR0L = 0;
    INTCONbits.TMR0IF = 0;      // Clear Timer0 overflow flag

    if (config & 0x80)          // If interrupts enabled
        INTCONbits.TMR0IE = 1;  // Enable Timer0 overflow interrupt
    else
        INTCONbits.TMR0IE = 0;

    T0CONbits.TMR0ON = 1;
}

unsigned int ReadTimer0(void) {
    union Timers timer;

    timer.bt[0] = TMR0L;        // Copy Timer0 low byte into union
    timer.bt[1] = TMR0H;        // Copy Timer0 high byte into union

    return (timer.lt);          // Return the int
}

void WriteTimer0(unsigned int timer0) {
    union Timers timer;

    timer.lt = timer0;          // Copy timer value into union

    TMR0H = timer.bt[1];        // Write high byte to Timer0
    TMR0L = timer.bt[0];        // Write low byte to Timer0
}

//##############################################################################

void OpenTimer1(unsigned char config, unsigned char config1) {
    T1GCON = (0XF3 & config1);

    T1CON = (unsigned char)((0x7F & config) << 1);

    TMR1H = 0;                  // Clear out timer registers
    TMR1L = 0;

    PIR1bits.TMR1IF = 0;

    if (config & 0x80)          // Enable interrupts if selected
        PIE1bits.TMR1IE = 1;
    else
        PIE1bits.TMR1IE = 0;

    PIR3bits.TMR1GIF = 0;
    if (config1 & 0x04) {
        PIE3bits.TMR1GIE = 1;
        T1GCONbits.T1GGO = 1;
    } else
        PIE3bits.TMR1GIE = 0;

    T1CONbits.TMR1ON = 1;       // Start Timer1
}

unsigned int ReadTimer1(void)
{
  union Timers timer;

  timer.bt[0] = TMR1L;          // Read Lower byte
  timer.bt[1] = TMR1H;          // Read upper byte

  return (timer.lt);            // Return the 16-bit value
}

void WriteTimer1(unsigned int timer1)
{
  union Timers timer;

  timer.lt = timer1;            // Save the 16-bit value in local

  TMR1H = timer.bt[1];          // Write high byte to Timer1 High byte
  TMR1L = timer.bt[0];          // Write low byte to Timer1 Low byte
}

//##############################################################################

void OpenTimer2(unsigned char config) {
    T2CON = (0xfb & config);    // Set all configuration values, but
                                // don't start timer yet

    TMR2 = 0;                   // Clear Timer2
    PIR1bits.TMR2IF = 0;

    if (config & 0x80)          // Enable timer interrupts?
        PIE1bits.TMR2IE = 1;
    else
        PIE1bits.TMR2IE = 0;

    T2CONbits.TMR2ON = 1;       // Turn on Timer2
}
//##############################################################################
//T3
//##############################################################################
//T4

//##############################################################################

void OpenTimer5(unsigned char config, unsigned char config1) {
    T5GCON = (0XF3 & config1);

    T5CON = (unsigned char)((0x7F & config) << 1);

    TMR5H = 0;                  // Clear out timer registers
    TMR5L = 0;

    PIR5bits.TMR5IF = 0;

    if (config & 0x80)          // Enable interrupts if selected
        PIE5bits.TMR5IE = 1;
    else
        PIE5bits.TMR5IE = 0;

    if (config1 & 0x04)
        PIE3bits.TMR5GIE = 1;
    else
        PIE3bits.TMR5GIE = 0;

    if (T5GCONbits.TMR5GE)
        T5GCONbits.T5GGO = 1;

    T5CONbits.TMR5ON = 1;       // Start Timer5
}

unsigned int ReadTimer5(void) {
    union Timers timer;

    timer.bt[0] = TMR5L;        // Read Lower byte
    timer.bt[1] = TMR5H;        // Read upper byte
    return (timer.lt);          // Return the 16-bit value
}

void WriteTimer5(unsigned int tmr5) {
    union Timers timer;
    timer.lt = tmr5;            // Save the 16-bit value in local

    TMR5H = timer.bt[1];        // Write high byte to Timer5 High byte
    TMR5L = timer.bt[0];        // Write low byte to Timer5 Low byte

}

//##############################################################################
//T6
//##############################################################################
//T7


//##############################################################################
//##############################################################################
//#############################      USART       ###############################
//##############################################################################
//##############################################################################

void Open1USART( unsigned char config, unsigned int spbrg)
{
  TXSTA1 = 0;                   // Reset USART registers to POR state
  RCSTA1 = 0;

  if(config&0x01)               // Sync or async operation
    TXSTA1bits.SYNC = 1;

  if(config&0x02)               // 8- or 9-bit mode
  {
    TXSTA1bits.TX9 = 1;
    RCSTA1bits.RX9 = 1;
  }

  if(config&0x04)               // Master or Slave (sync only)
    TXSTA1bits.CSRC = 1;

  if(config&0x08)               // Continuous or single reception
    RCSTA1bits.CREN = 1;
  else
    RCSTA1bits.SREN = 1;

  if(config&0x10)               // Baud rate select (asychronous mode only)
    TXSTA1bits.BRGH = 1;

  if(config&0x20)               // Address Detect Enable
    RCSTA1bits.ADDEN = 1;

  // SENDB (asychronous mode only)  - need to be added

  if(config&0x40)               // Interrupt on receipt
    PIE1bits.RC1IE = 1;
  else
    PIE1bits.RC1IE = 0;

  if(config&0x80)               // Interrupt on transmission
    PIE1bits.TX1IE = 1;
  else
    PIE1bits.TX1IE = 0;

  SPBRG1 = (unsigned char)spbrg;               // Write baudrate to SPBRG1
  SPBRGH1 = spbrg >> 8;         // For 16-bit baud rate generation

  TXSTA1bits.TXEN = 1;          // Enable transmitter
  RCSTA1bits.SPEN = 1;          // Enable receiver
}

void Open2USART( unsigned char config, unsigned int spbrg)
{
  TXSTA2 = 0;                   // Reset USART registers to POR state
  RCSTA2 = 0;

  if(config&0x01)               // Sync or async operation
    TXSTA2bits.SYNC = 1;

  if(config&0x02)               // 8- or 9-bit mode
  {
    TXSTA2bits.TX9 = 1;
    RCSTA2bits.RX9 = 1;
  }

  if(config&0x04)               // Master or Slave (sync only)
    TXSTA2bits.CSRC = 1;

  if(config&0x08)               // Continuous or single reception
    RCSTA2bits.CREN = 1;
  else
    RCSTA2bits.SREN = 1;

  if(config&0x10)               // Baud rate select (asychronous mode only)
    TXSTA2bits.BRGH = 1;
  else
    TXSTA2bits.BRGH = 0;

  if(config&0x20)               // Address Detect Enable
    RCSTA2bits.ADDEN = 1;

  // SENDB(asychronous mode only)  - need to be added

  if(config&0x40)               // Interrupt on receipt
    PIE3bits.RC2IE = 1;
  else
    PIE3bits.RC2IE = 0;

  if(config&0x80)               // Interrupt on transmission
    PIE3bits.TX2IE = 1;
  else
    PIE3bits.TX2IE = 0;

  SPBRG2 = (unsigned char)spbrg;               // Write baudrate to SPBRG2
  SPBRGH2 = spbrg >> 8;         // For 16-bit baud rate generation

  TXSTA2bits.TXEN = 1;          // Enable transmitter
  RCSTA2bits.SPEN = 1;          // Enable receiver
}

//##############################################################################
//##############################################################################
//#############################       SPI        ###############################
//##############################################################################
//##############################################################################

void OpenSPI1(unsigned char sync_mode,
        unsigned char bus_mode,
        unsigned char smp_phase) {
    SSP1STAT &= 0x3F;               // power on state
    SSP1CON1 = 0x00;                // power on state
    SSP1CON1 |= sync_mode;          // select serial mode
    SSP1STAT |= smp_phase;          // select data input sample phase

    switch (bus_mode) {
        case 0:                     // SPI1 bus mode 0,0
            SSP1STATbits.CKE = 1;   // data transmitted on rising edge
            break;
        case 2:                     // SPI1 bus mode 1,0
            SSP1STATbits.CKE = 1;   // data transmitted on falling edge
            SSP1CON1bits.CKP = 1;   // clock idle state high
            break;
        case 3:                     // SPI1 bus mode 1,1
            SSP1CON1bits.CKP = 1;   // clock idle state high
            break;
        default:                    // default SPI1 bus mode 0,1
            break;
    }

    switch (sync_mode) {
        case 4:                     // slave mode w /SS enable
            TRISAbits.TRISA5 = 1;   // define /SS1 pin as input
            TRISCbits.TRISC3 = 1;   // define clock pin as input
            break;
        case 5:                     // slave mode w/o /SS enable
            TRISCbits.TRISC3 = 1;   // define clock pin as input
            break;

        default:                    // master mode, define clock pin as output
            TRISCbits.TRISC3 = 0;   // define clock pin as output
            break;
    }
    TRISCbits.TRISC4 = 1;           // define SDI pin as input
    TRISCbits.TRISC5 = 0;           // define SDO pin as output

    SSP1CON1 |= SSPENB;             // enable synchronous serial port
}

signed char WriteSPI1(unsigned char data_out) {
    unsigned char TempVar;
    TempVar = SSP1BUF;              // Clears BF
    PIR1bits.SSP1IF = 0;            // Clear interrupt flag
    SSP1CON1bits.WCOL = 0;          // Clear any previous write collision
    SSP1BUF = data_out;             // write byte to SSP1BUF register
    if (SSP1CON1 & 0x80)            // test if write collision occurred
        return ( -1);               // if WCOL bit is set return negative #
    else
        //while( !SSP1STATbits.BF );  // wait until bus cycle complete
        while (!PIR1bits.SSP1IF){;} // wait until bus cycle complete
    return (0);                     // if WCOL bit is not set ret. non-negative#
}

unsigned char ReadSPI1(void)
{
    unsigned char TempVar;
    TempVar = SSP1BUF;              //Clear BF
    PIR1bits.SSP1IF = 0;            //Clear interrupt flag
    SSP1BUF = 0x00;                 // initiate bus cycle
    //while ( !SSP1STATbits.BF );     // wait until cycle complete
    while (!PIR1bits.SSP1IF);       //wait until cycle complete
    return ( SSP1BUF);              // return with byte read
}

void getsSPI1(unsigned char *rdptr, unsigned char length)
{
    while (length){                 // stay in loop until length = 0
        *rdptr++ = getcSPI1();      // read a single byte
        length--;                   // reduce string length count by 1
    }
}

void putsSPI1(unsigned char *wrptr)
{
    while (*wrptr){                 // test for string null character
        SSP1BUF = *wrptr++;         // initiate SPI1 bus cycle
        while (!SSP1STATbits.BF);   // wait until 'BF' bit is set
    }
}

//##############################################################################
//##############################################################################
//#############################       I2C        ###############################
//##############################################################################
//##############################################################################

void OpenI2C1( unsigned char sync_mode, unsigned char slew )
{
  SSP1STAT &= 0x3F;                // power on state
  SSP1CON1 = 0x00;                 // power on state
  SSP1CON2 = 0x00;                 // power on state
  SSP1CON1 |= sync_mode;           // select serial mode
  SSP1STAT |= slew;                // slew rate on/off

  SSP1CON1bits.SSPEN = 1;              // enable synchronous serial port
}

signed char WriteI2C1( unsigned char data_out )
{
    SSP1BUF = data_out; // write single byte to SSP1BUF
    if (SSP1CON1bits.WCOL) // test if write collision occurred
        return (-1); // if WCOL bit is set return negative #
    else {
        if (((SSP1CON1 & 0x0F) != 0x08) && ((SSP1CON1 & 0x0F) != 0x0B)) //slave mode only
        {
            SSP1CON1bits.CKP = 1; // release clock line
            while (!PIR1bits.SSP1IF) {
                ;
            } // wait until ninth clock pulse received
            if ((!SSP1STATbits.R_W) && (!SSP1STATbits.BF))// if R/W=0 and BF=0, NOT ACK was received
                return ( -2); //Return NACK
        }
        else if (((SSP1CON1 & 0x0F) == 0x08) || ((SSP1CON1 & 0x0F) == 0x0B)) //master mode only
        {
            while (SSP1STATbits.BF){;} // wait until write cycle is complete
            IdleI2C1(); // ensure module is idle
            if (SSP1CON2bits.ACKSTAT) // test for ACK condition received
                return ( -2); //Return NACK
        }
        return (0); //Return ACK
    }
}

unsigned char ReadI2C1( void)
{
    if ((SSP1CON1bits.SSPM == MASTER) || (SSP1CON1bits.SSPM == MASTER_FIRMW))
        SSP1CON2bits.RCEN = 1;      // enable master for 1 byte reception
    Plib_TO_Cnt = 0;
    while (!SSP1STATbits.BF && (Plib_TO_Cnt <= I2C_TIMEOUT)){Plib_TO_Cnt++;}     // wait until byte received
    return (SSP1BUF);               // return with read byte
}

#ifdef NON_BLOCKING
void AckI2C1()
{
    SSP1CON2bits.ACKDT = 0;
    SSP1CON2bits.ACKEN = 1; Plib_TO_Cnt = 0;
    while (SSPCON2bits.ACKEN && (Plib_TO_Cnt <= I2C_TIMEOUT)){Plib_TO_Cnt++;}
}
    
void NotAckI2C1()
{
    SSP1CON2bits.ACKDT = 1;
    SSP1CON2bits.ACKEN = 1; Plib_TO_Cnt = 0;
    while (SSP1CON2bits.ACKEN && (Plib_TO_Cnt <= I2C_TIMEOUT)){Plib_TO_Cnt++;}
}
#endif