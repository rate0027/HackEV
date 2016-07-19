#ifndef EV3_UNIT_STARTER_H_
#define EV3_UNIT_STARTER_H_

/* センサを使う場合はincludeが必要*/
#include "TouchSensor.h"

using namespace ev3api;

/* クラスの宣言 */
class Starter {
public:
  explicit Starter(const TouchSensor& touchSensor);
	bool isPressed() const;

private:
	const TouchSensor& mTouchSensor;
};


#endif // EV3_UNIT_STARTER_H_
