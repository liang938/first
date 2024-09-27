#ifndef __SENSOR_H
#define __SENSOR_H

void ADC_Read();		//读取adc数据
void Pos_Deviation();		//位置偏差计算
void Servos_Control();		//舵机控制
void __encoder_integral();//编码器积分

#endif