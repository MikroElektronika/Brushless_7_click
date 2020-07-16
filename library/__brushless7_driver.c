/*
    __brushless7_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2019, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__brushless7_driver.h"
#include "__brushless7_hal.c"

// ------------------------------------------------------------------- MACROS 

const uint8_t BRUSHLESS7_SLAVE_ADDR         = 0x32;

const uint8_t BRUSHLESS7_REG_0              = 0;
const uint8_t BRUSHLESS7_REG_1              = 1;
const uint8_t BRUSHLESS7_REG_2              = 2;
const uint8_t BRUSHLESS7_REG_3              = 3;
const uint8_t BRUSHLESS7_REG_4              = 4;
const uint8_t BRUSHLESS7_REG_5              = 5;
const uint8_t BRUSHLESS7_REG_6              = 6;
const uint8_t BRUSHLESS7_REG_7              = 7;
const uint8_t BRUSHLESS7_REG_8              = 8;
const uint8_t BRUSHLESS7_REG_9              = 9;
const uint8_t BRUSHLESS7_REG_10             = 10;
const uint8_t BRUSHLESS7_REG_11             = 11;
const uint8_t BRUSHLESS7_REG_12             = 12;
const uint8_t BRUSHLESS7_REG_13             = 13;
const uint8_t BRUSHLESS7_REG_14             = 14;
const uint8_t BRUSHLESS7_REG_15             = 15;
const uint8_t BRUSHLESS7_REG_16             = 16;
const uint8_t BRUSHLESS7_REG_17             = 17;
const uint8_t BRUSHLESS7_REG_18             = 18;
const uint8_t BRUSHLESS7_REG_19             = 19;
const uint8_t BRUSHLESS7_REG_20             = 20;
const uint8_t BRUSHLESS7_REG_21             = 21;
const uint8_t BRUSHLESS7_REG_22             = 22;
const uint8_t BRUSHLESS7_REG_23             = 23;
const uint8_t BRUSHLESS7_REG_24             = 24;
const uint8_t BRUSHLESS7_REG_25             = 25;
const uint8_t BRUSHLESS7_REG_26             = 26;
const uint8_t BRUSHLESS7_REG_27             = 27;
const uint8_t BRUSHLESS7_REG_28             = 28;
const uint8_t BRUSHLESS7_REG_29             = 29;
const uint8_t BRUSHLESS7_REG_30             = 30;
const uint8_t BRUSHLESS7_REG_86             = 86;
const uint8_t BRUSHLESS7_REG_87             = 87;

const uint8_t BRUSHLESS7_DEV_ERROR          = 0xFF;
const uint8_t BRUSHLESS7_DEV_OK             = 0x00;

const uint8_t BRUSHLESS7_MAX_SPEED_4096     = 0x00;
const uint8_t BRUSHLESS7_MAX_SPEED_8192     = 0x02;
const uint8_t BRUSHLESS7_MAX_SPEED_16384    = 0x04;
const uint8_t BRUSHLESS7_MAX_SPEED_32768    = 0x06;

const uint8_t BRUSHLESS7_CTRL_TYPE_RPM      = 0xAA;
const uint8_t BRUSHLESS7_CTRL_TYPE_DUTY     = 0xBB;
const uint8_t BRUSHLESS7_CTRL_TYPE_STOP     = 0xCC;

const uint8_t BRUSHLESS7_DIR_CW             = 0xDD;
const uint8_t BRUSHLESS7_DIR_CCW            = 0xEE;

#define ZERO                                0

#define START_DUTY_MAX                      49.8
#define START_DUTY_AMP                      512

#define STOP_DUTY_MAX                       49.6
#define STOP_DUTY_AMP                       256
#define STOP_DUTY_MASK                      0x80

#define CHANGE_DUTY_MIN                     0.4
#define CHANGE_DUTY_MAX                     99.6
#define CHANGE_DUTY_AMP                     256

#define MAX_DUTY_MIN                        50.2
#define MAX_DUTY_MAX                        100.0
#define MAX_DUTY_AMP                        512
#define MAX_DUTY_DEC                        257

#define START_RPM_MAX                       4095
#define START_RPM_SHIFT                     4
#define START_RPM_MASK                      0x0F

#define MAX_SPEED_RMP_MASK                  0xF9

#define PRECENTAGE_DIV                      100

// ---------------------------------------------------------------- VARIABLES

#ifdef   __BRUSHLESS7_DRV_I2C__
static uint8_t dev_slave_addr;
#endif

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint16_t dev_get_max_speed_rpm ( uint8_t reg_14_val );

static void dev_enable_wr ( uint8_t wr_macro );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

#ifdef   __BRUSHLESS7_DRV_SPI__

void brushless7_spi_driver_init( brushless7_obj_t gpio_obj, 
                                 brushless7_obj_t spi_obj )
{
    hal_spi_map( (hal_p_t)spi_obj );
    hal_gpio_map( (hal_p_t)gpio_obj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __BRUSHLESS7_DRV_I2C__

void brushless7_i2c_driver_init( brushless7_obj_t gpio_obj, 
                                 brushless7_obj_t i2c_obj, 
                                 uint8_t slave )
{
    dev_slave_addr = slave;
    hal_i2c_map( (hal_p_t)i2c_obj );
    hal_gpio_map( (hal_p_t)gpio_obj );

    // ... power ON
    // ... configure CHIP
    hal_gpio_cs_set( 1 );
}

#endif
#ifdef   __BRUSHLESS7_DRV_UART__

void brushless7_uart_driver_init( brushless7_obj_t gpio_obj, 
                                  brushless7_obj_t uart_obj )
{
    hal_uart_map( (hal_p_t)uart_obj );
    hal_gpio_map( (hal_p_t)gpio_obj );

    // ... power ON
    // ... configure CHIP
}

#endif

// ----------------------------------------------------------- IMPLEMENTATION 

void brushless7_generic_write ( uint8_t reg_adr, uint8_t tx_data )
{
    uint8_t write_data[ 2 ];

    write_data[ 0 ] = reg_adr;
    write_data[ 1 ] = tx_data;

    hal_i2c_start(  );
    hal_i2c_write( dev_slave_addr, write_data, 2, END_MODE_STOP );
}

uint8_t brushless7_generic_read ( uint8_t reg_adr )
{
    uint8_t rx_data;

    hal_i2c_start(  );
    hal_i2c_write( dev_slave_addr, &reg_adr, 1, END_MODE_RESTART );
    hal_i2c_read( dev_slave_addr, &rx_data, 1, END_MODE_STOP );
    
    return rx_data;
}

void brushless7_set_sby_pin_state ( uint8_t state )
{
    hal_gpio_cs_set( state );
}

uint8_t brushless7_get_int_pin_state ( void )
{
    return hal_gpio_int_get(  );
}

uint8_t brushless7_start_duty ( float duty_ptc )
{
    uint8_t temp_data = 0;
    volatile float temp_duty = 0;

    if ( ( START_DUTY_MAX < duty_ptc ) || ( ZERO > duty_ptc ) )
    {
        return BRUSHLESS7_DEV_ERROR;
    }
    
    temp_duty = duty_ptc / 100;

    temp_data = temp_duty * START_DUTY_AMP;

    brushless7_generic_write( BRUSHLESS7_REG_3, temp_data );
    
    return BRUSHLESS7_DEV_OK;
}

uint8_t brushless7_stop_duty ( float duty_ptc )
{
    uint8_t stop_data = 0;
    uint8_t temp_data = 0;
    volatile float temp_duty = 0;

    if ( ( STOP_DUTY_MAX < duty_ptc ) || ( ZERO > duty_ptc ) )
    {
        return BRUSHLESS7_DEV_ERROR;
    }
    temp_duty = duty_ptc / 100;
    temp_data = brushless7_generic_read( BRUSHLESS7_REG_2 );
    temp_data &= 0x80;
    stop_data = temp_duty * STOP_DUTY_AMP;
    temp_data |= stop_data;
    brushless7_generic_write( BRUSHLESS7_REG_2, temp_data );
    
    return BRUSHLESS7_DEV_OK;
}

uint8_t brushless7_change_duty ( float duty_ptc )
{
    uint8_t temp_data = 0;
    volatile float temp_duty = 0;

    if ( ( CHANGE_DUTY_MAX < duty_ptc ) || ( CHANGE_DUTY_MIN > duty_ptc ) )
    {
        return BRUSHLESS7_DEV_ERROR;
    }
    temp_duty = duty_ptc / PRECENTAGE_DIV;
    temp_data = temp_duty * CHANGE_DUTY_AMP;

    brushless7_generic_write( BRUSHLESS7_REG_4, temp_data );
    
    return BRUSHLESS7_DEV_OK;
}

uint8_t brushless7_max_duty ( float duty_ptc )
{
    uint8_t temp_data = 0;
    volatile float temp_duty = 0;

    if ( ( MAX_DUTY_MAX < duty_ptc ) || ( MAX_DUTY_MIN > duty_ptc ) )
    {
        return BRUSHLESS7_DEV_ERROR;
    }

    temp_duty = duty_ptc / PRECENTAGE_DIV;
    temp_data = temp_duty * STOP_DUTY_AMP;

    brushless7_generic_write( BRUSHLESS7_REG_5, temp_data );
    
    return BRUSHLESS7_DEV_OK;
}

uint8_t brushless7_start_rpm ( uint16_t rpm_val )
{
    uint8_t lsb_data = 0;
    uint8_t msb_data = 0;
    uint8_t temp_data;

    if ( ( START_RPM_MAX < rpm_val ) )
    {
        return BRUSHLESS7_DEV_ERROR;
    }

    temp_data = brushless7_generic_read( BRUSHLESS7_REG_7 );

    lsb_data = ( uint8_t )( rpm_val & 0x00FF );

    msb_data = rpm_val >> 8;
    msb_data <<= 4;
    temp_data &= START_RPM_MASK;
    temp_data |= msb_data;

    brushless7_generic_write( BRUSHLESS7_REG_6, lsb_data );
    brushless7_generic_write( BRUSHLESS7_REG_7, temp_data );
    
    return BRUSHLESS7_DEV_OK;
}

uint8_t brushless7_max_speed_rpm ( uint8_t max_speed_rpm )
{
    uint8_t temp_data = 0;

    if ( !( ( BRUSHLESS7_MAX_SPEED_4096 == max_speed_rpm  ) || 
            ( BRUSHLESS7_MAX_SPEED_8192 == max_speed_rpm  ) ||
            ( BRUSHLESS7_MAX_SPEED_16384 == max_speed_rpm  ) ||
            ( BRUSHLESS7_MAX_SPEED_32768 == max_speed_rpm  ) ) )
    {
        return BRUSHLESS7_DEV_ERROR;
    }

    temp_data = brushless7_generic_read( BRUSHLESS7_REG_14 );

    temp_data &= MAX_SPEED_RMP_MASK;
    temp_data |= max_speed_rpm;

    brushless7_generic_write( BRUSHLESS7_REG_14, temp_data );

    return BRUSHLESS7_DEV_OK;
}

uint8_t brushless7_rotating_direction ( uint8_t direction_rot )
{
    uint8_t temp_data;
    temp_data = brushless7_generic_read( BRUSHLESS7_REG_14 );
    switch ( direction_rot )
    {
        case BRUSHLESS7_DIR_CW:
        {
            temp_data &= 0xBF;
            brushless7_generic_write( BRUSHLESS7_REG_14, temp_data );
            return BRUSHLESS7_DEV_OK;
        }
        case BRUSHLESS7_DIR_CCW:
        {
            temp_data |= 0x40;
            brushless7_generic_write( BRUSHLESS7_REG_14, temp_data );
            return BRUSHLESS7_DEV_OK;
        }
        default:
        {
            return BRUSHLESS7_DEV_ERROR;
        }
    }
}

uint8_t brushless7_control_mode_set ( uint8_t ctrl_type )
{
    uint8_t ctrl_mode_data1;
    uint8_t ctrl_mode_data2;
    uint8_t ctrl_mode_data3;

    switch ( ctrl_type )
    {
        case BRUSHLESS7_CTRL_TYPE_RPM:
        {
            ctrl_mode_data1 = brushless7_generic_read( BRUSHLESS7_REG_2 );
            ctrl_mode_data2 = brushless7_generic_read( BRUSHLESS7_REG_9 );
            ctrl_mode_data3 = brushless7_generic_read( BRUSHLESS7_REG_11 );
            ctrl_mode_data1 |= 0x80;
            ctrl_mode_data2 &= 0xFC;
            ctrl_mode_data3 &= 0xFE;
            brushless7_generic_write( BRUSHLESS7_REG_2, ctrl_mode_data1 );
            brushless7_generic_write( BRUSHLESS7_REG_9, ctrl_mode_data2 );
            brushless7_generic_write( BRUSHLESS7_REG_11, ctrl_mode_data3 );
            return BRUSHLESS7_DEV_OK;
        }
        case BRUSHLESS7_CTRL_TYPE_DUTY:
        {
            ctrl_mode_data1 = brushless7_generic_read( BRUSHLESS7_REG_2 );
            ctrl_mode_data2 = brushless7_generic_read( BRUSHLESS7_REG_9 );
            ctrl_mode_data3 = brushless7_generic_read( BRUSHLESS7_REG_11 );
            ctrl_mode_data1 |= 0x80;
            ctrl_mode_data2 &= 0xFC;
            ctrl_mode_data2 |= 0x01;
            ctrl_mode_data3 |= 0x01;
            brushless7_generic_write( BRUSHLESS7_REG_2, ctrl_mode_data1 );
            brushless7_generic_write( BRUSHLESS7_REG_9, ctrl_mode_data2 );
            brushless7_generic_write( BRUSHLESS7_REG_11, ctrl_mode_data3 );
            return BRUSHLESS7_DEV_OK;
        }
        case BRUSHLESS7_CTRL_TYPE_STOP:
        {
            ctrl_mode_data1 = brushless7_generic_read( BRUSHLESS7_REG_2 );
            ctrl_mode_data2 = brushless7_generic_read( BRUSHLESS7_REG_9 );
            ctrl_mode_data1 &= 0x7F;
            ctrl_mode_data2 &= 0xFC;
            brushless7_generic_write( BRUSHLESS7_REG_2, ctrl_mode_data1 );
            brushless7_generic_write( BRUSHLESS7_REG_9, ctrl_mode_data2 );
            return BRUSHLESS7_DEV_OK;
        }
        default:
        {
            return BRUSHLESS7_DEV_ERROR;
        }
    }
}

void brushless7_default_config ( void )
{
    brushless7_generic_write( BRUSHLESS7_REG_0, 0x00 );
    brushless7_generic_write( BRUSHLESS7_REG_1, 0x00 );
    brushless7_generic_write( BRUSHLESS7_REG_2, 0x0F );
    brushless7_generic_write( BRUSHLESS7_REG_3, 0x33 );
    brushless7_generic_write( BRUSHLESS7_REG_4, 0x00 );
    brushless7_generic_write( BRUSHLESS7_REG_5, 0xCC );
    brushless7_generic_write( BRUSHLESS7_REG_6, 0x33 );
    brushless7_generic_write( BRUSHLESS7_REG_7, 0x08 );
    brushless7_generic_write( BRUSHLESS7_REG_8, 0x12 );
    brushless7_generic_write( BRUSHLESS7_REG_9, 0x00 );
    brushless7_generic_write( BRUSHLESS7_REG_10, 0x00 );
    brushless7_generic_write( BRUSHLESS7_REG_11, 0x00 );
    brushless7_generic_write( BRUSHLESS7_REG_12, 0x7F );
    brushless7_generic_write( BRUSHLESS7_REG_13, 0x7F );
    brushless7_generic_write( BRUSHLESS7_REG_14, 0x37 );
    brushless7_generic_write( BRUSHLESS7_REG_15, 0x11 );
    brushless7_generic_write( BRUSHLESS7_REG_16, 0x10 );
    brushless7_generic_write( BRUSHLESS7_REG_17, 0xC3 );
    brushless7_generic_write( BRUSHLESS7_REG_18, 0x01 );
    brushless7_generic_write( BRUSHLESS7_REG_19, 0x02 );
    brushless7_generic_write( BRUSHLESS7_REG_20, 0xA2 );
    brushless7_generic_write( BRUSHLESS7_REG_21, 0x0C );
    brushless7_generic_write( BRUSHLESS7_REG_22, 0x82 );
    brushless7_generic_write( BRUSHLESS7_REG_23, 0x3F );
    brushless7_generic_write( BRUSHLESS7_REG_24, 0x40 );
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

static uint16_t dev_get_max_speed_rpm ( uint8_t reg_14_val )
{
    switch ( reg_14_val )
    {
    case BRUSHLESS7_MAX_SPEED_4096:
        return 4096;
    case BRUSHLESS7_MAX_SPEED_8192:
        return 8192;
    case BRUSHLESS7_MAX_SPEED_16384:
        return 16384;
    case BRUSHLESS7_MAX_SPEED_32768:
        return 32768;
    default:
        return BRUSHLESS7_DEV_ERROR;
    }
}

// --------------------------------------------------------------------------

/*
  __brushless7_driver.c

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