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
 * ϵͳƵ�ʣ��ɲ鿴board.h�е� FOSC �궨���޸ġ�
 * board.h�ļ���FOSC��ֵ����Ϊ0,������Զ�����ϵͳƵ��Ϊ33.1776MHZ
 * ��board_init��,�Ѿ���P54��������Ϊ��λ
 * �����Ҫʹ��P54����,������board.c�ļ��е�board_init()������ɾ��SET_P54_RESRT����
 */


uint16 distance[5]={0,0,0,0,0};
uint16 distance_out=0;

sbit led = P3^1;
void main()
{
	board_init();			// ��ʼ���Ĵ���,��ɾ���˾���롣
	
	// �˴���д�û�����(���磺�����ʼ�������)

	while(dl1a_init())
	{
		delay_ms(500);
		//printf("VL53L0X init try again.\r\n");
	}
	
	pit_timer_ms(TIM_4, 5);
	
    while(1)
	{
		if(dl1a_finsh_flag)
		{
			//if(dl1a_distance_mm<8190)
			//printf("%d\r\n", dl1a_distance_mm);
			
			//printf("%d\r\n", distance_out);
			if(dl1a_distance_mm<900) led=0;
			else led=1;
			
			dl1a_finsh_flag = 0;
		}
    }
}


// �ú�����isr.c�е�TM4_Isr������
void pit_handler(void)
{
	dl1a_get_distance();
	
//	distance[4]=distance[3];
//	distance[3]=distance[2];
//	distance[2]=distance[1];
//	distance[1]=distance[0];
//	distance[0]=dl1a_distance_mm;
//	distance_out=distance[0]+distance[1]+distance[2]+distance[3]+distance[4];
//	
//	
//	distance_out/=5;
	
	//if(distance_out>=1000) distance_out=1000;
	
}



