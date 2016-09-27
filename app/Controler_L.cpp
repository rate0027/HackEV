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
		case WALKING: //初めの直線
			msg_f("running...", 1);		
			mTracer->run(TARGET, 0);
			if (mDistanceDetection->left(3500)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				mState = STEP2;
			}
			break;
		case STEP2: //カーブ
			msg_f("running...", 1);		
			mTracer->run(TARGET, 0);
			if (mDistanceDetection->left(1600)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				mState = STEP3;
			}
			break;
		case STEP3: //直線 
			msg_f("running...", 1);		
			mTracer->run(TARGET, 0);
			if (mDistanceDetection->left(1500)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				mState = STEP4;
			}
			break;
		case STEP4: //カーブからラインチェンジ直前まで
			msg_f("running...", 1);		
			mTracer->run(TARGET, 0);
			if (mDistanceDetection->left(2240)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				mState = STEP5;
			}
			break;
		case STEP5: //反対側のラインへ移動
			msg_f("running...", 1);		
			mTracer->NLT(20,10);
			if (mDistanceDetection->left(50)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				mState = STEP6;
			}
			break;
		case STEP6: //ライン復帰
			msg_f("running...", 1);		
			mTracer->run(TARGET, 0);
			
			if (mDistanceDetection->left(1500)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				mState = STEP7;
			}
			break;
		case STEP7: //星取りまで
			msg_f("running...", 1);		
			mTracer->run(TARGET, 0);
			
			if ((star =  mColorJudge->isColor()) > 0) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				mDistanceDetection->reset();
				mState = STEP8;
			}
			break;
		case STEP8: //バック
			msg_f("running...", 1);		
			mTracer->NLT(-10,-10);
			if (mDistanceDetection->left(-300)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				mTimeDetection->reset();
				mState = STEP9;
			}
			break;
		case STEP9: //若干停止
			msg_f("running...", 1);		
			mTracer->NLT(0,0);
			if (mTimeDetection->isOver(250)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				mDistanceDetection->reset();
				mState = STEP10;
			}
			break; 
		case STEP10: //反対側のラインへ移動
			msg_f("running...", 1);		
			mTracer->NLT(20,0);
			if (mDistanceDetection->right(100)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				mState = STEP11;
			}
			break;
		case STEP11: //相撲の前まで移動
			msg_f("running...", 1);		
			mTracer->run(TARGET, 0);
			if (mDistanceDetection->left(1600)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
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
				mTracer->run(TARGET, 0);
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

void Controler::L_course() {
	switch (mLState) {
		case step1:
			msg_f("running...", 1);		
			mTracer->run(TARGET, 0);
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
