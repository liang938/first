#include "headfile.h"

void main()
{
  WTST = 0;               //���ó������ȴ���������ֵΪ0�ɽ�CPUִ�г�����ٶ�����Ϊ���  
	DisableGlobalIRQ();		//�ر����ж�
  sys_clk = 35000000;     //����ϵͳƵ��Ϊ35MHz
	board_init();			//��ʼ���Ĵ���
		pwm_init(PWMA_CH1P_P60, 15000, 0);		//����
	pwm_init(PWMA_CH2P_P62, 15000, 0);		//����-����
	pwm_init(PWMA_CH3P_P64, 15000, 0);		//�ҵ��
	pwm_init(PWMA_CH4P_P66, 15000, 0);		//�ҵ��-����
	EnableGlobalIRQ();		//�������ж�
  while(1)
	{
			pwm_duty(PWMA_CH1P_P60, 2000);		//��������pwm
		pwm_duty(PWMA_CH2P_P62, 0);
		pwm_duty(PWMA_CH3P_P64, 0);
		pwm_duty(PWMA_CH4P_P66, 2000);		//��������pwm
  }
}

