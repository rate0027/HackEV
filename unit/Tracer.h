#ifndef EV3_UNIT_TRACER_H_
#define EV3_UNIT_TRACER_H_

#include "Motor.h"
#include "ColorSensor.h"
#include "util.h"

using namespace ev3api;

class Tracer {
public:
  explicit Tracer(const ColorSensor& colorSensor,
				 Motor& leftWheel,
				 Motor& rightWheel,
				 Motor& tailWheel);
  void run();
  void init();
  void terminate();

private:
	Motor& mLeftWheel;
	Motor& mRightWheel;
	Motor& mTailWheel;
	const ColorSensor& mColorSensor;
  const int8_t mThreshold = 21;
  const int8_t pwm = (Motor::PWM_MAX) / 6;
};


#endif // EV3_UNIT_TRACER_H_
