#include "Prelude.h"

/* コンストラクタ */
/* センサ類を扱う場合はポートの宣言が必要 */
Prelude::Prelude(const TouchSensor& touchSensor,
		ColorControl* colorControl)
	: mTouchSensor(touchSensor), 
		mColorControl(colorControl),
		mState(BLACK) {
}

/* 押し判断メソッド */
bool Prelude::isPressed() const{
	return mTouchSensor.isPressed();
}

int Prelude::calibration() {
  switch(mState){
	  case BLACK:
		  tslp_tsk(100);
	    msg_f("caribration:black", 1);		
	    if (isPressed()) {
        black = mColorControl->getBright();
		    mState = WHITE;
	    }
	    break;
	  case WHITE:
	    tslp_tsk(100);
			msg_f("caribration:white", 1);		
			if (isPressed()) {
				white = mColorControl->getBright();
				mState = COMPLETE;
			}
			break;
		case COMPLETE:
			target = (black + white)/2;
			break;
		default:
			break;
	}
	
	return target;
  
}


