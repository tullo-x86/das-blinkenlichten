#ifndef RINGS_H
#define RINGS_H

#if F_CPU==16000000UL
#include "../include/ws2811.h"
typedef RGB_t rgb;
#elif F_CPU==8000000UL
#include "../include/ws2811_8.h"
#endif

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
