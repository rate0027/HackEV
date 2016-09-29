#ifndef EV3_APP_CONTROLER_H_
#define EV3_APP_CONTROLER_H_

#include "Tracer.h"
#include "Ar.h"
#include "Prelude.h"
#include "ObjectDetection.h"
#include "TimeDetection.h"
#include "HitDetection.h"
#include "DistanceDetection.h"
#include "ColorJudge.h"
#include "util.h"


/* クラスの宣言 */
class Controler {
/* 外から触れる部分を記述 */
public:
  /* publicメソッドの宣言
	 * メソッドの詳細はcppを参照 */
	Controler(Tracer* tracer,
      Ar* ar,
			Prelude* prelude,
			ObjectDetection* objectDetection,
			TimeDetection* timeDetection,
			HitDetection* hitDetection,
			DistanceDetection* distanceDetection,
			ColorJudge* colorJudge);
	void init();
	void terminate();
	void run();


/* 内部だけで動かす部分を記述 */
private:
	enum State{
		UNDEFINED,
		WAITING_FOR_START,
		WALKING,
		STEP2,
		STEP3,
		STEP4,
		STEP5,
		STEP6,
		STEP7,
		STEP8,
		STEP9,
		STEP10,
		STEP11,
        STEP12,
        STEP13,
        STEP14,
        STEP15,
        STEP16,
        STEP17,
        STEP18,
        STEP19,
        STEP20,
        STEP21,
        STEP22,
        STEP23,
        STEP24,
        STEP25,
        STEP26,
        STEP27,
        STEP28,
        STEPC0,
        STEPUP,
		STOP
	};
	
	Tracer* mTracer;
  Ar* mAr;
	Prelude* mPrelude;
	ObjectDetection* mObjectDetection;
	TimeDetection* mTimeDetection;
	HitDetection* mHitDetection;
	DistanceDetection* mDistanceDetection;
	ColorJudge* mColorJudge;
	State mState;
	int TARGET = 0;
	int star = 0;
    int color1 = 0;

};


#endif // EV3_APP_CONTROLER_H_
