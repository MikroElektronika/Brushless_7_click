![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# Brushless7 Click

---

- **CIC Prefix**  : BRUSHLESS7
- **Author**      : Luka Filipovic
- **Verison**     : 1.0.0
- **Date**        : May 2020.

---

- **Libstock** : https://libstock.mikroe.com/projects/view/3807/brushless-7-click
- **HEXIWEAR** : ${HEXI_LINK}
- **GitHub**   : ${GITHUB_LINK}

---

### Software Support

We provide a library for the Brushless7 Click on our [LibStock](https://libstock.mikroe.com/projects/view/3807/brushless-7-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

Library provides functions for controlling brushless motor. It has functions for communicating with device with I2C module, and controlling pins.
There are function for controlling device over couple of modes.

Key functions :

- ``` void brushless7_generic_write ( uint8_t reg_adr, uint8_t tx_data ) ``` - Function for writing one byte of data to device
- ``` uint8_t brushless7_generic_read ( uint8_t reg_adr ) ``` - Function for reading one byte of data from device
- ``` void brushless7_default_config ( void ) ``` - Function for setting default configuration of device

**Examples Description**

The application is composed of three sections :

- System Initialization - Initialization of communication module
- Application Initialization - Setts default configuration and sets 
                               parameters for selected mode
- Application Task - Setts 3 different speed of motor in span of 20 seconds


```.c

void application_task ( )
{
    if ( BRUSHLESS7_CTRL_TYPE_DUTY == demo_type_data )
    {
        mikrobus_logWrite( " ----- 20 ----- ", _LOG_LINE );
        stop_start();
        brushless7_change_duty( 20 );
        Delay_ms( 20000 );
        mikrobus_logWrite( " ----- 40 ----- ", _LOG_LINE );
        stop_start();
        brushless7_change_duty( 40 );
        Delay_ms( 20000 );
        mikrobus_logWrite( " ----- 8 ----- ", _LOG_LINE );
        stop_start();
        brushless7_change_duty( 8 );
        Delay_ms( 20000 );
    }
    else if ( BRUSHLESS7_CTRL_TYPE_RPM == demo_type_data )
    {
        mikrobus_logWrite( " ----- 400 ----- ", _LOG_LINE );
        stop_start();
        brushless7_start_rpm( 400 );
        Delay_ms( 20000 );
        mikrobus_logWrite( " ----- 1000 ----- ", _LOG_LINE );
        stop_start();
        brushless7_start_rpm( 1000 );
        Delay_ms( 20000 );
        mikrobus_logWrite( " ----- 100 ----- ", _LOG_LINE );
        stop_start();
        brushless7_start_rpm( 100 );
        Delay_ms( 20000 );
    }
}

```

Additional Functions :

- void stop_start (  ) - Funcnction stops motor and then restores 
                         previous mode of working

The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/3807/brushless-7-click) page.

Other mikroE Libraries used in the example:

- I2C
- UART

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
### Architectures Supported

#### mikroC

| STM | KIN | CEC | MSP | TIVA | PIC | PIC32 | DSPIC | AVR | FT90x |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| x | x | x | x | x | x | x | x | x | x |

#### mikroBasic

| STM | KIN | CEC | MSP | TIVA | PIC | PIC32 | DSPIC | AVR | FT90x |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| x | x | x | x | x | x | x | x | x | x |

#### mikroPascal

| STM | KIN | CEC | MSP | TIVA | PIC | PIC32 | DSPIC | AVR | FT90x |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| x | x | x | x | x | x | x | x | x | x |

---
---
