#include "headfile.h"


extern PID_InitTypeDef PID_Servos;		//舵机PID结构体变量	

void Init_all()
{
	WTST = 0;							//设置程序代码等待参数，赋值为0可将CPU执行程序的速度设置为最快  
	DisableGlobalIRQ();		//关闭总中断
	sys_clk = 35000000;		//设置系统频率为35MHz
  board_init();					//初始化寄存器
	pit_timer_ms(TIM_4, 10);								//配置定时器4，5ms进一次中断，用于读取、调整速度

//pid初始化  PID_Init(结构体, KP, KI, KD, 输出限幅, 积分限幅)
	PID_Init(&PID_Servos, 0, 0, 0, 0, 0);					//舵机PID初始化

	delay_ms(500);

	EnableGlobalIRQ();		//开启总中断
}