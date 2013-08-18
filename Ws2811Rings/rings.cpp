#include "rings.h"

RingSet::RingSet(rgb *buffer, uint8_t ringSize) {
	_rgbBuffer = buffer;
	RingSize = ringSize;
}

void RingSet::SetElement(uint8_t ring, uint8_t element, rgb colour) {

	const uint8_t index = (ring * RingSize) + element;
	_rgbBuffer[index] = colour;
}

void RingSet::FadeAll() {
	for (int i = 0; i < RingSize * 4; ++i)
	{
		_rgbBuffer[i].red = _rgbBuffer[i].red >> 1;
		_rgbBuffer[i].green = _rgbBuffer[i].green >> 1;
		_rgbBuffer[i].blue = _rgbBuffer[i].blue >> 1;
	}
}

void RingSet::ClearAll() {
	for (int i = 0; i < RingSize * 4; ++i)
	{
		_rgbBuffer[i].red = 0;
		_rgbBuffer[i].green = 0;
		_rgbBuffer[i].blue = 0;
	}
}