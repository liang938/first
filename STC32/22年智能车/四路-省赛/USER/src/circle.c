#include "headfile.h"

bit circle_num=0;
bit servos_flag_in=0;									//入环岛标志位
bit servos_flag_move=0;								//环岛内标志位
bit servos_flag_out=0;								//出环岛标志位
int forward_time=0;
extern int time_count;								//时间积分
extern int element_num;								//经过元素的数量
extern int ADC_MIN;										//电感采集最小值
extern int ADC_MAX;										//电感采集最大值
extern int READ_MAX;									//归一化后电感最大值
extern int servos_flag;								//环岛标志位
extern bit Stop_flag;									//冲出赛道标志
extern float Speed;										//预设速度
extern float speed_err;								//转向电机增益
extern float l,lm,rm,r;								//左、左中、右中、右四路电感
extern float sensor_err;							//电感偏差值
extern float servos_err;							//舵机偏差值
extern int encoder_num;
extern PID_InitTypeDef PID_Servos;		//舵机PID

//时间积分在sensor.c文件中，每调整一次速度积一次分，也就是5ms积一次分

void circle_judge0()																															//环岛判断
{
	if(READ_MAX-10<l&&READ_MAX-10<r&&servos_flag==0)																		//如果左右横电感达到最大值并且不在环岛中
	{
		P50=0;																																			//开启蜂鸣器
		servos_flag=(lm>rm)?-1:-1;																										//根据竖电感的值判断左右环岛
	}
	if(time_count==50&&servos_flag_in==0)																					//还没有入环,time_count为入环前直行距离
	{
		P50=1;																																			//关闭蜂鸣器
		time_count=0;																																//时间积分清零
		servos_flag_in=1;																														//开始入环
	}
	if(time_count==80&&servos_flag_in==1&&servos_flag_move==0)										//正在入环，time_count为打死角入环时间
		servos_flag_move=1;																													//入环结束，开始环内寻迹
	if((READ_MAX-lm<30||READ_MAX-rm<30)&&servos_flag_move==1&&servos_flag_out==0)	//如果任意竖电感值大于于30并且在环内并且还未出环
	{
		time_count=0;																																//时间积分清零
		servos_flag_out=1;																													//开始出环
	}
}

void circle_move0()																									//环岛寻迹
{
	if(servos_flag_out==1)																						//出环
	{
		if(time_count>200)																							//时间大于1s，给所有标志清零，防止在出环岛处重新误判为环岛
		{																																                             
			servos_flag=0;																								//环岛标志清零
			time_count=0;																									//时间积分清零
			servos_flag_in=0;																							//入环岛标志清零
			servos_flag_move=0;																						//环内寻迹标志清零
			servos_flag_out=0;																						//出环岛标志清零
			element_num+=1;																								//经过元素数量加一
			circle_num=1;			
			encoder_num=0;			
			Speed = 110;
			
		}
		else if(time_count>30)																					//time_count为打死角出环岛时间
			sensor_err = 100*(1.2*(l-r)+(lm-rm))/((l+r)+0.5*(lm+rm));			//出环岛寻迹
		else 																														
			sensor_err = (servos_flag==1)?80:-80;													//打死角出环岛
	}
	else if(servos_flag_move==1)																			//环内寻迹
	{
			sensor_err = 100*(1.2*(l-r)+(lm-rm))/((l+r)+0.5*(lm+rm));			//正常寻迹
	}
	else																															//入环岛
	{
		if(servos_flag_in==0)																						//如果没有开始入环
			sensor_err = (servos_flag==1)?-10:25;				  								//向相反方向打偏角,防止车身向环岛方向偏移
		else																														//如果开始入环
			sensor_err = (servos_flag==1)?80:-50;													//打死角入环
	}
}


//***************************************************************************************************************************************//


void circle_judge1()																															//环岛判断
{
	if(READ_MAX==l&&READ_MAX==r&&servos_flag==0)																		//如果左右横电感达到最大值并且不在环岛中
	{
		P50=0;																																			//开启蜂鸣器
		servos_flag=(lm>rm)?-1:-1;																										//根据竖电感的值判断左右环岛
	}
	if(time_count==40&&servos_flag_in==0)																					//还没有入环,time_count为检测到环岛后直行时间
	{
		P50=1;																																			//关闭蜂鸣器
		time_count=0;																																//时间积分清零
		servos_flag_in=1;																														//开始入环
	}
	if(time_count==70&&servos_flag_in==1&&servos_flag_move==0)										//正在入环，time_count为打死角入环的时间
		servos_flag_move=1;																													//入环结束，开始环内寻迹
	if((READ_MAX-lm<45||READ_MAX-rm<45)&&servos_flag_move==1&&servos_flag_out==0)	//如果任意竖电感值小于40并且在环内并且还未出环
	{
		time_count=0;																																//时间积分清零
		servos_flag_out=1;																													//开始出环
	}
}

