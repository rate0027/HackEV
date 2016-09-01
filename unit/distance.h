#ifndef EV3_UNIT_DISTANCE_H_
#define EV3_UNIT_DISTANCE_H_
#include "Motor.h"
#include "util.h"
using namespace ev3api;
class distance {
public:
explicit distance(Motor& leftWheel,
Motor& rightWheel);
bool back();
bool move();
bool movea();
bool mover();
bool movel();
int32_t s = 0;
int32_t t = 0;
private:
Motor& mLeftWheel;
Motor& mRightWheel;
};

#endif // EV3_UNIT_DISTANCE_H_