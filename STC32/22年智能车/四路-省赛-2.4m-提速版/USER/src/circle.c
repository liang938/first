#include "headfile.h"

bit servos_flag_in=0;									//�뻷����־λ
bit servos_flag_move=0;								//�����ڱ�־λ
bit servos_flag_out=0;								//��������־λ
extern int time_count;								//ʱ�����
extern int ADC_MIN;										//��вɼ���Сֵ
extern int ADC_MAX;										//��вɼ����ֵ
extern int element_num;								//����Ԫ�ص�����
extern int READ_MAX;									//��һ���������ֵ
extern int servos_flag;								//������־λ
extern bit Stop_flag;									//���������־
extern float Speed;										//Ԥ���ٶ�
extern float speed_err;								//ת��������
extern float l,lm,rm,r;								//�����С����С�����·���
extern float sensor_err;							//���ƫ��ֵ
extern float servos_err;							//���ƫ��ֵ
extern PID_InitTypeDef PID_Servos;		//���PID

//ʱ�������sensor.c�ļ��У�ÿ����һ���ٶȻ�һ�η֣�Ҳ����5ms��һ�η�

void circle_judge()																															//�����ж�
{
	if(READ_MAX==l&&READ_MAX==r&&servos_flag==0)																		//������Һ��дﵽ���ֵ���Ҳ��ڻ�����
	{
		P50=0;																																			//����������
		servos_flag=(lm>rm)?1:-1;																										//��������е�ֵ�ж����һ���
	}
	if(time_count==25&&servos_flag_in==0)																					//��û���뻷,time_countΪ��⵽������ֱ��ʱ��
	{
		P50=1;																																			//�رշ�����
		time_count=0;																																//ʱ���������
		servos_flag_in=1;																														//��ʼ�뻷
	}
	if(time_count==70&&servos_flag_in==1&&servos_flag_move==0)										//�����뻷��time_countΪ�������뻷��ʱ��
		servos_flag_move=1;																													//�뻷��������ʼ����Ѱ��
	if((READ_MAX-lm<45||READ_MAX-rm<45)&&servos_flag_move==1&&servos_flag_out==0)	//������������ֵС��40�����ڻ��ڲ��һ�δ����
	{
		time_count=0;																																//ʱ���������
		servos_flag_out=1;																													//��ʼ����
	}
}

void circle_move()																									//����Ѱ��
{
	if(servos_flag_out==1)																						//����
	{
		if(time_count>200)																							//ʱ�����1s�����б�־���㣬��ֹ�ڳ���������������Ϊ����
		{																																
			servos_flag=0;																								//������־����
			time_count=0;																									//ʱ���������
			servos_flag_in=0;																							//�뻷����־����
			servos_flag_move=0;																						//����Ѱ����־����
			servos_flag_out=0;																						//��������־����
			element_num+=1;																								//����Ԫ��������һ
		}
		else if(time_count>20)																					//time_countΪ�����ǳ�����ʱ��
			sensor_err = 100*(1.6*(l-r)+1.2*(lm-rm))/((l+r)+0.5*(lm+rm));	//������Ѱ��
		else 																														
			sensor_err = (servos_flag==1)?80:-80;													//�����ǳ�����
	}
	else if(servos_flag_move==1)																			//����Ѱ��
	{
			sensor_err = 100*(1.6*(l-r)+1.2*(lm-rm))/((l+r)+0.5*(lm+rm));	//����Ѱ��
	}
	else																															//�뻷��
	{
		if(servos_flag_in==0)																						//���û�п�ʼ�뻷
			sensor_err = (servos_flag==1)?-10:30;				  								//���෴�����ƫ��,��ֹ�����򻷵�����ƫ��
		else																														//�����ʼ�뻷
			sensor_err = (servos_flag==1)?80:-80;													//�������뻷
	}
}