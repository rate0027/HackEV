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
			if (mObjectDetection->isPressed() <= 10){
				mState = OBJECT_DETECTION;
			} else {
				msg_f("running...", 1);
				mTracer->run(TARGET);
			}
			break;
		case OBJECT_DETECTION:
			if (mObjectDetection->isPressed() >= 11) {
				mState = WALKING;
			}else {
				msg_f("object_detection", 1);
				mTracer->terminate();
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

