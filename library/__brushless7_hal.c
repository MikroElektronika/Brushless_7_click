/*
    __brushless7_hal.c
    
-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2019, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**  

| Global Library Prefix | **HAL**            |
|:---------------------:|:------------------:|
| Version               | **3.2.0**          |
| Date                  | **Sep 2019**       |
| Developer             | **MikroE FW Team** |

*/

// -------------------------------------------------------------------------- 

#include "stdint.h"

 
// HAL Global Abstract Type

#define hal_p_t         const uint8_t*      

#define hal_obj_spi_t   const hal_struct_spi_t*
#define hal_obj_i2c_t   const hal_struct_i2c_t*
#define hal_obj_uart_t  const hal_struct_uart_t*
#define hal_obj_gpio_t  const hal_struct_gpio_t*
     
//   #define   __HAL_SPI__   // SPI HAL selector               
    #define   __HAL_I2C__   // I2C HAL selector 
//  #define   __HAL_UART__  // UART HAL selector                         

  #define   __AN_PIN_INPUT__          0
// #define   __RST_PIN_INPUT__         1
// #define   __CS_PIN_INPUT__          2
// #define   __SCK_PIN_INPUT__         3
// #define   __MISO_PIN_INPUT__        4                                   
// #define   __MOSI_PIN_INPUT__        5
// #define   __PWM_PIN_INPUT__         6                                  
  #define   __INT_PIN_INPUT__         7
// #define   __RX_PIN_INPUT__          8                              
// #define   __TX_PIN_INPUT__          9
// #define   __SCL_PIN_INPUT__         10                                  
// #define   __SDA_PIN_INPUT__         11  

// #define   __AN_PIN_OUTPUT__         0
  #define   __RST_PIN_OUTPUT__        1                                   
  #define   __CS_PIN_OUTPUT__         2                              
// #define   __SCK_PIN_OUTPUT__        3
// #define   __MISO_PIN_OUTPUT__       4                                    
// #define   __MOSI_PIN_OUTPUT__       5
  #define   __PWM_PIN_OUTPUT__        6                                    
// #define   __INT_PIN_OUTPUT__        7
// #define   __RX_PIN_OUTPUT__         8                                
// #define   __TX_PIN_OUTPUT__         9
// #define   __SCL_PIN_OUTPUT__        10                                    
// #define   __SDA_PIN_OUTPUT__        11    
 
// -------------------------------------------------------------------------- 
 
#ifdef __HAL_SPI__

/**
 * @brief Map SPI Function Pointers
 */
static void hal_spi_map(hal_p_t spi_obj);

/**
 * @brief hal_spi_write
 *
 * @param[in] p_buf             pointer to data buffer
 * @param[in] len           number of bytes for writing
 *
 * Function executes write sequence of n bytes.
 *
 * @note
 * This function have not using CS pin.
 */
static void hal_spi_write(uint8_t *p_buf, uint16_t len);

/**
 * @brief hal_spi_read
 *
 * @param[out] p_buf            pointer to data buffer
 * @param[in]  len          number of bytes for writing
 *
 * Function executes read sequence of n bytes.
 *
 * @note
 * This function should not use CS pin.
 */
static void hal_spi_read(uint8_t *p_buf, uint16_t len);

/**
 * @brief hal_spi_transfer
 *
 * @param[in]  p_in             pointer to write data buffer
 * @param[out] p_out            pointer to read data buffer
 * @param[in]  len          number of bytes for writing
 *
 * Function should executes read/write sequence of n bytes.
 *
 * @note
 * This function should not use CS pin.
 */
static void hal_spi_transfer(uint8_t *p_in, uint8_t *p_out, uint16_t len);
                                                      
#endif

// --------------------------------------------------------------------------    

#ifdef __HAL_I2C__

/**
 * @brief Map I2C Function Pointers
 */
static void hal_i2c_map(hal_p_t i2c_obj);

/**
 * @brief hal_i2c_start
 *
 * @return    0                No Error
 *
 * Function executes start condition on I2C BUS.
 */
static int hal_i2c_start(void);

