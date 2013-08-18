#ifndef CHASERS_H
#define CHASERS_H

#include "rings.h"

class Chaser
{
public:
	Chaser(uint8_t ring, uint8_t element, bool clockwise, rgb colour);

	uint8_t Ring;
	uint8_t Element;
	rgb Colour;
	bool Clockwise;
};

struct Junction
{
	Junction(uint8_t fromR, uint8_t fromE, uint8_t toR, uint8_t toE);

	uint8_t FromRing;
	uint8_t FromElem;

	uint8_t ToRing;
	uint8_t ToElem;
};

class ChasePattern
{
public:
	ChasePattern(RingSet* rings, Chaser* chasers, uint8_t chaserCount);
	
	void Logic();
	void Render();

	void SetJunctions(Junction* junction, uint8_t junctionCount);

private:
	RingSet *_rings;
	Chaser *_chasers;
	uint8_t _chaserCount;

	Junction *_junctions;
	uint8_t _juncCount;
};

#endif