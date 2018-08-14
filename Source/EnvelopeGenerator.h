#pragma once


#define EG_DEFAULT_STATE_TIME 1000 // 1000 mSec

class CEnvelopeGenerator
{
public:
	CEnvelopeGenerator(void);
	~CEnvelopeGenerator(void);

	// --- analog and digital mode
	int m_uEGMode;
	enum { analog, digital };

	// --- special modes
	bool m_bResetToZero; // return to zero
	bool m_bLegatoMode;  // S-trigger
	bool m_bOutputEG;	 // true if this EG is being used to control the DCA output

protected:
	double m_dSampleRate;

	// --- current output
	double m_dEnvelopeOutput;

	//--- Coefficient, offset and TCO values
	//    for each state
	double m_dAttackCoeff;
	double m_dAttackOffset;
	double m_dAttackTCO;

	double m_dDecayCoeff;
	double m_dDecayOffset;
	double m_dDecayTCO;

	double m_dReleaseCoeff;
	double m_dReleaseOffset;
	double m_dReleaseTCO;

	//--- ADSR times from user
	double m_dAttackTime_mSec;	// att: is a time duration
	double m_dDecayTime_mSec;	// dcy: is a time to decay 1->0
	double m_dReleaseTime_mSec;	// rel: is a time to decay 1->0

								// --- this is set internally; user normally not allowed to adjust
	double m_dShutdownTime_mSec; // shutdown is a time

								 // --- sustain is a level, not a time
	double m_dSustainLevel;

	// --- inc value for shutdown
	double m_dIncShutdown;

	// --- stage variable
	int m_uState;
	enum { off, attack, decay, sustain, release, shutdown };

public:

	double getAttackTime() { return m_dAttackTime_mSec; }
	double getDecayTime() { return m_dDecayTime_mSec; }
	double getSustainValue() { return m_dSustainLevel; }
	double getReleaseTime() { return m_dReleaseTime_mSec; }
	// --- accessors - allow owner to get our state
	inline int getState() { return m_uState; }

	// --- is the EG active
	inline bool isActive()
	{
		if (m_uState != release && m_uState != off)
			return true;
		return false;
	}

	// --- can do note off now?
	inline bool canNoteOff()
	{
		if (m_uState != release && m_uState != shutdown && m_uState != off)
			return true;
		return false;
	}

	// --- reset
	void reset();

	// --- function to set the time constants
	void setEGMode(int u);

	// --- calculate time params
	void calculateAttackTime();
	void calculateDecayTime();
	void calculateReleaseTime();

	// --- go to release state; reset counter
	void noteOff();

	// --- go to shutdown state
	void shutDown();

	// --- mutators
	//	inline void setState(UINT u){m_uState = u;}
	inline void setSampleRate(double d) { m_dSampleRate = d; }

	// --- called during updates
	inline void setAttackTime_mSec(double d)
	{
		m_dAttackTime_mSec = d;
		calculateAttackTime();
	}
	inline void setDecayTime_mSec(double d)
	{
		m_dDecayTime_mSec = d;
		calculateDecayTime();
	}
	inline void setReleaseTime_mSec(double d)
	{
		m_dReleaseTime_mSec = d;
		calculateReleaseTime();
	}
	// --- sustain is a level not a time
	inline void setSustainLevel(double d)
	{
		m_dSustainLevel = d;

		// --- sustain level affects decay
		calculateDecayTime();

		// --- and release, if not in release state
		if (m_uState != release)
			calculateReleaseTime();
	}

	// reset and go to attack state
	inline void startEG()
	{
		// --- ignore
		if (m_bLegatoMode && m_uState != off && m_uState != release)
			return;

		// --- reset and go
		reset();
		m_uState = attack;
	}

	// --- go to off state
	inline void stopEG()
	{
		m_uState = off;
	}

	// --- update params
	inline void update()
	{
		// nothing yet
	}

	/* do the envelope
	returns normal Envelope out
	optionally, can get biased output in argument
	*/
	inline double doEnvelope(double* pBiasedOutput = nullptr)
	{
		// --- decode the state
		switch (m_uState)
		{
		case off:
		{
			// --- output is OFF
			if (m_bResetToZero)
				m_dEnvelopeOutput = 0.0;
			break;
		}
		case attack:
		{
			// --- render value
			m_dEnvelopeOutput = m_dAttackOffset + m_dEnvelopeOutput * m_dAttackCoeff;

			// --- check go to next state
			if (m_dEnvelopeOutput >= 1.0 || m_dAttackTime_mSec <= 0.0)
			{
				m_dEnvelopeOutput = 1.0;
				m_uState = decay;	// go to next state
				break;
			}
			break;
		}
		case decay:
		{
			// --- render value
			m_dEnvelopeOutput = m_dDecayOffset + m_dEnvelopeOutput * m_dDecayCoeff;

			// --- check go to next state
			if (m_dEnvelopeOutput <= m_dSustainLevel || m_dDecayTime_mSec <= 0.0)
			{
				m_dEnvelopeOutput = m_dSustainLevel;
				m_uState = sustain;		// go to next state
				break;
			}
			break;
		}
		case sustain:
		{
			// --- render value
			m_dEnvelopeOutput = m_dSustainLevel;
			break;
		}
		case release:
		{
			// --- render value
			m_dEnvelopeOutput = m_dReleaseOffset + m_dEnvelopeOutput * m_dReleaseCoeff;

			// --- check go to next state
			if (m_dEnvelopeOutput <= 0.0 || m_dReleaseTime_mSec <= 0.0)
			{
				m_dEnvelopeOutput = 0.0;
				m_uState = off;		// go to next state
				break;
			}
			break;
		}
		case shutdown:
		{
			if (m_bResetToZero)
			{
				// --- the shutdown state is just a linear taper since it is so short
				m_dEnvelopeOutput += m_dIncShutdown;

				// --- check go to next state
				if (m_dEnvelopeOutput <= 0)
				{
					m_uState = off;		// go to next state
					m_dEnvelopeOutput = 0.0; // reset envelope
					break;
				}
			}
			else
			{
				// --- we are guaranteed to be retriggered
				//     just go to off state
				m_uState = off;
			}
			break;
		}
		}

		// --- set the biased (pitchEG) output if there is one
		if (pBiasedOutput)
			*pBiasedOutput = m_dEnvelopeOutput - m_dSustainLevel;

		// --- set the normal
		return m_dEnvelopeOutput;
	}

};