/**
 * @brief hal_i2c_write
 *
 * @param[in] slave_addr     7 bit slave addres without 0 bit (read/write bit)
 * @param[in] p_buf             pointer to data buffer
 * @param[in] len           number of bytes for writing
 * @param[in] end_mode          END_MODE_STOP / END_MODE_RESTART / END_MODE_NO
 *
 * @return    0                No Error
 *
 * Function should executes write sequence on I2C bus.
 *
 * |       8 Bits      | Write Sequence (n Bytes) | End Mode       |
 * |:-----------------:|:------------------------:|:--------------:|
 * | Slave Address + W | Data Bytes               | Stop / Restart |
 *
 * @note
 * This function alongside with hal_i2c_start represents comlete write sequence.
 *
 * @warning
 * No End mode is not possible on all architectures.
 */
static int hal_i2c_write(uint8_t slave_addr, uint8_t *p_buf, uint16_t len, uint8_t end_mode);

/**
 * @brief hal_i2c_read
 *
 * @param[in] slave_addr     7 bit slave addres without 0 bit (read/write bit)
 * @param[in] p_buf             pointer to data buffer
 * @param[in] len           number of bytes to read
 * @param[in] end_mode          END_MODE_STOP / END_MODE_RESTART / END_MODE_NO
 *
 * @return    0                No Error
 *
 * Function should executes read sequence on I2C bus.
 * 
 * |       8 Bits      | Read Sequence (n Bytes)  | End Mode       |
 * |:-----------------:|:------------------------:|:--------------:|
 * | Slave Address + R | Data Bytes + ACK/NACK    | Stop / Restart |
 *
 * @note
 * This function alongside with hal_i2c_start represents comlete read sequence.
 *
 * @warning
 * No End mode is not possible on all architectures.
 */
static int hal_i2c_read(uint8_t slave_addr, uint8_t *p_buf, uint16_t len, uint8_t end_mode);

#endif

// --------------------------------------------------------------------------    

#ifdef __HAL_UART__

/**
 * @brief Map UART Function Pointers
 */
static void hal_uart_map(hal_p_t uart_obj);

/**
 * @brief hal_uart_write
 *
 * @param[in] input tx data byte
 *
 * Function writes one byte on UART.
 */
static void hal_uart_write(uint8_t input);

/**
 * @brief hal_uart_read
 *
 * @return rx data byte
 *
 * Function reads one byte.
 */
static uint8_t hal_uart_read();

/**
 * @brief hal_uart_ready
 *
 * @return rx buffer state
 *
 * Function should return 1 if rx buffer have received new data.
 */
static uint8_t hal_uart_ready();

#endif

// --------------------------------------------------------------------------    

typedef void    (*hal_gpio_set_fp_t)(uint8_t);                         
typedef uint8_t (*hal_gpio_get_fp_t)();

typedef struct
{
    hal_gpio_set_fp_t      gpio_set[ 12 ];
    hal_gpio_get_fp_t      gpio_get[ 12 ];
  
}hal_struct_gpio_t;

