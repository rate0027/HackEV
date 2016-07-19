#include "Tracer.h"

Tracer::Tracer():
  leftWheel(PORT_C), rightWheel(PORT_B),
  colorSensor(PORT_2) {
}

void Tracer::init() {
}

void Tracer::terminate() {
  leftWheel.stop();
  rightWheel.stop();
}

void Tracer::run() {
	const float Kp = 0.83; /* 0.63 */
	const int target = 25;
	const int bias = 0;

	int diff = colorSensor.getBrightness() - target;
	float turn = Kp * diff + bias;
	leftWheel.setPWM(pwm - turn);
	rightWheel.setPWM(pwm + turn);
}
