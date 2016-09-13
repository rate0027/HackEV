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
	mTracer->init();
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
			mTracer->run(TARGET);
			if (mDistanceDetection->left(3500)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				mState = STEP2;
			}
			break;
		case STEP2:
			msg_f("running...", 1);		
			mTracer->run(TARGET);
			if (mDistanceDetection->left(1600)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				mState = STEP3;
			}
			break;
		case STEP3:
			msg_f("running...", 1);		
			mTracer->run(TARGET);
			if (mDistanceDetection->left(1500)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				mState = STEP4;
			}
			break;
		case STEP4:
			msg_f("running...", 1);		
			mTracer->run(TARGET);
			if (mDistanceDetection->left(2240)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				mState = STEP5;
			}
			break;
		case STEP5:
			msg_f("running...", 1);		
			mTracer->NLT(20,10);
			if (mDistanceDetection->left(50)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				mState = STEP6;
			}
			break;
		case STEP6:
			msg_f("running...", 1);		
			mTracer->run(TARGET);
			
			if (mDistanceDetection->left(1500)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				mState = STEP7;
			}
			break;
		case STEP7:
			msg_f("running...", 1);		
			mTracer->run(TARGET);
			
			if (mColorJudge->JudgeGray()) {
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

void Controler::L_course() {
	switch (mLState) {
		case step1:
			msg_f("running...", 1);		
			mTracer->run(TARGET);
			if (mDistanceDetection->left(4000)) {
					ev3_speaker_play_tone(NOTE_D5, 200);
					mLState = step3;
				}
			break;
		case step2:
			break;
		case step3:
			msg_f("STOP", 1);
			mTracer->terminate();
			break;
		default:
			break;
	}
}
