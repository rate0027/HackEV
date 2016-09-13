#ifndef EV3_UNIT_COLOR_JUDGE_H_
#define EV3_UNIT_COLOR_JUDGE_H_

#include "ColorSensor.h"
#include "util.h"
#include "stdlib.h"

using namespace ev3api;

class ColorJudge {
	public:
	explicit ColorJudge(const ColorSensor& colorSensor);
	bool judgeRED();
	bool judgeBLUE();
	bool judgeGREEN();
	bool judgeYELOW();
	bool judgeBLACK();
	bool JudgeGray();
	
private:
	const ColorSensor& mColorSensor;		
	rgb_raw_t* rgb;
	char str1[128]={0};
};

#endif // EV3_UNIT_COLOR_JUDGE_H_
