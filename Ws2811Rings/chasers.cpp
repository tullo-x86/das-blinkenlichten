#include "chasers.h"

Chaser::Chaser(uint8_t ring, uint8_t element, rgb colour) {
	Ring = ring;
	Element = element;
	Colour = colour;
	Clockwise = false;
}

ChasePattern::ChasePattern(RingSet* rings, Chaser* chasers, uint8_t chaserCount) {
	_rings = rings;
	_chasers = chasers;
	_chaserCount = chaserCount;
}

void ChasePattern::Logic() {
	for (int i = 0; i < _chaserCount; i++)
	{
		Chaser* chaser = _chasers + i;
		
		int d = chaser->Clockwise ? 1 : -1;
		chaser->Element = (chaser->Element + d) % 15;

		_rings->SetElement(chaser->Ring, chaser->Element, chaser->Colour);
	}
}

void ChasePattern::Render() 
{
	_rings->FadeAll();
	
	for (int i = 0; i < _chaserCount; i++)
	{
		Chaser* chaser = _chasers + i;

		_rings->SetElement(chaser->Ring, chaser->Element, chaser->Colour);
	}
}