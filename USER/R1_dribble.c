#include "R1_dribble.h"
#include "motorctrl.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "gpio.h"
extern motor_measure_t *motor_data_can1[8];
extern motor_measure_t *motor_data_can2[8];
extern motor_measure_t *motor_data_can3[8];
void dribbling_init(void){//PID参数

}
void going_up(void){

    while(!(motor_data_can3[6]->circle>CIRCLES_UP)) 
		{
				rtU.status_CH3_7=1;
        set_target(3,7,2000);
		};
	
		rtU.status_CH3_7=2;
		set_target(3,7,8191*CIRCLES_UP);
        
}
void dribbling(void){
				rtU.status_CH3_7=2;
        set_target(3,5,-8191*CIRCLES_OPEN); //开爪，圈数待测
        set_target(3,7,10*8191); //降，圈数待测
        HAL_GPIO_WritePin(SOLENOID_VALVE_GPIO_Port, SOLENOID_VALVE_Pin, GPIO_PIN_RESET);
        osDelay(SOLENOID_VALVE_TIME);
        HAL_GPIO_WritePin(SOLENOID_VALVE_GPIO_Port, SOLENOID_VALVE_Pin, GPIO_PIN_SET);
        osDelay(TOTAL_WAIT_TIME-SOLENOID_VALVE_TIME);								//延时待测
        set_target(3,5,0); //合爪
    // }else{
    //     loading();
//    }
}

void loading(void){
    set_target(3,6,LOAD_POSITION);//升降至合适高度
    set_target(3,7,LOAD_ANGLE);//爪子下翻递球
    osDelay(500);
    set_target(1,6,8191*CIRCLES_UP);//升降至最高位，不影响投球
    set_target(3,7,0);//爪子归位
}
