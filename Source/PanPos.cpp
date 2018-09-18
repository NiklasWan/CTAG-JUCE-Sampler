#include "PanPos.h"




void PanPos::setPosition(float _position)
{
	position = _position * piovr2;
	angle = position * 0.5;
}

float PanPos::processLeftChannel(float leftChannel)
{
	leftChannel *= root2ovr2 * (cos(angle) - sin(angle));
	return leftChannel;
}

float PanPos::processRightChannel(float rightChannel)
{
	rightChannel *= root2ovr2 * (cos(angle) + sin(angle));
	return rightChannel;
}