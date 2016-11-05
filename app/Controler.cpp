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
				mState = STEP1;
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
			  mState = TRACE;
			}
			break;
		case TRACE:
			if ( rBasic() ) {
				mState = STOP;
			}
			break;
#endif
/*-------- 懸賞 --------*/
		case STEP1:
			msg_f("Running...", 1);
			mTracer->run(TARGET,0,15,15);
			if (mObjectDetection->isObject(10) ) {
				mState = STEP2;
			}
			break;
		case STEP2:
			mTracer->NLT(0,0);
			if (mAr->armDown(-17)) {
				mState = STEP3;
				mDistanceDetection->reset();
			}
			break;
		case STEP3:
			mTracer->NLT(10,10);
			if (mDistanceDetection->left(200) ) {
				mState = STEP4;
			}
			break;
		case STEP4:
			mTracer->NLT(0,0);
			if (mAr->armUp(60)) {
				mState = STEP5;
				mDistanceDetection->reset();
			}
			break;
		case STEP5:
			mTracer->NLT(10,-10);
			if (mDistanceDetection->left(-160)) {
				mState = STEP6;
			}
			break;
		case STEP6:
			mTracer->NLT(10,10);
			if (mDistanceDetection->left(600)) {
				mState = STEP7;
			}
			break;
		case STEP7:
			mTracer->NLT(10,-10);
			if (mDistanceDetection->left(-73)) {
				mState = STEP8;
			}
			break;
		case STEP8:
			mTracer->NLT(15,15);
			if (mDistanceDetection->left(4200)) {
				mState = STOP;
			}
			break;
/*------------------------------*/
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
			mTracer->run(TARGET, 0, 30, 30);
			if (mDistanceDetection->left(3900)) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 1;
				return false;
			}
			break;
		case 1: //カーブ
			msg_f("running...", 1);		
			mTracer->run(TARGET, 0, 15, 15);
			if (mDistanceDetection->left(1600)) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 2;
				return false;
			}
			break;
		case 2: //直線 
			msg_f("running...", 1);		
			mTracer->run(TARGET, 0, 30, 30);
			if (mDistanceDetection->left(1500)) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 3;
				return false;
			}
			break;
		case 3: //カーブからラインチェンジ直前まで
			msg_f("running...", 1);		
			mTracer->run(TARGET, 0, 16, 16);
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
			mTracer->run(TARGET, 0, 18, 18);
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
			mTracer->run(TARGET, 1, 13, 13);
			if (mDistanceDetection->left(700)) {
				mDistanceDetection->reset();
				ev3_speaker_play_tone(NOTE_D5, 10);
				flag = 1;
				return false;
			}
			break;
		case 1:
			mTracer->NLT(10, -10);
			if (mDistanceDetection->right(137)) {
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
			mTracer->NLT(15,15);
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
			mTracer->run(TARGET, 1, 30,30);
			if(mDistanceDetection->left(1400)) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 1;
				return false;
			}
			break;
		case 1:
			mTracer->run(TARGET, 1, 20,20);
			if (mDistanceDetection->left(850)) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 2;
				return false;
			}
			break;
		case 2:
			mTracer->run(TARGET, 1, 30,30);
			if (mDistanceDetection->left(1700)) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 3;
				return false;
			}
			break;
		case 3:
			mTracer->run(TARGET, 1, 15,15);
			if (mDistanceDetection->left(1050)) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 4;
				return false;
			}
			break;
		case 4: 
			mTracer->run(TARGET, 1, 30,30);
			if (mDistanceDetection->left(1800)) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 5;
				return false;
			}
			break;
		case 5:
			mTracer->run(TARGET, 1, 15,15);
			if (mDistanceDetection->left(1250)) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 6;
				return false;
			}
			break;
		case 6: 
			mTracer->run(TARGET, 1, 30,30);
			if (mDistanceDetection->left(2800)) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 7;
				return false;
			}
			break;
		case 7:
			mTracer->run(TARGET, 1, 12,12);
			if (mDistanceDetection->left(800)) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 8;
				return false;
			}
			break;
		case 8:
			mTracer->run(TARGET, 1, 40,40);
			if (mColorJudge->isColorRGB() != 0) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 0;
				return true;
			}
			break;
	}
}

bool Controler::thr_bl(void) {

  switch(flag) {	
	case 0: //避けるために後ろに下がる
		mTracer->NLT(-15,-15);
		if (mDistanceDetection->left(-230)) {
			mDistanceDetection->reset();
			flag = 1;
			return false;
		}	
		break;
	case 1: 
		mTracer->NLT(18, -18);
		if (mDistanceDetection->right(100)) { 
			mTimeDetection->reset();
			flag = 2;
			return false;
		}
		break;
	case 2:
	 mTracer->NLT(15, 26); //10 18	
	 if (mTimeDetection->isOver(3000) ) {
		 flag = 3;
		 return false;
	 }
	 break;
	case 3:
	 mTracer->NLT(10, 18);	
	 if (mColorJudge->judgeBlack() ) {
			mDistanceDetection->reset();
		 flag = 4;
		 return false;
	 }
	 break;
	case 4: 
		mTracer->NLT(8, -10);
		if (mDistanceDetection->left(-30)) {
			flag = 5;
			return false;
		}
		break;
	case 5: 
		mTracer->NLT(10, 0);
		if (mDistanceDetection->right(70)) {
			flag = 0;
			return true;
		}
		break;
	}
}
