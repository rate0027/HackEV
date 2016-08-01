#include "Tracer.h"

Tracer::Tracer(const ColorControl* colorControl,
							 Motor& leftWheel,
							 Motor& rightWheel,
							 Motor& tailWheel)
	: mColorControl(colorControl),
		mLeftWheel(leftWheel), 
	  mRightWheel(rightWheel),
		mTailWheel(tailWheel) {
}

void Tracer::init() {
}

void Tracer::terminate() {
  mLeftWheel.stop();
  mRightWheel.stop();
}

void Tracer::run() {

	const float Kp = 0.83; /* 0.63 */
	int target = mColorControl->getTarget();
	const int bias = 0;

	int diff = mColorControl->getBright() - target;
	float turn = Kp * diff + bias;
	mLeftWheel.setPWM(pwm - turn);
	mRightWheel.setPWM(pwm + turn);
	mTailWheel.setPWM(turn*10);
}



