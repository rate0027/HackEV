#include "Prelude.h"

/* コンストラクタ */
/* センサ類を扱う場合はポートの宣言が必要 */
Prelude::Prelude(const TouchSensor& touchSensor,
		ColorControl* colorControl)
	: mTouchSensor(touchSensor), 
		mColorControl(colorControl) {
}

/* 押し判断メソッド */
bool Prelude::isPressed() const{
	return mTouchSensor.isPressed();
}

void Prelude::calibration() {
  switch(mState){
	  case black:
		  tslp_tsk(100);
	    msg_f("caribration:black", 1);		
	    if (isPressed()) {
        mColorControl->getBlack();
		    mState = white;
	    }
	    break;
	  case white:
	    tslp_tsk(100);
			msg_f("caribration:white", 1);		
			if (isPressed()) {
				mColorControl->getWhite();
			}
			break;
		default:
			break;
	}
  
}