void circle_move1()																									//环岛寻迹
{
	if(servos_flag_out==1)																						//出环
	{
		if(time_count>200)																							//时间大于1s，所有标志清零，防止在出环岛处重新误判为环岛
		{																																
			servos_flag=0;																								//环岛标志清零
			time_count=0;																									//时间积分清零
			servos_flag_in=0;																							//入环岛标志清零
			servos_flag_move=0;																						//环内寻迹标志清零
			servos_flag_out=0;																						//出环岛标志清零
			element_num+=1;																								//经过元素数量加一
			circle_num=1;	
			encoder_num=0;
			Speed = 90;
		}
		else if(time_count>20)																					//time_count为打死角出环岛时间
			sensor_err = 100*(1.6*(l-r)+1.2*(lm-rm))/((l+r)+0.5*(lm+rm));	//出环岛寻迹
		else 																														
			sensor_err = (servos_flag==1)?80:-80;													//打死角出环岛
	}
	else if(servos_flag_move==1)																			//环内寻迹
	{
			sensor_err = 100*(1.6*(l-r)+1.2*(lm-rm))/((l+r)+0.5*(lm+rm));	//正常寻迹
	}
	else																															//入环岛
	{
		if(servos_flag_in==0)																						//如果没有开始入环
			sensor_err = (servos_flag==1)?-10:20;				  								//向相反方向打偏角,防止车身向环岛方向偏移
		else																														//如果开始入环
			sensor_err = (servos_flag==1)?80:-60;													//打死角入环
	}
}


//***************************************************************************************************************************************//


void circle_judge2()																															//环岛判断
{
	if(READ_MAX-10<l&&READ_MAX-10<r&&servos_flag==0)																		//如果左右横电感达到最大值并且不在环岛中
	{
		P50=0;																																			//开启蜂鸣器
		servos_flag=(lm>rm)?-1:-1;																										//根据竖电感的值判断左右环岛
	}
	if(time_count==35&&servos_flag_in==0)																					//还没有入环,time_count为检测到环岛后直行时间
	{
		P50=1;																																			//关闭蜂鸣器
		time_count=0;																																//时间积分清零
		servos_flag_in=1;																														//开始入环
	}
	if(time_count==70&&servos_flag_in==1&&servos_flag_move==0)										//正在入环，time_count为打死角入环的时间
		servos_flag_move=1;																													//入环结束，开始环内寻迹
	if((READ_MAX-lm<45||READ_MAX-rm<45)&&servos_flag_move==1&&servos_flag_out==0)	//如果任意竖电感值小于40并且在环内并且还未出环
	{
		time_count=0;																																//时间积分清零
		servos_flag_out=1;																													//开始出环
	}
}

void circle_move2()																									//环岛寻迹
{
	if(servos_flag_out==1)																						//出环
	{
		if(time_count>200)																							//时间大于1s，所有标志清零，防止在出环岛处重新误判为环岛
		{																																
			servos_flag=0;																								//环岛标志清零
			time_count=0;																									//时间积分清零
			servos_flag_in=0;																							//入环岛标志清零
			servos_flag_move=0;																						//环内寻迹标志清零
			servos_flag_out=0;																						//出环岛标志清零
			element_num+=1;																								//经过元素数量加一
			Speed = 110;
		}
		else if(time_count>20)																					//time_count为打死角出环岛时间
			sensor_err = 100*(1.6*(l-r)+1.2*(lm-rm))/((l+r)+0.5*(lm+rm));	//出环岛寻迹
		else 																														
			sensor_err = (servos_flag==1)?80:-80;													//打死角出环岛
	}
	else if(servos_flag_move==1)																			//环内寻迹
	{
			sensor_err = 100*(1.6*(l-r)+1.2*(lm-rm))/((l+r)+0.5*(lm+rm));	//正常寻迹
	}
	else																															//入环岛
	{
		if(servos_flag_in==0)																						//如果没有开始入环
			sensor_err = (servos_flag==1)?-10:20;				  								//向相反方向打偏角,防止车身向环岛方向偏移
		else																														//如果开始入环
			sensor_err = (servos_flag==1)?80:-80;													//打死角入环
	}
}
