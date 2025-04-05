#ifndef R1_DRIBBLE_H
#define R1_DRIBBLE_H

#include "main.h"
#include "fdcan.h"
#include "tim.h"
#include "gpio.h"

#define SOLENOID_VALVE_PIN GPIO_PIN_2  //	电磁阀的引脚，待分配
#define SOLENOID_VALVE_PORT GPIOB //			电磁阀的引脚，待分配
#define SOLENOID_VALVE_TIME 200 //				电磁阀开和闭之间的延时，不重要
#define TOTAL_WAIT_TIME 600 //						放爪子到合爪子的总时间，待测
#define CIRCLES_OPEN 24 // 								开爪子圈数，待测
#define LOAD_POSITION 8191*10 //					能把球放到发射机构上的位置，待测
#define CIRCLES_UP 38 //									导轨上到顶的圈数，待测
#define LOAD_ANGLE -8191*10 //						上弹时爪子往下翻的角度，待测


void dribbling_init(void); //初始化，里面调用了电磁阀初始化

uint8_t dribbling(void); //运球时循环调用该函数，返回1说明运了一次球了，break掉

void loading(void);//上弹

#endif
