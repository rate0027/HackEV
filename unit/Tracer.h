#ifndef EV3_UNIT_TRACER_H_
#define EV3_UNIT_TRACER_H_

#include "Motor.h"
#include "ColorSensor.h"
#include "util.h"

using namespace ev3api;

class Tracer {
public:
  explicit Tracer(ColorSensor& colorSensor,
				 Motor& leftWheel,
				 Motor& rightWheel,
				 Motor& tailWheel,
         Motor& arm);
  void run(int);
	void NLT(int, int);
  void init();
  void terminate();

private:
	ColorSensor& mColorSensor;
	Motor& mLeftWheel;
	Motor& mRightWheel;
	Motor& mTailWheel;
  Motor& mArm;
  const int8_t mThreshold = 21;
  //const int8_t pwm = (Motor::PWM_MAX) / 6;
  const int8_t pwm = 25;
	rgb_raw_t* rgb;
	char str1[128]={0};
};


#endif // EV3_UNIT_TRACER_H_
