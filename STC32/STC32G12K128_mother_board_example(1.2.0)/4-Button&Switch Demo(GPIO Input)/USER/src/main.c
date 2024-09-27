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



//���尴������
#define KEY1_PIN    P70
#define KEY2_PIN    P71
#define KEY3_PIN    P72
#define KEY4_PIN    P73
//���岦�뿪������
#define SW1_PIN     P75
#define SW2_PIN     P76


//���뿪��״̬����
uint8 sw1_status;
uint8 sw2_status;

//����״̬����
uint8 key1_status = 1;
uint8 key2_status = 1;
uint8 key3_status = 1;
uint8 key4_status = 1;

//��һ�ο���״̬����
uint8 key1_last_status;
uint8 key2_last_status;
uint8 key3_last_status;
uint8 key4_last_status;

//���ر�־λ
uint8 key1_flag;
uint8 key2_flag;
uint8 key3_flag;
uint8 key4_flag;

uint8 test1=0,test2=0,test3=0,test4=0;





void main()
{
    WTST = 0;               //���ó������ȴ���������ֵΪ0�ɽ�CPUִ�г�����ٶ�����Ϊ���
    
	DisableGlobalIRQ();		//�ر����ж�
	
    //sys_clk��ѡֵ:35000000��30000000, 27000000. 24000000, 22118400, 20000000, 18432000, 12000000, 11059200, 6000000, 5529600��
    //����ϵͳƵ�ʣ���Ƶ����Ҫ��STC-ISP����е� <�����û��������е�IRCƵ��>ѡ���Ƶ��һ�¡�
    //���Ƶ�����ò��ԣ����ᵼ�´��ڵ����ݲ�����,PWM�Ĺ����������ȵȡ�
    sys_clk = 35000000;     //����ϵͳƵ��Ϊ35MHz
    
	board_init();		//��ʼ��

//	lcd_init();			//1.8��TFT��ʼ��
	ips114_init();		//��ʼ��1.14��IPS��Ļ
//	oled_init();		//OLED��ʼ��
	
	EnableGlobalIRQ();	//�������ж�
    while(1)
	{
		//��ȡ���뿪��״̬
        sw1_status = SW1_PIN;
        sw2_status = SW2_PIN;
        
        //ʹ�ô˷����ŵ����ڣ�����Ҫʹ��while(1) �ȴ������⴦������Դ�˷�
        //���水��״̬
        key1_last_status = key1_status;
        key2_last_status = key2_status;
        key3_last_status = key3_status;
        key4_last_status = key4_status;
        //��ȡ��ǰ����״̬
        key1_status = KEY1_PIN;
        key2_status = KEY2_PIN;
        key3_status = KEY3_PIN;
        key4_status = KEY4_PIN;
        
        //��⵽��������֮��  ���ſ���λ��־λ
        if(key1_status && !key1_last_status)    key1_flag = 1;
        if(key2_status && !key2_last_status)    key2_flag = 1;
        if(key3_status && !key3_last_status)    key3_flag = 1;
        if(key4_status && !key4_last_status)    key4_flag = 1;
        
        //��־λ��λ֮�󣬿���ʹ�ñ�־λִ���Լ���Ҫ�����¼�
        if(key1_flag)   
        {
            key1_flag = 0;//ʹ�ð���֮��Ӧ�������־λ
            test1++;
        }
        
        if(key2_flag)   
        {
            key2_flag = 0;//ʹ�ð���֮��Ӧ�������־λ
            test2++;
        }
        
        if(key3_flag)   
        {
            key3_flag = 0;//ʹ�ð���֮��Ӧ�������־λ
            test3++;
        }
        
        if(key4_flag)   
        {
            key4_flag = 0;//ʹ�ð���֮��Ӧ�������־λ
            test4++;
        }
        

//        //��TFT����ʾ���뿪��״̬����Ҫ�ȳ�ʼ��TFT��Ļ������ʹ�á�
//        lcd_showstr(0,1,"SW1 STATUS:");     lcd_showint32(11*8,1,sw1_status,1);
//        lcd_showstr(0,2,"SW2 STATUS:");     lcd_showint32(11*8,2,sw2_status,1);
//        //��TFT����ʾ���Ա���
//        lcd_showstr(0,3,"KEY1 TEST:");      lcd_showint32(11*8,3,test1,3);
//        lcd_showstr(0,4,"KEY2 TEST:");      lcd_showint32(11*8,4,test2,3);
//        lcd_showstr(0,5,"KEY3 TEST:");      lcd_showint32(11*8,5,test3,3);
//        lcd_showstr(0,6,"KEY4 TEST:");      lcd_showint32(11*8,6,test4,3);

		//��1.14��IPS��Ļ����ʾ���뿪��״̬����Ҫ��ʼ��1.14��IPS��Ļ������ʹ�á�
        ips114_showstr(0,1,"SW1 STATUS:");  ips114_showint32(11*8,1,sw1_status,1);
        ips114_showstr(0,2,"SW2 STATUS:");  ips114_showint32(11*8,2,sw2_status,1);
        //��1.14��IPS��Ļ����ʾ���Ա���
        ips114_showstr(0,3,"KEY1 TEST:");   ips114_showint32(11*8,3,test1,3);
        ips114_showstr(0,4,"KEY2 TEST:");   ips114_showint32(11*8,4,test2,3);
        ips114_showstr(0,5,"KEY3 TEST:");   ips114_showint32(11*8,5,test3,3);
        ips114_showstr(0,6,"KEY4 TEST:");   ips114_showint32(11*8,6,test4,3);
		
//		//��OLED��Ļ����ʾ���뿪��״̬����Ҫ��ʼ��OLED��Ļ������ʹ�á�
//        oled_p6x8str(0,1,"SW1 STATUS:");  	oled_printf_int32(11*8,1,sw1_status,1);
//        oled_p6x8str(0,2,"SW2 STATUS:");  	oled_printf_int32(11*8,2,sw2_status,1);
//        //��OLED��Ļ����ʾ���Ա���	
//        oled_p6x8str(0,3,"KEY1 TEST:");   	oled_printf_int32(11*8,3,test1,3);
//        oled_p6x8str(0,4,"KEY2 TEST:");   	oled_printf_int32(11*8,4,test2,3);
//        oled_p6x8str(0,5,"KEY3 TEST:");   	oled_printf_int32(11*8,5,test3,3);
//        oled_p6x8str(0,6,"KEY4 TEST:");   	oled_printf_int32(11*8,6,test4,3);

    }
}