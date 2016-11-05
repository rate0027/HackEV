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
        //mState = STEP7;
			}
			ev3_led_set_color(LED_ORANGE);
            mTimeDetection->reset();
			break;
		case WALKING: //初めの直線
			msg_f("running...", 1);
			mTracer->run(TARGET,0,35,35);
			if (mDistanceDetection->left(3550)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				mState = STEP2;
			}
			break;
		case STEP2: //カーブ
			msg_f("running...", 1);		
			mTracer->run(TARGET,0,20,20);
			if (mDistanceDetection->left(1450)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				mState = STEP3;
			}
			break;
		case STEP3: //直線 
			msg_f("running...", 1);		
			mTracer->run(TARGET,0,30,30);
			if (mDistanceDetection->left(1650)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				mState = STEP4;
			}
			break;
		case STEP4: //カーブからラインチェンジ直前まで
			msg_f("running...", 1);		
			mTracer->run(TARGET,0,25,25);
			if (mDistanceDetection->left(2300)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				mState = STEP5;
			}
			break;
		case STEP5: //反対側のラインへ移動
			msg_f("running...", 1);		
			mTracer->NLT(25,9);
			if (mDistanceDetection->left(100)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				mState = STEP6;
			}
			break;
		case STEP6: //ライン復帰
			msg_f("running...", 1);		
			mTracer->run(TARGET,0,25,25);
			
			if (mDistanceDetection->left(2600)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				mState = STEP7;
			}
			break;
		case STEP7: //星取りまで
			msg_f("running...", 1);		
			mTracer->run(TARGET,0,15,15);
			if ((star =  (mColorJudge->isColorRGB())) > 0) {
				ev3_speaker_play_tone(NOTE_D5, 10);
                mTimeDetection->reset();
				mDistanceDetection->reset();
				mState = STEPC0;
			}
			break;
		case STEP8: //バック
						msg_f("running...", 1);
            mTracer->NLT(0,0);
            if (mTimeDetection->isOver(500)) {
                ev3_speaker_play_tone(NOTE_D5, 10);
                mTimeDetection->reset();
				mState = STEP9;
			}
			break;
		case STEP9: //若干停止
            msg_f("running...", 1);
            mTracer->NLT(20,-19);
            if (mDistanceDetection->right(200)) {
                ev3_speaker_play_tone(NOTE_D5, 10);
                mDistanceDetection->reset();
				mState = STEP10;
			}
			break; 
		case STEP10: //反対側のラインへ移動
			msg_f("running...", 1);		
			mTracer->NLT(10,10);
			if (mDistanceDetection->right(220)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
				mState = STEP11;
			}
			break;
		case STEP11: //相撲の前まで移動
			msg_f("running...", 1);		
			mTracer->run(TARGET,1,15,15);
			if (mDistanceDetection->left(1650)) {
				ev3_speaker_play_tone(NOTE_D5, 10);
                mTimeDetection->reset();
				mState = STOP;
			}
			break;
        case STEP12: //ちょっと休憩
            msg_f("running...", 1);
            mTracer->NLT(0,0);
            if (mTimeDetection->isOver(500)) {
                ev3_speaker_play_tone(NOTE_D5, 10);
                mDistanceDetection->reset();
                mState = STEP13;            }
            break;
        case STEP13: //電車を検知するまで停止
            mTracer->NLT(0,0);
            if (mObjectDetection->isObject(20)) {
                ev3_speaker_play_tone(NOTE_D5, 10);
                mTimeDetection->reset();
                mState = STEP14;
            }
            break;
        case STEP14: //電車が通りすぎるまでwait
            mTracer->NLT(0,0);
            if (mTimeDetection->isOver(1000)) {
                mTimeDetection->reset();
                ev3_speaker_play_tone(NOTE_D5, 10);
                mState = STEP15;
            }
            break;
        case STEP15: //相撲エリアに侵入
            msg_f("running...", 1);
            mTracer->NLT(6,6);
            if (mTimeDetection->isOver(2500)) {
                mDistanceDetection->reset();
                ev3_speaker_play_tone(NOTE_D5, 10);
                mState = STEP16;
            }
            break;
        case STEP16: //相撲エリアに侵入(加速用バック)
            msg_f("running...", 1);
            mTracer->NLT(-10,-10);
            if (mDistanceDetection->left(-50)) {
                ev3_speaker_play_tone(NOTE_D5, 10);
                mState = STEP17;
            }
            break;
        case STEP17: //相撲エリアに侵入(侵入)
            msg_f("running...", 1);
            mTracer->NLT(50,50);
            if (mDistanceDetection->left(100)) {
                ev3_speaker_play_tone(NOTE_D5, 10);
                mState = STEPUP;
            }
        case STEPUP: //相撲エリアに侵入(侵入2)
            msg_f("running...", 1);
            mTracer->NLT(100,100);
            if (mDistanceDetection->left(200)) {
                mTimeDetection->reset();
                ev3_speaker_play_tone(NOTE_D5, 10);
                mState = STEP18;
            }
            break;
        case STEP18: //制御が落ち着くまで待機（動いてなさそう）
            msg_f("running...", 1);
            mTracer->NLT(0,0);
            if (mTimeDetection->isOver(5000)) {
                ev3_speaker_play_tone(NOTE_D5, 10);
                mState = STEP19;
            }
        case STEP19: //円を検知するまで進む
            msg_f("running...", 1);
            mTracer->run((int)(TARGET*0.98),0, 10,10);
            if ((star =  mColorJudge->isColor()) > 0) {
                mTimeDetection->reset();
                ev3_speaker_play_tone(NOTE_D5, 10);
                mState = STEP20;
            }
            break;
        case STEP20: //星の色と一致すれば22へ、しなければ21へ
            msg_f("running...", 1);
            mTracer->NLT(0,0);
            if (mTimeDetection->isOver(1000)) {
                mDistanceDetection->reset();
                ev3_speaker_play_tone(NOTE_D5, 10);
                if(color1 == (mColorJudge->isColor())){
                    mState = STEP22;
                }else{
                    mState = STEP21;
                }
            }
            break;
        case STEP21: //押し出し
            msg_f("running...", 1);
            mTracer->NLT(10,10);
            if (mDistanceDetection->left(180)) {
                ev3_speaker_play_tone(NOTE_D5, 10);
                mState = STEP23;
            }
            break;
        case STEP22: //バック
            msg_f("running...", 1);
            mTracer->NLT(-10,-10);
            if (mDistanceDetection->left(-100)) {
                ev3_speaker_play_tone(NOTE_D5, 10);
                mState = STEP24;
            }
            break;
        case STEP23: //大きくバック（押し出した後用）
            msg_f("running...", 1);
            mTracer->NLT(-10,-10);
            if (mDistanceDetection->left(-280)) {
                ev3_speaker_play_tone(NOTE_D5, 10);
                mState = STEP24;
            }
            break;
        case STEP24: //一回転
            msg_f("running...", 1);
            mTracer->NLT(-10,10);
            if (mDistanceDetection->left(300)) {
                mTimeDetection->reset();
                ev3_speaker_play_tone(NOTE_D5, 10);
                mState = STEP25;
            }
            break;
        case STEP25: //待機（動いてなさそう）
            msg_f("running...", 1);
            mTracer->NLT(0,0);
            if (mTimeDetection->isOver(5000)) {
                mDistanceDetection->reset();
                ev3_speaker_play_tone(NOTE_D5, 10);
                mState = STEP26;
            }
						break;
        case STEP26: //ライントレース（動いてなさそう）
            msg_f("running...", 1);
            mTracer->runL(TARGET,15,15);
            if (mDistanceDetection->left(100)) {
                mTimeDetection->reset();
                ev3_speaker_play_tone(NOTE_D5, 10);
                mState = STOP;
            }
						break;
        case STEP27: //円を検知するまでライントレース（動いてなさそう）
            msg_f("running...", 1);
            mTracer->runL(TARGET*0.98, 10,10);
            if ((star =  mColorJudge->isColor()) > 0) {
                mDistanceDetection->reset();
                mTimeDetection->reset();
                ev3_speaker_play_tone(NOTE_D5, 10);
                mState = STEP28;
            }
						break;
        case STEP28: //STEP20の処理と同じ（仮）
            msg_f("running...", 1);
            mTracer->NLT(0,0);
            if (mTimeDetection->isOver(1000)) {
                mTimeDetection->reset();
                ev3_speaker_play_tone(NOTE_D5, 10);
                if(color1 == (mColorJudge->isColor())){
                    mState = STEP22;
                }else{
                    mState = STEP21;
                }
            }
						break;
        case STEPC0: //色を判定する
            msg_f("running...", 1);
            mTracer->NLT(0,0);
            if (mTimeDetection->isOver(1000)) {
                if((mColorJudge->isColor()) == (1)){
                    //color1 = 1;
                    color1 = mColorJudge->isColor();
                    mState = STEP9;break;
                }
                else if((mColorJudge->isColor()) == (2)){
                    //color1 = 2;
                    color1 = mColorJudge->isColor();
                    mState = STEP9;break;
                }
                else if((mColorJudge->isColor()) == (3)){
                    //color1 = 3;
                    color1 = mColorJudge->isColor();
                    mState = STEP9;break;
                }
                else if((mColorJudge->isColor()) == (4)){
                    //color1 = 4;
                    color1 = mColorJudge->isColor();
                    mState = STEP9;break;
                }
                else if((mColorJudge->isColor()) == (5)){
                    //color1 = 5;
                    color1 = mColorJudge->isColor();
                    mState = STEP9;break;
                }
                else if((mColorJudge->isColor()) == 6){
                    //color1 = 6;
                    color1 = mColorJudge->isColor();
                    mState = STEP9;break;
                }
                mDistanceDetection->reset();
                mState = STEP9;
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

