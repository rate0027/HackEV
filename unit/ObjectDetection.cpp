#include "ObjectDetection.h"

/* コンストラクタ */
/* センサ類を扱う場合はポートの宣言が必要 */
ObjectDetection::ObjectDetection(SonarSensor& sonarSensor)
	: mSonarSensor(sonarSensor) {
}

/* 距離判断メソッド */
bool ObjectDetection::isObject(int dist) {
	if ( mSonarSensor.getDistance() <= dist) {
		return true;
	} else {
		return false;
	}
}
