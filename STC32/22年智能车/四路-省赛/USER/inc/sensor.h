#ifndef __SENSOR_H
#define __SENSOR_H

void ADC_Read();		//读取adc数据
void Pos_Deviation0();		//位置偏差计算
void Pos_Deviation1();		//位置偏差计算
void Pos_Deviation2();		//位置偏差计算
void Pos_Deviation3();		//位置偏差计算
void Pos_Deviation4();		//位置偏差计算
void Pos_Deviation5();		//位置偏差计算
void Servos_Control0();		//舵机控制
void Servos_Control1();		//舵机控制
void Servos_Control2();		//舵机控制
void Servos_Control3();		//舵机控制
void Servos_Control4();		//舵机控制
void Servos_Control5();		//舵机控制
void __encoder_integral();//编码器积分

#endif