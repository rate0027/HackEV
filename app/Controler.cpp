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
#if 0
		case WALKING:
			msg_f("running...", 1);
			if (rStart()) {
			  mState = THROUGH;
			}
			break;
		case THROUGH:
			msg_f("running...", 1);
			if (rSortThrough()) {
				mDistanceDetection->reset();
			  mState = TRACE;
			}
			break;
		case TRACE:
			mTracer->run(TARGET,1);
			if(mDistanceDetection->left(15300)) {
				mState = STOP;
			}
			break;
#endif
		case WALKING:
			if ( rBasic() ) {
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
			mTracer->run(TARGET, 0, 30);
			if (mDistanceDetection->left(3900)) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 1;
				return false;
			}
			break;
		case 1: //カーブ
			msg_f("running...", 1);		
			mTracer->run(TARGET, 0, 15);
			if (mDistanceDetection->left(1600)) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 2;
				return false;
			}
			break;
		case 2: //直線 
			msg_f("running...", 1);		
			mTracer->run(TARGET, 0, 30);
			if (mDistanceDetection->left(1500)) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 3;
				return false;
			}
			break;
		case 3: //カーブからラインチェンジ直前まで
			msg_f("running...", 1);		
			mTracer->run(TARGET, 0, 16);
			if (mDistanceDetection->left(2240)) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 4;
				return false;
			}
			break;
		case 4: //反対側のラインへ移動
			msg_f("running...", 1);		
			mTracer->NLT(20,10);
			if (mDistanceDetection->left(50)) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 5;
				return false;
			}
			break;
		case 5: //ライン復帰
			msg_f("running...", 1);		
			mTracer->run(TARGET, 0, 18);
			if (mDistanceDetection->left(1500)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				flag = 0;
				return true;
			}
			break;
	}
	return false;
}

/*
 * rStart
 * Rコースをスタートしてブロック並べの方向へ向く 
 */
bool Controler::rStart(void) {
	switch(flag) {
		case 0:
			mTracer->run(TARGET, 1, 13);
			if (mDistanceDetection->left(700)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				mDistanceDetection->reset();
				flag = 1;
				return false;
			}
			break;
		case 1:
			mTracer->NLT(10, -10);
			if (mDistanceDetection->right(125)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				flag = 0;
				return true;
			}
			break;
	}
	return false;
}

/*
 * rSortThrough
 * ブロック並べエリアを無視する
 */ 
bool Controler::rSortThrough(void){
	switch(flag) {
		case 0:
			mTracer->NLT(10,10);
			if (mColorJudge->judgeBlack()) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				mTimeDetection->reset();
				flag = 1;
				return false;
			}
			break;
		case 1:
			if (mTimeDetection->isOver(500)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				if (++count == 5) {
					flag = 2;
					mDistanceDetection->reset();
				} else {
					flag = 0;
				}
				return false;
			}
			break;
		case 2:
			mTracer->NLT(-10, 10);
			if (mDistanceDetection->left(135)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				flag = 0;
				return true;
			}
			break;
	}
	return false;
}

bool Controler::rBasic(void) {
	switch(flag){
		case 0:
			mTracer->run(TARGET, 1, 40);
			if(mDistanceDetection->left(1500)) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 1;
				return false;
			}
			break;
		case 1:
			mTracer->run(TARGET, 1, 20);
			if (mDistanceDetection->left(800)) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 2;
				return false;
			}
			break;
		case 2:
			mTracer->run(TARGET, 1, 30);
			if (mDistanceDetection->left(2000)) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 3;
				return false;
			}
			break;
		case 3:
			mTracer->run(TARGET, 1, 15);
			if (mDistanceDetection->left(1000)) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 4;
				return false;
			}
			break;
		case 4: 
			mTracer->run(TARGET, 1, 20);
			if (mDistanceDetection->left(2000)) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 5;
				return false;
			}
			break;
		case 5:
			mTracer->run(TARGET, 1, 12);
			if (mDistanceDetection->left(1200)) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 6;
				return false;
			}
			break;
		case 6:
			mTracer->run(TARGET, 1, 17);
			if (mColorJudge->isColorRGB() != 0) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 0;
				return true;
			}
			break;
	}
}
