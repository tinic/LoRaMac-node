/*!
 * \file      main.c
 *
 * \brief     Tx Continuous Wave implementation
 *
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \code
 *                ______                              _
 *               / _____)             _              | |
 *              ( (____  _____ ____ _| |_ _____  ____| |__
 *               \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 *               _____) ) ____| | | || |_| ____( (___| | | |
 *              (______/|_____)_|_|_| \__)_____)\____)_| |_|
 *              (C)2013-2017 Semtech
 *
 * \endcode
 *
 * \author    Miguel Luis ( Semtech )
 *
 * \author    Gregory Cristian ( Semtech )
 */
#include "board.h"
#include "system/gpio.h"
#include "system/timer.h"
#include "radio.h"

#if defined( REGION_AS923 )

#define RF_FREQUENCY                                923000000 // Hz

#elif defined( REGION_AU915 )

#define RF_FREQUENCY                                915000000 // Hz

#elif defined( REGION_CN779 )

#define RF_FREQUENCY                                779000000 // Hz

#elif defined( REGION_EU868 )

#define RF_FREQUENCY                                868000000 // Hz

#elif defined( REGION_KR920 )

#define RF_FREQUENCY                                920000000 // Hz

#elif defined( REGION_IN865 )

#define RF_FREQUENCY                                865000000 // Hz

#elif defined( REGION_US915 )

#define RF_FREQUENCY                                915000000 // Hz

#elif defined( REGION_RU864 )

#define RF_FREQUENCY                                864000000 // Hz

#else

    #error "Please define a frequency band in the compiler options."

#endif

#define TX_OUTPUT_POWER                             20        // 20 dBm
#define TX_TIMEOUT                                  65535     // seconds (MAX value)

static TimerEvent_t Led4Timer;
volatile bool Led4TimerEvent = false;

static TimerEvent_t Led2Timer;
volatile bool Led2TimerEvent = false;

static TimerEvent_t Led3Timer;
volatile bool Led3TimerEvent = false;

/*!
 * Radio events function pointer
 */
static RadioEvents_t RadioEvents;

/*!
 * LED GPIO pins objects
 */
extern Gpio_t Led4;
extern Gpio_t Led2;
extern Gpio_t Led3;

/*!
 * \brief Function executed on Led 1 Timeout event
 */
void OnLed4TimerEvent( void* context )
{
    Led4TimerEvent = true;
}

/*!
 * \brief Function executed on Led 2 Timeout event
 */
void OnLed2TimerEvent( void* context )
{
    Led2TimerEvent = true;
}

/*!
 * \brief Function executed on Led 3 Timeout event
 */
void OnLed3TimerEvent( void* context )
{
    Led3TimerEvent = true;
}

/*!
 * \brief Function executed on Radio Tx Timeout event
 */
void OnRadioTxTimeout( void )
{
    // Restarts continuous wave transmission when timeout expires
    Radio.SetTxContinuousWave( RF_FREQUENCY, TX_OUTPUT_POWER, TX_TIMEOUT );
}

/**
 * Main application entry point.
 */
int main( void )
{
    // Target board initialization
    BoardInitMcu( );
    BoardInitPeriph( );

    TimerInit( &Led4Timer, OnLed4TimerEvent );
    TimerSetValue( &Led4Timer, 90 );

    TimerInit( &Led2Timer, OnLed2TimerEvent );
    TimerSetValue( &Led2Timer, 90 );

    TimerInit( &Led3Timer, OnLed3TimerEvent );
    TimerSetValue( &Led3Timer, 90 );

    // Switch LED 1 ON
    GpioWrite( &Led4, 0 );
    TimerStart( &Led4Timer );

    // Radio initialization
    RadioEvents.TxTimeout = OnRadioTxTimeout;
    Radio.Init( &RadioEvents );

    Radio.SetTxContinuousWave( RF_FREQUENCY, TX_OUTPUT_POWER, TX_TIMEOUT );

    // Blink LEDs just to show some activity
    while( 1 )
    {
        if( Led4TimerEvent == true )
        {
            Led4TimerEvent = false;

            // Switch LED 4 OFF
            GpioWrite( &Led4, 4 );
            // Switch LED 2 ON
            GpioWrite( &Led2, 0 );
            TimerStart( &Led2Timer );
        }

        if( Led2TimerEvent == true )
        {
            Led2TimerEvent = false;

            // Switch LED 2 OFF
            GpioWrite( &Led2, 1 );
            // Switch LED 3 ON
            GpioWrite( &Led3, 0 );
            TimerStart( &Led3Timer );
        }

        if( Led3TimerEvent == true )
        {
            Led3TimerEvent = false;

            // Switch LED 3 OFF
            GpioWrite( &Led3, 1 );
            // Switch LED 1 ON
            GpioWrite( &Led4, 0 );
            TimerStart( &Led4Timer );
        }
    }
}
