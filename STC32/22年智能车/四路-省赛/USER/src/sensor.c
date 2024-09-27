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
int servos_middle = 845;							//舵机中间位置
int leftspeed,rightspeed;							//左右电机差速度
float l,lm,rm,r;											//左、左中、右中、右四路电感
float speed_add=0;										//直道加速
float speed_err=0;										//转弯速度增益
float speed_low=0;										//转弯差速程度,越小差速越大
float sensor_err;											//电感偏差值
float servos_err;											//舵机偏差值
bit forward_flag=0;
extern float Speed;										//预设速度
extern bit Stop_flag;									//冲出赛道标志
extern bit Barrier_flag;							//避障标志位
extern int mode;
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
	if((l+lm+rm+r)<20)
		Stop_flag=1;
	if(mode==0)								//1.8
		circle_judge0();
	else if(mode==1)					//2.4					
		circle_judge1();
}


//***************************************************************************************************************************************//


//位置偏差计算
void Pos_Deviation0()	
{
	if(servos_flag!=0)																							//如果是环岛
		circle_move0();																								//环岛寻迹
	else																														//如果是正常路段
		sensor_err = 100*(1.2*(l-r)+(lm-rm))/((l+r)+0.5*(lm+rm));			//差比和算法,偏差值小于零向右转，大于零向左转 
	if(-30<sensor_err&&sensor_err<30)																//在直道上
	{
		forward_flag=0;
		speed_add = 0;																								//直道加速
		speed_err	=	400;					//直道转弯速度增益
		speed_low = 300;					//转弯差速程度,越小差速越大
		PID_Servos.KP = 0.5;																					
		PID_Servos.KI = 0;
		PID_Servos.KD = 5;
	}
	else
	{
		forward_flag=1;
		speed_add = 0;																								//弯道取消加速
		speed_err	=	400;					//直道转弯速度增益
		speed_low = -200;					//转弯差速程度,越小差速越大
		PID_Servos.KP = 1;
		PID_Servos.KI = 0;
		PID_Servos.KD = 20;
	}
}

void Servos_Control0()																								//车身姿态调整
{
	if(servos_flag!=0)								//如果在环岛中
		time_count+=1;									//开始时间积分
	//printf("%.0f,%.0f,%.0f,%.0f,%.0f,%d,%d\n",l,lm,rm,r,sensor_err,servos_flag,element_num);
//舵机控制
	PID_Calc_Positional(&PID_Servos, 0, sensor_err);															//舵机输出值计算
	pwm_duty(PWMB_CH1_P74,servos_middle-(int)PID_Servos.Total_Out);								//舵机控制  

//电机差速
	if(sensor_err<0)
	{
		leftspeed = (int)((Speed+speed_add)*(1+PID_Servos.Total_Out/speed_err));
		rightspeed = (int)((Speed+speed_add)*(1-PID_Servos.Total_Out/(speed_err+speed_low)));
	}
	else
	{
		rightspeed = (int)((Speed+speed_add)*(1-PID_Servos.Total_Out/speed_err));
		leftspeed = (int)((Speed+speed_add)*(1+PID_Servos.Total_Out/(speed_err+speed_low)));
	}
	Speedcontrol(leftspeed, rightspeed);															//调整当前速度
}


//***************************************************************************************************************************************//



//位置偏差计算
void Pos_Deviation1()	
{
	if(servos_flag!=0)																							//如果是环岛
		circle_move1();																								//环岛寻迹
	else																														//如果是正常路段
		sensor_err = 100*(1.4*(l-r)+1.2*(lm-rm))/((l+r)+0.5*(lm+rm));	//差比和算法,偏差值小于零向右转，大于零向左转 
	if(-40<sensor_err&&sensor_err<40)
	{
		forward_flag=0;
		speed_add = 0;						//直道加速
		speed_err	=	400;					//直道转弯速度增益
		speed_low = 300;					//转弯差速程度,越小差速越大
		PID_Servos.KP = 0.4;
		PID_Servos.KI = 0;
		PID_Servos.KD = 4.5;
	}
	else
	{
		forward_flag=1;
		speed_add = 0;						//直道加速
		speed_err	=	500;					//弯道转弯速度增益	
		speed_low = -400;					//转弯差速程度,越小差速越大
		PID_Servos.KP = 1;
		PID_Servos.KI = 0;
		PID_Servos.KD = 30;
	}
}

