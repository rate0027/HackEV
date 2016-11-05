#include "ColorJudge.h"

ColorJudge::ColorJudge(const ColorSensor& colorSensor)
	: mColorSensor(colorSensor) {
}

int ColorJudge::isColor() {
	int Color = mColorSensor.getColorNumber();
	if (Color > 1 && 6 > Color) {
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


int ColorJudge::isColorRGB(){
	rgb_raw_t rgb_val;
	ev3_color_sensor_get_rgb_raw(EV3_PORT_2, &rgb_val);
	if ( (30 < rgb_val.r && rgb_val.r < 60) && 
			 (90< rgb_val.g && rgb_val.g <150) && 
			 (10< rgb_val.b && rgb_val.b < 40)  ) { //green
		msg_f("Green", 2);
		return 3;
	} else if ( (20 < rgb_val.r && rgb_val.r < 40) && 
							(60 < rgb_val.g && rgb_val.g < 150) && 
							(30 < rgb_val.b && rgb_val.b < 130)) { //blue
		msg_f("Blue", 2);
		return 2;
	} else if ( (100 < rgb_val.r ) && 
							(rgb_val.g < 100) && 
							(10 < rgb_val.b && rgb_val.b < 25)) { //red
		msg_f("Red", 2);
		return 5;
	}else if ( (150 < rgb_val.r && rgb_val.r < 255) && 
						 (200 < rgb_val.g) && 
						 (0 < rgb_val.b && rgb_val.b < 50) ) { //yellow
		msg_f("Yellow", 2);
		return 4;
	} else {
		return 0;
	}
}

