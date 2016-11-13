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
				mState = START;
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

		case START:
			msg_f("starting!!!", 1);
			if (rStart() == true) {
			  mState = SET;
			}
			break;

		case SET:
			if(rSET() == true){
				mState = WALKING;
			}
			break;
		case WALKING:
				msg_f("running...", 1);
				mTracer->run(TARGET, 1,20,20);
				if(mColorJudge->isColorRGB() != 0){
				  mDistanceDetection->reset();
				  mState = MOVE1;
				}
			break;	

		case MOVE1:
			msg_f("THROUGH",2);
			if(thr_bl() == true){
				  mDistanceDetection->reset();
					mState = MOVE2;
			}
			break;	
	
		case MOVE2:
			msg_f("LT_MOVE2",2);
				mTracer->run(TARGET,1,20,20);
				if(mColorJudge->isColorRGB() != 0){
				  mDistanceDetection->reset();
					mState = MOVE3;	
				}
			break;

		case MOVE3:
			msg_f("DIRECT_L_1st",2);
			if(ch_dirL() == true){
				  mDistanceDetection->reset();
				mState = MOVE4;
			}
			break;

		case MOVE4:
			msg_f("LT_MOVE4",2);
				mTracer->run(TARGET,1,20,20);
				if(mColorJudge->isColorRGB() != 0){
				  mDistanceDetection->reset();
					mState = MOVE5;	
				}
			break;
		case MOVE5:
			msg_f("POSLAN",2);
			if(pos_run(TARGET) == true){
				mTracer->run(TARGET,1,20,20);
				if(mColorJudge->isColorRGB() != 0){
				  mDistanceDetection->reset();
					mState = MOVE6;	
				}
			}
			break;
		case MOVE6:
			msg_f("BLOCK_CHECK",2);
			if(bl_ch() == true){
				  mDistanceDetection->reset();
					mState = MOVE8;
			}
			break;	
			
			break;
		case MOVE8:
			msg_f("DIRECT_Left",2);
			if(ch_dirL() == true){
			  mDistanceDetection->reset();
				mState = MOVE9;
			}
			break;		
		case MOVE9:
				mTracer->run(TARGET,1,20,20);
				if(mColorJudge->isColorRGB() != 0){
				  mDistanceDetection->reset();
					mState = MOVE10;	
				}
			break;
		case MOVE10:
			msg_f("DIRECT_Left",2);
			if(ch_dirL() == true){
				  mDistanceDetection->reset();
					mState = MOVE11;	
				}
				break;
		case MOVE11:
				mTracer->run(TARGET,1,20,20);
				if(mColorJudge->isColorRGB() != 0){
				  mDistanceDetection->reset();
					mState = MOVE12;	
				}
				break;
	
/*
		case MOVE9:
			msg_f("DIRECT_L",2);
			if(ch_dirL() == true){
				sCount = 6;
				mState = MOVE10;
			}
			break;

		case MOVE10:	
			msg_f("2pos",2);
			if(pos_run(TARGET) == true){
				//sCount = 2;
				mTracer->run(TARGET,1,20,20);
				if(mColorJudge->isColorRGB() != 0){
					mState = MOVE11;	
				}
			}
			break;	
		case MOVE11:
			msg_f("2pos",2);
			if(pos_run(TARGET) == true){
				//sCount = 2;
				mTracer->run(TARGET,1,20,20);
				if(mColorJudge->isColorRGB() != 0){
					mState = MOVE12;	
				}
			}
			break;		
	*/		
		case MOVE12:
			msg_f("EXIT_R",2);
			mTracer->NLT(-15,-15);
			if (mDistanceDetection->left(-230)) {
				mDistanceDetection->reset();
				mState = MOVE15;
			}	
			break;
			
			/*
		case MOVE13:
			mTracer->NLT(18,-18);
			if (mDistanceDetection->right(90)) {
				mDistanceDetection->reset();
				mState = MOVE16;
			}	
			break;
		
		case MOVE14:
			mTracer->NLT(18,18);
			if (mDistanceDetection->left(150)) {
				mDistanceDetection->reset();
				mState = MOVE15;
			}	
			break;
		*/
		case MOVE15:
			mTracer->NLT(18,-18);
			if (mDistanceDetection->left(-135)) {
				mDistanceDetection->reset();
				mState = MOVE16;
			}	
			break;

		case MOVE16: 
			
			if (rEXIT() == true) { 
				mTimeDetection->reset();
				mState = MOVE17;
			}
			break;
			
		case MOVE17:
			if(rBasic() == true){
				mState = STOP;
			}
			break;
			
			
    default:
  		break;
	}
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
bool Controler::rEXIT(void){
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
				if (++count == 1) {
					flag = 2;
					mDistanceDetection->reset();
				} else {
					flag = 0;
				}
				return false;
			}
			break;
		case 2:
			mTracer->NLT(10, 10);
			if (mDistanceDetection->left(105)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				flag = 3;
			}
			break;

		case 3:
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
bool Controler::rSET(void){
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
				if (++count == 1) {
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
			if (mDistanceDetection->left(2600)) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 7;
				return false;
			}
			break;
		case 7:
			mTracer->run(TARGET, 1, 12,12);
			if (mDistanceDetection->left(1000)) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 8;
				return false;
			}
			break;
		case 8:
			mTracer->run(TARGET, 1, 40,40);
			if (mDistanceDetection->left(2000)) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 9;
				return false;
			}
			break;
		case 9:
			mTracer->run(TARGET, 1, 20,20);
			if (mColorJudge->isColorRGB() != 0) {
				ev3_speaker_play_tone(NOTE_D5, 20);
				flag = 0;
				return true;
			}
			break;
	}
}

