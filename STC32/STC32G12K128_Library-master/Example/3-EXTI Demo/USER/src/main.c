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
#include "SEEKFREE_OLED.h"

extern float Lenth;  //距离
extern float count;
/*
 *关于内核频率的设定，可以查看board.h文件
 *在board_init中,已经将P54引脚设置为复位
 *如果需要使用P54引脚,可以在board.c文件中的board_init()函数中删除SET_P54_RESRT即可
 */

void Timer1_Init(void)		//1毫秒@24.000MHz
{
	AUXR &= 0xBF;			//定时器时钟12T模式
	TMOD &= 0x0F;			//设置定时器模式
	TMOD |= 0x10;			//设置定时器模式
	TL1 = 0x00;				//设置定时初始值
	TH1 = 0x00;				//设置定时初始值
	TF1 = 0;				//清除TF1标志
	TR1 = 0;				//定时器1不开始计时
    ET1 = 1;                //允许定时器1中断     
}



void main()
{
    WTST = 0;               //设置程序代码等待参数，赋值为0可将CPU执行程序的速度设置为最快
    
	DisableGlobalIRQ();		//关闭总中断
	
    //sys_clk可选值:35000000，30000000, 27000000. 24000000, 22118400, 20000000, 18432000, 12000000, 11059200, 6000000, 5529600。
    //设置系统频率，此频率需要跟STC-ISP软件中的 <输入用户程序运行的IRC频率>选项的频率一致。
    //如果频率设置不对，将会导致串口的数据不正常,PWM的工作不正常等等。
    sys_clk = 35000000;     //设置系统频率为35MHz
    
	board_init();			//初始化寄存器
	//此处编写用户代码(例如：外设初始化代码等)
    //触发中断LED 就会被点亮
    pit_timer_us(TIM_1, 10);
    pit_timer_ms(TIM_4, 10);
    gpio_mode(P3_3,GPIO);
    exit_init(INT1_P33, BOTH);	//下降沿触发INT0_P32中断
//    exit_init(INT0_P32, FALLING_EDGE);	//下降沿触发INT0_P32中断                                    
    oled_init();
	//总中断最后开启
	EnableGlobalIRQ();		//开启总中断
    while(1)
	{
        P32=1;             //发送开始测距信号
        delay_us(15);      
        P32=0;             //结束发送
        
        oled_printf_float(0,0,Lenth,5,2); 
        oled_printf_float(0,2,count,5,2); 
        delay_ms(100);
    }
}



