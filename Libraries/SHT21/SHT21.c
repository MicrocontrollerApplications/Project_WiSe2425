//*******************************************************************
//
//  File:           SHT21.c
//  Author:         VSK
//
//  Created on      26. Nov 2019
//  Modified        26. Nov. 2019
//
//*******************************************************************

#include "SHT21.h"

#include <xc.h>
#include <stdint.h>
#include "PLIB/plib.h"

void initSHT21(TYPE_USER_REG mode)
{
    OpenI2C1(MASTER, SLEW_ON);
    IdleI2C1();                             // 
    StartI2C1();                            // send start condition
    while(SSP1CON2bits.SEN){;}              // 
    WriteI2C1(SHT21_WR);                    // addressing 
    while(SSP1CON2bits.ACKSTAT){;}          // ACK-bit
    WriteI2C1(CMD_WR_USER_REG);             // command
    while(SSP1CON2bits.ACKSTAT){;}          // ACK-bit
    WriteI2C1(mode);                        // mode
    while(SSP1CON2bits.ACKSTAT){;}          // ACK-bit
    StopI2C1();
}

void wrSHT21(TYPE_SHT21_CMD cmd)
{
    IdleI2C1();                             // 
    StartI2C1();                            // send start condition
    while(SSP1CON2bits.SEN){;}              // 
    WriteI2C1(SHT21_WR);                    // addressing 
    while(SSP1CON2bits.ACKSTAT){;}          // ACK from sensor
    WriteI2C1(cmd);                         // command
    while(SSP1CON2bits.ACKSTAT){;}          // ACK from sensor
    StopI2C1();
}

void rdSHT21(uint8_t *pntData)
{
    IdleI2C1();                             // 
    StartI2C1();                            // send start condition
    while(SSP1CON2bits.SEN){;}              // 
    WriteI2C1(SHT21_RD);                    // addressing 
    while(SSP1CON2bits.ACKSTAT){;}          // ACK from sensor
    
    pntData[1] = ReadI2C1();                // MSB
    AckI2C1();                              // ACK master
    pntData[0] = ReadI2C1();                // LSB
    NotAckI2C1();                           // NACK master
    StopI2C1();
}

void rdSHT21_user(TYPE_USER_REG *pntData)
{
    IdleI2C1();                             // 
    StartI2C1();                            // send start condition
    while(SSP1CON2bits.SEN){;}              // 
    WriteI2C1(SHT21_WR);                    // addressing 
    while(SSP1CON2bits.ACKSTAT){;}          // ACK from sensor
    WriteI2C1(CMD_RD_USER_REG);             // 
    while(SSP1CON2bits.ACKSTAT){;}          // ACK from sensor
    WriteI2C1(SHT21_RD);
    while(SSP1CON2bits.ACKSTAT){;}          // ACK from sensor
    *pntData = ReadI2C1();                  //
    NotAckI2C1();                           // NACK master
    StopI2C1();
}
