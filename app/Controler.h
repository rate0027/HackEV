#ifndef EV3_APP_CONTROLER_H_
#define EV3_APP_CONTROLER_H_

#include "Tracer.h"
#include "Starter.h"
#include "ObjectDetection.h"
#include "util.h"
#include "Clock.h"


/* クラスの宣言 */
class Controler {
/* 外から触れる部分を記述 */
public:
  /* publicメソッドの宣言
	 * メソッドの詳細はcppを参照 */
	Controler(Tracer* tracer,
			const Starter* starter,
			ObjectDetection* objectDetection);
	void init();
	void terminate();
	void run();


/* 内部だけで動かす部分を記述 */
private:
	enum State{
		UNDEFINED,
		WAITING_FOR_START,
		WARKING,
		OBJECT_DETECTION
	};
	
	Clock clock;

	Tracer* mTracer;
	const Starter* mStarter;
	ObjectDetection* mObjectDetection;
	State mState;

};


#endif // EV3_APP_CONTROLER_H_
