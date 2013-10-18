/*
 * Ws2811Rings.c
 *
 * Created: 16/08/2013 6:52:11 PM
 *  Author: mccubbinaj
 */ 

#define F_CPU 8000000UL  // 8 MHz

#include <util/delay.h>

#include <avr/io.h>
#include <string.h>
#include "../include/ws2811_8.h"
#include "../include/chasers.h"

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
rgb chaser2Colour = {0,br, 0};

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

RingSet rings(buffer, 15);
const uint8_t chaserCount = 2;
Chaser chasers[chaserCount] = {
	Chaser(0, 0, true, &chaser1Colour),
	Chaser(1, 0, false, &chaser2Colour),
	/*Chaser(2,12, true, &Red),
	Chaser(3, 3, true, &Blue)*/
};

ChasePattern chasePattern(&rings, chasers, chaserCount);


const int phaseLength = 4;
const int period = phaseLength * 6;

void interpolateRgb(rgb &c, int iteration, int phaseLength);
int main(void)
{
	DDRB = _BV(3);
	memset(buffer, 0, sizeof(uint8_t) * 180);

	chasePattern.SetJunctions(junctions, juncCount);
	
	int iter = 0;
	int iter2 = 30;
	while(1)
    {		
		iter = ++iter % period;
		iter2 = ++iter2 % period;

		interpolateRgb(chaser1Colour, iter, phaseLength);
		interpolateRgb(chaser2Colour, iter2, phaseLength);

		chasePattern.Logic();
		rings.FadeAll();
		chasePattern.Render();

		_delay_ms(30);

		// Update the display twice, because sending once seems to miss the first pixel
		// and I dno't have time to figure out why.
		send( buffer, 60, 3);
		send( buffer, 60, 3);
    }
}

void interpolateRgb(rgb &c, int iteration, int phaseLength) {
	// Determine which phase we are in
	int phase = iteration / phaseLength;
	int step = iteration % phaseLength;
		
	switch(phase)
	{
		case 0: // Red on, green increasing, blue off
		c.red   = 1 << phaseLength;
		c.green = 1 << step;
		c.blue  = 0;
		break;
		
		case 1: // Red decreasing, green on, blue off
		c.red   = (1 << phaseLength) >> (step);
		c.green = 1 << phaseLength;
		c.blue  = 0;
		break;
		
		case 2: // Red off, green on, blue increasing
		c.red   = 0;
		c.green = 1 << phaseLength;
		c.blue  = 1 << step;
		break;
		
		case 3: // Red off, green decreasing, blue on
		c.red   = 0;
		c.green = (1 << phaseLength) >> (step);
		c.blue  = 1 << phaseLength;
		break;
		
		case 4: // Red increasing, green off, blue on
		c.red   = 1 << step;
		c.green = 0;
		c.blue  = 1 << phaseLength;
		break;
		
		case 5: // Red on, green off, blue decreasing
		c.red   = 1 << phaseLength;
		c.green = 0;
		c.blue  = (1 << phaseLength) >> (step);
		break;
	}
}
