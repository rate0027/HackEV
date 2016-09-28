#include "ColorJudge.h"

ColorJudge::ColorJudge(const ColorSensor& colorSensor)
	: mColorSensor(colorSensor) {
}

int ColorJudge::isColor() {
	int Color = mColorSensor.getColorNumber();
	if (Color > 1 && 6 > Color) {
		msg_f("retrun Color",3);
		return Color;
	} else {
		return 0;
	}
}

bool ColorJudge::judgeBlack() {
	if(  mColorSensor.getColorNumber() == 1){
		return(true);
	}else{
		return(false);
	}
}


bool ColorJudge::judgeYellow(){
	rgb_raw_t rgb_val;
	ev3_color_sensor_get_rgb_raw(EV3_PORT_2, &rgb_val);
	if ( (150 < rgb_val.r && rgb_val.r < 255) && (0 < rgb_val.b && rgb_val.b < 120) ) { //黄色
    return(true);
	} else {
		return(false);
	}
}

