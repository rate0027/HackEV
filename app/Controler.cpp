#include "Controler.h"

/* コンストラクタ */
Controler::Controler(Tracer* tracer,
										 const Starter* starter,
										 ObjectDetection* objectDetection)
	: mTracer(tracer),
	  mStarter(starter),
		mObjectDetection(objectDetection),
		mState(UNDEFINED) {
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
			mState = WAITING_FOR_START;
		  break;
		case WAITING_FOR_START:	
			msg_f("waiting", 1);		
 			if (mStarter->isPressed()) {
				mState = WARKING;
			}
			ev3_led_set_color(LED_ORANGE);
			break;
		case WALKING:
			if (mObjectDetection->isPressed() <= 10){
				mState = OBJECT_DETECTION;
			} else {
				msg_f("running...", 1);		
				mTracer->run();
			}
			break;
		case OBJECT_DETECTION:
			if (mObjectDetection->isPressed() >= 11) {
				mState = WARKING;
			}else {
				msg_f("object_detection", 1);
				mTracer->terminate();
			}
			break;
		default:
			break;
	}
	
}

