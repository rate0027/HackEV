#include "DistanceDetection.h"


DistanceDetection::DistanceDetection(Motor& leftWheel,
													           Motor& rightWheel,
											               Motor& tailWheel,
									                   Motor& arm)
: mLeftWheel(leftWheel),
	mRightWheel(rightWheel),
	mTailWheel(tailWheel),
	mArm(arm) {
}


bool DistanceDetection::left(int dist) {
	float count = (float)(mLeftWheel.getCount());
	if (dist > 0) {
		if (count >= dist ) {
			mLeftWheel.setCount(0);
			return true;
		} else {
			return false;
		}
	} else {
		if (count <= dist ) {
			mLeftWheel.setCount(0);
			return true;
		} else {
			return false;
		}
	}

}

bool DistanceDetection::right(int dist) {
	float count = (float)(mRightWheel.getCount());
	if (dist > 0) {
		if (count >= dist ) {
			mRightWheel.setCount(0);
			return true;
		} else {
			return false;
		}
	} else {
		if (count <= dist ) {
			mRightWheel.setCount(0);
			return true;
		} else {
			return false;
		}
	}

}


void DistanceDetection::reset() {
	mLeftWheel.setCount(0);
	mRightWheel.setCount(0);
}
