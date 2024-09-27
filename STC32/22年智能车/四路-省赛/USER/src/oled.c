#include "headfile.h"

bit lock = 0;
int line = 0;
int mode = 0;

void oled_show()
{
	while(1)
	{
		oled_p6x8str(0,0,"1.8");							//main�ļ��еı���
		oled_p6x8str(0,1,"2.0");						//sensor�ļ��еı���
		oled_p6x8str(0,2,"2.2");						//sensor�ļ��еı���
		oled_p6x8str(60,line,"<-");						//��ʾ��ͷѡ���ļ�
		if(P70==1&&P71==1)
			lock=0;
		if(P71==0&&lock==0)											//����ѡ��
		{
			delay_ms(10);
			if(P71==0)
			{
				lock=1;
				line+=1;
				if(line==3)
					line=0;
				oled_fill(0x00);
			}
		}
		else if(P70==0&&lock==0)
		{
			delay_ms(10);
			if(P70==0)
			{
				lock=1;
				mode = line;
			}
			break;
		}
		delay_ms(50);
	}
}
