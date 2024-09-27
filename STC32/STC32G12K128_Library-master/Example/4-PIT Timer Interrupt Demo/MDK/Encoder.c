#include "zf_tim.h"
#include "isr.h"
#include <string.h>
#include <stdio.h>
#include "common.h"
#include "Encoder.h"

int32 Enc_L;
int32 Enc_R;

int32 Get_EncoderNum(CTIMN_enum tim_n)	//获取当前速度
{
	int32 Enc;
	Enc = ctimer_count_read(tim_n);		//读取左轮数值
	ctimer_count_clean(tim_n);				//清除计数值
	return Enc;
}