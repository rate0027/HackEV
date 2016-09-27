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
		OBJECT,
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
	int Color;					//Color比較用変数
	int count = 0;				//何回移動したかのテスト用++してつかう
	int flag = 0;				//pos_run--state
	int patt = 1;				//
	int check = 1;			//bl_ch--state
	int X = 1;				//現在X
	int Y = 2;				//現在Y
	int Z	= 1;				//現在方向Z
	int nX,nY;		//nextX,nextYまでsのdistance
	int p=0,n=0;		//block_point,block_nummber
	int bxy[4][2] = {	{3,1},		//{point,nummber}_Blockの場所
							{2,2},
							{3,3},
							{4,4}}	;

	int watcher(int, int);
	int pos_run(int, int);
	bool bl_ch();
	bool thr_bl(void);
	
};


#endif // EV3_APP_CONTROLER_H_
