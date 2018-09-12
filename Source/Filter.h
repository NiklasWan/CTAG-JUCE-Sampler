/**
	Describes the abstract Base Class for all Filters.
	You have to extend this class if you want to write your own Implementation.

	Implemented by Example of a Filter from Will Pirkle
	(http://www.willpirkle.com/)

	@author Niklas Wantrupp
	@version v1.0 11/09/2018
*/

#pragma once

#include <cmath>
#define PI 3.14159265358979323846264338327950288



#define FILTER_FC_MOD_RANGE 46.881879936465680	
#define FILTER_FC_MIN 80		// 80Hz
#define FILTER_FC_MAX 18000		// 18kHz
#define FILTER_FC_DEFAULT 18000	// 10kHz
#define FILTER_Q_DEFAULT 0.707	// Butterworth


class Filter
{
public:
	Filter(void);

	/**

		The frequency cutoff position.
	*/

	double cutoffControl;

	/**

		The resonance control position.
	*/
	double resonanceControl;


	/**

		The differentfilter types you can choose.
	*/

	enum { LPF1, HPF1, LPF2, HPF2, BPF2, BSF2, LPF4, HPF4, BPF4 };

	/**
		The selected filter type.
	*/
	int filterType;

protected:
	/**

		The given sample rate of the audio processor.
	*/

	double sampleRate;

	/**

		Actual cutoff used for calculation.
	*/

	double cutoffValue;

	/**

		The actual resonance value used for calculation.
	*/

	double resonanceValue;

	/**

		Describes whether the filter is active or not.
	*/

	bool activeState;

	//double cutoffModulation;

public:

	/**

		Check whether the filter is active or not.
	*/

	bool isActive() { return activeState; }

	/**
		Set whether the filter is active or not.

	*/

	void setActive(bool activeState) { this->activeState = activeState; }

	double getCutofff() { return cutoffValue; }

	/**

		The derived class has to implement doFilter().
		This is where all the calculations happen.
	*/

	virtual double doFilter(double xn) = 0;

	/**

		Set the sample rate of the filter.
	*/

	inline void setSampleRate(double sampleRate) { this->sampleRate = sampleRate; }

	/**

			Flush buffers and reset the Filter.
	*/

	virtual void reset();

	/**

		Set resonance Value.
		This can change from filter to filter.
	*/

	virtual void setQControl(double resonanceControl);

	/**

		Recalculate the cutoffValue.
	*/

	inline virtual void update()
	{
		/**

			Update the resonance Control.
		*/

		setQControl(resonanceControl);

		cutoffValue = cutoffControl;

		/**

			Check if the Value is in the allowed range.
		*/
		if (cutoffValue > FILTER_FC_MAX)
			cutoffValue = FILTER_FC_MAX;
		if (cutoffValue < FILTER_FC_MIN)
			cutoffValue = FILTER_FC_MIN;
	}

	inline double pitchShiftMultiplier(double dPitchShiftSemitones)
	{
		if (dPitchShiftSemitones == 0)
			return 1.0;

		// 2^(N/12)
		//	return fastPow(2.0, dPitchShiftSemitones/12.0);
		return std::pow(2.0, dPitchShiftSemitones / 12.0);
	}
};
