#ifndef EV3_UNIT_ARM_H_
#define EV3_UNIT_ARM_H_
#include "Motor.h"
#include "util.h"

using namespace ev3api;

class Ar {
public:
explicit Ar(Motor& arm);
bool armUp(int);
bool armDown(int);
void reset();
int32_t u = 0;
int32_t v = 0;
int32_t w = 0;
private:
Motor& mArm;
};

#endif // EV3_UNIT_ARM_H_
