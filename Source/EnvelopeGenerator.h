/**
	Implementation of an envelope generator.


	Based on an Implementation by Will Pirkle
	(http://www.willpirkle.com/)

	@author Niklas Wantrupp
	@version v1.0 11/09/2018
*/


#pragma once

#include <cmath>
#define EG_DEFAULT_STATE_TIME 1000 


class EnvelopeGenerator
{
public:
	EnvelopeGenerator(void);



	int envelopeMode;
	enum { analog, digital };


	bool resetToZeroMode;
	bool legatoMode;
	bool isControllingDCA;

protected:
	double sampleRate;


	double envelopeOutput;


	double attackCoeff;
	double attackOffset;
	double attackTCO;

	double decayCoeff;
	double decayOffset;
	double decayTCO;

	double releaseCoeff;
	double releaseOffset;
	double releaseTCO;


	double attackTime;
	double decayTime;
	double releaseTime;


	double shutdownTime;


	double sustainLevel;


	double incValueShutdown;


	int envelopeState;
	enum { off, attack, decay, sustain, release, shutdown };

public:

	/**

		Returns attack time in ms of the envelope.
	*/

	double getAttackTime() { return attackTime; }

	/**

		Returns decay time in ms of the envelope.
	*/

	double getDecayTime() { return decayTime; }

	/**

		Returns sustain level of the envelope.
	*/

	double getSustainValue() { return sustainLevel; }

	/**

		Returns release time in ms of the envelope.
	*/

	double getReleaseTime() { return releaseTime; }


	/**

		Returns state of the envelope.
	*/

	inline int getState() { return envelopeState; }

	/**

		Returns whether the envelope is active or inactive.
	*/

	inline bool isActive()
	{
		if (envelopeState != release && envelopeState != off)
			return true;
		return false;
	}

	/**

		Checks whether noteOff() can be used.
	*/

	inline bool canNoteOff()
	{
		if (envelopeState != release && envelopeState != shutdown && envelopeState != off)
			return true;
		return false;
	}

	/**

		Resets the envelope.
	*/

	void reset();

	/**

		Set the envelope mode.
	*/


	void setEGMode(int envelopeMode);

	/**

		Calculate attack time parameters.
	*/

	void calculateAttackTime();

	/**

		Calculate decay time parameters.
	*/

	void calculateDecayTime();

	/**

		Calculate release time parameters.
	*/

	void calculateReleaseTime();


	/**

		Goes to the release state and resets the counter.
	*/

	void noteOff();


	/**

		Goes to shutdown state.
	*/

	void shutDown();


	inline void setSampleRate(double sampleRate) { this->sampleRate = sampleRate; }


	/**

		Set the attack time in msec.
	*/


	inline void setAttackTime_mSec(double attackTime)
	{
		this->attackTime = attackTime;
		calculateAttackTime();
	}

	/**

		Set the decay time in msec.
	*/

	inline void setDecayTime_mSec(double decayTime)
	{
		this->decayTime = decayTime;
		calculateDecayTime();
	}

	/**

		Set the release time in msec.
	*/

	inline void setReleaseTime_mSec(double releaseTime)
	{
		this->releaseTime = releaseTime;
		calculateReleaseTime();
	}


	/**

		Set the sustain level.
	*/

	inline void setSustainLevel(double sustainLevel)
	{
		this->sustainLevel = sustainLevel;


		calculateDecayTime();


		if (envelopeState != release)
			calculateReleaseTime();
	}

	/**

		Start the envelope generator.
	*/


	inline void startEG()
	{
		/**

			Ignore when in legato mode
		*/

		if (legatoMode && envelopeState != off && envelopeState != release)
			return;


		reset();
		envelopeState = attack;
	}

	/**

		Set envelope state to off.
	*/

	inline void stopEG()
	{
		envelopeState = off;
	}

	/**

		Update parameters.
	*/
	inline void update()
	{
		// nothing yet
	}

	/**

		Perform envelope operation.
		Optionally can have biased output.
	*/


	inline double doEnvelope(double* biasedOutput = nullptr)
	{

		switch (envelopeState)
		{
		case off:
		{

			if (resetToZeroMode)
				envelopeOutput = 0.0;
			break;
		}
		case attack:
		{

			envelopeOutput = attackOffset + envelopeOutput * attackCoeff;


			if (envelopeOutput >= 1.0 || attackTime <= 0.0)
			{
				envelopeOutput = 1.0;
				envelopeState = decay;
				break;
			}
			break;
		}
		case decay:
		{

			envelopeOutput = decayOffset + envelopeOutput * decayCoeff;


			if (envelopeOutput <= sustainLevel || decayTime <= 0.0)
			{
				envelopeOutput = sustainLevel;
				envelopeState = sustain;
				break;
			}
			break;
		}
		case sustain:
		{

			envelopeOutput = sustainLevel;
			break;
		}
		case release:
		{

			envelopeOutput = releaseOffset + envelopeOutput * releaseCoeff;


			if (envelopeOutput <= 0.0 || releaseTime <= 0.0)
			{
				envelopeOutput = 0.0;
				envelopeState = off;
				break;
			}
			break;
		}
		case shutdown:
		{
			if (resetToZeroMode)
			{

				envelopeOutput += incValueShutdown;


				if (envelopeOutput <= 0)
				{
					envelopeState = off;
					envelopeOutput = 0.0;
					break;
				}
			}
			else
			{

				envelopeState = off;
			}
			break;
		}
		}


		if (biasedOutput)
			*biasedOutput = envelopeOutput - sustainLevel;


		return envelopeOutput;
	}



};
