#include "headfile.h"
#include "pid.h"
/*
 *�����ں�Ƶ�ʵ��趨�����Բ鿴board.h�ļ�
 *��board_init��,�Ѿ���P54��������Ϊ��λ
 *�����Ҫʹ��P54����,������board.c�ļ��е�board_init()������ɾ��SET_P54_RESRT����
 */

void main()
{
  WTST = 0;               //���ó������ȴ���������ֵΪ0�ɽ�CPUִ�г�����ٶ�����Ϊ���
	DisableGlobalIRQ();		//�ر����ж�
	sys_clk = 35000000;     //����ϵͳƵ��Ϊ35MHz   
	board_init();			//��ʼ���Ĵ���
	//���ж������
	EnableGlobalIRQ();		//�������ж�
	//pwm_init(PWMB_CH1_P74, 50, 0);		//���
	while(1)
	{
			//pwm_duty(PWMB_CH1_P74,750);
	}
}

