#include "headfile.h"

float angle = 0;											//角度积分

bit barrier_in=0;											//回赛道标志
bit barrier_out=0;										//出赛道标志
bit barrier_back=0;										//入赛道回正标志
bit barrier_forward=0;								//入赛道前直行标志
int barrier_time=0;
int adc_rm = 0;
extern int mode;
extern float Speed;

extern bit flag;											//判断是否经过10ms
extern bit Stop_flag;
extern bit Barrier_flag;							//避障标志位
extern bit first_barrier;

void Avoid_barrier()									//避障
{
	while(1)
	{
		if(flag == 0)												
		{
			adc_rm = adc_once(ADC_P06, ADC_8BIT);		//三路电感
			mpu6050_get_gyro();
			mpu_gyro_z = (mpu_gyro_z*2000)/32768;
			angle += mpu_gyro_z*0.005;
//			printf("%.3f\n",angle);
			if(barrier_out==0)
			{
				pwm_duty(PWMB_CH1_P74,840+60);											
				pwm_duty(PWMA_CH2P_P62, 3500);						
				pwm_duty(PWMA_CH3P_P64, 4500);
				if(25<angle&&angle<35)
					barrier_out=1;
			}
			else if(barrier_in==0)
			{
				pwm_duty(PWMB_CH1_P74,840-60);											
				pwm_duty(PWMA_CH2P_P62, 4500);						
				pwm_duty(PWMA_CH3P_P64, 3500);
				if(-25<angle&&angle<-15)
					barrier_in=1;				
			}
			else if(barrier_forward==0)
			{
				pwm_duty(PWMB_CH1_P74,840);											
				pwm_duty(PWMA_CH2P_P62, 3500);						
				pwm_duty(PWMA_CH3P_P64, 3500);
				barrier_time+=1;
				if(barrier_time>70)
				{
					barrier_time=0;
					barrier_forward=1;					
				}
			}
			else if(barrier_back==0)
			{
				pwm_duty(PWMB_CH1_P74,840+60);											
				pwm_duty(PWMA_CH2P_P62, 2000);						
				pwm_duty(PWMA_CH3P_P64, 4000);
				barrier_time+=1;
				if(barrier_time>55)
					barrier_back=1;		
			}
			else
			{
				first_barrier=1;
				Barrier_flag=0;
				//Stop_flag=1;
				if(mode==0)								//1.8
					Speed = 110;
				else if(mode==1)					//2.4					
					Speed = 130;
				else if(mode==2)					//2.4					
					Speed = 160;
				break;
			}
			flag = 1;												
		}
	}
}


