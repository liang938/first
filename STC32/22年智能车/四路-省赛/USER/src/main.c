/*    	ÿ��һ�� �ù�ʡ��             ����ΰ� �ȹ�����        */
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
// // //      ���汣��      ����BUG      �����޸�        \\ \\ \\
// // // // // // || || || || || || || || || || \\ \\ \\ \\ \\ */

#include "headfile.h"

float Speed = 100;								//Ԥ���ٶ�	
	
bit flag = 1;											//�ж��Ƿ񾭹�10ms
bit Stop_flag = 0;								//�ж��Ƿ�������
bit Barrier_flag = 0;							//�ж��Ƿ�ʼ����
bit Garage_in_flag = 0;						//�ж��Ƿ��복��
bit Garage_out_flag = 0;					//�ж��Ƿ������
bit encoder_start = 0;						//��ʼ���ֱ�־
int element_num = 0;							//����Ԫ�ص�����
int barrier_num=0;								//�ϰ���⣬��ֹ����
int encoder_num = 0;							//����������

PID_InitTypeDef PID_Left;					//����PID
PID_InitTypeDef PID_Right;				//����PID
PID_InitTypeDef PID_Servos;				//���PID
extern int mode;
extern float angle;
extern int encoder_left;					//���ֱ���������
extern int encoder_right;					//���ֱ���������
extern bit circle_num;
extern bit forward_flag;

bit first_barrier=0;

void main()
{
	Init_all();																	//��ʼ������
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
////����
		if(P33==0&&first_barrier==0&&forward_flag==0)				//�����⵽�ϰ�
			Barrier_flag=1;											//�������ϱ�־λ
		if(Barrier_flag==1)											//�����⵽�ϰ�
			Avoid_barrier();											//��ʼ����

		if(Garage_out_flag==0)									//���û�г���
			Garage_out();													//����

//���-����
		if(P26==0)													//�����⵽����
			Garage_in_flag=1;										//��������־
		if(Garage_in_flag==1)										//�����⵽����־
		{
			if(mode==0)								//1.8
				Garage_in0();
			else if(mode==1)					//2.4					
				Garage_in1();
			else if(mode==2)					//2.4					
				Garage_in2();
		}

		if(Stop_flag == 0)											//δ�������
		{
			if(flag == 0)													//10ms��ȡһ�ε��ֵ������ƫ�������������̬
			{
				ADC_Read();													//��ȡ���ֵ
				if(mode==0)								//1.8
					Pos_Deviation0();										//λ��ƫ�����
				else if(mode==1)					//2.0					
					Pos_Deviation1();										//λ��ƫ�����
				else if(mode==2)					//2.2					
					Pos_Deviation2();										//λ��ƫ�����

				if(mode==0)								//1.8
					Servos_Control0();										//����������̬
				else if(mode==1)					//2.4					
					Servos_Control1();										//����������̬
				else if(mode==2)					//2.4					
					Servos_Control2();										//����������̬
				//Sendspeed();
				flag = 1;														//10ms��־λ�ı䣬������һ��Ѱ��
			}
		}
		else																		//�������
		{
			pwm_duty(PWMB_CH1_P74,845);
			pwm_duty(PWMA_CH2P_P62, 0);						//����pwm��0	
			pwm_duty(PWMA_CH3P_P64, 0);						//����pwm��0
			P52=0;
			while(1);
		}
	}
}