#ifndef EV3_UNIT_PRELUDE_H_
#define EV3_UNIT_PRELUDE_H_

/* センサを使う場合はincludeが必要*/
#include "TouchSensor.h"
#include "ColorSensor.h"
#include "util.h"

using namespace ev3api;

/* クラスの宣言 */
class Prelude {
public:
  explicit Prelude(const TouchSensor& touchSensor,
			const ColorSensor& colorSensor);
	bool isPressed() const;
	int calibration() ;

private:
  enum State {
    BLACK,
		WHITE,
		COMPLETE
	};

	const TouchSensor& mTouchSensor;
	const ColorSensor& mColorSensor;
	State mState;
	int8_t black, white = 0;
	int target = 0;
};


#endif // EV3_UNIT_PRELUDE_H_
