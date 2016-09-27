#include "Prelude.h"

/* コンストラクタ */
/* センサ類を扱う場合はポートの宣言が必要 */
Prelude::Prelude(const TouchSensor& touchSensor,
		const ColorSensor& colorSensor)
	: mTouchSensor(touchSensor), 
		mColorSensor(colorSensor),
		mState(BLACK) {
}

/* 押し判断メソッド */
bool Prelude::isPressed() const{
	return mTouchSensor.isPressed();
}

int Prelude::calibration() {
  switch(mState){
	  case BLACK:
		  tslp_tsk(200);
	    msg_f("caribration:black", 1);		
	    if (mTouchSensor.isPressed()) {
        black = mColorSensor.getBrightness();
		    mState = WHITE;
	    }
	    break;
	  case WHITE:
	    tslp_tsk(200);
			msg_f("caribration:white", 1);		
			if (mTouchSensor.isPressed()) {
				white = mColorSensor.getBrightness();
				mState = COMPLETE;
			}
			break;
		case COMPLETE:
	    tslp_tsk(200);
			target = (black + white) * 0.3;
			break;
		default:
			break;
	}
	
	return target;
  
}


