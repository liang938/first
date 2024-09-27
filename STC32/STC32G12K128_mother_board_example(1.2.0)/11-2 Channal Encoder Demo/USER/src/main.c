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
 
//�����̽�֧�ִ�����ı���������

//������������
#define SPEEDL_PLUSE   CTIM0_P34
#define SPEEDR_PLUSE   CTIM3_P04
//���巽������
#define SPEEDL_DIR     P35
#define SPEEDR_DIR     P53

int16 templ_pluse = 0;
int16 tempr_pluse = 0;

void main()
{
    WTST = 0;               //���ó������ȴ���������ֵΪ0�ɽ�CPUִ�г�����ٶ�����Ϊ���
    
	DisableGlobalIRQ();		//�ر����ж�
	
    //sys_clk��ѡֵ:35000000��30000000, 27000000. 24000000, 22118400, 20000000, 18432000, 12000000, 11059200, 6000000, 5529600��
    //����ϵͳƵ�ʣ���Ƶ����Ҫ��STC-ISP����е� <�����û��������е�IRCƵ��>ѡ���Ƶ��һ�¡�
    //���Ƶ�����ò��ԣ����ᵼ�´��ڵ����ݲ�����,PWM�Ĺ����������ȵȡ�
    sys_clk = 35000000;     //����ϵͳƵ��Ϊ35MHz
    
	board_init();		//��ʼ��
    
	ctimer_count_init(SPEEDL_PLUSE);	//��ʼ����ʱ��0��Ϊ�ⲿ����
	ctimer_count_init(SPEEDR_PLUSE);	//��ʼ����ʱ��3��Ϊ�ⲿ����
//	lcd_init();							//1.8��TFT��ʼ��
	ips114_init();						//��ʼ��1.14��IPS��Ļ
//	oled_init_spi();					//OLED��ʼ��
	
	EnableGlobalIRQ();					//�������ж�
    while(1)
	{
        //��ȡ�ɼ����ı�����������
        templ_pluse = ctimer_count_read(SPEEDL_PLUSE);
		tempr_pluse = ctimer_count_read(SPEEDR_PLUSE);

        //����������
        ctimer_count_clean(SPEEDL_PLUSE);
		ctimer_count_clean(SPEEDR_PLUSE);

        //�ɼ�������Ϣ
        if(1 == SPEEDL_DIR)    
        {
            templ_pluse = -templ_pluse;
        }
        else                  
        {
            templ_pluse = templ_pluse;
        }
		if(1 == SPEEDR_DIR)    
        {
            tempr_pluse = -tempr_pluse;
        }
        else                  
        {
            tempr_pluse = tempr_pluse;
        }            
		
		//��TFT����ʾ����Ҫ��ʼ��1.8��TFT��Ļ������ʹ�á�
//		lcd_showstr(0, 0, "pluse_l =");			lcd_showint16(8*10, 0, templ_pluse);
//		lcd_showstr(0, 1, "pluse_r =");			lcd_showint16(8*10, 1, tempr_pluse);

		//��1.14IPS��Ļ����ʾ����Ҫ��ʼ��1.14��ips��Ļ������ʹ�á�
		ips114_showstr(0, 0, "pluse_l =");		ips114_showint16(8*10, 0, templ_pluse);
		ips114_showstr(0, 1, "pluse_r =");		ips114_showint16(8*10, 1, tempr_pluse);
		
		//��OLED��Ļ����ʾ����Ҫ��ʼ��OLED��Ļ������ʹ�á�
//		oled_p6x8str_spi(0, 0, "pluse_l =");	oled_int16_spi(8*10, 0, templ_pluse);
//		oled_p6x8str_spi(0, 1, "pluse_r =");	oled_int16_spi(8*10, 1, tempr_pluse);
		
		//��ʱ100ms
		delay_ms(100);
	}
}

