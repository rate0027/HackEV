#include "TimeDetection.h"

/* コンストラクタ */
TimeDetection::TimeDetection() {
}

/* 時間判断
 * @time : 設定時間(msec) */
bool TimeDetection::isOver(uint32_t time) const{
	if (time < clock.now()) {
		return true;
	} else {
		char str1[128]={0};
		sprintf(str1, "time is: %u", clock.now());
		msg_f(str1,2);
		return false;
	}

}

/* 経過時間をリセットする関数
 * isOverを使う前のステートで使用 */
void TimeDetection::reset() {
  clock.reset();
}

