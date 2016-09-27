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
#include "Clock.h"


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
			ColorJudge* colorJudge
				);
	void init();
	void terminate();
	void run();
	

/* 内部だけで動かす部分を記述 */
private:
	enum State{
		UNDEFINED,
		WAITING_FOR_START,
		WALKING,
		COLOR,
		STOP
	};
	
	Clock clock;

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
	int flag=0;
	
	int pos_run(int, int);
};


#endif // EV3_APP_CONTROLER_H_
