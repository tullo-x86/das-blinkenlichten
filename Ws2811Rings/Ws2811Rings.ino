/*
 * Ws2811Rings.c
 *
 * Created: 16/08/2013 6:52:11 PM
 *  Author: mccubbinaj
 */ 

#define F_CPU 8000000UL  // 8 MHz

#include <util/delay.h>

#include <avr/io.h>
#include "ws2811_8.h"
#include "chasers.h"

rgb buffer[] =
 {
	{40,40,40}, {0,40,0}, {40,0,0},
	{0,0,10}, {0,10,0}, {10,0,0},
	{0,0,10}, {0,10,0}, {10,0,0},
	{0,0,10}, {0,10,0}, {10,0,0},
	{0,0,10}, {0,10,0}, {10,0,0},
	{0,0,10}, {0,10,0}, {10,0,0},
	{0,0,10}, {0,10,0}, {10,0,0},
	{0,0,10}, {0,10,0}, {10,0,0},
	{0,0,10}, {0,10,0}, {10,0,0},
	{0,0,10}, {0,10,0}, {10,0,0},
	{0,0,10}, {0,10,0}, {10,0,0},
	{0,0,10}, {0,10,0}, {10,0,0},
	{0,0,10}, {0,10,0}, {10,0,0},
	{0,0,10}, {0,10,0}, {10,0,0},
	{0,0,10}, {0,10,0}, {10,0,0},
	{0,0,10}, {0,10,0}, {10,0,0},
	{0,0,10}, {0,10,0}, {10,0,0},
	{0,0,10}, {0,10,0}, {10,0,0},
	{0,0,10}, {0,10,0}, {10,0,0},
	{0,0,10}, {0,10,0}, {10,0,0},
 };

rgb Green = {40, 0, 0};
rgb Red	  = {0, 40, 0};
rgb Blue  = {0, 0, 40};
	
int main(void)
{
	memset(buffer, 0, sizeof(uint8_t) * 60 * 3);

	DDRB = _BV(3);
	
	RingSet rings(buffer, 15);
	Chaser chasers[3] = {
		Chaser(0, 0, Red),
		Chaser(2, 0, Green),
		Chaser(3, 0, Blue)
	};
	ChasePattern chasePattern(&rings, chasers, 3);
	
    while(1)
    {
		_delay_ms(20);

		chasePattern.Update();

		// Update the display
		send( buffer, 60, 3);
    }
}