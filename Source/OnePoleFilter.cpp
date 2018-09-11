#include "OnePoleFilter.h"



VAOnePoleFilter::VAOnePoleFilter(void)
{
	/**

		Initialize to a basic LPF/HPF structure.
	*/

	alpha = 1.0;
	beta = 0.0;
	z1 = 0.0;
	gamma = 1.0;
	delta = 0.0;
	epsilon = 0.0;
	inputGain = 1.0;
	feedback = 0.0;


	filterType = LPF1;

	reset();
}



/**

	Used to recalculate the coefficients.
*/
void VAOnePoleFilter::update()
{

	Filter::update();

	double wd = 2 * PI * cutoffValue;
	double T = 1 / sampleRate;
	double wa = (2 / T) * tan(wd * T / 2);
	double g = wa * T / 2;

	alpha = g / (1.0 + g);
}


double VAOnePoleFilter::doFilter(double xn)
{
	if (!isActive()) return xn;

	/**

		If filter is not supported return xn.
	*/

	if (filterType != LPF1 && filterType != HPF1)
		return xn;

	/**

		Diode filter support.
	*/

	xn = xn * gamma + feedback + epsilon * getFeedbackOutput();

	/**

		Calculate v(n)
	*/

	double vn = (inputGain * xn - z1) * alpha;


	double lpf = vn + z1;


	z1 = vn + lpf;


	double hpf = xn - lpf;

	if (filterType == LPF1)
		return lpf;
	else if (filterType == HPF1)
		return hpf;

	return xn; 
}


