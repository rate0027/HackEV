#ifndef EV3_UNIT_COLOR_JUDGE_H_
#define EV3_UNIT_COLOR_JUDGE_H_

#include "ColorSensor.h"

using namespace ev3api;

class ColorJudge {
	public:
	explicit ColorJudge(const ColorSensor& colorSensor);
	bool judgeRED();
	bool judgeBLUE();
	bool judgeGREEN();
	bool judgeYELOW();
	bool judgeBLACK();
	
private:
		const ColorSensor& mColorSensor;		
};

#endif // EV3_UNIT_COLOR_JUDGE_H_
