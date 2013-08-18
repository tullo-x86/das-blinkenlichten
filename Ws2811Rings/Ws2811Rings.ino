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

rgb Green = {20, 0, 0};
rgb Yellow= {10,10, 0};
rgb Red	  = { 0,10, 0};
rgb Blue  = { 0, 0,05};
	
int main(void)
{
	memset(buffer, 0, sizeof(uint8_t) * 60 * 3);

	DDRB = _BV(3);
	
	RingSet rings(buffer, 15);
	Chaser chasers[4] = {
		Chaser(0, 0, Green),
		Chaser(1, 0, Yellow),
		Chaser(2, 0, Red),
		Chaser(3, 0, Blue)
	};
	chasers[1].Clockwise = true;
	ChasePattern chasePattern(&rings, chasers, 4);

	// Junctions:
	// 0,0 touches 1,0
	// 1,5 touches 3,13
	// 1,10 touches 2,2

    while(1)
    {
		_delay_ms(40);

		chasePattern.Logic();
		chasePattern.Render();

		// Update the display
		send( buffer, 60, 3);
    }
}