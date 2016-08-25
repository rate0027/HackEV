#ifndef EV3_APP_CONTROLER_H_
#define EV3_APP_CONTROLER_H_

#include "Tracer.h"
#include "Prelude.h"
#include "ObjectDetection.h"
#include "TimeDetection.h"
#include "util.h"
#include "ColorJudge.h"


/* クラスの宣言 */
class Controler {
/* 外から触れる部分を記述 */
public:
  /* publicメソッドの宣言
	 * メソッドの詳細はcppを参照 */
	Controler(Tracer* tracer,
			Prelude* prelude,
			ObjectDetection* objectDetection,
			TimeDetection* timeDetection,
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
		OBJECT_DETECTION,
		STOP,
		JUDGE_RED
	};
	
	Tracer* mTracer;
	Prelude* mPrelude;
	ObjectDetection* mObjectDetection;
	TimeDetection* mTimeDetection;
	ColorJudge* mColorJudge;
	State mState;
	int TARGET = 0;

};


#endif // EV3_APP_CONTROLER_H_
