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
    const float Kp = 0.6; /* 0.63 */
    const float Ki = 0.3;
    const float Kd = 0.525; /*0.125*/
    const int bias = 0;
    int p,i,d;
    float integral;
    
    int diff[2];
    diff[0] = diff[1];
    diff[1] = mColorSensor.getBrightness() - target;
    integral += (diff[1] + diff[0]) / 2.0 * 0.004;
    p = Kp * diff[1] + bias;
    i = Ki * integral;
    d = Kd * (diff[1] - diff[0]) / 0.004;
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
        ipwmL = ((pwm+3) - turn);
    }
    else if(turn < 0){
        ipwmL = (pwm+3);
        ipwmR = (pwm + turn);
    }
    mLeftWheel.setPWM(ipwmL);
    mRightWheel.setPWM(ipwmR);
    
    mTailWheel.setPWM(turn*5);
}



