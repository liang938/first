#include "headfile.h"

extern PID_InitTypeDef PID_Left;			//����PID�ṹ�����	
extern PID_InitTypeDef PID_Right;			//����PID�ṹ�����	
extern PID_InitTypeDef PID_Servos;		//���PID�ṹ�����	

void Init_all()
{
	WTST = 0;							//���ó������ȴ���������ֵΪ0�ɽ�CPUִ�г�����ٶ�����Ϊ���  
	DisableGlobalIRQ();		//�ر����ж�
	sys_clk = 35000000;		//����ϵͳƵ��Ϊ35MHz
  board_init();					//��ʼ���Ĵ���

//�����ǳ�ʼ��
	mpu6050_init();

//adc��ʼ��
	adc_init(ADC_P00, ADC_SYSclk_DIV_2);
	adc_init(ADC_P05, ADC_SYSclk_DIV_2);
	adc_init(ADC_P06, ADC_SYSclk_DIV_2);
	adc_init(ADC_P16, ADC_SYSclk_DIV_2);

//��������ʼ��
	ctimer_count_init(CTIM0_P34);					//��ʱ���ⲿ����ģʽ--����
	ctimer_count_init(CTIM3_P04);					//��ʱ���ⲿ����ģʽ--����
	pit_timer_ms(TIM_4, 5);								//���ö�ʱ��4��5ms��һ���жϣ����ڶ�ȡ�������ٶ�

//pwm��ʼ��
	pwm_init(PWMA_CH1P_P60, 15000, 0);		//����
	pwm_init(PWMA_CH2P_P62, 15000, 0);		//����-����
	pwm_init(PWMA_CH3P_P64, 15000, 0);		//�ҵ��
	pwm_init(PWMA_CH4P_P66, 15000, 0);		//�ҵ��-����
	pwm_init(PWMB_CH1_P74, 50, 0);				//���

//pid��ʼ��  PID_Init(�ṹ��, KP, KI, KD, ����޷�, �����޷�)
	PID_Init(&PID_Left, 200, 4, 0, 8000, 5000);			//����PID��ʼ��
	PID_Init(&PID_Right, 200, 4, 0, 8000, 5000);		//����PID��ʼ��
	PID_Init(&PID_Servos, 0, 0, 0, 60, 0);					//���PID��ʼ��

	delay_ms(500);

	EnableGlobalIRQ();		//�������ж�
}