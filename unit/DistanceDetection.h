#ifndef EV3_UNIT_DISTANCEDETECTION_H_
#define EV3_UNIT_DISTANCEDETECTION_H_

/* センサを使う場合はincludeが必要*/
#include "Motor.h"

using namespace ev3api;

/* クラスの宣言 */
class DistanceDetection {
public:
  explicit DistanceDetection(Motor& leftWheel,
				 Motor& rightWheel,
				 Motor& tailWheel,
				 Motor& arm);
	bool test(int);
private:
	Motor& mLeftWheel;
	Motor& mRightWheel;
	Motor& mTailWheel;
	Motor& mArm;
};


#endif // EV3_UNIT_DISTANCEDETECTION_H_
