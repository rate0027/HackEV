#include "Tracer.h"

Tracer::Tracer(const ColorSensor& colorSensor,
							 Motor& leftWheel,
							 Motor& rightWheel)
	: mLeftWheel(leftWheel), 
	  mRightWheel(rightWheel),
    mColorSensor(colorSensor) {
}

void Tracer::init() {
}

void Tracer::terminate() {
  mLeftWheel.stop();
  mRightWheel.stop();
}

void Tracer::run() {

	const float Kp = 0.83; /* 0.63 */
	const int target = 26;
	const int bias = 0;

	int diff = mColorSensor.getBrightness() - target;
	float turn = Kp * diff + bias;
	mLeftWheel.setPWM(pwm - turn);
	mRightWheel.setPWM(pwm + turn);
}



