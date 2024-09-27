#ifndef __MOVE_H
#define __MOVE_H

void Getspeed();		//获取编码器数值
void Sendspeed();		//发送速度
void Speedcontrol(int left_speed, int right_speed);		//调整当前速度

#endif