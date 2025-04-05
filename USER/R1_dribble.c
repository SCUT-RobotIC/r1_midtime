#include "R1_dribble.h"
#include "motorctrl.h"

void dribbling_init(void){//PID参数

}

uint8_t dribbling(void){
    uint8_t move=0;
//    if(flag){
    if(move){
				rtU.status_CH1_6=2;
        set_target(1,5,-8191*CIRCLES_OPEN); //开爪，圈数待测
        set_target(1,6,0); //降，圈数待测
        HAL_GPIO_WritePin(SOLENOID_VALVE_PORT, SOLENOID_VALVE_PIN, GPIO_PIN_SET);
        HAL_Delay(SOLENOID_VALVE_TIME);
        HAL_GPIO_WritePin(SOLENOID_VALVE_PORT, SOLENOID_VALVE_PIN, GPIO_PIN_RESET);
        HAL_Delay(TOTAL_WAIT_TIME-SOLENOID_VALVE_TIME);								//延时待测
        set_target(1,5,0); //合爪
        move=0;
				return 1;
    }else{
				rtU.status_CH1_6=1;
        set_target(1,6,2000);
        if(rtU.circle_CH1_6>CIRCLES_UP) {
            move=1;
            HAL_Delay(100);
        }
    }
		return 0;
    // }else{
    //     loading();
//    }
}

void loading(void){
    set_target(1,6,LOAD_POSITION);//升降至合适高度
    set_target(1,7,LOAD_ANGLE);//爪子下翻递球
    HAL_Delay(500);
    set_target(1,6,8191*CIRCLES_UP);//升降至最高位，不影响投球
    set_target(1,7,0);//爪子归位
}
