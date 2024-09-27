#include "headfile.h"

int ADC_MIN = 0;											//电感采集最小值
int ADC_MAX = 100;										//电感采集最大值
int READ_MAX = 100;										//电感归一化后最大值(不需要修改)
int temp;															//中值滤波临时变量
int ad[4][3];													//二维数组，存储四路adc连续采集三次的电感值
int sensor[4];												//滤波后的当前四路电感值
int cross_num=0;											//防止十字误判
int cross_flag=0;											//十字标志位
int time_count=0;											//时间积分变量
int servos_flag=0;										//判断是否为环岛
int servos_middle = 840;							//舵机中间位置
int leftspeed,rightspeed;							//左右电机差速度
float l,lm,rm,r;											//左、左中、右中、右四路电感
float speed_add=0;										//直道加速
float speed_err=0;										//转弯速度增益
float sensor_err;											//电感偏差值
float servos_err;											//舵机偏差值
extern float Speed;										//预设速度
extern bit Stop_flag;									//冲出赛道标志
extern bit Barrier_flag;							//避障标志位
extern int element_num;								//经过元素的数量
extern PID_InitTypeDef PID_Servos;		//舵机结构体变量

void ADC_Read()																//电感采集
{
	int i;
	for(i=0;i<3;i++)														//连续采集3次
	{
		ad[0][i] = adc_once(ADC_P00, ADC_8BIT);		//一路电感
		ad[1][i] = adc_once(ADC_P05, ADC_8BIT);		//二路电感
		ad[2][i] = adc_once(ADC_P06, ADC_8BIT);		//三路电感
		ad[3][i] = adc_once(ADC_P16, ADC_8BIT);		//四路电感
	}
	for(i=0;i<4;i++)														//中值滤波,取连续采集三次电感值的中间值	
	{
		if(ad[i][0]>ad[i][1])
		{
			temp = ad[i][0];
			ad[i][0] = ad[i][1];
			ad[i][1] = temp;
		}
		if(ad[i][1]>ad[i][2])
		{
			temp = ad[i][0];
			ad[i][0] = ad[i][1];
			ad[i][1] = temp;
		}
		if(ad[i][0]>ad[i][1])
		{
			temp = ad[i][0];
			ad[i][0] = ad[i][1];
			ad[i][1] = temp;
		}
		ad[i][1] = (ad[i][1]>ADC_MAX)?ADC_MAX:ad[i][1];					//对电感值进行限幅处理
		ad[i][1] = 100*(ad[i][1]-ADC_MIN)/(ADC_MAX-ADC_MIN);		//归一化,将电感值限制在0~100之间
	}
	l = ad[0][1];					//左电感
	lm = ad[1][1];				//左中电感
	rm = ad[2][1];				//右中电感
	r = ad[3][1];					//右电感
	circle_judge();
	if(l+lm+rm+r<20)
		Stop_flag=1;
}

//位置偏差计算
void Pos_Deviation()	
{
	if(cross_flag==1)													//如果判断为十字，开始时间积分，防止在经过十字时多次判断为十字
	{									
		cross_num+=1;														//开始十字时间积分
		if(cross_num==20)												//如果十字时间积分等于100ms
		{
			cross_flag=0;													//十字标志清零
			cross_num=0;													//十字时间积分清零
		}
	}
	else	
	{
		if(servos_flag==0&&lm>50&&rm>50)															//如果是十字
		{
			cross_flag=1;																								//十字标志开启
			element_num+=1;																							//元素数量加一
		}
	}
	if(servos_flag!=0)																							//如果是环岛
		circle_move();																								//环岛寻迹
	else																														//如果是正常路段
		sensor_err = 100*(1.2*(l-r)+1.2*(lm-rm))/((l+r)+0.5*(lm+rm));			//差比和算法,偏差值小于零向右转，大于零向左转 
	if(-55<sensor_err&&sensor_err<55)																//在直道上
	{
		speed_add = 50;																								//直道加速
		speed_err	=	400;																							//直道差速大小
		PID_Servos.KP = 0.5;																					
		PID_Servos.KI = 0;
		PID_Servos.KD = 5;
	}
	else
	{
		speed_add = (servos_flag==0)?-10:0;																								//弯道取消加速
		speed_err	=	200;																							//弯道差速大小
		PID_Servos.KP = 1;
		PID_Servos.KI = 0;
		PID_Servos.KD = 25;
	}
}

void Servos_Control()																								//车身姿态调整
{
	if(servos_flag!=0)								//如果在环岛中
		time_count+=1;									//开始时间积分
	printf("%.0f,%.0f,%.0f,%.0f,%.0f,%d,%d\n",l,lm,rm,r,sensor_err,servos_flag,element_num);
//舵机控制
	PID_Calc_Positional(&PID_Servos, 0, sensor_err);															//舵机输出值计算
	pwm_duty(PWMB_CH1_P74,servos_middle-(int)PID_Servos.Total_Out);								//舵机控制  

//电机差速
	if(sensor_err<0)																															//向左转
	{
		leftspeed = (int)((Speed+speed_add)*(1+PID_Servos.Total_Out/speed_err));		//左轮加速
		rightspeed = (int)(Speed+speed_add);																				//右轮速度不变
	}
	else																																					//向右转
	{				
		leftspeed = (int)(Speed+speed_add);																					//左轮速度不变
		rightspeed = (int)((Speed+speed_add)*(1-PID_Servos.Total_Out/speed_err));		//右轮加速
	}
	Speedcontrol(leftspeed, rightspeed);																					//调整当前速度
}










