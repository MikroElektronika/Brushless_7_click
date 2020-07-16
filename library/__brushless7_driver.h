/*
    __brushless7_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2019, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**

| Global Library Prefix | **BRUSHLESS7** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **May 2020.**      |
| Developer             | **Luka Filipovic**     |

*/

// --------------------------------------------------------------------------    

#include "stdint.h"

#ifndef _BRUSHLESS7_H_
#define _BRUSHLESS7_H_

/** 
 * @macro brushless7_obj_t
 * @brief Driver Abstract type 
 */
#define brushless7_obj_t    const uint8_t*

// --------------------------------------------------------------------------    

//  #define   __BRUSHLESS7_DRV_SPI__                            
   #define   __BRUSHLESS7_DRV_I2C__                                                                      
// #define   __BRUSHLESS7_DRV_UART__                           

extern const uint8_t BRUSHLESS7_SLAVE_ADDR;

extern const uint8_t BRUSHLESS7_REG_0;
extern const uint8_t BRUSHLESS7_REG_1;
extern const uint8_t BRUSHLESS7_REG_2;
extern const uint8_t BRUSHLESS7_REG_3;
extern const uint8_t BRUSHLESS7_REG_4;
extern const uint8_t BRUSHLESS7_REG_5;
extern const uint8_t BRUSHLESS7_REG_6;
extern const uint8_t BRUSHLESS7_REG_7;
extern const uint8_t BRUSHLESS7_REG_8;
extern const uint8_t BRUSHLESS7_REG_9;
extern const uint8_t BRUSHLESS7_REG_10;
extern const uint8_t BRUSHLESS7_REG_11;
extern const uint8_t BRUSHLESS7_REG_12;
extern const uint8_t BRUSHLESS7_REG_13;
extern const uint8_t BRUSHLESS7_REG_14;
extern const uint8_t BRUSHLESS7_REG_15;
extern const uint8_t BRUSHLESS7_REG_16;
extern const uint8_t BRUSHLESS7_REG_17;
extern const uint8_t BRUSHLESS7_REG_18;
extern const uint8_t BRUSHLESS7_REG_19;
extern const uint8_t BRUSHLESS7_REG_20;
extern const uint8_t BRUSHLESS7_REG_21;
extern const uint8_t BRUSHLESS7_REG_22;
extern const uint8_t BRUSHLESS7_REG_23;
extern const uint8_t BRUSHLESS7_REG_24;
extern const uint8_t BRUSHLESS7_REG_25;
extern const uint8_t BRUSHLESS7_REG_26;
extern const uint8_t BRUSHLESS7_REG_27;
extern const uint8_t BRUSHLESS7_REG_28;
extern const uint8_t BRUSHLESS7_REG_29;
extern const uint8_t BRUSHLESS7_REG_30;
extern const uint8_t BRUSHLESS7_REG_86;
extern const uint8_t BRUSHLESS7_REG_87;

extern const uint8_t BRUSHLESS7_DEV_ERROR;
extern const uint8_t BRUSHLESS7_DEV_OK;

extern const uint8_t BRUSHLESS7_MAX_SPEED_4096;
extern const uint8_t BRUSHLESS7_MAX_SPEED_8192;
extern const uint8_t BRUSHLESS7_MAX_SPEED_16384;
extern const uint8_t BRUSHLESS7_MAX_SPEED_32768;

extern const uint8_t BRUSHLESS7_CTRL_TYPE_RPM;
extern const uint8_t BRUSHLESS7_CTRL_TYPE_DUTY;
extern const uint8_t BRUSHLESS7_CTRL_TYPE_STOP;

extern const uint8_t BRUSHLESS7_DIR_CW;
extern const uint8_t BRUSHLESS7_DIR_CCW;

// -------------------------------------------------------------------------- 
   
