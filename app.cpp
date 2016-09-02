#include "app.h"

#include "Controler.h"

using namespace ev3api;

//Device objects
ColorSensor	gColorSensor(PORT_2);
//GyroSensor	gGyroSensor(PORT_4);
TouchSensor gTouchSensor(PORT_1);
SonarSensor	gSonarSensor(PORT_3);
Motor		gLeftWheel(PORT_C);
Motor		gRightWheel(PORT_B);
Motor		gTailWheel(PORT_D);
Motor		gArm(PORT_A);

/* インスタンスの作成 */
static Controler *gControler;
static Prelude *gPrelude;
static ColorJudge *gColorJudge;
static ObjectDetection *gObjectDetection;
static TimeDetection *gTimeDetection;
static Tracer *gTracer;
static distance *gdistance;
static Ar *gAr;


static void user_system_create() {
	tslp_tsk(2);

	gPrelude = new Prelude(gTouchSensor,
												 gColorSensor);
	gColorJudge = new ColorJudge(gColorSensor);
  gdistance = new distance(gLeftWheel,
                           gRightWheel);
  	gAr = new Ar(gArm);
	gObjectDetection = new ObjectDetection(gSonarSensor);
	gTimeDetection = new TimeDetection();
	gTracer = new Tracer(gColorSensor,
											 gLeftWheel,
											 gRightWheel,
											 gTailWheel,
							gArm);
	gControler = new Controler(gTracer,
														 gPrelude,
														 gObjectDetection,
														 gTimeDetection,
														 gColorJudge,
                             gdistance,
                             gAr);

	ev3_led_set_color(LED_ORANGE);
}

static void user_system_destroy() {
	gLeftWheel.reset();
	gRightWheel.reset();
	gTailWheel.reset();
  gArm.reset();

	delete gPrelude;
	delete gColorJudge;
  delete gdistance;
  delete gAr;
	delete gObjectDetection;
	delete gTimeDetection;
	delete gTracer;
	delete gControler;
}



/* 周期ハンドラ */
void tracer_cyc(intptr_t exinf) {
    act_tsk(TRACER_TASK);
}

/* ロボットを走らせるタスク */
void tracer_task(intptr_t exinf) {
  if (ev3_button_is_pressed(LEFT_BUTTON)) {
    wup_tsk(MAIN_TASK);         // 左ボタン押下でメインを起こす
  } else {
	  gControler->run();               // 走行
	}
  ext_tsk();
}

/* メインタスク */
void main_task(intptr_t unused) {
	user_system_create();
	gControler->init();
	ev3_sta_cyc(TRACER_CYC);
	slp_tsk();                    // 起きたら、走行をやめる
  ev3_stp_cyc(TRACER_CYC);
  gControler->terminate();
	user_system_destroy();
	ext_tsk();
}
