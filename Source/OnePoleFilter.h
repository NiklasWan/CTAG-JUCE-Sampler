/**
	Describes a basic One Pole Filter.

	Based on an implementation from Will Pirkle
	(http://www.willpirkle.com/)

	@author Niklas Wantrupp
	@version v1.0 11/09/2018
*/

#pragma once

#include "Filter.h"


class VAOnePoleFilter : public Filter
{
public:
	VAOnePoleFilter(void);

	

	/**
		This is used to set the feedback of the filter.
	*/
	void setFeedback(double feedback) { this->feedback = feedback; }

	/**

		Allows acces to feedback output.
	*/
	double getFeedbackOutput() { return beta * (z1 + feedback * delta); }


	/**

		Resets the filter.
	*/

	virtual void reset() { z1 = 0; feedback = 0; }

	/**

		Recalculates the coefficients.
	*/
	virtual void update();


	/**

		Performs the actual filter calculation.
	*/
	virtual double doFilter(double xn);

protected:
	double alpha;
	double beta;
	double gamma;
	double delta;
	double epsilon;
	double inputGain;
	double feedback;
	double z1;
};

