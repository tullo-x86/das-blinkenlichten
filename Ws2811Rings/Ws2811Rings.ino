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
	{0,0,40}, {0,02,0}, {02,0,0},
	{0,0,02}, {0,02,0}, {02,0,0},
	{0,0,02}, {0,02,0}, {02,0,0},
	{0,0,02}, {0,02,0}, {02,0,0},
	{0,0,02}, {0,02,0}, {02,0,0},

	{40,40,0}, {0,02,0}, {02,0,0},
	{0,0,02}, {0,02,0}, {02,0,0},
	{0,0,02}, {0,02,0}, {02,0,0},
	{0,0,02}, {0,02,0}, {02,0,0},
	{0,0,02}, {0,02,0}, {02,0,0},

	{0,0,02}, {0,40,0}, {02,0,0},
	{0,0,02}, {0,02,0}, {02,0,0},
	{0,0,02}, {0,02,0}, {02,0,0},
	{0,0,02}, {0,02,0}, {02,0,0},
	{0,0,02}, {0,02,0}, {02,0,0},

	{0,0,02}, {0,02,0}, {40,0,0},
	{0,0,02}, {0,02,0}, {02,0,0},
	{0,0,02}, {0,02,0}, {02,0,0},
	{0,0,02}, {0,02,0}, {02,0,0},
	{0,0,02}, {0,02,0}, {02,02,02},
 };

const uint8_t br = 22;
rgb Green = {br, 0, 0};
rgb Yellow= {br,br, 0};
rgb Red	  = { 0,br, 0};
rgb Blue  = { 0, 0,br};

rgb chaser1Colour = {br,0, 0};

int main(void)
{
	memset(buffer, 0, sizeof(uint8_t) * 180);

	DDRB = _BV(3);
	
	RingSet rings(buffer, 15);
	const uint8_t chaserCount = 3;
	Chaser chasers[chaserCount] = {
		Chaser(0, 0, true, &chaser1Colour),
		//Chaser(1, 0, false, Yellow),
		Chaser(2,12, true, &Red),
		Chaser(3, 3, true, &Blue)
	};

	ChasePattern chasePattern(&rings, chasers, chaserCount);

	// Junctions:
	// 0,0 touches 1,0
	// 1,5 touches 3,13
	// 1,10 touches 2,2

	const int juncCount = 6;
	Junction junctions[juncCount] =
	{		
		Junction( 0, 0,  1, 1 ),
		Junction( 1, 0,  0,14 ),

		Junction( 1, 5,  3,12 ),
		Junction( 3,13,  1, 6 ),

		Junction( 1,10,  2, 1 ),
		Junction( 2, 2,  1,11 )
	};

	chasePattern.SetJunctions(junctions, juncCount);
	
	bool trigger=false;
	while(1)
    {
		chaser1Colour.blue = (trigger = !trigger) ? br : 0;	
		chaser1Colour.blue = (trigger) ? 0 : br;		 

		chasePattern.Logic();
		chasePattern.Render();

		_delay_ms(100);

		// Update the display twice, because sending once seems to miss the first pixel
		// and I dno't have time to figure out why.
		send( buffer, 60, 3);
		send( buffer, 60, 3);
    }
}