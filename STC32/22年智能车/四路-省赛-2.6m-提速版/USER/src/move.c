#include "headfile.h"

int encoder_left;												//���ֱ���������
int encoder_right;											//���ֱ���������
extern PID_InitTypeDef PID_Left;				//���ֽṹ�����
extern PID_InitTypeDef PID_Right;				//���ֽṹ�����
extern int leftspeed;										//���ֲ��ٶ�
extern int rightspeed;									//���ֲ��ٶ�
extern int encoder_num;									//����������

void Getspeed()																		//��ȡ��ǰ�ٶ�
{
	encoder_left = ctimer_count_read(CTIM3_P04);		//��ȡ��ֵ
	encoder_right = ctimer_count_read(CTIM0_P34);		//��ȡ��ֵ
	ctimer_count_clean(CTIM3_P04);									//�������ֵ����ʼ��һ�ּ���
	ctimer_count_clean(CTIM0_P34);									//�������ֵ����ʼ��һ�ּ���
	encoder_num += (encoder_left+encoder_right)/100;
}

void Speedcontrol(int left_speed, int right_speed)								//�������		
{
	PID_Calc_Incremental(&PID_Left, left_speed, encoder_left);			//�������ֵ����	
	PID_Calc_Incremental(&PID_Right, right_speed, encoder_right);		//�������ֵ����
	pwm_duty(PWMA_CH2P_P62, (int)PID_Left.Total_Out);								//��������pwm
	pwm_duty(PWMA_CH3P_P64, (int)PID_Right.Total_Out);							//��������pwm
}

void Sendspeed()
{
	printf("%d,%d,%d,%d\n",encoder_left,leftspeed,encoder_right,rightspeed);
}