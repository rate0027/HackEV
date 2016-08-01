#ifndef EV3_UNIT_PRELUDE_H_
#define EV3_UNIT_PRELUDE_H_

/* センサを使う場合はincludeが必要*/
#include "TouchSensor.h"
#include "ColorControl.h"
#include "util.h"

using namespace ev3api;

/* クラスの宣言 */
class Prelude {
public:
  explicit Prelude(const TouchSensor& touchSensor,
			ColorControl* colorControl);
	bool isPressed() const;
	void calibration() ;

private:
  enum State {
    black,
		white
	};

	const TouchSensor& mTouchSensor;
	ColorControl* mColorControl;
	State mState;
};


#endif // EV3_UNIT_PRELUDE_H_
