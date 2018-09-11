#include "Filter.h"


Filter::Filter()
{
	/**
		Instantiate the filter with standard values.
	*/

	sampleRate = 48000;
	resonanceControl = 1.0; // Q is 1 to 10 on GUI
	cutoffValue = FILTER_FC_DEFAULT;
	resonanceValue = FILTER_Q_DEFAULT;
	cutoffControl = FILTER_FC_DEFAULT;
	activeState = false;
}

void Filter::reset()
{
	
}

void Filter::setQControl(double resonanceControl)
{
	
}