#ifdef __AN_PIN_INPUT__
static hal_gpio_get_fp_t          hal_gpio_an_get; 
#endif
#ifdef __CS_PIN_INPUT__
static hal_gpio_get_fp_t          hal_gpio_cs_get; 
#endif
#ifdef __RST_PIN_INPUT__
static hal_gpio_get_fp_t          hal_gpio_rst_get; 
#endif
#ifdef __SCK_PIN_INPUT__
static hal_gpio_get_fp_t          hal_gpio_sck_get; 
#endif
#ifdef __MISO_PIN_INPUT__
static hal_gpio_get_fp_t          hal_gpio_miso_get; 
#endif
#ifdef __MOSI_PIN_INPUT__
static hal_gpio_get_fp_t          hal_gpio_mosi_get; 
#endif
#ifdef __PWM_PIN_INPUT__
static hal_gpio_get_fp_t          hal_gpio_pwm_get; 
#endif
#ifdef __INT_PIN_INPUT__
static hal_gpio_get_fp_t          hal_gpio_int_get; 
#endif
#ifdef __RX_PIN_INPUT__   
static hal_gpio_get_fp_t          hal_gpio_rx_get; 
#endif
#ifdef __TX_PIN_INPUT__   
static hal_gpio_get_fp_t          hal_gpio_tx_get; 
#endif
#ifdef __SCL_PIN_INPUT__  
static hal_gpio_get_fp_t          hal_gpio_scl_get; 
#endif
#ifdef __SDA_PIN_INPUT__  
static hal_gpio_get_fp_t          hal_gpio_sda_get; 
#endif
#ifdef __AN_PIN_OUTPUT__  
static hal_gpio_set_fp_t          hal_gpio_an_set;  
#endif
#ifdef __CS_PIN_OUTPUT__
static hal_gpio_set_fp_t          hal_gpio_cs_set;  
#endif
#ifdef __RST_PIN_OUTPUT__ 
static hal_gpio_set_fp_t          hal_gpio_rst_set;  
#endif
#ifdef __SCK_PIN_OUTPUT__ 
static hal_gpio_set_fp_t          hal_gpio_sck_set;  
#endif
#ifdef __MISO_PIN_OUTPUT__
static hal_gpio_set_fp_t          hal_gpio_miso_set;  
#endif
#ifdef __MOSI_PIN_OUTPUT__
static hal_gpio_set_fp_t          hal_gpio_mosi_set;  
#endif
#ifdef __PWM_PIN_OUTPUT__ 
static hal_gpio_set_fp_t          hal_gpio_pwm_set;  
#endif
#ifdef __INT_PIN_OUTPUT__ 
static hal_gpio_set_fp_t          hal_gpio_int_set;  
#endif
#ifdef __RX_PIN_OUTPUT__  
static hal_gpio_set_fp_t          hal_gpio_rx_set;  
#endif
#ifdef __TX_PIN_OUTPUT__  
static hal_gpio_set_fp_t          hal_gpio_tx_set;  
#endif
#ifdef __SCL_PIN_OUTPUT__ 
static hal_gpio_set_fp_t          hal_gpio_scl_set;  
#endif
#ifdef __SDA_PIN_OUTPUT__ 
static hal_gpio_set_fp_t          hal_gpio_sda_set;  
#endif                              

/**
 * @brief Map GPIO Function pointers
 */
