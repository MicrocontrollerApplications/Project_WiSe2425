//*******************************************************************
//
//  File:       SHT21.h
//  Author:     VSK
//
//  Created on  26. Nov. 2019
//  Modified    
//
//*******************************************************************

#ifndef SHT21_H
#define	SHT21_H

#include <xc.h>
#include <stdint.h>
#include "PLIB/plib.h"

#define SHT21_WR     0x80
#define SHT21_RD     0x81

#define SHT21_TEMP_FROM_VAL(x) (float)((175.72 * x) / 65536) - 46.85f;
#define SHT21_RH_FROM_VAL(x) 125.f*x/65536.f - 6.f

typedef enum
{
    CMD_TRIG_T_HOLD     = 0xE3,
    CMD_TRIG_RH_HOLD    = 0xE5,
    CMD_WR_USER_REG     = 0xE6,
    CMD_RD_USER_REG     = 0xE7,
    CMD_TRIG_T          = 0xF3,
    CMD_TRIG_RH         = 0xF5,
    CMD_SOFT_RES        = 0xFE
}TYPE_SHT21_CMD;

typedef enum
{
    MODE_RH12_T14_BIT   = 0x00,
    MODE_RH08_T12_BIT   = 0x40,
    MODE_RH10_T13_BIT   = 0x80,
    MODE_RH11_T11_BIT   = 0xC0,
    BAT_STATUS_MASK     = 0x20,
    EN_OC_HEATER        = 0x02,
    DIS_OC_HEATER       = 0x00,
    DIS_OTP_RELOAD      = 0x01,
    EN_OTP_RELOAD       = 0x00
}TYPE_USER_REG;

typedef enum
{
    TMAX_14BIT  = 85,   // ms
    TMAX_13BIT  = 43,
    TMAX_12BIT  = 22,
    TMAX_11BIT  = 11,
    RHMAX_12BIT = 29,
    RHMAX_11BIT = 15,
    RHMAX_10BIT = 9,
    RHMAX_8BIT  = 4
}TYPE_SHT21_MEASUREMENT_TIME;

extern void initSHT21(TYPE_USER_REG mode);
extern void wrSHT21(TYPE_SHT21_CMD cmd);
extern void rdSHT21(uint16_t *pntData);
extern void rdSHT21_user(TYPE_USER_REG *pntData);

#endif  //SHT21_H
