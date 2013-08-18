#include "rings.h"

RingSet::RingSet(rgb *buffer, uint8_t ringSize) {
	_rgbBuffer = buffer;
	_ringSize = ringSize;
}

void RingSet::SetElement(uint8_t ring, uint8_t element, rgb colour) {
	const uint8_t index = (ring * _ringSize) + element;
	_rgbBuffer[index] = colour;
}

void RingSet::FadeAll() {
	for (int i = 0; i < _ringSize * 4; ++i)
	{
		_rgbBuffer[i].red = _rgbBuffer[i].red >> 1;
		_rgbBuffer[i].green = _rgbBuffer[i].green >> 1;
		_rgbBuffer[i].blue = _rgbBuffer[i].blue >> 1;
	}
}