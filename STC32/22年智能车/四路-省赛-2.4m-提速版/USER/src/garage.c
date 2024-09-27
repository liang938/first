#include "headfile.h"

extern bit Stop_flag;
extern bit Garage_in_flag;						//判断是否入车库
extern bit Garage_out_flag;						//判断是否出车库

void Garage_out()
{
//直走
	pwm_duty(PWMB_CH1_P74,840);
	pwm_duty(PWMA_CH2P_P62, 5000);						//左轮pwm置0	
	pwm_duty(PWMA_CH3P_P64, 5000);						//右轮pwm置0
	delay_ms(250);
//出库左转:+60																									右转:-60
	pwm_duty(PWMB_CH1_P74,840+60);						//                  pwm_duty(PWMB_CH1_P74,840-60);								
	pwm_duty(PWMA_CH2P_P62, 5000);						//左轮pwm置0	      pwm_duty(PWMA_CH2P_P62, 8000);
	pwm_duty(PWMA_CH3P_P64, 8000);						//右轮pwm置0        pwm_duty(PWMA_CH3P_P64, 5000);
	delay_ms(380);
	Garage_out_flag=1;
}

//void Garage_in()
//{
//	pwm_duty(PWMB_CH1_P74,840+60);						//                  pwm_duty(PWMB_CH1_P74,840-60);								
//	pwm_duty(PWMA_CH2P_P62, 3000);						//左轮pwm置0	      pwm_duty(PWMA_CH2P_P62, 8000);
//	pwm_duty(PWMA_CH3P_P64, 5000);						//右轮pwm置0        pwm_duty(PWMA_CH3P_P64, 5000);
//	delay_ms(250);
//	pwm_duty(PWMB_CH1_P74,840);						// 
//	pwm_duty(PWMA_CH2P_P62, 5000);						//左轮pwm置0	      pwm_duty(PWMA_CH2P_P62, 8000);
//	pwm_duty(PWMA_CH3P_P64, 5000);						//右轮pwm置0        pwm_duty(PWMA_CH3P_P64, 5000);
//	delay_ms(50);
////电机反转配置
//	pwm_duty(PWMB_CH1_P74,840);
//	pwm_duty(PWMA_CH2P_P62, 0);						//左轮pwm置0	
//	pwm_duty(PWMA_CH3P_P64, 0);						//右轮pwm置0
////直行倒车
//	pwm_duty(PWMB_CH1_P74,840);
//	pwm_duty(PWMA_CH1P_P60, 8000);				//左电机
//	pwm_duty(PWMA_CH4P_P66, 8000);				//右电机
//	delay_ms(350);
////完全停下后停止运动
//	pwm_duty(PWMB_CH1_P74,840);
//	pwm_duty(PWMA_CH1P_P60, 0);						//左电机
//	pwm_duty(PWMA_CH2P_P62, 0);						//左轮
//	pwm_duty(PWMA_CH3P_P64, 0);						//右轮
//	pwm_duty(PWMA_CH4P_P66, 0);						//右电机
//	while(1);
//}

void Garage_in()
{
//电机反转配置
	pwm_duty(PWMB_CH1_P74,840);
	pwm_duty(PWMA_CH2P_P62, 0);						//左轮pwm置0	
	pwm_duty(PWMA_CH3P_P64, 0);						//右轮pwm置0
//直行倒车
	pwm_duty(PWMB_CH1_P74,840);
	pwm_duty(PWMA_CH1P_P60, 8000);				//左电机
	pwm_duty(PWMA_CH4P_P66, 8000);				//右电机
	delay_ms(750);
//打角倒车入库，左边：+60                             右边：-60
	pwm_duty(PWMB_CH1_P74,840+60);				//            pwm_duty(PWMB_CH1_P74,840-60);
	pwm_duty(PWMA_CH1P_P60, 5000);				//左电机			pwm_duty(PWMA_CH1P_P60, 8000);
	pwm_duty(PWMA_CH4P_P66, 8000);				//右电机			pwm_duty(PWMA_CH4P_P66, 5000);
	delay_ms(400);
//入库后向后倒退，车身完全进入车库
	pwm_duty(PWMB_CH1_P74,840);
	pwm_duty(PWMA_CH1P_P60, 5000);				//左电机
	pwm_duty(PWMA_CH4P_P66, 5000);				//右电机
	delay_ms(100);
//电机反转，防止因惯性后移
	pwm_duty(PWMB_CH1_P74,840);
	pwm_duty(PWMA_CH1P_P60, 0);						//左电机
	pwm_duty(PWMA_CH2P_P62, 8000);				//左轮	
	pwm_duty(PWMA_CH3P_P64, 8000);				//右轮
	pwm_duty(PWMA_CH4P_P66, 0);						//右电机
	delay_ms(300);
//完全停下后停止运动
	pwm_duty(PWMB_CH1_P74,840);
	pwm_duty(PWMA_CH1P_P60, 0);						//左电机
	pwm_duty(PWMA_CH2P_P62, 0);						//左轮
	pwm_duty(PWMA_CH3P_P64, 0);						//右轮
	pwm_duty(PWMA_CH4P_P66, 0);						//右电机
	while(1);
}
