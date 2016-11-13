#ifndef EV3_UNIT_COLOR_JUDGE_H_
#define EV3_UNIT_COLOR_JUDGE_H_

#include "ColorSensor.h"
#include "util.h"
#include "stdlib.h"


using namespace ev3api;

class ColorJudge {
	public:
	explicit ColorJudge(const ColorSensor& colorSensor);
	int isColor();
	int judgeBlack();
	int isColorRGB();	
private:
	const ColorSensor& mColorSensor;		
	rgb_raw_t* rgb = {0};
	char str1[128]={0};
};

#endif // EV3_UNIT_COLOR_JUDGE_H_
