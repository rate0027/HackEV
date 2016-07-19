#include "app.h"

#include "Controler.h"

using namespace ev3api;

//Device objects
ColorSensor	gColorSensor(PORT_2);
//GyroSensor	gGyroSensor(PORT_4);
TouchSensor gTouchSensor(PORT_1);
Motor				gLeftWheel(PORT_C);
Motor				gRightWheel(PORT_B);

/* インスタンスの作成 */
static Controler *gControler;
static Starter *gStarter;
static Tracer *gTracer;

static void user_system_create() {
	tslp_tsk(2);

	gStarter = new Starter(gTouchSensor);
	gTracer = new Tracer(gColorSensor, 
											 gLeftWheel, 
											 gRightWheel);
	gControler = new Controler(gTracer,
														 gStarter);

	ev3_led_set_color(LED_ORANGE);
}

static void user_system_destroy() {
	gLeftWheel.reset();
	gRightWheel.reset();

	delete gStarter;
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
