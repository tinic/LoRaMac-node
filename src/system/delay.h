/*!
 * \file      delay.h
 *
 * \brief     Delay implementation
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
#ifndef __SEMTECH_DELAY_H__
#define __SEMTECH_DELAY_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

/*! 
 * Blocking delay of "s" seconds
 */
void Delay( float s );

/*! 
 * Blocking delay of "ms" milliseconds
 */
void DelayMs( uint32_t ms );

#ifdef __cplusplus
}
#endif

#endif // __SEMTECH_DELAY_H__

