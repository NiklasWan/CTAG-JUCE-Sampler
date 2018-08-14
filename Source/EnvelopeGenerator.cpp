#include "EnvelopeGenerator.h"
#include <cmath>

CEnvelopeGenerator::CEnvelopeGenerator(void)
{
	// defaults
	m_dSampleRate = 48000;
	m_dAttackTime_mSec = 500;
	m_dDecayTime_mSec = 0;
	m_dReleaseTime_mSec = 1000;
	m_dSustainLevel = 1.0;
	m_dEnvelopeOutput = 0.0;
	m_dIncShutdown = 0.0;

	// --- user normally not allowed to set the time
	m_dShutdownTime_mSec = 10.0; // mSec

								 // --- states and flags
	m_uState = off;
	m_bOutputEG = true;
	m_uEGMode = digital;
	setEGMode(m_uEGMode);
	m_bResetToZero = true;
	m_bLegatoMode = false;
}

CEnvelopeGenerator::~CEnvelopeGenerator(void)
{
}

void CEnvelopeGenerator::setEGMode(int u)
{
	// --- save it
	m_uEGMode = u;

	// --- analog - use e^-1.5x, e^-4.95x
	if (m_uEGMode == analog)
	{
		m_dAttackTCO = exp(-1.5);  // fast attack
		m_dDecayTCO = exp(-4.95);
		m_dReleaseTCO = m_dDecayTCO;
	}
	else
	{
		// digital is linear-in-dB so use
		m_dAttackTCO = 0.99999;
		m_dDecayTCO = m_dDecayTCO = exp(-11.05);
		m_dReleaseTCO = m_dDecayTCO;
	}

	// --- recalc these
	calculateAttackTime();
	calculateDecayTime();
	calculateReleaseTime();
}

// reset
void CEnvelopeGenerator::reset()
{
	// --- state
	m_uState = off;

	// --- reset 
	setEGMode(m_uEGMode);

	// --- may be modified in noteOff()
	calculateReleaseTime();

	// --- if reset to zero, clear
	//     else let it stay frozen
	if (m_bResetToZero)
	{
		m_dEnvelopeOutput = 0.0;
	}
}

void CEnvelopeGenerator::calculateAttackTime()
{
	// --- samples for the exponential rate
	double dSamples = m_dSampleRate * ((m_dAttackTime_mSec) / 1000.0);

	// --- coeff and base for iterative exponential calculation
	m_dAttackCoeff = exp(-log((1.0 + m_dAttackTCO) / m_dAttackTCO) / dSamples);
	m_dAttackOffset = (1.0 + m_dAttackTCO)*(1.0 - m_dAttackCoeff);
}

// --- changes to the decay rate OR the sustain level require
//     an update in analog mode
void CEnvelopeGenerator::calculateDecayTime()
{
	// --- samples for the exponential rate
	double dSamples = m_dSampleRate * ((m_dDecayTime_mSec) / 1000.0);

	// --- coeff and base for iterative exponential calculation
	m_dDecayCoeff = exp(-log((1.0 + m_dDecayTCO) / m_dDecayTCO) / dSamples);
	m_dDecayOffset = (m_dSustainLevel - m_dDecayTCO)*(1.0 - m_dDecayCoeff);
}

void CEnvelopeGenerator::calculateReleaseTime()
{
	// --- samples for the exponential rate
	double dSamples = m_dSampleRate * (m_dReleaseTime_mSec / 1000.0);

	// --- coeff and base for iterative exponential calculation
	m_dReleaseCoeff = exp(-log((1.0 + m_dReleaseTCO) / m_dReleaseTCO) / dSamples);
	m_dReleaseOffset = -m_dReleaseTCO * (1.0 - m_dReleaseCoeff);
}

// --- go to release state; reset 
void CEnvelopeGenerator::noteOff()
{
	// --- go directly to release state
	if (m_dEnvelopeOutput > 0)
		m_uState = release;
	else // sustain was already at zero
		m_uState = off;
}

// --- goto shutdown state
void CEnvelopeGenerator::shutDown()
{
	// --- legato mode - ignore
	if (m_bLegatoMode)
		return;

	// --- calculate the linear inc values based on current outputs
	m_dIncShutdown = -(1000.0*m_dEnvelopeOutput) / m_dShutdownTime_mSec / m_dSampleRate;

	// --- set state and reset counter
	m_uState = shutdown;
}