void Servos_Control1()																								//车身姿态调整
{

	if(servos_flag!=0)								//如果在环岛中
		time_count+=1;									//开始时间积分
	//printf("%.0f,%.0f,%.0f,%.0f,%.0f,%d\n",l,lm,rm,r,sensor_err,servos_flag);
//舵机控制
	PID_Calc_Positional(&PID_Servos, 0, sensor_err);									//舵机输出值计算
	pwm_duty(PWMB_CH1_P74,servos_middle-(int)PID_Servos.Total_Out);		//舵机控制  

//电机差速
	if(sensor_err<0)
	{
		leftspeed = (int)((Speed+speed_add)*(1+PID_Servos.Total_Out/speed_err));
		rightspeed = (int)((Speed+speed_add)*(1-PID_Servos.Total_Out/(speed_err+speed_low)));
	}
	else
	{
		rightspeed = (int)((Speed+speed_add)*(1-PID_Servos.Total_Out/speed_err));
		leftspeed = (int)((Speed+speed_add)*(1+PID_Servos.Total_Out/(speed_err+speed_low)));
	}
	Speedcontrol(leftspeed, rightspeed);															//调整当前速度
}


//***************************************************************************************************************************************//



//位置偏差计算
void Pos_Deviation2()	
{
	if(servos_flag!=0)																							//如果是环岛
		circle_move2();																								//环岛寻迹
	else																														//如果是正常路段
		sensor_err = 100*(1.5*(l-r)+1.3*(lm-rm))/((l+r)+0.5*(lm+rm));	//差比和算法,偏差值小于零向右转，大于零向左转 
	if(-50<sensor_err&&sensor_err<50)
	{
		forward_flag=0;
		speed_add = 0;						//直道加速
		speed_err	=	400;					//直道转弯速度增益
		speed_low = 300;					//转弯差速程度,越小差速越大
		PID_Servos.KP = 0.4;
		PID_Servos.KI = 0;
		PID_Servos.KD = 4.5;
	}
	else
	{
		forward_flag=1;
		speed_add = (servos_flag==0)?-10:0;						//直道加速
		speed_err	=	800;															//弯道转弯速度增益	
		speed_low = -700;															//转弯差速程度,越小差速越大
		PID_Servos.KP = 1;
		PID_Servos.KI = 0;
		PID_Servos.KD =30;
	}
}

void Servos_Control2()																								//车身姿态调整
{

	if(servos_flag!=0)								//如果在环岛中
		time_count+=1;									//开始时间积分

	printf("%.0f,%.0f,%.0f,%.0f,%.0f,%d\n",l,lm,rm,r,sensor_err,servos_flag);
//舵机控制
	PID_Calc_Positional(&PID_Servos, 0, sensor_err);									//舵机输出值计算
	pwm_duty(PWMB_CH1_P74,servos_middle-(int)PID_Servos.Total_Out);		//舵机控制  

//电机差速
	if(sensor_err<0)
	{
		leftspeed = (int)((Speed+speed_add)*(1+PID_Servos.Total_Out/speed_err));
		rightspeed = (int)((Speed+speed_add)*(1-PID_Servos.Total_Out/(speed_err+speed_low)));
		//rightspeed = (int)(Speed+speed_add);
	}
	else
	{
		rightspeed = (int)((Speed+speed_add)*(1-PID_Servos.Total_Out/speed_err));
		leftspeed = (int)((Speed+speed_add)*(1+PID_Servos.Total_Out/(speed_err+speed_low)));
		//leftspeed = (int)(Speed+speed_add);
	}
	Speedcontrol(leftspeed, rightspeed);															//调整当前速度
}













