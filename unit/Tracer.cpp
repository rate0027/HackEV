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
	mLeftWheel.setBrake(false);
	mRightWheel.setBrake(false);
}

void Tracer::terminate() {
  mLeftWheel.stop();
  mRightWheel.stop();
  mArm.stop();
}


void Tracer::run(int target, int edge) {
	const float Kp = 0.7; /* 0.63 */
	const float Ki = 0.15;
	const float Kd = 0.03; /*0.125*/
	//const float Kp = 0.2;
	//const float Ki = 0.1;
	//const float Kd = 0.3;

	const int bias = 0;
	int p,i,d;
	float integral;

	int diff[2];
	diff[0] = diff[1];
	diff[1] = mColorSensor.getBrightness() - target;
	integral += (diff[1] + diff[0]) / 2.0;
	p = Kp * diff[1] + bias;
	float turn = p+i+d;
	int ipwmR = pwm;
	int ipwmL = pwm;
	//    mLeftWheel.setPWM(pwm - turn);
	//    mRightWheel.setPWM(pwm + turn);

	/*
		 int diff = mColorControl->getBrightness() - target;
		 float turn = Kp * diff + bias;
		 */

	if (edge == 0) { // Right edge
		if(turn > 0){
			ipwmR = (pwm);
			ipwmL = (pwm - turn);
		}
		else if(turn < 0){
			ipwmL = (pwm);
			ipwmR = (pwm + turn);
		}
	
	} else if (edge == 1) { //Left edge
		if(turn > 0){
			ipwmL = (pwm);
			ipwmR = (pwm - turn);
		}
		else if(turn < 0){
			ipwmR = (pwm);
			ipwmL = (pwm + turn);
		}
	}

	mLeftWheel.setPWM(ipwmL);
	mRightWheel.setPWM(ipwmR);
//	mTailWheel.setPWM(turn*3);

}


void Tracer::runL(int target) {
    const float Kp = 0.8; /* 0.63 */
    const float Ki = 0.1;
    const float Kd = 0.1; /*0.125*/
    const int bias = 0;
    int p,i,d;
    float integral;
    
    int diff[2];
    diff[0] = diff[1];
    diff[1] = mColorSensor.getBrightness() - target;
    integral += (diff[1] + diff[0]) / 2.0;
    p = Kp * diff[1] + bias;
    i = Ki * integral;
    d = Kd * (diff[1] - diff[0]);
    float turn = p+i+d;
    int ipwmR = pwm;
    int ipwmL = pwm;
    
    if(turn > 0){
        ipwmL = (pwm);
        ipwmR = (pwm - turn);
    }
    else if(turn < 0){
        ipwmR = (pwm);
        ipwmL = (pwm + turn);
    }
    mLeftWheel.setPWM(ipwmL);
    mRightWheel.setPWM(ipwmR);
//    mTailWheel.setPWM(turn*3);

    
}



void Tracer::NLT(int ipwmR, int ipwmL) {
    mLeftWheel.setPWM(ipwmL*1.05);
    mRightWheel.setPWM(ipwmR);
}
