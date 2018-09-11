#include "WaveShaper.h"



WaveShaper::WaveShaper()
{
	ampFactorPositive = ampFactorNegative = 0.2f;
	activeState = false;
}

void WaveShaper::setPositiveAmplification(double ampFactorPositive)
{

	/**
	
		Only values between 0.2 and 5.0 are allowed.
	*/

	if (ampFactorPositive < 0.2f)
		this->ampFactorPositive = 0.2f;
	if (ampFactorPositive > 5.0f)
		this->ampFactorPositive = 5.0f;
	else
		this->ampFactorPositive = ampFactorPositive;
}

void WaveShaper::setNegativeAmplification(double ampFactorNegative)
{
	if (ampFactorNegative < 0.2f)
		this->ampFactorNegative = 0.2f;
	if (ampFactorNegative > 5.0f)
		this->ampFactorNegative = 5.0f;
	else
		this->ampFactorNegative = ampFactorNegative;
}

void WaveShaper::setAmplificationSymmetrical(double ampFactorSymmetrical)
{
	setPositiveAmplification(ampFactorSymmetrical);
	setNegativeAmplification(ampFactorSymmetrical);
}



