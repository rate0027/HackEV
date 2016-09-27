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
				if (mDistanceDetection->left(1600)) {
					ev3_speaker_play_tone(NOTE_D5, 10);
					mDistanceDetection->reset();
					mState = OBJECT_DETECTION;
				}
				break;
		case OBJECT_DETECTION:
				mTracer->NLT(0,0);
				if (mObjectDetection->isObject(10)) {
					ev3_speaker_play_tone(NOTE_D5, 10);
					mTimeDetection->reset();
					mState = TRAIN_WAIT;
				}
				break;
		case TRAIN_WAIT:
				mTracer->NLT(0,0);
				if (mTimeDetection->isOver(1500)) {
					ev3_speaker_play_tone(NOTE_D5, 10);
					mState = TRACE;
				}
		case TRACE:
				msg_f("running...", 1);
				mTracer->run(TARGET, 1);
				if (mDistanceDetection->left(500)) {
					ev3_speaker_play_tone(NOTE_D5, 10);
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

bool Controler::thr_bl(void) {

  switch(flag) {	
	case 0: //避けるために後ろに下がる
		mTracer->NLT(-10,-10);
		if (mDistanceDetection->left(-230)) {
			mDistanceDetection->reset();
			flag = 1;
			return false;
		}	
		break;
	case 1: 
		mTracer->NLT(10, -10);
		if (mDistanceDetection->right(100)) {
			flag = 2;
			return false;
		}
		break;
	case 2:
	 mTracer->NLT(10, 18);	
	 if (mColorJudge->judgeBLACK() ) {
			mDistanceDetection->reset();
		 flag = 3;
		 return false;
	 }
	 break;
	case 3: 
		mTracer->NLT(8, -10);
		if (mDistanceDetection->left(-30)) {
			flag = 4;
			return false;
		}
		break;
	case 4: 
		mTracer->NLT(10, 0);
		if (mDistanceDetection->right(70)) {
			flag = 0;
			return true;
		}
		break;
	}
}


