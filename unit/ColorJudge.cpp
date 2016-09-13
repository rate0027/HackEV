#include "ColorJudge.h"

ColorJudge::ColorJudge(const ColorSensor& colorSensor)
	: mColorSensor(colorSensor) {
}


bool ColorJudge::judgeRED() {
if(  mColorSensor.getColorNumber() == 5){
	return(true);
}else{
	return(false);
}
}

bool ColorJudge::judgeBLUE() {
if(  mColorSensor.getColorNumber() == 2){
	return(true);
}else{
	return(false);
}
}

bool ColorJudge::judgeGREEN() {
if(  mColorSensor.getColorNumber() == 3){
	return(true);
}else{
	return(false);
}
}

bool ColorJudge::judgeYELOW() {
if(  mColorSensor.getColorNumber() == 4){
	return(true);
}else{
	return(false);
}
}

bool ColorJudge::judgeBLACK() {
if(  mColorSensor.getColorNumber() == 1){
	return(true);
}else{
	return(false);
}
}


bool ColorJudge::JudgeGray(){
	mColorSensor.getRawColor(*rgb);	
	if (45 < rgb->r && rgb->r <  65 && 70 < rgb->g && rgb->g < 80 && 50 < rgb->b && rgb->b < 65 ) {
    return(true);
	} else {
		return(false);
	}
}

