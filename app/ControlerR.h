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
        CALC,
        MOVE_R,
        MOVE_BL,
        MOVE_CALC,
        BLOCK_SERCH,
		DIRECT_R,
		DIRECT_L,
		BLOCK_CHECK,
        BLOCK_RESULT,
		THROUGH,
		TRACE,
        CH_R,
        CH_L,
        TRACE_R,
        TRACE_F,
        THROUGH_BLOCK,
        POSITHON_RUN,
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
    int flag = 0;
    int count = 0;
    int Color;
    int i;
    int exitCount = 0;
    int blCheck = 0;
    int blColor = 0; //when robot move x-direction is true
    char test[];
    /* now Robot Point and ditection */
    int x = 1, y = 2, z = 1;
    
    
    /****************************/
    /* block set point          */
    /* 確認するときはX{x,0},Y{y,1}*/
    /***************************/
    int xy[4][2] = {  {3, 2},
                    {1, 2},
                    {2, 3},
                    {2, 1} };
    
    int p = 0;
    
    /* robot move distance (1 direction!) */
    int distance = 0;
	
	bool rStart(void);
	bool rSET(void);
	bool rSortThrough(void);
	bool rCorse(void);
    bool pos_run(int);
    bool thr_bl(void);
	bool bl_ch(void);
	bool ch_dirL(void);
	bool ch_dirR(void);
    bool rEXIT(void);
    bool rBasic(void);

};


#endif // EV3_APP_CONTROLER_H_
