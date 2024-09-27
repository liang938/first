#include "headfile.h"

int ADC_MIN = 0;											//��вɼ���Сֵ
int ADC_MAX = 100;											//��вɼ����ֵ
int READ_MAX = 100;										//��й�һ�������ֵ
int ad[4][3];													//��ά���飬�洢��·adc�����ɼ����εĵ��ֵ
int temp;															//��ֵ�˲���ʱ����
int sensor[4];												//�˲���ĵ�ǰ��·���ֵ
int time_count=0;											//ʱ����ֱ���
int servos_flag=0;										//�ж��Ƿ�Ϊ����
int servos_middle = 840;							//����м�λ��
int leftspeed,rightspeed;							//���ҵ�����ٶ�
int cross_num=0;											//��ֹʮ������
int cross_flag=0;											//ʮ�ֱ�־λ
float speed_add=0;										//ֱ������
float speed_err=0;										//ת���ٶ�����
float speed_low=0;										//ת����ٳ̶�,ԽС����Խ��
float l,lm,rm,r;											//�����С����С�����·���
float sensor_err;											//���ƫ��ֵ
float servos_err;											//���ƫ��ֵ
extern bit Stop_flag;									//���������־
extern bit Barrier_flag;							//���ϱ�־λ
extern int element_num;								//����Ԫ�ص�����
extern float Speed;										//Ԥ���ٶ�
extern PID_InitTypeDef PID_Servos;		//����ṹ�����

void ADC_Read()																//��вɼ�
{
	int i;
	for(i=0;i<3;i++)														//�����ɼ�3��
	{
		ad[0][i] = adc_once(ADC_P00, ADC_8BIT);		//һ·���
		ad[1][i] = adc_once(ADC_P05, ADC_8BIT);		//��·���
		ad[2][i] = adc_once(ADC_P06, ADC_8BIT);		//��·���
		ad[3][i] = adc_once(ADC_P16, ADC_8BIT);		//��·���
	}
	for(i=0;i<4;i++)														//��ֵ�˲�,ȡ�����ɼ����ε��ֵ���м�ֵ	
	{
		if(ad[i][0]>ad[i][1])
		{
			temp = ad[i][0];
			ad[i][0] = ad[i][1];
			ad[i][1] = temp;
		}
		if(ad[i][1]>ad[i][2])
		{
			temp = ad[i][0];
			ad[i][0] = ad[i][1];
			ad[i][1] = temp;
		}
		if(ad[i][0]>ad[i][1])
		{
			temp = ad[i][0];
			ad[i][0] = ad[i][1];
			ad[i][1] = temp;
		}
		ad[i][1] = (ad[i][1]>ADC_MAX)?ADC_MAX:ad[i][1];					//�Ե��ֵ�����޷�����
		ad[i][1] = 100*(ad[i][1]-ADC_MIN)/(ADC_MAX-ADC_MIN);		//��һ��,�����ֵ������0~100֮��
	}
	l = ad[0][1];					//����
	lm = ad[1][1];				//���е��
	rm = ad[2][1];				//���е��
	r = ad[3][1];					//�ҵ��
	if((l+lm+rm+r)<20)
		Stop_flag=1;
	circle_judge();
}

//λ��ƫ�����
void Pos_Deviation()	
{
	if(cross_flag==1)													//����ж�Ϊʮ�֣���ʼʱ����֣���ֹ�ھ���ʮ��ʱ����ж�Ϊʮ��
	{									
		cross_num+=1;														//��ʼʮ��ʱ�����
		if(cross_num==20)												//���ʮ��ʱ����ֵ���100ms
		{
			cross_flag=0;													//ʮ�ֱ�־����
			cross_num=0;													//ʮ��ʱ���������
		}
	}
	else	
	{
		if(servos_flag==0&&lm>50&&rm>50)															//�����ʮ��
		{
			cross_flag=1;																								//ʮ�ֱ�־����
			element_num+=1;																							//Ԫ��������һ
		}
	}
	if(servos_flag!=0)																							//����ǻ���
		circle_move();																								//����Ѱ��
	else																														//���������·��
		sensor_err = 100*(1.6*(l-r)+1.5*(lm-rm))/((l+r)+0.5*(lm+rm));	//��Ⱥ��㷨,ƫ��ֵС��������ת������������ת 
	if(-70<sensor_err&&sensor_err<70)
	{
		speed_add = 50;						//ֱ������
		speed_err	=	400;					//ֱ��ת���ٶ�����
		speed_low = 300;					//ת����ٳ̶�,ԽС����Խ��
		PID_Servos.KP = 0.4;
		PID_Servos.KI = 0;
		PID_Servos.KD = 4.5;
	}
	else
	{
		speed_add = 0;						//ֱ������
		speed_err	=	700;					//���ת���ٶ�����	
		speed_low = -500;					//ת����ٳ̶�,ԽС����Խ��
		PID_Servos.KP = 1;
		PID_Servos.KI = 0;
		PID_Servos.KD = 30;
	}
}

void Servos_Control()																								//������̬����
{

	if(servos_flag!=0)								//����ڻ�����
		time_count+=1;									//��ʼʱ�����

	//printf("%.0f,%.0f,%.0f,%.0f,%.0f,%d\n",l,lm,rm,r,sensor_err,servos_flag);
//�������
	PID_Calc_Positional(&PID_Servos, 0, sensor_err);									//������ֵ����
	pwm_duty(PWMB_CH1_P74,servos_middle-(int)PID_Servos.Total_Out);		//�������  

//�������
	if(sensor_err<0)
	{
		leftspeed = (int)((Speed+speed_add)*(1+PID_Servos.Total_Out/speed_err));
		rightspeed = (int)((Speed+speed_add)*(1-PID_Servos.Total_Out/(speed_err+speed_low)));
		//rightspeed = (int)(Speed+speed_add);
	}
	else
	{
		rightspeed = (int)((Speed+speed_add)*(1-PID_Servos.Total_Out/speed_err));
		leftspeed = (int)((Speed+speed_add)*(1+PID_Servos.Total_Out/(speed_err+speed_low)));
		//leftspeed = (int)(Speed+speed_add);
	}
	Speedcontrol(leftspeed, rightspeed);															//������ǰ�ٶ�
}










