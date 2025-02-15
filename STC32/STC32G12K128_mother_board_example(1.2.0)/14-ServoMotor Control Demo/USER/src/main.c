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
 
uint16 duty;
uint16 duty_dir;  
void main()
{
    WTST = 0;               //设置程序代码等待参数，赋值为0可将CPU执行程序的速度设置为最快
    
	DisableGlobalIRQ();		//关闭总中断
	
    //sys_clk可选值:35000000，30000000, 27000000. 24000000, 22118400, 20000000, 18432000, 12000000, 11059200, 6000000, 5529600。
    //设置系统频率，此频率需要跟STC-ISP软件中的 <输入用户程序运行的IRC频率>选项的频率一致。
    //如果频率设置不对，将会导致串口的数据不正常,PWM的工作不正常等等。
    sys_clk = 35000000;     //设置系统频率为35MHz
    
	board_init();		//初始化
    oled_init();
    //特别提示这里的舵机居中是在没有安装在车模上的时候，才能使用这个居中方式。
    //如果舵机已经安装在车模上，切勿使用本程序，因为舵机由于机械限位，导致可活动范围小很多。

	//pwm初始化频率为50hz 舵机居中
	duty = 1.5*1000/20;

	pwm_init(PWMB_CH1_P74, 50, duty);
	pwm_init(PWMA_CH1P_P60, 1000, 0);
	pwm_init(PWMA_CH2P_P62, 1000, 0);		//左电机--PWM
	EnableGlobalIRQ();		//开启总中断
    while(1)
	{
		//计算舵机位置舵机位置   （0.5ms - 2.5ms）ms/20ms * 10000（1000是PWM的满占空比时候的值）
        //舵机最小值为250，   最大值为1250。
		
		//修改duty的值，可以修改舵机最大最小值。
		//例：将PWM_DUTY_MAX设置为1000，则舵机最小值为25，最大值为125。
		//PWM_DUTY_MAX的值在zf_pwm.h的文件中定义。
		pwm_duty(PWMB_CH1_P74, duty);
        oled_p8x16str(0 ,0,"PWM");
		oled_printf_float(0,2,duty,5,2);
        if(duty_dir == 1) 
        { 
            duty++; 
            if(duty >= 125) 
            { 
                duty_dir = 0; 
            } 
        } 
        else 
        { 
            duty--; 
            if(duty < 25) 
                duty_dir = 1;  
        }
        
        //控制舵机达到指定位置
        pwm_duty(PWMB_CH1_P74, duty);
//        pwm_duty(PWMA_CH1P_P60, 100);
        delay_ms(50);
    }
}
