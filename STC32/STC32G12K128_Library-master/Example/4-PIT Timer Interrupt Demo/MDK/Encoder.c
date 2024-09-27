#include "zf_tim.h"
#include "isr.h"
#include <string.h>
#include <stdio.h>
#include "common.h"
#include "Encoder.h"

int32 Enc_L;
int32 Enc_R;

int32 Get_EncoderNum(CTIMN_enum tim_n)	//��ȡ��ǰ�ٶ�
{
	int32 Enc;
	Enc = ctimer_count_read(tim_n);		//��ȡ������ֵ
	ctimer_count_clean(tim_n);				//�������ֵ
	return Enc;
}