#ifdef __cplusplus
extern "C"{
#endif

// ----------------------------------------------------- Driver Initialization

#ifdef   __BRUSHLESS7_DRV_SPI__
void brushless7_spi_driver_init( brushless7_obj_t gpio_obj, 
                                 brushless7_obj_t spi_obj );
#endif
#ifdef   __BRUSHLESS7_DRV_I2C__
void brushless7_i2c_driver_init( brushless7_obj_t gpio_obj, 
                                 brushless7_obj_t i2c_obj, 
                                 uint8_t slave );
#endif
#ifdef   __BRUSHLESS7_DRV_UART__
void brushless7_uart_driver_init( brushless7_obj_t gpio_obj, 
                                  brushless7_obj_t uart_obj );
#endif

// -------------------------------------------------------- Driver Functions 

/**
 * @brief Generic function for writing data to register
 * 
 * @param[in]    reg_adr            register address
 * 
 * @param[in]    tx_data            data to be written
 */
void brushless7_generic_write ( uint8_t reg_adr, uint8_t tx_data );

/**
 * @brief Generic function for reading data from registar
 * 
 * @param[in]    reg_adr            register address
 * 
 * @return Read data
 */
uint8_t brushless7_generic_read ( uint8_t reg_adr );

/**
 * @brief Generic function for setting SBY pin state
 *
 * @param[in]    state           state of the pin
 */
void brushless7_set_sby_pin_state ( uint8_t state );

/**
 * @brief Generic function for getting INT pin state
 *
 * @return   State of the pin
 */
uint8_t brushless7_get_int_pin_state ( void );

/**
 * @brief Function for setting start duty of device
 *
 * @param[in]    duty_ptc         duty in percentage
 *
 * @return   One of two dev status.
 * 
 * @note duty_ptc should be in range 0% to 49.8%
 */
uint8_t brushless7_start_duty ( float duty_ptc );

/**
 * @brief Function for setting stop duty of device
 *
 * @param[in]    duty_ptc         duty in percentage
 *
 * @return   One of two dev status.
 * 
 * @note duty_ptc should be in range 0% to 49.6%
 */
uint8_t brushless7_stop_duty ( float duty_ptc );

/**
 * @brief Function for changeing duty of device
 *
 * @param[in]    duty_ptc         duty in percentage
 *
 * @return   One of two dev status.
 * 
 * @note duty_ptc should be in range 0.4% to 99.6%
 */
uint8_t brushless7_change_duty ( float dury_ptc );

/**
 * @brief Function for setting max duty of device
 *
 * @param[in]    duty_ptc         duty in percentage
 *
 * @return   One of two dev status.
 * 
 * @note duty_ptc should be in range 50.2% to 100%
 */
uint8_t brushless7_max_duty ( float duty_ptc );

/**
 * @brief Function for setting start rpm parameter of device
 *
 * @param[in]    rpm_val         value
 *
 * @return   One of two dev status.
 * 
 * @note value should be in range 0 to 4095
 */
uint8_t brushless7_start_rpm ( uint16_t rpm_val );

/**
 * @brief Function for setting max rpm parameter of device
 *
 * @param[in]    max_speed_rpm         library macro
 *
 * @return   One of two dev status.
 */
uint8_t brushless7_max_speed_rpm ( uint8_t max_speed_rpm );

/**
 * @brief Function for setting rotation direction
 *
 * @param[in]    direction_rot         library macro
 *
 * @return   One of two dev status.
 */
uint8_t brushless7_rotating_direction ( uint8_t direction_rot );

/**
 * @brief Function for setting type of device control
 *
 * @param[in]    ctrl_type         library macro
 *
 * @return   One of two dev status.
 */
uint8_t brushless7_control_mode_set ( uint8_t ctrl_type );

/**
 * @brief Function for setting default device configuration
 */
void brushless7_default_config ( void );

// --------------------------------------------------------------------------    

#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_Brushless7_STM.c
    @example Click_Brushless7_TIVA.c
    @example Click_Brushless7_CEC.c
    @example Click_Brushless7_KINETIS.c
    @example Click_Brushless7_MSP.c
    @example Click_Brushless7_PIC.c
    @example Click_Brushless7_PIC32.c
    @example Click_Brushless7_DSPIC.c
    @example Click_Brushless7_AVR.c
    @example Click_Brushless7_FT90x.c
    @example Click_Brushless7_STM.mbas
    @example Click_Brushless7_TIVA.mbas
    @example Click_Brushless7_CEC.mbas
    @example Click_Brushless7_KINETIS.mbas
    @example Click_Brushless7_MSP.mbas
    @example Click_Brushless7_PIC.mbas
    @example Click_Brushless7_PIC32.mbas
    @example Click_Brushless7_DSPIC.mbas
    @example Click_Brushless7_AVR.mbas
    @example Click_Brushless7_FT90x.mbas
    @example Click_Brushless7_STM.mpas
    @example Click_Brushless7_TIVA.mpas
    @example Click_Brushless7_CEC.mpas
    @example Click_Brushless7_KINETIS.mpas
    @example Click_Brushless7_MSP.mpas
    @example Click_Brushless7_PIC.mpas
    @example Click_Brushless7_PIC32.mpas
    @example Click_Brushless7_DSPIC.mpas
    @example Click_Brushless7_AVR.mpas
    @example Click_Brushless7_FT90x.mpas
**/

// --------------------------------------------------------------------------    
/*
  __brushless7_driver.h

  Copyright (c) 2019, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */