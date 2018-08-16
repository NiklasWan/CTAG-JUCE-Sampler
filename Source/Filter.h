#pragma once

#include <cmath>
#define PI 3.14159265358979323846264338327950288


// 46.881879936465680 semitones = semitonesBetweenFrequencies(80, 18000.0)/2.0
#define FILTER_FC_MOD_RANGE 46.881879936465680	
#define FILTER_FC_MIN 80		// 80Hz
#define FILTER_FC_MAX 18000		// 18kHz
#define FILTER_FC_DEFAULT 18000	// 10kHz
#define FILTER_Q_DEFAULT 0.707	// Butterworth

// CFilter Abastract Base Class for all filters
class CFilter
{
public:
	CFilter(void);
	

	// --- ATTRIBUTES
	// --- PUBLIC: these variables may be get/set 
	//             you may make get/set functions for them 
	//             if you like, but will add function call layer

	// --- the user's cutoff frequency control position
	double m_dFcControl;

	// --- the user's cutoff frequency control position
	double m_dQControl;

	// --- for an aux filter specific like SEM BSF 
	//     control or paasband gain comp (Moog)
	double m_dAuxControl;

	// --- for NLP - Non Linear Procssing
	int m_uNLP;
	enum { OFF, ON };  // switch enum

					   // --- to add more distortion
	double m_dSaturation;

	// --- NOTE: these are shared; even though some filters won't use some of them
	//           need to maintain the indexing
	enum { LPF1, HPF1, LPF2, HPF2, BPF2, BSF2, LPF4, HPF4, BPF4 };

	// --- our selected filter type
	int m_uFilterType;

protected:
	// --- PROTECTED: generally these are either basic calc variables
	//                and modulation stuff
	//
	double m_dSampleRate;	// fs

							// --- the actual cutoff used in the calculation
	double m_dFc;

	// --- the current value of Q (internal)
	double m_dQ;

	// --- our cutoff frequency modulation input
	double m_dFcMod;
	bool activity;
	// --- add more mods here

public:

	bool isActive() { return activity; }
	void setActive(bool val) { activity = val; }
	// --- FUNCTIONS: all public
	//	
	inline void setFcMod(double d) { m_dFcMod = d; }

	// --- VIRTUAL FUNCTIONS ----------------------------------------- //
	//
	// --- PURE ABSTRACT: derived class MUST implement
	virtual double doFilter(double xn) = 0;

	// --- ABSTRACT: derived class overrides if needed
	//
	inline virtual void setSampleRate(double d) { m_dSampleRate = d; }

	// --- flush buffers, reset filter
	virtual void reset();

	// --- decode the Q value; this can change from filter to filter
	virtual void setQControl(double dQControl);

	// --- recalculate the Fc (called after modulations)
	inline virtual void update()
	{
		// --- update Q (filter-dependent)
		setQControl(m_dQControl);

		// --- do the modulation freq shift
		m_dFc = m_dFcControl * pitchShiftMultiplier(m_dFcMod);

		// --- bound the final frequency
		if (m_dFc > FILTER_FC_MAX)
			m_dFc = FILTER_FC_MAX;
		if (m_dFc < FILTER_FC_MIN)
			m_dFc = FILTER_FC_MIN;
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
