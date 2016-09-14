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

bool ColorJudge::judgeBLACK() {
	if(  mColorSensor.getColorNumber() == 1){
		return(true);
	}else{
		return(false);
	}
}


bool ColorJudge::judgeGray(){
	mColorSensor.getRawColor(*rgb);	
	if (45 < rgb->r && rgb->r <  65 && 70 < rgb->g && rgb->g < 80 && 50 < rgb->b && rgb->b < 65 ) {
    return(true);
	} else {
		return(false);
	}
}

