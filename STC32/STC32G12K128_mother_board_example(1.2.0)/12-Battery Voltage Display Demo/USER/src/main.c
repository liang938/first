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
 
#define BAT_VOL_PIN ADC_P15

uint16 ad_result = 0;           //���ŵ�ѹ
uint16 battery_voltage = 0;     //��ص�ѹ

uint32 temp;
    
void main()
{
    WTST = 0;               //���ó������ȴ���������ֵΪ0�ɽ�CPUִ�г�����ٶ�����Ϊ���
    
	DisableGlobalIRQ();		//�ر����ж�
	
    //sys_clk��ѡֵ:35000000��30000000, 27000000. 24000000, 22118400, 20000000, 18432000, 12000000, 11059200, 6000000, 5529600��
    //����ϵͳƵ�ʣ���Ƶ����Ҫ��STC-ISP����е� <�����û��������е�IRCƵ��>ѡ���Ƶ��һ�¡�
    //���Ƶ�����ò��ԣ����ᵼ�´��ڵ����ݲ�����,PWM�Ĺ����������ȵȡ�
    sys_clk = 35000000;     //����ϵͳƵ��Ϊ35MHz
    
	board_init();		//��ʼ��
    
    adc_init(BAT_VOL_PIN, ADC_SYSclk_DIV_32);
	
//	lcd_init();							//1.8��TFT��ʼ��
	ips114_init();						//��ʼ��1.14��IPS��Ļ
//	oled_init_spi();					//OLED��ʼ��
	
	EnableGlobalIRQ();					//�������ж�
	
    while(1)
	{
		ad_result = adc_once(BAT_VOL_PIN, ADC_12BIT);
		temp = (((uint32)ad_result * 5000) / 4096);  //�������ǰadc���ŵĵ�ѹ ���㹫ʽΪ ad_result*VCC/ADC�ֱ���    VCC��λΪmv
		battery_voltage =  temp * 4;//�������ŵ�ѹ  �ͷ�ѹ�������ֵ�����ص�ѹ ���㹫˾Ϊ   ���ŵ�ѹ*(R2+R3)/R3   R3Ϊ�ӵض˵���
		
		//��TFT����ʾ����Ҫ��ʼ��1.8��TFT��Ļ������ʹ�á�
//		lcd_showstr(0, 0, "voltage:");
//		lcd_showuint16(8*8, 0, battery_voltage);
		
		//��1.14IPS��Ļ����ʾ����Ҫ��ʼ��1.14��ips��Ļ������ʹ�á�
		ips114_showstr(0, 0, "voltage:");
		ips114_showuint16(8*8, 0, battery_voltage);
		ips114_showstr(0, 1, "ADC = ");
		ips114_showuint16(8*8, 1, ad_result);
		
		//��OLED��Ļ����ʾ����Ҫ��ʼ��OLED��Ļ������ʹ�á�
//		oled_p6x8str_spi(0, 0, "voltage:");
//		oled_uint16_spi(8*8, 0, battery_voltage);
		
		//��ʱ100ms
		delay_ms(100);
    }
}



