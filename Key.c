#include "STC15.h"

//定义中间变量
unsigned char middle;


//检测按键状态返回
unsigned char Detection_key()
{
	unsigned char KeyNumber=0;
	
	if(P10==0){KeyNumber=1;}
	if(P11==0){KeyNumber=2;}
	if(P12==0){KeyNumber=3;}
	
	return KeyNumber;
}

//扫描按键状态改变全局变量（扫描间隔20ms，这次扫描结果和上次不一样时把键值写入全局变量）
void Scan_key(){
	static unsigned char oldnum,newnum;
	oldnum=newnum;
	newnum=Detection_key();
	if(oldnum!=newnum && newnum==0){middle=oldnum;}
}

//输出后清零
unsigned char switch0000(){
	unsigned char tem;//中间变量
	if(middle){
		tem=middle;
		middle=0;
		return tem;
	}
	return tem;
}