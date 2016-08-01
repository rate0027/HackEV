#include "ColorControl.h"

ColorControl::ColorControl(const ColorSensor& colorSensor)
	: mColorSensor(colorSensor) {
}

int8_t ColorControl::getBright() const {
  return mColorSensor.getBrightness();
}
colorid_t ColorControl::getColor() const{
	return mColorSensor.getColorNumber();
}
void ColorControl::getBlack(){
  BLACK = getBright();
}
void ColorControl::getWhite(){
  WHITE = getBright();
}
int ColorControl::getTarget() const{
  return ((BLACK+WHITE)/2);
}


