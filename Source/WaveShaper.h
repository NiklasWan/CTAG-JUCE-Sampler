/*
  ==============================================================================

    WaveShaper.h
    Created: 14 Aug 2018 2:00:57pm
    Author:  nikla

  ==============================================================================
*/

#pragma once
#include <cmath>

class WaveShaper
{
private:
	double ampFactorPositive, ampFactorNegative;
	bool isActive;
public:
	WaveShaper();
	void setPositiveAmplification(double amp);
	void setNegativeAmplification(double amp);
	void setActive(bool active) { isActive = active; }
	void setAmplificationSymmetrical(double amp);
	inline double processSample(double xn)
	{
		if (!isActive) return xn;
		double yn = 0.0f;
		if (xn >= 0)
			yn = std::tanh(xn * ampFactorPositive) / std::tanh(ampFactorNegative);
		else
			yn = std::tanh(xn * ampFactorNegative) / std::tanh(ampFactorNegative);

		return yn;
	}
};