#include "STC15.h"

#include <Digital_LED.H>
#include <Timer0.H>
#include <DELAY.H>
#include <Key.H>

unsigned char num,key;

void main(){
	Timer0_Init();
	led888_Init();
	while(1){
		key=switch0000();
		if(key!=0){
			if(key==1){
				num=1;
			}
			if(key==2){
				num=2;
			}
			if(key==3){
				num=3;
			}
		}
    	Set_888led(1,num);	
		delay(10);
    	}
}


void Timer0_Routine() interrupt 1
{
	static  unsigned int T0Count,T0Count1;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	T0Count1++;
	if(T0Count>=2)  //2毫秒
	{
		T0Count=0;
		Scan_888led();
	}
	if(T0Count1>=20)  //20毫秒
	{
		T0Count1=0;
		Scan_key();
	}
}

