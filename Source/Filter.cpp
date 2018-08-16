#include "Filter.h"

// --- construction
CFilter::CFilter()
{
	// --- defaults
	m_dSampleRate = 48000;
	m_dQControl = 1.0; // Q is 1 to 10 on GUI
	m_dFc = FILTER_FC_DEFAULT;
	m_dQ = FILTER_Q_DEFAULT;
	m_dFcControl = FILTER_FC_DEFAULT;

	// --- clear
	m_dFcMod = 0.0;
	m_dAuxControl = 0.0;
	m_uNLP = OFF;
	m_dSaturation = 1.0;
	activity = false;
}




// --- flush buffers
void CFilter::reset()
{
	// do nothing
}

// --- optional depending on filter type
void CFilter::setQControl(double dQControl)
{
	// do nothing
}