static void hal_gpio_map(hal_p_t gpio_obj)
{
    hal_obj_gpio_t tmp = (hal_obj_gpio_t)gpio_obj;

#ifdef __AN_PIN_INPUT__
    hal_gpio_an_get = tmp->gpio_get[ __AN_PIN_INPUT__ ];
#endif
#ifdef __CS_PIN_INPUT__
    hal_gpio_cs_get = tmp->gpio_get[ __CS_PIN_INPUT__ ];
#endif
#ifdef __RST_PIN_INPUT__
    hal_gpio_rst_get = tmp->gpio_get[ __RST_PIN_INPUT__ ];
#endif
#ifdef __SCK_PIN_INPUT__  
    hal_gpio_sck_get = tmp->gpio_get[ __SCK_PIN_INPUT__ ];
#endif
#ifdef __MISO_PIN_INPUT__ 
    hal_gpio_miso_get = tmp->gpio_get[ __MISO_PIN_INPUT__ ];
#endif
#ifdef __MOSI_PIN_INPUT__ 
    hal_gpio_mosi_get = tmp->gpio_get[ __MOSI_PIN_INPUT__ ];
#endif
#ifdef __PWM_PIN_INPUT__  
    hal_gpio_pwm_get = tmp->gpio_get[ __PWM_PIN_INPUT__ ];
#endif
#ifdef __INT_PIN_INPUT__ 
    hal_gpio_int_get = tmp->gpio_get[ __INT_PIN_INPUT__ ];
#endif
#ifdef __RX_PIN_INPUT__   
    hal_gpio_rx_get = tmp->gpio_get[ __RX_PIN_INPUT__ ];
#endif
#ifdef __TX_PIN_INPUT__   
    hal_gpio_tx_get = tmp->gpio_get[ __TX_PIN_INPUT__ ];
#endif
#ifdef __SCL_PIN_INPUT__  
    hal_gpio_scl_get = tmp->gpio_get[ __SCL_PIN_INPUT__ ];
#endif
#ifdef __SDA_PIN_INPUT__  
    hal_gpio_sda_get = tmp->gpio_get[ __SDA_PIN_INPUT__ ];
#endif
#ifdef __AN_PIN_OUTPUT__  
    hal_gpio_an_set = tmp->gpio_set[ __AN_PIN_OUTPUT__ ];
#endif
#ifdef __CS_PIN_OUTPUT__
    hal_gpio_cs_set = tmp->gpio_set[ __CS_PIN_OUTPUT__ ];
#endif
#ifdef __RST_PIN_OUTPUT__ 
    hal_gpio_rst_set = tmp->gpio_set[ __RST_PIN_OUTPUT__ ];
#endif
#ifdef __SCK_PIN_OUTPUT__ 
    hal_gpio_sck_set = tmp->gpio_set[ __SCK_PIN_OUTPUT__ ];
#endif
#ifdef __MISO_PIN_OUTPUT__
    hal_gpio_miso_set = tmp->gpio_set[ __MISO_PIN_OUTPUT__ ];
#endif
#ifdef __MOSI_PIN_OUTPUT__
    hal_gpio_mosi_set = tmp->gpio_set[ __MOSI_PIN_OUTPUT__ ];
#endif
#ifdef __PWM_PIN_OUTPUT__ 
    hal_gpio_pwm_set = tmp->gpio_set[ __PWM_PIN_OUTPUT__ ];
#endif
#ifdef __INT_PIN_OUTPUT__ 
    hal_gpio_int_set = tmp->gpio_set[ __INT_PIN_OUTPUT__ ];
#endif
#ifdef __RX_PIN_OUTPUT__  
    hal_gpio_rx_set = tmp->gpio_set[ __RX_PIN_OUTPUT__ ];
#endif
#ifdef __TX_PIN_OUTPUT__  
    hal_gpio_tx_set = tmp->gpio_set[ __TX_PIN_OUTPUT__ ];
#endif
#ifdef __SCL_PIN_OUTPUT__ 
    hal_gpio_scl_set = tmp->gpio_set[ __SCL_PIN_OUTPUT__ ];
#endif
#ifdef __SDA_PIN_OUTPUT__ 
    hal_gpio_sda_set = tmp->gpio_set[ __SDA_PIN_OUTPUT__ ];
#endif
}
// --------------------------------------------------------------------------    

#ifdef __MIKROC_PRO_FOR_PIC__
#include "__HAL_PIC.c"
#endif

#ifdef __MIKROC_PRO_FOR_PIC32__
#include "__HAL_PIC32.c"
#endif

#ifdef __MIKROC_PRO_FOR_DSPIC__
#include "__HAL_DSPIC.c"
#endif

#ifdef __MIKROC_PRO_FOR_AVR__
#include "__HAL_AVR.c"
#endif

#ifdef __MIKROC_PRO_FOR_FT90x__
#include "__HAL_FT90x.c"
#endif

#ifdef __MIKROC_PRO_FOR_ARM__
#ifdef __STM32__
#include "__HAL_STM32.c"
#endif
#endif

#ifdef __MIKROC_PRO_FOR_ARM__
#ifdef __TI__
#ifndef MSP432P401R
#include "__HAL_TIVA.c"
#endif
#endif
#endif

#ifdef __MIKROC_PRO_FOR_ARM__
#ifdef MSP432P401R
#include "__HAL_MSP432.c"
#endif
#endif

#ifdef __MIKROC_PRO_FOR_ARM__
#ifdef __KINETIS__
#include "__HAL_KINETIS.c"
#endif
#endif

#ifdef __MIKROC_PRO_FOR_ARM__
#ifdef __MCHP__
#include "__HAL_CEC.c"
#endif
#endif

// --------------------------------------------------------------------------    

/*
  __brushless7_hal.c

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
