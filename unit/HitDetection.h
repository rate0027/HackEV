#ifndef EV3_UNIT_HITDETECTION_H_
#define EV3_UNIT_HITDETECTION_H_

/* センサを使う場合はincludeが必要*/
#include "GyroSensor.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

using namespace ev3api;

/* クラスの宣言 */
class HitDetection {
public:
  explicit HitDetection(GyroSensor& gyroSensor);
	bool isCollision();

private:
	GyroSensor& mGyroSensor;
	FILE *logfile;
};


#endif // EV3_UNIT_HITDETECTION_H_
