#include "headfile.h"
#include "pid.h"
/*
 *关于内核频率的设定，可以查看board.h文件
 *在board_init中,已经将P54引脚设置为复位
 *如果需要使用P54引脚,可以在board.c文件中的board_init()函数中删除SET_P54_RESRT即可
 */

void main()
{
  WTST = 0;               //设置程序代码等待参数，赋值为0可将CPU执行程序的速度设置为最快
	DisableGlobalIRQ();		//关闭总中断
	sys_clk = 35000000;     //设置系统频率为35MHz   
	board_init();			//初始化寄存器
	//总中断最后开启
	EnableGlobalIRQ();		//开启总中断
	//pwm_init(PWMB_CH1_P74, 50, 0);		//舵机
	while(1)
	{
			//pwm_duty(PWMB_CH1_P74,750);
	}
}

