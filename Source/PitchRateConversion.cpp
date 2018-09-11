#include "PitchRateConversion.h"



PitchRateConversion::PitchRateConversion()
{
	setMode(CHROMATIC);
	setRootNote("C");
}

int PitchRateConversion::performPithShift(int value)
{
	if (mode == 0) return value;
	return conversionTable[value + 7];
}

String PitchRateConversion::getTextBoxSymbol(int value)
{	
	if (value < 0)
	{
		int index = 0;
		int factor = performPithShift(value);
		if(rootIndex - factor > 0 )
		{
			index = (rootIndex + factor + 12) % 12;
		}else
		{
			int index = (rootIndex + factor + 12);
		}
		
		return symbols[index];
	}

	return symbols[(rootIndex + performPithShift(value)) % 12];
}


