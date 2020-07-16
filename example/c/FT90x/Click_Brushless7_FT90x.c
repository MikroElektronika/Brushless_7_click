/*
Example for Brushless7 Click

    Date          : May 2020.
    Author        : Luka Filipovic

Test configuration FT90x :
    
    MCU                : FT900
    Dev. Board         : EasyFT90x v7 
    FT90x Compiler ver : v2.3.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initialization of communication module
- Application Initialization - Setts default configuration and sets 
                               parameters for selected mode
- Application Task - Setts 3 different speed of motor in span of 20 seconds

Additional Functions :

- void stop_start (  ) - Funcnction stops motor and then restores 
                         previous mode of working

*/

#include "Click_Brushless7_types.h"
#include "Click_Brushless7_config.h"
#include "Click_Brushless7_other_peripherals.h"

char demo_txt[ 30 ] = "";
uint8_t demo_type_data = 0;

void stop_start (  )
{
    brushless7_control_mode_set( BRUSHLESS7_CTRL_TYPE_STOP );
    Delay_ms( 1000 );
    brushless7_control_mode_set( demo_type_data );
}

void system_init ( )
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_INPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_AN_PIN, _GPIO_INPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_RST_PIN, _GPIO_OUTPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_CS_PIN, _GPIO_OUTPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_PWM_PIN, _GPIO_OUTPUT );

    mikrobus_i2cInit( _MIKROBUS1, &BRUSHLESS7_I2C_CFG[0] );

    mikrobus_logInit( _LOG_USBUART, 9600 );

    Delay_ms( 100 );
}

void application_init ( )
{
    uint8_t error_flag = 0;
    
    mikrobus_logWrite( "", _LOG_LINE );
    mikrobus_logWrite( " ***** APP INIT ***** ", _LOG_LINE );
    
    brushless7_i2c_driver_init( (brushless7_obj_t)&_MIKROBUS1_GPIO, 
                                (brushless7_obj_t)&_MIKROBUS1_I2C, 
                                BRUSHLESS7_SLAVE_ADDR );
    Delay_ms( 100 );

    brushless7_default_config(  );
    
    demo_type_data = BRUSHLESS7_CTRL_TYPE_DUTY;

    brushless7_control_mode_set( demo_type_data );
    brushless7_rotating_direction( BRUSHLESS7_DIR_CW );

    if ( BRUSHLESS7_CTRL_TYPE_DUTY == demo_type_data )
    {
        error_flag |= brushless7_max_duty( 95.0 );
        error_flag |= brushless7_start_duty( 5.0 );
        error_flag |= brushless7_stop_duty( 2.0 );
        brushless7_change_duty( 20 );
        mikrobus_logWrite( " ----- DUTY CONTROL ----- ", _LOG_LINE );
    }
    else if ( BRUSHLESS7_CTRL_TYPE_RPM == demo_type_data )
    {
        error_flag |= brushless7_max_speed_rpm( BRUSHLESS7_MAX_SPEED_4096 );
        error_flag |= brushless7_start_rpm( 400 );
        mikrobus_logWrite( " ----- RPM CONTROL ----- ", _LOG_LINE );
    }
    
    if ( BRUSHLESS7_DEV_ERROR == error_flag )
    {
        mikrobus_logWrite( " ----- ERROR ----- ", _LOG_LINE );
        for( ; ; );
    }

    mikrobus_logWrite( " ***** APP TASK ***** ", _LOG_LINE );
}

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

void main ( )
{
    system_init( );
    application_init( );

    for ( ; ; )
    {
            application_task( );
    }
}