#include "Starter.h"

/* コンストラクタ */
/* センサ類を扱う場合はポートの宣言が必要 */
Starter::Starter(const TouchSensor& touchSensor)
	: mTouchSensor(touchSensor) {
}

/* 押し判断メソッド */
bool Starter::isPressed() const{
	return mTouchSensor.isPressed();
}
