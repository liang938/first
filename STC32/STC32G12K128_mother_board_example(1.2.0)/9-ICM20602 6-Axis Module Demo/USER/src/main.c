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

uint8 test1[] = "seekfree wireless to uart test\n";
uint8 test2[] = "seekfree.taobao.com\n";

 
void main()
{
    WTST = 0;               //���ó������ȴ���������ֵΪ0�ɽ�CPUִ�г�����ٶ�����Ϊ���
    
	DisableGlobalIRQ();		//�ر����ж�
	
    //sys_clk��ѡֵ:35000000��30000000, 27000000. 24000000, 22118400, 20000000, 18432000, 12000000, 11059200, 6000000, 5529600��
    //����ϵͳƵ�ʣ���Ƶ����Ҫ��STC-ISP����е� <�����û��������е�IRCƵ��>ѡ���Ƶ��һ�¡�
    //���Ƶ�����ò��ԣ����ᵼ�´��ڵ����ݲ�����,PWM�Ĺ����������ȵȡ�
    sys_clk = 35000000;     //����ϵͳƵ��Ϊ35MHz
    
	board_init();		//��ʼ��
    
//	lcd_init();							//1.8��TFT��ʼ��
//	ips114_init();						//��ʼ��1.14��IPS��Ļ
//	oled_init_spi();					//OLED��ʼ��
			
    icm20602_init_simspi();    			//���������ǳ�ʼ��
	
	EnableGlobalIRQ();					//�������ж�
    while(1)
	{
		get_icm20602_gyro_simspi(); 		//��ȡ���ٶ�����
        get_icm20602_accdata_simspi();    	//��ȡ����������
		
		//��TFT����ʾ����Ҫ��ʼ��1.8��TFT��Ļ������ʹ�á�
//		lcd_showstr(0, 0, "acc.x=");
//		lcd_showstr(0, 1, "acc.y=");
//		lcd_showstr(0, 2, "acc.z=");
//		lcd_showstr(0, 3, "gyro.x=");
//		lcd_showstr(0, 4, "gyro.y=");
//		lcd_showstr(0, 5, "gyro.z=");
//		lcd_showint16(6*10, 0, icm_acc_x);
//		lcd_showint16(6*10, 1, icm_acc_y);
//		lcd_showint16(6*10, 2, icm_acc_z);
//		lcd_showint16(6*10, 3, icm_gyro_x);
//		lcd_showint16(6*10, 4, icm_gyro_y);
//		lcd_showint16(6*10, 5, icm_gyro_z);

		printf("acc.z=%d\r\n",  icm_acc_z);
		//��1.14IPS��Ļ����ʾ����Ҫ��ʼ��1.14��ips��Ļ������ʹ�á�
//		ips114_showstr(0, 0, "acc.x=");
//		ips114_showstr(0, 1, "acc.y=");
//		ips114_showstr(0, 2, "acc.z=");
//		ips114_showstr(0, 3, "gyro.x=");
//		ips114_showstr(0, 4, "gyro.y=");
//		ips114_showstr(0, 5, "gyro.z=");
//		ips114_showint16(6*10, 0, icm_acc_x);
//		ips114_showint16(6*10, 1, icm_acc_y);
//		ips114_showint16(6*10, 2, icm_acc_z);
//		ips114_showint16(6*10, 3, icm_gyro_x);
//		ips114_showint16(6*10, 4, icm_gyro_y);
//		ips114_showint16(6*10, 5, icm_gyro_z);
		
		//��OLED��Ļ����ʾ����Ҫ��ʼ��OLED��Ļ������ʹ�á�
//		oled_p6x8str_spi(0, 0, "acc.x=");
//		oled_p6x8str_spi(0, 1, "acc.y=");
//		oled_p6x8str_spi(0, 2, "acc.z=");
//		oled_p6x8str_spi(0, 3, "gyro.x=");
//		oled_p6x8str_spi(0, 4, "gyro.y=");
//		oled_p6x8str_spi(0, 5, "gyro.z=");
//		oled_int16_spi(6*10, 0, icm_acc_x);
//		oled_int16_spi(6*10, 1, icm_acc_y);
//		oled_int16_spi(6*10, 2, icm_acc_z);
//		oled_int16_spi(6*10, 3, icm_gyro_x);
//		oled_int16_spi(6*10, 4, icm_gyro_y);
//		oled_int16_spi(6*10, 5, icm_gyro_z);
		
		delay_ms(100);
	}
}

