#ifndef __Digital_LED_H__
#define __Digital_LED_H__

void led888_Init(void);							//初始化数码管接口
void Scan_888led(void);							//扫描函数，用下面的扫描模板在定时器中开启扫描
void Set_888led(unsigned char Location,Number);	//在哪一位显示哪个数，执行一次就行，不显示填10


//扫描模板
/*
void Timer0_Routine() interrupt 1
{
	static  unsigned int T0Count;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=2)  //2毫秒
	{
		T0Count=0;
		Scan_888led();
	}
}
*/

#endif