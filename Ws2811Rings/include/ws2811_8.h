//
// Copyright (c) 2013 Danny Havenith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

/**
 * Library for bit-banging data to WS2811 led controllers.
 * This file contains a definition of the rgb and the send() function.
 */

#ifndef WS2811_8_H_
#define WS2811_8_H_
#include <avr/io.h>

#if !defined( WS2811_PORT)
#	define WS2811_PORT PORTB
#endif


typedef struct 
{
    uint8_t green;
    uint8_t red;
    uint8_t blue;
} rgb;


/**
 * This function sends the RGB-data in an array of rgb structs through
 * the given io-pin.
 * The port is determined by the macro WS2811_PORT, but the actual pin to
 * be used is an argument to this function. This allows a single instance of this function
 * to control up to 8 separate channels.
 */

void send( const rgb *values, uint16_t array_size, uint8_t bit);


#endif /* WS2811_8_H_ */