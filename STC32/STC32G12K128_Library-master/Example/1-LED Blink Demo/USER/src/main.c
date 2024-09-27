#include "headfile.h"

void main()
{
  WTST = 0;               //设置程序代码等待参数，赋值为0可将CPU执行程序的速度设置为最快  
	DisableGlobalIRQ();		//关闭总中断
  sys_clk = 35000000;     //设置系统频率为35MHz
	board_init();			//初始化寄存器
		pwm_init(PWMA_CH1P_P60, 15000, 0);		//左电机
	pwm_init(PWMA_CH2P_P62, 15000, 0);		//左电机-主控
	pwm_init(PWMA_CH3P_P64, 15000, 0);		//右电机
	pwm_init(PWMA_CH4P_P66, 15000, 0);		//右电机-主控
	EnableGlobalIRQ();		//开启总中断
  while(1)
	{
			pwm_duty(PWMA_CH1P_P60, 2000);		//设置左轮pwm
		pwm_duty(PWMA_CH2P_P62, 0);
		pwm_duty(PWMA_CH3P_P64, 0);
		pwm_duty(PWMA_CH4P_P66, 2000);		//设置右轮pwm
  }
}

