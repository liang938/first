#include "headfile.h"
#include "Encoder.h"

void Init_all(void)
{
	WTST = 0;						//设置程序代码等待参数，赋值为0可将CPU执行程序的速度设置为最快  
	DisableGlobalIRQ();				//关闭总中断
	sys_clk = 35000000;				//设置系统频率为35MHz
	board_init();					//初始化寄存器

//OLED初始化
	oled_init();					//初始化oled屏幕
	
//定时器初始化
	pit_timer_ms(TIM_4, 10);		//配置定时器4，5ms进一次中断，用于读取、调整速度
//编码器初始化
	ctimer_count_init(CTIM0_P34);	//定时器外部计数模式--右轮
	ctimer_count_init(CTIM3_P04);	//定时器外部计数模式--左轮

	
}

void main(void)
{
	Init_all();

	//总中断最后开启
	EnableGlobalIRQ();		//开启总中断
    while(1)
	{
		oled_p8x16str(0,0,"Enc:");							//main文件中的变量
		oled_printf_float(0,2,Enc_L,2,3);
		oled_printf_float(0,4,Enc_R,2,3);
    }
}



