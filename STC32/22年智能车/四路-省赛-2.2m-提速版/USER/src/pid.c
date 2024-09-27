#include "headfile.h"

float err_add = 0;
extern int leftspeed;										//���ֲ��ٶ�
extern int rightspeed;									//���ֲ��ٶ�
extern int encoder_left;								//���ֱ���������
extern int encoder_right;								//���ֱ���������

void PID_Init(PID_InitTypeDef *PID_InitStruct, float kp, float ki, float kd, float out_limit, float integral_limit)		//PID��ʼ��
{
	PID_InitStruct->KP = kp;
	PID_InitStruct->KI = ki;
	PID_InitStruct->KD = kd;
	PID_InitStruct->err = 0;
	PID_InitStruct->err_last = 0;
	PID_InitStruct->err_prev = 0;
	PID_InitStruct->Total_Out = 0;
	PID_InitStruct->Out_Limit = out_limit;
	PID_InitStruct->Integral_Limit = integral_limit;
}

float Limit(float value, float limit)		//�޷�
{
	value = (value<-limit)?-limit:value;
	value = (value>limit)?limit:value;		//�ж��Ƿ񳬳��޷�
	return value;	
}

void PID_Calc_Positional(PID_InitTypeDef *PID_InitStruct, float deviation_expected, float deviation_now)		//λ��ʽPID����
{
	PID_InitStruct->ExpectedValue = deviation_expected;		//����ƫ��ֵ
	PID_InitStruct->ActualValue = deviation_now;					//ʵ��ƫ��ֵ

	PID_InitStruct->err = (PID_InitStruct->ExpectedValue)-(PID_InitStruct->ActualValue);		//errֵΪ����ƫ���뵱ǰƫ��Ĳ�ֵ
	
	err_add += PID_InitStruct->err;		//���ֵ�ۼ�

	PID_InitStruct->P_Out = (PID_InitStruct->err)*(PID_InitStruct->KP);		//�������Ʋ��� P_Out=KP*err
	PID_InitStruct->I_Out = err_add*(PID_InitStruct->KI);									//���ֿ��Ʋ���	I_Out+=KI*err
	PID_InitStruct->D_Out = ((PID_InitStruct->err)-(PID_InitStruct->err_last))*(PID_InitStruct->KD);			//΢�ֿ��Ʋ��� D_Out=KD*(err-err_last)
	
	PID_InitStruct->I_Out = Limit(PID_InitStruct->I_Out, PID_InitStruct->Integral_Limit);									//�����޷�

	PID_InitStruct->Total_Out = (PID_InitStruct->P_Out)+(PID_InitStruct->I_Out)+(PID_InitStruct->D_Out);	//�����������
	PID_InitStruct->Total_Out = Limit(PID_InitStruct->Total_Out, PID_InitStruct->Out_Limit);							//����޷�

	PID_InitStruct->err_last = PID_InitStruct->err;		//������һ��err
}

void PID_Calc_Incremental(PID_InitTypeDef *PID_InitStruct, int speed_expected, int speed_now)		//����ʽPID����
{
	PID_InitStruct->ExpectedValue = speed_expected;		//�����ٶ�
	PID_InitStruct->ActualValue = speed_now;					//��ǰ�ٶ�

	PID_InitStruct->err = (PID_InitStruct->ExpectedValue)-(PID_InitStruct->ActualValue);								//errֵΪ�����ٶ��뵱ǰ�ٶȵĲ�ֵ

	PID_InitStruct->P_Out += ((PID_InitStruct->err)-(PID_InitStruct->err_last))*(PID_InitStruct->KP);		//�������Ʋ���	P_Out=KP*(err-err_last)

	PID_InitStruct->I_Out += (PID_InitStruct->err)*(PID_InitStruct->KI);																//���ֿ��Ʋ���	I_Out=KI*error
	PID_InitStruct->I_Out = Limit(PID_InitStruct->I_Out, PID_InitStruct->Integral_Limit);								//�����޷�
	
	PID_InitStruct->D_Out += ((PID_InitStruct->err)-2*(PID_InitStruct->err_last)+(PID_InitStruct->err_prev))*(PID_InitStruct->KD);		//΢�ֿ��Ʋ���	D_Out=KD*(err-2*err_last+err_prev)

	PID_InitStruct->Total_Out = (PID_InitStruct->P_Out)+(PID_InitStruct->I_Out)+(PID_InitStruct->D_Out);//�����������
	PID_InitStruct->Total_Out = Limit(PID_InitStruct->Total_Out, PID_InitStruct->Out_Limit);						//����޷�
  PID_InitStruct->Total_Out = (PID_InitStruct->Total_Out<0)?0:PID_InitStruct->Total_Out;

	PID_InitStruct->err_prev = PID_InitStruct->err_last;		//����ǰһ��err
	PID_InitStruct->err_last = PID_InitStruct->err;					//������һ��err
}






