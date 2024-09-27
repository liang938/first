#ifndef __PID_H
#define __PID_H

typedef struct 
{
	float ExpectedValue;		//�����趨ֵ
	float ActualValue;		//����ʵ��ֵ

	float err;		//����ƫ��ֵ
	float err_last;		//������һ��ƫ��ֵ
	float err_prev;		//����ǰһ��ƫ��ֵ

	float KP,KI,KD;		//������������֡�΢��

	float P_Out,I_Out,D_Out;		//����PID�����
	float	Total_Out;		//�����������
	float Out_Limit;		//��������޷�
	float Integral_Limit;		//��������޷�
}PID_InitTypeDef;

float Limit(float vlaue, float out_limit);		//�޷�
void PID_Init(PID_InitTypeDef *PID_InitStruct, float kp, float ki, float kd, float out_limit, float integral_limit);		//PID��ʼ��
void PID_Calc_Incremental(PID_InitTypeDef *PID_InitStruct, int speed_now, int speed_expected);		//����ʽPID����
void PID_Calc_Positional(PID_InitTypeDef *PID_InitStruct, float devition_expected, float devation_now);		//λ��ʽPID����

#endif