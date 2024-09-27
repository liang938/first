#include "headfile.h"

int encoder_left;												//左轮编码器计数
int encoder_right;											//右轮编码器计数
extern PID_InitTypeDef PID_Left;				//左轮结构体变量
extern PID_InitTypeDef PID_Right;				//右轮结构体变量
extern int leftspeed;										//左轮差速度
extern int rightspeed;									//右轮差速度
extern int encoder_num;									//编码器积分

void Getspeed()																		//获取当前速度
{
	encoder_left = ctimer_count_read(CTIM3_P04);		//读取数值
	encoder_right = ctimer_count_read(CTIM0_P34);		//读取数值
	ctimer_count_clean(CTIM3_P04);									//清除计数值，开始下一轮计数
	ctimer_count_clean(CTIM0_P34);									//清除计数值，开始下一轮计数
	encoder_num += (encoder_left+encoder_right)/100;
}

void Speedcontrol(int left_speed, int right_speed)								//电机控制		
{
	PID_Calc_Incremental(&PID_Left, left_speed, encoder_left);			//左轮输出值计算	
	PID_Calc_Incremental(&PID_Right, right_speed, encoder_right);		//右轮输出值计算
	pwm_duty(PWMA_CH2P_P62, (int)PID_Left.Total_Out);								//设置左轮pwm
	pwm_duty(PWMA_CH3P_P64, (int)PID_Right.Total_Out);							//设置右轮pwm
}

void Sendspeed()
{
	printf("%d,%d,%d,%d\n",encoder_left,leftspeed,encoder_right,rightspeed);
}