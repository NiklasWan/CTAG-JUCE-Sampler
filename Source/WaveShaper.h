/**
	A tanh waveshaper.

	@author Niklas Wantrupp
	@version v1.0 11/09/2018
*/

#pragma once
#include <cmath>

class WaveShaper
{
private:
	double ampFactorPositive, ampFactorNegative;
	bool activeState;
public:
	WaveShaper();

	/**
	 
		Sets the positive amplification for the Shaper.	
	*/

	void setPositiveAmplification(double ampFactorPositive);


	/**

		Sets the negative amplification for the Shaper.
	*/

	void setNegativeAmplification(double ampFactorNegative);

	/**

		When used as a symmetrical Shaper this returns the amplification Factor.
	*/


	double getSymmetrical() { return ampFactorNegative; }

	/**

		Cecks whether the processor is active or inactive.
	*/

	bool isActive() { return activeState; }

	/**

		Sets whether the processor is active or inactive.
	*/

	void setActive(bool activeState) { this->activeState = activeState; }

	/**

		When used as a symmetrical Shaper this sets the amplification Factor.
	*/

	void setAmplificationSymmetrical(double ampFactorSymmetrical);

	/**

		Processes the Sample passed to the function.
	*/


	inline double processSample(double xn)
	{
		if (!isActive()) return xn;
		double yn = 0.0f;
		if (xn >= 0)
			yn = std::tanh(xn * ampFactorPositive) / std::tanh(ampFactorNegative);
		else
			yn = std::tanh(xn * ampFactorNegative) / std::tanh(ampFactorNegative);

		return yn;
	}
};