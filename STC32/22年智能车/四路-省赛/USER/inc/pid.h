#ifndef __PID_H
#define __PID_H

typedef struct 
{
	float ExpectedValue;		//定义设定值
	float ActualValue;		//定义实际值

	float err;		//定义偏差值
	float err_last;		//定义上一次偏差值
	float err_prev;		//定义前一个偏差值

	float KP,KI,KD;		//定义比例、积分、微分

	float P_Out,I_Out,D_Out;		//定义PID输出量
	float	Total_Out;		//定义总输出量
	float Out_Limit;		//定义输出限幅
	float Integral_Limit;		//定义积分限幅
}PID_InitTypeDef;

float Limit(float vlaue, float out_limit);		//限幅
void PID_Init(PID_InitTypeDef *PID_InitStruct, float kp, float ki, float kd, float out_limit, float integral_limit);		//PID初始化
void PID_Calc_Incremental(PID_InitTypeDef *PID_InitStruct, int speed_now, int speed_expected);		//增量式PID计算
void PID_Calc_Positional(PID_InitTypeDef *PID_InitStruct, float devition_expected, float devation_now);		//位置式PID计算

#endif