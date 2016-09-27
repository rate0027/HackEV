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
				if (lBasic()) {
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

/*
 * lBasic
 * ベーシック部分のシナリオ(星取前まで)
 */

bool Controler::lBasic() {
	switch(flag) {
		case 0:
			msg_f("running...", 1);		
			mTracer->run(TARGET, 0);
			if (mDistanceDetection->left(4000)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				flag = 1;
				return false;
			}
			break;
		case 1: //カーブ
			msg_f("running...", 1);		
			mTracer->run(TARGET, 0);
			if (mDistanceDetection->left(1600)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				flag = 2;
				return false;
			}
			break;
		case 2: //直線 
			msg_f("running...", 1);		
			mTracer->run(TARGET, 0);
			if (mDistanceDetection->left(1500)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				flag = 3;
				return false;
			}
			break;
		case 3: //カーブからラインチェンジ直前まで
			msg_f("running...", 1);		
			mTracer->run(TARGET, 0);
			if (mDistanceDetection->left(2240)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				flag = 4;
				return false;
			}
			break;
		case 4: //反対側のラインへ移動
			msg_f("running...", 1);		
			mTracer->NLT(20,10);
			if (mDistanceDetection->left(50)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				flag = 5;
				return false;
			}
			break;
		case 5: //ライン復帰
			msg_f("running...", 1);		
			mTracer->run(TARGET, 0);
			if (mDistanceDetection->left(1500)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				flag = 0;
				return true;
			}
			break;
			
	}
}