bool Controler::ch_dirR(void){
		switch(flag){		
			case 0:	//斜め方向に移動
				mTracer->NLT(-10,10);
				msg_f("turnRight",2);
					if (mDistanceDetection->left(60)) {
					mDistanceDetection->reset();
						flag = 1;
					}
					break;
			case 1:
				msg_f("run.CheckBlack.",2);
				mTracer->NLT(10, 18);	
				 if (mColorJudge->judgeBlack() ) {
					mDistanceDetection->reset();
					 flag = 2;
					}
					break;
			case 2:
				msg_f("Black_Checked.",2);
					mTracer->NLT(10, 0);
					if (mDistanceDetection->right(50)) {
						flag = 3;
					}
					break;
			case 3: 
					mTracer->NLT(10, 10);
					if (mDistanceDetection->right(50)) {
					flag = 0;
					return true;
					}
					break;
		}
}
bool Controler::ch_dirL(void){
		switch(flag){		
			case 0:	//斜め方向に移動
				mTracer->NLT(10,-10);
					if (mDistanceDetection->right(50)) {
					mDistanceDetection->reset();
						flag = 1;
					}
					return false;
					break;
			case 1:
				mTracer->NLT(10, 18);	
				 if (mColorJudge->judgeBlack() ) {
					mDistanceDetection->reset();
					 flag = 0;
					 return true;
					}
					break;
				default:
					flag = 0;
					return false;
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

bool Controler::bl_ch(void){
	switch(flag_ch){
		case 0:
			mTracer->NLT(-10,-10);
			if(mDistanceDetection->left(-120)){
				mDistanceDetection->reset();
				msg_f("NLT",1);
				flag_ch = 1;
				return false;
			}
			break;
		case 1:
			if(mAr->armUp() == true){
				msg_f("ArmUp",1);
				mAr->reset();
				flag_ch = 2;
				return false;
			}
			break;
		case 2:
			mTracer->NLT(10,10);
				msg_f("Foward_and_Judge",1);
				if((Color = mColorJudge->isColorRGB()) != 0){
				mDistanceDetection->reset();
				flag_ch = 4;
				return false;
				}
			 break;
		case 3:
				msg_f("JUDGE",1);
			if((Color = mColorJudge->isColorRGB()) != 0){
			mDistanceDetection->reset();
			 	flag_ch = 4;	
			 	return false;
			 }
			break;
		case 4:
			mTracer->NLT(-10,-10);
				msg_f("BACK",1);
			if(mDistanceDetection->left(-80)){
			mDistanceDetection->reset();
			flag_ch = 5;
			return false;
			}
			break;
		case 5:
				msg_f("DOWN",1);
			if(mAr->armDown() == true){
				mAr->reset();
				flag_ch = 6;
				return true;
			}
			break;
		default:
			break;
	}
}
bool Controler::pos_run(int target) {	
		mTracer->NLT(16,15);
		if (mDistanceDetection->left(150)) {
			mDistanceDetection->reset();
			return true;
		}
}

int Controler::pos_X(int x){
       		msg_f("POS_X",3);
			if(pos_run(TARGET) == true){
				if(++check == x){
					check =0;
					if(sCount ==1){
						sCount = 2;
						return 1;
					}else if(sCount ==4){
						sCount = 5;
						return 1;
					}else if(sCount == 6){
						sCount = 7;
						return 1;
					}
				}
			}
}
		