#ifndef EV3_UNIT_COLOR_CONTROL_H_
#define EV3_UNIT_COLOR_CONTROL_H_

#include "ColorSensor.h"

using namespace ev3api;

class ColorControl {
	public:
		explicit ColorControl(const ColorSensor& colorSensor);
		int8_t getBright() const;
		colorid_t getColor() const;
		void getBlack();
		void getWhite();
		int getTarget() const;

	private:
		const ColorSensor& mColorSensor;
		int8_t BLACK, WHITE;

};

#endif // EV3_UNIT_COLOR_CONTROL_H_
