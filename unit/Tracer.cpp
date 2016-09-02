#include "Tracer.h"

Tracer::Tracer(ColorSensor& colorSensor,
							 Motor& leftWheel,
							 Motor& rightWheel,
							 Motor& tailWheel,
               Motor& arm)
	: mColorSensor(colorSensor),
		mLeftWheel(leftWheel), 
	  mRightWheel(rightWheel),
		mTailWheel(tailWheel),
    mArm(arm){
}

void Tracer::init() {
}

void Tracer::terminate() {
  mLeftWheel.stop();
  mRightWheel.stop();
  mArm.stop();
}


void Tracer::run(int target) {

  const float Kp = 0.63; /* 0.63 */
	const float Ki = 0.30;
  const float Kd = 0.026;
	const int bias = 0;
  int p,i,d;
	float integral;

/* P制御
	int diff = mColorSensor.getBrightness() - target;
	float turn = Kp * diff + bias;
*/
	/* PID制御 */
	int diff[2];
	diff[1] = mColorSensor.getBrightness() - target;
	diff[0] = diff[1];
	integral += (diff[1] + diff[0])/ 2.0 * 0.004;
	p = Kp * diff[1] + bias;
	i = Ki * integral;
	d = Kd * (diff[1] - diff[0]) / 0.004;
	float turn = p+i+d;

	mLeftWheel.setPWM(pwm - turn);
	mRightWheel.setPWM(pwm + turn);
	//mTailWheel.setPWM(turn*10);
}



