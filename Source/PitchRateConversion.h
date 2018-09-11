/**
	The Pitch Rate Conversion Class can pitch given Values in a selected mode.



	@author Niklas Wantrupp
	@version v1.0 11/09/2018
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

static int chromatic[] = { -12, -11, -10, -9, -8, -7, 6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
static int major[] = { -12, -10, -8, -7, -5, -3, -1, 0, 2, 4, 5, 7, 9, 11, 12 };
static int minor[] = { -12, -10, -9, -7, -5, -4, -2, 0, 2, 3, 5, 7, 8, 10, 12 };
static int melodicMinor[] = { -12, -10, -9, -7, -5, -3, -1, 0, 2, 3, 5, 7, 9, 11, 12 };
static int harmonicMinor[] = { -12, -10, -9, -7, -5, -4, 1, 0, 2, 3, 5, 7, 8, 11, 12 };
static StringArray symbols = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };

class PitchRateConversion
{
private:
	int mode;
	int* conversionTable;
	int rootIndex;

	enum { CHROMATIC = 0, MAJOR, MINOR, MELODICMINOR, HARMONICMINOR};
	
public:
	PitchRateConversion();

	/**
		Returns the current mode.
	*/
	int getMode() { return mode; }

	/**
		Sets the root note.
	*/
	void setRootNote(String root) { rootIndex = symbols.indexOf(root);  }

	/**
		Use this to set your mode you would like to use.
	*/

	void setMode(int mode)
	{
		this->mode = mode;
		switch(mode)
		{
		case MAJOR:
			conversionTable = major;
			break;
		case MINOR:
			conversionTable = minor;
			break;
		case MELODICMINOR:
			conversionTable = melodicMinor;
			break;
		case HARMONICMINOR:
			conversionTable = harmonicMinor;
			break;
		case CHROMATIC:
			conversionTable = chromatic;
			break;
		}
		
	}

	/**
		Input a value between -7 and 7 and the corresponding in Juce String format is returned.
	*/
	String getTextBoxSymbol(int value);

	/**
		Input a value between -7 and 7 and the corresponding semitone value is returned.
	*/
	int performPithShift(int value);
	
	
};