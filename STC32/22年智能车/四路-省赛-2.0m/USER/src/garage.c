#include "headfile.h"

extern bit Stop_flag;
extern bit Garage_in_flag;						//�ж��Ƿ��복��
extern bit Garage_out_flag;						//�ж��Ƿ������

void Garage_out()
{
//ֱ��
	pwm_duty(PWMB_CH1_P74,840);
	pwm_duty(PWMA_CH2P_P62, 5000);						//����pwm��0	
	pwm_duty(PWMA_CH3P_P64, 5000);						//����pwm��0
	delay_ms(250);
//������ת:+60																									��ת:-60
	pwm_duty(PWMB_CH1_P74,840+60);						//                  pwm_duty(PWMB_CH1_P74,840-60);								
	pwm_duty(PWMA_CH2P_P62, 5000);						//����pwm��0	      pwm_duty(PWMA_CH2P_P62, 8000);
	pwm_duty(PWMA_CH3P_P64, 8000);						//����pwm��0        pwm_duty(PWMA_CH3P_P64, 5000);
	delay_ms(380);
	Garage_out_flag=1;
}

//ֱ�����
//void Garage_in()
//{
//	pwm_duty(PWMB_CH1_P74,840+60);						//                  pwm_duty(PWMB_CH1_P74,840-60);								
//	pwm_duty(PWMA_CH2P_P62, 3000);						//����pwm��0	      pwm_duty(PWMA_CH2P_P62, 8000);
//	pwm_duty(PWMA_CH3P_P64, 5000);						//����pwm��0        pwm_duty(PWMA_CH3P_P64, 5000);
//	delay_ms(250);
//	pwm_duty(PWMB_CH1_P74,840);						// 
//	pwm_duty(PWMA_CH2P_P62, 5000);						//����pwm��0	      pwm_duty(PWMA_CH2P_P62, 8000);
//	pwm_duty(PWMA_CH3P_P64, 5000);						//����pwm��0        pwm_duty(PWMA_CH3P_P64, 5000);
//	delay_ms(50);
////�����ת����
//	pwm_duty(PWMB_CH1_P74,840);
//	pwm_duty(PWMA_CH2P_P62, 0);						//����pwm��0	
//	pwm_duty(PWMA_CH3P_P64, 0);						//����pwm��0
////ֱ�е���
//	pwm_duty(PWMB_CH1_P74,840);
//	pwm_duty(PWMA_CH1P_P60, 8000);				//����
//	pwm_duty(PWMA_CH4P_P66, 8000);				//�ҵ��
//	delay_ms(350);
////��ȫͣ�º�ֹͣ�˶�
//	pwm_duty(PWMB_CH1_P74,840);
//	pwm_duty(PWMA_CH1P_P60, 0);						//����
//	pwm_duty(PWMA_CH2P_P62, 0);						//����
//	pwm_duty(PWMA_CH3P_P64, 0);						//����
//	pwm_duty(PWMA_CH4P_P66, 0);						//�ҵ��
//	while(1);
//}

void Garage_in()
{
//�����ת����
	pwm_duty(PWMB_CH1_P74,840);
	pwm_duty(PWMA_CH2P_P62, 0);						//����pwm��0	
	pwm_duty(PWMA_CH3P_P64, 0);						//����pwm��0
//ֱ�е���
	pwm_duty(PWMB_CH1_P74,840);
	pwm_duty(PWMA_CH1P_P60, 8000);				//����
	pwm_duty(PWMA_CH4P_P66, 8000);				//�ҵ��
	delay_ms(550);
//��ǵ�����⣬��ߣ�+60                             �ұߣ�-60
	pwm_duty(PWMB_CH1_P74,840+60);				//            pwm_duty(PWMB_CH1_P74,840-60);
	pwm_duty(PWMA_CH1P_P60, 5000);				//����			pwm_duty(PWMA_CH1P_P60, 8000);
	pwm_duty(PWMA_CH4P_P66, 8000);				//�ҵ��			pwm_duty(PWMA_CH4P_P66, 5000);
	delay_ms(450);
//��������ˣ�������ȫ���복��
	pwm_duty(PWMB_CH1_P74,840);
	pwm_duty(PWMA_CH1P_P60, 5000);				//����
	pwm_duty(PWMA_CH4P_P66, 5000);				//�ҵ��
	delay_ms(100);
//�����ת����ֹ����Ժ���
	pwm_duty(PWMB_CH1_P74,840);
	pwm_duty(PWMA_CH1P_P60, 0);						//����
	pwm_duty(PWMA_CH2P_P62, 8000);				//����	
	pwm_duty(PWMA_CH3P_P64, 8000);				//����
	pwm_duty(PWMA_CH4P_P66, 0);						//�ҵ��
	delay_ms(300);
//��ȫͣ�º�ֹͣ�˶�
	pwm_duty(PWMB_CH1_P74,840);
	pwm_duty(PWMA_CH1P_P60, 0);						//����
	pwm_duty(PWMA_CH2P_P62, 0);						//����
	pwm_duty(PWMA_CH3P_P64, 0);						//����
	pwm_duty(PWMA_CH4P_P66, 0);						//�ҵ��
	while(1);
}


