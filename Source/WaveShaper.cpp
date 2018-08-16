/*
  ==============================================================================

    WaveShaper.cpp
    Created: 14 Aug 2018 2:00:57pm
    Author:  nikla

  ==============================================================================
*/

#include "WaveShaper.h"
WaveShaper::WaveShaper()
{
	ampFactorPositive = ampFactorNegative = 0.2f;
	activity = false;
}

void WaveShaper::setPositiveAmplification(double amp)
{
	if (amp < 0.2f)
		ampFactorPositive = 0.2f;
	if (amp > 5.0f)
		ampFactorPositive = 5.0f;
	else
		ampFactorPositive = amp;
}

void WaveShaper::setNegativeAmplification(double amp)
{
	if (amp < 0.2f)
		ampFactorNegative = 0.2f;
	if (amp > 5.0f)
		ampFactorNegative = 5.0f;
	else
		ampFactorNegative = amp;
}

void WaveShaper::setAmplificationSymmetrical(double amp)
{
	setPositiveAmplification(amp);
	setNegativeAmplification(amp);
}



