/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ790875685)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC32G12K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-12-18
 ********************************************************************************************************************/

#include "headfile.h"


/*
 *�����ں�Ƶ�ʵ��趨�����Բ鿴board.h�ļ�
 *��board_init��,�Ѿ���P54��������Ϊ��λ
 *�����Ҫʹ��P54����,������board.c�ļ��е�board_init()������ɾ��SET_P54_RESRT����
 */

uint8  dir = 0;
int16 duty = 0;
 
void main()
{
    WTST = 0;               //���ó������ȴ���������ֵΪ0�ɽ�CPUִ�г�����ٶ�����Ϊ���
    
	DisableGlobalIRQ();		//�ر����ж�
	
    //sys_clk��ѡֵ:35000000��30000000, 27000000. 24000000, 22118400, 20000000, 18432000, 12000000, 11059200, 6000000, 5529600��
    //����ϵͳƵ�ʣ���Ƶ����Ҫ��STC-ISP����е� <�����û��������е�IRCƵ��>ѡ���Ƶ��һ�¡�
    //���Ƶ�����ò��ԣ����ᵼ�´��ڵ����ݲ�����,PWM�Ĺ����������ȵȡ�
    sys_clk = 35000000;     //����ϵͳƵ��Ϊ35MHz
    
	board_init();		//��ʼ��

    pwm_init(PWMA_CH1P_P60, 17000, 0); //��ʼ��PWM1  ʹ��P60����  ��ʼ��Ƶ��Ϊ17Khz
	pwm_init(PWMA_CH2P_P62, 17000, 0); //��ʼ��PWM2  ʹ��P62����  ��ʼ��Ƶ��Ϊ17Khz
	
	pwm_init(PWMA_CH3P_P64, 17000, 0); //��ʼ��PWM3  ʹ��P64����  ��ʼ��Ƶ��Ϊ17Khz
	pwm_init(PWMA_CH4P_P66, 17000, 0); //��ʼ��PWM4  ʹ��P66����  ��ʼ��Ƶ��Ϊ17Khz
	
	EnableGlobalIRQ();	//�������ж�
    while(1)
	{
     
		if(dir)                                 
        {
            duty++;
            if(PWM_DUTY_MAX<=duty)   dir = 0;
        }
        else                                    
        {
            duty--;
            if(-PWM_DUTY_MAX>=duty)   dir = 1;
        }
		
        delay_ms(1);
       
        if(duty >= 0) //��ת
        {
            pwm_duty(PWMA_CH1P_P60, duty);       
            pwm_duty(PWMA_CH2P_P62,0);     
                     
			pwm_duty(PWMA_CH3P_P64, duty);       
            pwm_duty(PWMA_CH4P_P66,0);  			
        }
        else         //��ת
        {
            pwm_duty(PWMA_CH1P_P60,0);          
            pwm_duty(PWMA_CH2P_P62, -duty);  
                     
			pwm_duty(PWMA_CH3P_P64,0);          
            pwm_duty(PWMA_CH4P_P66, -duty);			
        }
	}	
}

