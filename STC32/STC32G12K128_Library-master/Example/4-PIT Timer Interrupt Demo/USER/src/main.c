#include "headfile.h"
#include "Encoder.h"

void Init_all(void)
{
	WTST = 0;						//���ó������ȴ���������ֵΪ0�ɽ�CPUִ�г�����ٶ�����Ϊ���  
	DisableGlobalIRQ();				//�ر����ж�
	sys_clk = 35000000;				//����ϵͳƵ��Ϊ35MHz
	board_init();					//��ʼ���Ĵ���

//OLED��ʼ��
	oled_init();					//��ʼ��oled��Ļ
	
//��ʱ����ʼ��
	pit_timer_ms(TIM_4, 10);		//���ö�ʱ��4��5ms��һ���жϣ����ڶ�ȡ�������ٶ�
//��������ʼ��
	ctimer_count_init(CTIM0_P34);	//��ʱ���ⲿ����ģʽ--����
	ctimer_count_init(CTIM3_P04);	//��ʱ���ⲿ����ģʽ--����

	
}

void main(void)
{
	Init_all();

	//���ж������
	EnableGlobalIRQ();		//�������ж�
    while(1)
	{
		oled_p8x16str(0,0,"Enc:");							//main�ļ��еı���
		oled_printf_float(0,2,Enc_L,2,3);
		oled_printf_float(0,4,Enc_R,2,3);
    }
}



