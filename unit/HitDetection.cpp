#include "HitDetection.h"

/* コンストラクタ */
HitDetection::HitDetection(GyroSensor& gyroSensor)
	: mGyroSensor(gyroSensor) {
}

/* 衝突判断メソッド */
bool HitDetection::isCollision() {
  /* LCD出力 */
	char str1[128]={0};
	sprintf(str1, "Gyro A : %d", mGyroSensor.getAngle());
	msg_f(str1,2);
	char str2[128]={0};
	sprintf(str2, "Gyro V : %d", mGyroSensor.getAnglerVelocity());
	msg_f(str2,3);

	/* ファイル書き出し？ */
	logfile = fopen("log.txt", "a");
	if (logfile == NULL) {
    msg_f("cannot open", 2);
	}

	fprintf(logfile, "%d\n", mGyroSensor.getAnglerVelocity());

	/*if (mGyroSensor.getAnglerVelocity() > 500) {
	  return true;
	} else {
    return false;
	}*/

	fclose(logfile);
	return true;
}
