/*    	每日一拜 好过省赛             天天参拜 稳过国赛        */
/* \\ \\ \\ \\ \\ \\ \\ || || || || || || // // // // // // // //
\\ \\ \\ \\ \\ \\ \\        _ooOoo_          // // // // // // //
\\ \\ \\ \\ \\ \\          o8888888o            // // // // // //
\\ \\ \\ \\ \\             88" . "88               // // // // //
\\ \\ \\ \\                (| -_- |)                  // // // //
\\ \\ \\                   O\  =  /O                     // // //
\\ \\                   ____/`---'\____                     // //
\\                    .'  \\|     |//  `.                      //
==                   /  \\|||  :  |||//  \                     ==
==                  /  _||||| -:- |||||-  \                    ==
==                  |   | \\\  -  /// |   |                    ==
==                  | \_|  ''\---/''  |   |                    ==
==                  \  .-\__  `-`  ___/-. /                    ==
==                ___`. .'  /--.--\  `. . ___                  ==
==              ."" '<  `.___\_<|>_/___.'  >'"".               ==
==            | | :  `- \`.;`\ _ /`;.`/ - ` : | |              \\
//            \  \ `-.   \_ __\ /__ _/   .-` /  /              \\
//      ========`-.____`-.___\_____/___.-`____.-'========      \\
//                           `=---='                           \\
// //   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  \\ \\
// // //      佛祖保佑      永无BUG      永不修改        \\ \\ \\
// // // // // // || || || || || || || || || || \\ \\ \\ \\ \\ */

#include "headfile.h"

float Speed = 100;								//预设速度	
	
bit flag = 1;											//判断是否经过10ms
bit Stop_flag = 0;								//判断是否冲出赛道
bit Barrier_flag = 0;							//判断是否开始避障
bit Garage_in_flag = 0;						//判断是否入车库
bit Garage_out_flag = 0;					//判断是否出车库
bit encoder_start = 0;						//开始积分标志
int element_num = 0;							//经过元素的数量
int barrier_num=0;								//障碍检测，防止误判
int encoder_num = 0;							//编码器积分

PID_InitTypeDef PID_Left;					//左轮PID
PID_InitTypeDef PID_Right;				//右轮PID
PID_InitTypeDef PID_Servos;				//舵机PID
extern int mode;
extern float angle;
extern int encoder_left;					//左轮编码器计数
extern int encoder_right;					//游轮编码器计数
extern bit circle_num;
extern bit forward_flag;

bit first_barrier=0;

void main()
{
	Init_all();																	//初始化所有
	oled_show();
	delay_ms(1000);
	if(mode==0)								//1.8
		Speed = 110;
	else if(mode==1)					//2.4					
		Speed = 130;
	else if(mode==2)					//2.4					
		Speed = 160;
	while(1)
	{
//		if(encoder_num>600&&first_barrier==0)
//		{
//			Speed = 110;
//		}
////避障
		if(P33==0&&first_barrier==0&&forward_flag==0)				//如果检测到障碍
			Barrier_flag=1;											//开启避障标志位
		if(Barrier_flag==1)											//如果检测到障碍
			Avoid_barrier();											//开始避障

		if(Garage_out_flag==0)									//如果没有出库
			Garage_out();													//出库

//入库-倒车
		if(P26==0)													//如果检测到磁铁
			Garage_in_flag=1;										//开启入库标志
		if(Garage_in_flag==1)										//如果检测到入库标志
		{
			if(mode==0)								//1.8
				Garage_in0();
			else if(mode==1)					//2.4					
				Garage_in1();
			else if(mode==2)					//2.4					
				Garage_in2();
		}

		if(Stop_flag == 0)											//未冲出赛道
		{
			if(flag == 0)													//10ms读取一次电感值，计算偏差，并调整自身姿态
			{
				ADC_Read();													//读取电感值
				if(mode==0)								//1.8
					Pos_Deviation0();										//位置偏差计算
				else if(mode==1)					//2.0					
					Pos_Deviation1();										//位置偏差计算
				else if(mode==2)					//2.2					
					Pos_Deviation2();										//位置偏差计算

				if(mode==0)								//1.8
					Servos_Control0();										//调整车身姿态
				else if(mode==1)					//2.4					
					Servos_Control1();										//调整车身姿态
				else if(mode==2)					//2.4					
					Servos_Control2();										//调整车身姿态
				//Sendspeed();
				flag = 1;														//10ms标志位改变，进入下一次寻迹
			}
		}
		else																		//冲出赛道
		{
			pwm_duty(PWMB_CH1_P74,845);
			pwm_duty(PWMA_CH2P_P62, 0);						//左轮pwm置0	
			pwm_duty(PWMA_CH3P_P64, 0);						//右轮pwm置0
			P52=0;
			while(1);
		}
	}
}