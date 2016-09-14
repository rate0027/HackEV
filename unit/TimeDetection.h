#ifndef EV3_UNIT_TIMEDETECTION_H_
#define EV3_UNIT_TIMEDETECTION_H_

/* センサを使う場合はincludeが必要*/
#include "Clock.h"
#include "util.h"

using namespace ev3api;

/* クラスの宣言 */
class TimeDetection {
public:
  explicit TimeDetection();
	bool isOver(uint32_t) const;
	void reset();

private:
  Clock clock; 
};


#endif // EV3_UNIT_TIMEDETECTION_H_
