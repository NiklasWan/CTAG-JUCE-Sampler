/**
	A standard const power pan pot. set position with setPosition() from -1 (left) to 1 (right). processLeft/RigtPan takes a variable sample of your buffer and returns the panned value.



	@author Niklas Wantrupp
	@version v1.0 18/09/2018
*/

#pragma once
#include <cmath>
#include "Filter.h"
#include "../JuceLibraryCode/JuceHeader.h"


class PanPos
{
	float position;
	
	float angle;
	const float piovr2;
	const float root2ovr2;

public:
	PanPos() : piovr2(PI * 0.5), root2ovr2(sqrt(2.0) * 0.5) { setPosition(0.0); }
	float getPosition() { return position; }
	void setPosition(float _position);


	float processLeftChannel(float leftChannel);


	float processRightChannel(float rightChannel);


};
