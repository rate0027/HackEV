#include "Controler.h"

/* コンストラクタ */
Controler::Controler(Tracer* tracer,
                     Ar* ar,
										 Prelude* prelude,
										 ObjectDetection* objectDetection,
										 TimeDetection* timeDetection,
										 HitDetection* hitDetection,
										 DistanceDetection* distanceDetection,
										 ColorJudge* colorJudge)
	: mTracer(tracer),
    mAr(ar),
	  mPrelude(prelude),
		mObjectDetection(objectDetection),
		mTimeDetection(timeDetection),
		mHitDetection(hitDetection),
		mDistanceDetection(distanceDetection),
		mColorJudge(colorJudge),
    mState(UNDEFINED){
}

void Controler::init() {
  init_f("Controler");
}

void Controler::terminate() {
  msg_f("Stopped.", 1);
	mTracer->terminate();
}

/* runメソッド: 状態に応じて動作させる */
void Controler::run() {
	switch(mState) {
		case UNDEFINED:
			if( (TARGET = mPrelude->calibration()) > 0 ) {
			  mState = WAITING_FOR_START;
			}
		  break;
		case WAITING_FOR_START:	
			msg_f("waiting", 1);		
 			if (mPrelude->isPressed()) {
				mState = WALKING;
			}
			ev3_led_set_color(LED_ORANGE);
			break;
		case WALKING:
				msg_f("running...", 1);
				mTracer->run(TARGET, 1);
#if 0
				if (mColorJudge->isColor() != 0) {
				  mState = COLOR;
					mDistanceDetection->reset();
				}
#endif
			break;
		case COLOR:
				msg_f("running...", 1);
				if (pos_run(TARGET, 2)) {
				  mState = STOP;
				}
			break;
		case STOP:
			msg_f("STOP", 1);
      mTracer->terminate();
      break;
    default:
  		break;
	}
	
}

int Controler::pos_run(int target, int X) {
	int count = 1; //色の検出回数

	switch(flag) {
		case 0:		
		mTracer->NLT(20,22);
		if (mDistanceDetection->left(200)) {
			flag = 1;
		}	
		break;
		case 1:
		mTracer->run(target, 0);
		if (mColorJudge->isColor() != 0) {
      flag = 0;
			count++;
		}
		break;
	}

	if (count == X) {
		flag = 0;
		return true;
	}else {
		return false;
	}
}



