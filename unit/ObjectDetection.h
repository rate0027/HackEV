#ifndef EV3_UNIT_OBJECTDETECTION_H_
#define EV3_UNIT_OBJECTDETECTION_H_

/* センサを使う場合はincludeが必要*/
#include "SonarSensor.h"

using namespace ev3api;

/* クラスの宣言 */
class ObjectDetection {
public:
  explicit ObjectDetection(SonarSensor& sonarSensor);
	int isPressed();

private:
	SonarSensor& mSonarSensor;
};


#endif // EV3_UNIT_OBJECTDETECTION_H_
