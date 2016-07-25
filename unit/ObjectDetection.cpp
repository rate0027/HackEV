#include "ObjectDetection.h"

/* コンストラクタ */
/* センサ類を扱う場合はポートの宣言が必要 */
ObjectDetection::ObjectDetection(SonarSensor& sonarSensor)
	: mSonarSensor(sonarSensor) {
}

/* 押し判断メソッド */
int ObjectDetection::isPressed() {
	return mSonarSensor.getDistance();
}
