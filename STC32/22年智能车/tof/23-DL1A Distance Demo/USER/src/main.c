/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ790875685)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC32G12K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-12-18
 ********************************************************************************************************************/
#include "headfile.h"


/*
 * 系统频率，可查看board.h中的 FOSC 宏定义修改。
 * board.h文件中FOSC的值设置为0,则程序自动设置系统频率为33.1776MHZ
 * 在board_init中,已经将P54引脚设置为复位
 * 如果需要使用P54引脚,可以在board.c文件中的board_init()函数中删除SET_P54_RESRT即可
 */


uint16 distance[5]={0,0,0,0,0};
uint16 distance_out=0;

sbit led = P3^1;
void main()
{
	board_init();			// 初始化寄存器,勿删除此句代码。
	
	// 此处编写用户代码(例如：外设初始化代码等)

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


// 该函数在isr.c中的TM4_Isr被调用
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



