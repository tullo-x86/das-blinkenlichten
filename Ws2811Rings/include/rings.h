#ifndef RINGS_H
#define RINGS_H

#include "ws2811_8.h"

class RingSet
{
public:
	RingSet(rgb *buffer, uint8_t ringSize);

	void SetElement(uint8_t ring, uint8_t element, rgb colour);
	void FadeAll();
	void ClearAll();

	uint8_t RingSize;

private:
	rgb *_rgbBuffer;
};

#endif