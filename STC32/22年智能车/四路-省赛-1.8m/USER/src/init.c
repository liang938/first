#include "headfile.h"


extern PID_InitTypeDef PID_Servos;		//���PID�ṹ�����	

void Init_all()
{
	WTST = 0;							//���ó������ȴ���������ֵΪ0�ɽ�CPUִ�г�����ٶ�����Ϊ���  
	DisableGlobalIRQ();		//�ر����ж�
	sys_clk = 35000000;		//����ϵͳƵ��Ϊ35MHz
  board_init();					//��ʼ���Ĵ���
	pit_timer_ms(TIM_4, 10);								//���ö�ʱ��4��5ms��һ���жϣ����ڶ�ȡ�������ٶ�

//pid��ʼ��  PID_Init(�ṹ��, KP, KI, KD, ����޷�, �����޷�)
	PID_Init(&PID_Servos, 0, 0, 0, 0, 0);					//���PID��ʼ��

	delay_ms(500);

	EnableGlobalIRQ();		//�������ж�
}