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

uint16 data1,data2,data3,data4;
 
void main()
{
    WTST = 0;               //���ó������ȴ���������ֵΪ0�ɽ�CPUִ�г�����ٶ�����Ϊ���
    
	DisableGlobalIRQ();		//�ر����ж�
	
    //sys_clk��ѡֵ:35000000��30000000, 27000000. 24000000, 22118400, 20000000, 18432000, 12000000, 11059200, 6000000, 5529600��
    //����ϵͳƵ�ʣ���Ƶ����Ҫ��STC-ISP����е� <�����û��������е�IRCƵ��>ѡ���Ƶ��һ�¡�
    //���Ƶ�����ò��ԣ����ᵼ�´��ڵ����ݲ�����,PWM�Ĺ����������ȵȡ�
    sys_clk = 35000000;     //����ϵͳƵ��Ϊ35MHz
    
	board_init();		//��ʼ��

	adc_init(ADC_P00,0);						//P00����		����ͨ�������Ŷ�Ӧ��ϵ���Բ鿴zf_adc.h�ļ�
	adc_init(ADC_P01,0);						//P01����		����ͨ�������Ŷ�Ӧ��ϵ���Բ鿴zf_adc.h�ļ�
	adc_init(ADC_P05,0);						//P05����		����ͨ�������Ŷ�Ӧ��ϵ���Բ鿴zf_adc.h�ļ�
	adc_init(ADC_P06,0);						//P06����		����ͨ�������Ŷ�Ӧ��ϵ���Բ鿴zf_adc.h�ļ�
	
//	lcd_init();									//1.8��TFT��ʼ��
	ips114_init();								//��ʼ��1.14��IPS��Ļ
//	oled_init_spi();							//OLED��ʼ��
	
	EnableGlobalIRQ();	//�������ж�
    while(1)
	{
     
        data1 = adc_once(ADC_P00,ADC_12BIT);  	//�ɼ�ADC_P00��ѹ������12λ
		data2 = adc_once(ADC_P01,ADC_10BIT); 	//�ɼ�ADC_P01��ѹ������10λ
		data3 = adc_once(ADC_P05,ADC_8BIT);		//�ɼ�ADC_P05��ѹ������8λ
		data4 = adc_once(ADC_P06,ADC_8BIT);		//�ɼ�ADC_P06��ѹ������8λ
		
		//��TFT����ʾ����Ҫ��ʼ��1.8��TFT��Ļ������ʹ�á�
//		lcd_showstr(0,0,"data1:");	
//		lcd_showuint16(6*8,0,data1);
//		lcd_showstr(0,1,"data2:");	
//		lcd_showuint16(6*8,1,data2);
//		lcd_showstr(0,2,"data3:");	
//		lcd_showuint16(6*8,2,data3);
//		lcd_showstr(0,3,"data4:");	
//		lcd_showuint16(6*8,3,data4);
		
		//��1.14IPS��Ļ����ʾ����Ҫ��ʼ��1.14��ips��Ļ������ʹ�á�
		ips114_showstr(0,0,"data1:");	
		ips114_showuint16(6*8,0,data1);
		ips114_showstr(0,1,"data2:");	
		ips114_showuint16(6*8,1,data2);
		ips114_showstr(0,2,"data3:");	
		ips114_showuint16(6*8,2,data3);
		ips114_showstr(0,3,"data4:");	
		ips114_showuint16(6*8,3,data4);

		//��OLED��Ļ����ʾ����Ҫ��ʼ��OLED��Ļ������ʹ�á�
//		oled_p6x8str_spi(0,0,"data1:");	
//		oled_uint16_spi(6*8,0,data1);
//		oled_p6x8str_spi(0,1,"data2:");	
//		oled_uint16_spi(6*8,1,data2);
//		oled_p6x8str_spi(0,2,"data3:");	
//		oled_uint16_spi(6*8,2,data3);
//		oled_p6x8str_spi(0,3,"data4:");	
//		oled_uint16_spi(6*8,3,data4);

	}	
}

