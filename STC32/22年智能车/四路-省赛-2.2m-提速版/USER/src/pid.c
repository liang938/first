#include "headfile.h"

float err_add = 0;
extern int leftspeed;										//左轮差速度
extern int rightspeed;									//右轮差速度
extern int encoder_left;								//左轮编码器计数
extern int encoder_right;								//右轮编码器计数

void PID_Init(PID_InitTypeDef *PID_InitStruct, float kp, float ki, float kd, float out_limit, float integral_limit)		//PID初始化
{
	PID_InitStruct->KP = kp;
	PID_InitStruct->KI = ki;
	PID_InitStruct->KD = kd;
	PID_InitStruct->err = 0;
	PID_InitStruct->err_last = 0;
	PID_InitStruct->err_prev = 0;
	PID_InitStruct->Total_Out = 0;
	PID_InitStruct->Out_Limit = out_limit;
	PID_InitStruct->Integral_Limit = integral_limit;
}

float Limit(float value, float limit)		//限幅
{
	value = (value<-limit)?-limit:value;
	value = (value>limit)?limit:value;		//判断是否超出限幅
	return value;	
}

void PID_Calc_Positional(PID_InitTypeDef *PID_InitStruct, float deviation_expected, float deviation_now)		//位置式PID计算
{
	PID_InitStruct->ExpectedValue = deviation_expected;		//期望偏差值
	PID_InitStruct->ActualValue = deviation_now;					//实际偏差值

	PID_InitStruct->err = (PID_InitStruct->ExpectedValue)-(PID_InitStruct->ActualValue);		//err值为期望偏差与当前偏差的差值
	
	err_add += PID_InitStruct->err;		//误差值累加

	PID_InitStruct->P_Out = (PID_InitStruct->err)*(PID_InitStruct->KP);		//比例控制部分 P_Out=KP*err
	PID_InitStruct->I_Out = err_add*(PID_InitStruct->KI);									//积分控制部分	I_Out+=KI*err
	PID_InitStruct->D_Out = ((PID_InitStruct->err)-(PID_InitStruct->err_last))*(PID_InitStruct->KD);			//微分控制部分 D_Out=KD*(err-err_last)
	
	PID_InitStruct->I_Out = Limit(PID_InitStruct->I_Out, PID_InitStruct->Integral_Limit);									//积分限幅

	PID_InitStruct->Total_Out = (PID_InitStruct->P_Out)+(PID_InitStruct->I_Out)+(PID_InitStruct->D_Out);	//计算总输出量
	PID_InitStruct->Total_Out = Limit(PID_InitStruct->Total_Out, PID_InitStruct->Out_Limit);							//输出限幅

	PID_InitStruct->err_last = PID_InitStruct->err;		//更新上一次err
}

void PID_Calc_Incremental(PID_InitTypeDef *PID_InitStruct, int speed_expected, int speed_now)		//增量式PID计算
{
	PID_InitStruct->ExpectedValue = speed_expected;		//期望速度
	PID_InitStruct->ActualValue = speed_now;					//当前速度

	PID_InitStruct->err = (PID_InitStruct->ExpectedValue)-(PID_InitStruct->ActualValue);								//err值为期望速度与当前速度的差值

	PID_InitStruct->P_Out += ((PID_InitStruct->err)-(PID_InitStruct->err_last))*(PID_InitStruct->KP);		//比例控制部分	P_Out=KP*(err-err_last)

	PID_InitStruct->I_Out += (PID_InitStruct->err)*(PID_InitStruct->KI);																//积分控制部分	I_Out=KI*error
	PID_InitStruct->I_Out = Limit(PID_InitStruct->I_Out, PID_InitStruct->Integral_Limit);								//积分限幅
	
	PID_InitStruct->D_Out += ((PID_InitStruct->err)-2*(PID_InitStruct->err_last)+(PID_InitStruct->err_prev))*(PID_InitStruct->KD);		//微分控制部分	D_Out=KD*(err-2*err_last+err_prev)

	PID_InitStruct->Total_Out = (PID_InitStruct->P_Out)+(PID_InitStruct->I_Out)+(PID_InitStruct->D_Out);//计算总输出量
	PID_InitStruct->Total_Out = Limit(PID_InitStruct->Total_Out, PID_InitStruct->Out_Limit);						//输出限幅
  PID_InitStruct->Total_Out = (PID_InitStruct->Total_Out<0)?0:PID_InitStruct->Total_Out;

	PID_InitStruct->err_prev = PID_InitStruct->err_last;		//更新前一次err
	PID_InitStruct->err_last = PID_InitStruct->err;					//更新上一次err
}






