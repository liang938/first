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

float Speed = 160;								//Ԥ���ٶ�	
bit flag = 1;											//�ж��Ƿ񾭹�10ms
bit Stop_flag = 0;								//�ж��Ƿ�������
bit Barrier_flag = 0;							//�ж��Ƿ�ʼ����
bit Garage_in_flag = 0;						//�ж��Ƿ��복��
bit Garage_out_flag = 0;					//�ж��Ƿ������
bit encoder_start = 0;						//��ʼ���ֱ�־
int element_num = 0;							//����Ԫ�ص�����
int encoder_num = 0;							//����������

PID_InitTypeDef PID_Left;					//����PID
PID_InitTypeDef PID_Right;				//����PID
PID_InitTypeDef PID_Servos;				//���PID
extern int encoder_left;					//���ֱ���������
extern int encoder_right;					//���ֱ���������

bit first_barrier=0;

void main()
{
	Init_all();																	//��ʼ������
	
	oled_init();					//��ʼ��oled��Ļ
  while(1)
	{
		
		oled_printf_float(0,0,encoder_left,4,2);
		oled_printf_float(0,2,encoder_right,4,2);
//		if(element_num==3)												//Ԫ��������⡢ʮ�ֺͻ���
//		{
//			if(encoder_start==0)
//			{
//				encoder_num=0;
//				encoder_start=1;
//			}
//			if(encoder_num>1700)
//				Garage_in();
//		}

//		if(encoder_num>2000)												//����������
//		{
//			Stop_flag=1;
//		}

//�����
		if(Garage_out_flag==0)									//���û�г���
			Garage_out();													//����
		if(P26==0)															//�����⵽����
			Garage_in_flag=1;											//��������־
		if(Garage_in_flag==1)										//�����⵽����־
			Garage_in();													//��ʼ���

//����
//		if(P33==0&&first_barrier==0)						//�����⵽�ϰ�
//			Barrier_flag=1;											//�������ϱ�־λ
//		if(Barrier_flag==1)											//�����⵽�ϰ�
//			Avoid_barrier();											//��ʼ����

		if(Stop_flag == 0)											//δ�������
		{
			if(flag == 0)													//10ms��ȡһ�ε��ֵ������ƫ�������������̬
			{
				ADC_Read();													//��ȡ���ֵ
				Pos_Deviation();										//λ��ƫ�����
				Servos_Control();										//����������̬
				//Sendspeed();
				flag = 1;														//10ms��־λ�ı䣬������һ��Ѱ��
			}
		}
		else																		//�������
		{
			pwm_duty(PWMB_CH1_P74,840);
			pwm_duty(PWMA_CH2P_P62, 0);						//����pwm��0	
			pwm_duty(PWMA_CH3P_P64, 0);						//����pwm��0
			P52=0;
			while(1);
		}
	}
}