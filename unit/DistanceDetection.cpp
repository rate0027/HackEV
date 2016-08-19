#include "DistanceDetection.h"


DistanceDetection::DistanceDetaction(Motor& leftMotor,
																		 Motor& rightMotor)
	: mLeftMotor(leftMotor),
	  mRightMotor(rightMotor) {
}


bool DistanceDetection::left(int dist) {
	int onerotate = 24;
	float num = dist/24;
	/* 目標角設定 */
  float target = 360 * num;  

	int Conut = mLeftMotor.getCount();
	if (Count >= target) {
    return 1;
	} else {
    return 0;
	}

}


bool DistanceDetection::right(int dist) {

}
