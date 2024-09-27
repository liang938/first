#include "headfile.h"

extern PID_InitTypeDef PID_Left;			//左轮PID结构体变量	
extern PID_InitTypeDef PID_Right;			//右轮PID结构体变量	
extern PID_InitTypeDef PID_Servos;		//舵机PID结构体变量	

void Init_all()
{
	WTST = 0;							//设置程序代码等待参数，赋值为0可将CPU执行程序的速度设置为最快  
	DisableGlobalIRQ();		//关闭总中断
	sys_clk = 35000000;		//设置系统频率为35MHz
  board_init();					//初始化寄存器

//陀螺仪初始化
	mpu6050_init();

//adc初始化
	adc_init(ADC_P00, ADC_SYSclk_DIV_2);
	adc_init(ADC_P05, ADC_SYSclk_DIV_2);
	adc_init(ADC_P06, ADC_SYSclk_DIV_2);
	adc_init(ADC_P16, ADC_SYSclk_DIV_2);

//编码器初始化
	ctimer_count_init(CTIM0_P34);					//定时器外部计数模式--右轮
	ctimer_count_init(CTIM3_P04);					//定时器外部计数模式--左轮
	pit_timer_ms(TIM_4, 5);								//配置定时器4，5ms进一次中断，用于读取、调整速度

//pwm初始化
	pwm_init(PWMA_CH1P_P60, 15000, 0);		//左电机
	pwm_init(PWMA_CH2P_P62, 15000, 0);		//左电机-主控
	pwm_init(PWMA_CH3P_P64, 15000, 0);		//右电机
	pwm_init(PWMA_CH4P_P66, 15000, 0);		//右电机-主控
	pwm_init(PWMB_CH1_P74, 50, 0);				//舵机

//pid初始化  PID_Init(结构体, KP, KI, KD, 输出限幅, 积分限幅)
	PID_Init(&PID_Left, 200, 4, 0, 8000, 5000);			//左轮PID初始化
	PID_Init(&PID_Right, 200, 4, 0, 8000, 5000);		//右轮PID初始化
	PID_Init(&PID_Servos, 0, 0, 0, 60, 0);					//舵机PID初始化

	delay_ms(500);

	EnableGlobalIRQ();		//开启总中断
}