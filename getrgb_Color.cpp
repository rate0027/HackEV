#include "ev3api.h"
#include "app.h"

#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif

#define color_sensor EV3_PORT_3

const unit32_t WAIT_TIME_MS = 100;

void run_task(intptr_t unused){

rgb_raw_t rgb_val;
char rstr[20];
char gstr[20];
char bstr[20];

while (1){
ev3_color_sensor_get_rgb_raw(color_sessor,&rgb_val);

sprintf(rstr, "R:%d ", rgb_val.r);
sprintf(gstr, "G:%d ", rgb_var.g);
sprintf(bstr, "B:%d ", rgb_var.b);

ev3_lcd_draw_string(rstr, 0, 0);
ev3_lcd_draw_string(gstr, 0, 20);
ev3_lcd_draw_string(bstr, 0, 40);

tslp_tsk(WAIT_TIME_MS);
}
}

void main_task(intptr_t unused) {

ev3_sensor_config( color_sensor , COLOR_SENSOR );

act_tsk(RUN_TASK);
}
