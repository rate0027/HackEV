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
		WATCH,
		POS_1,
		POS_2,
		POS_3,
		MOVE0,
		MOVE1,
		MOVE2,
		MOVE3,
		MOVE4,
		MOVE5,
		MOVE6,
		MOVE7,
		MOVE8,
		MOVE9,
		MOVE10,
		MOVE11,
		MOVE12,
		MOVE13,
		MOVE14,
		MOVE15,
		MOVE16,
		MOVE17,														
		DIRECT_R,
		DIRECT_L,
		BLOCK_CHECK,
		THROUGH,
		TRACE,
		EXIT,
		START,
		SET,
#if 0
		TRACE,
#endif
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
	int count = 0;
	int sCount = 0;		//こっから
	int check = 0;
	int Color;
	int flag_ch =0;
	
	
	bool lBasic(void);
	bool rStart(void);
	bool rSET(void);
	bool rBasic(void);
	bool rSortThrough(void);
	bool rCorse(void);
	bool thr_bl(void);
	bool pos_run(int);					//こっから足したとこ
	bool bl_ch(void);
	bool rEXIT(void);
	bool ch_dirL(void);
	bool ch_dirR(void);
	int pos_X(int);
	
};


#endif // EV3_APP_CONTROLER_H_
