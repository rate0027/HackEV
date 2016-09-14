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



void Tracer::run(int target) {
    const float Kp = 0.7; /* 0.63 */
    const float Ki = 0.3;
    const float Kd = 0.14; /*0.125*/
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
    //    mLeftWheel.setPWM(pwm - turn);
    //    mRightWheel.setPWM(pwm + turn);
    
    /*
     int diff = mColorControl->getBrightness() - target;
     float turn = Kp * diff + bias;
     */
    
    if(turn > 0){
        ipwmR = (pwm);
        ipwmL = ((pwm+2) - turn);
    }
    else if(turn < 0){
        ipwmL = (pwm+2);
        ipwmR = (pwm + turn);
    }
    mLeftWheel.setPWM(ipwmL);
    mRightWheel.setPWM(ipwmR);
   // mLeftWheel.setPWM(0);
   // mRightWheel.setPWM(0);
		mTailWheel.setPWM(turn*3);
/*
	mColorSensor.getRawColor(*rgb);	
	sprintf(str1, "%u  %u  %u", rgb->r, rgb->g, rgb->b);
	msg_f(str1,2);
*/

}


void Tracer::NLT(int ipwmR, int ipwmL) {
    mLeftWheel.setPWM(ipwmL);
    mRightWheel.setPWM(ipwmR);
}
