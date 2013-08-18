#include "chasers.h"

Chaser::Chaser(uint8_t ring, uint8_t element, bool clockwise, rgb *colour_ptr) {
	Ring = ring;
	Element = element;
	Colour = colour_ptr;
	Clockwise = clockwise;
}

ChasePattern::ChasePattern(RingSet* rings, Chaser* chasers, uint8_t chaserCount) {
	_rings = rings;
	_chasers = chasers;
	_chaserCount = chaserCount;
	_juncCount = 0;
}

void ChasePattern::Logic() {
	for (int i = 0; i < _chaserCount; i++)
	{
		Chaser* chaser = _chasers + i;

		bool jumped = false;
		for (int i = 0; i < _juncCount; i++) {
			Junction *junc = _junctions + i;
            if (junc->FromRing == chaser->Ring
                && junc->FromElem == chaser->Element) {
                // Jump!
				chaser->Ring = junc->ToRing;
				chaser->Element = junc->ToElem;
                chaser->Clockwise = !chaser->Clockwise;
				jumped = true;
                break;
            }
        }
		
		if (!jumped)
		{                
			if (chaser->Clockwise) {
                if (chaser->Element == 0) {
                    chaser->Element = _rings->RingSize - 1;
                }
				else
				{
					chaser->Element--;
				}
            }
            else {
                chaser->Element++;
                if (chaser->Element >= _rings->RingSize) {
                    chaser->Element = 0;
                }
            }
		}
	}
}

void ChasePattern::Render() 
{
	for (int i = 0; i < _chaserCount; i++)
	{
		Chaser* chaser = _chasers + i;

		_rings->SetElement(chaser->Ring, chaser->Element, *(chaser->Colour));
	}
}

void ChasePattern::SetJunctions(Junction* junctions, uint8_t junctionCount) {
	_junctions = junctions;
	_juncCount= junctionCount;
}

Junction::Junction(uint8_t fromR, uint8_t fromE, uint8_t toR, uint8_t toE) {
	FromRing = fromR;
	FromElem= fromE;
	ToRing = toR;
	ToElem = toE;
}
