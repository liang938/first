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
 *关于内核频率的设定，可以查看board.h文件
 *在board_init中,已经将P54引脚设置为复位
 *如果需要使用P54引脚,可以在board.c文件中的board_init()函数中删除SET_P54_RESRT即可
 */
 


uint16 distance;
//该函数在isr.c文件中的UART3_Isr函数进行回调
void Split_Ultrasonic_callback(uint8 buf)
{
    static uint8 dat[3];
    static uint8 num = 0;
    
    dat[num] = buf;
    if(dat[0] != 0xa5)  num = 0;//检查头帧是否正确，不正确就重新接收
    else                num++;

    if(num==3)                  //接收完成，开始处理数据
    {
        num = 0;
        //将数据的高八位与低八位进行组合，得到距离信息单位MM
        distance = dat[1]<<8 | dat[2];
    }
}


    
void main()
{
    WTST = 0;               //设置程序代码等待参数，赋值为0可将CPU执行程序的速度设置为最快
    
	DisableGlobalIRQ();		//关闭总中断
	
    //sys_clk可选值:35000000，30000000, 27000000. 24000000, 22118400, 20000000, 18432000, 12000000, 11059200, 6000000, 5529600。
    //设置系统频率，此频率需要跟STC-ISP软件中的 <输入用户程序运行的IRC频率>选项的频率一致。
    //如果频率设置不对，将会导致串口的数据不正常,PWM的工作不正常等等。
    sys_clk = 35000000;     //设置系统频率为35MHz
    
	board_init();		//初始化

    //数据接收在isr.c文件中的UART3_Isr函数进行数据接收
    uart_init(UART_3, UART3_RX_P50, UART3_TX_P51, 115200, TIM_2);
	
	EnableGlobalIRQ();		//开启总中断
    while(1)
	{
        delay_ms(100);
        printf("%dmm\r\n", distance); 
    }
}
