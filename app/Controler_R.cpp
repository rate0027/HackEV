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
	int x=1,y=1,z=4;
	int i=0,f=0;
	int bxy[4][2] = {	{3,1},
							{2,2},
							{3,3},
							{4,4}}	;
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
/********************************************************			
			case WALKING:
			if (mObjectDetection->isPressed() <= 10){
				mState = OBJECT_DETECTION;
			} else {
				msg_f("running...", 1);
				mTracer->run(TARGET);
			}
			break;
		case OBJECT_DETECTION:
			if (mObjectDetection->isPressed() >= 11) {
				mState = WALKING;
			}else {
				msg_f("object_detection", 1);
				mTracer->terminate();
			}
			break;
**********************************************************/
/************************************************************ 追加した部分 Rコース用 */
/*座標,速度等はいじる必要あり*/
		case WALKING:
		{
			mTracer->run(TARGET);				/*難所内のLT.色発見したらスルーステートへ*/
			if(mColorJudge->isColor() != 0) {
				mState = BLOCK_THROUGH;
			}
		}
			break;
		case COLOR_THROUGH:					/*NLTを使ってちょっと進んでLTへ戻る*/
		{
			mTracer->NLT(10,10);
			if(mDistanceDetection->left(300)){
				ev3_speaker_play_tone(NOTE_D5, 10);
				mState = WALKING;	
			}
		}
			break;
		case BLOCK_THROUGH:				/*ブロック避ステート*/
		{
			mTracer->NLT(5,5);
			if(mDistanceDetection->left(400)){
				mState = CURVE;
			}
		}
			break;
		case CURVE:
		{
			mTracer->NLT(10,15);
			if(mDistanceDetection->left(300)){
				mState =  WALKING;
			}	
		}
			break;
/*		case DIRECTION_CHANGE:	//方向転換ステート.現在のzを取得してturnの長さを変えたい
		{
			if(bx < 0){
				
		}
			break;
		case POINT_SEARCH:
		{
			if(i =< 3 && f <= 1){
				bx = x - bxy[i][f];
				f ++;
				by = y - bxy[i][f];
			}else if(f > 1){
				mState = DIRECTION_CHANGE;
		}
			break;
*/
/*ここまで */			
		case STOP:
			msg_f("STOP", 1);
     		mTracer->terminate();
      		break;
    	default:
  			break;
	}
	
}

