#include "Controler.h"

/* コンストラクタ */
Controler::Controler(Tracer* tracer,
										 const Starter* starter)
	: mTracer(tracer),
	  mStarter(starter),
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
		case WARKING:
			msg_f("running...", 1);		
			mTracer->run();
			break;
		default:
			break;
	}
	
}

