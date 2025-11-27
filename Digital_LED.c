#include "STC15.h"


//全局变量存储四个数码管的状态，主函数里改变全局变量，扫描函数里读取全局变量刷新到数码管
unsigned char code_888led[]={10,10,10,10};


/**
	* @brief		传入位置和数字，在位置上显示数字//0~9每个码代表一个数字,10代表空白
	* @param		要显示的位置，1~8
	* @param		要显示的数字0~9，10为空白
	* @retval		无
	*/
unsigned char code leddata[]={
	0xc0,//0
	0xf9,//1
	0xa4,//2
	0xb0,//3
	0x99,//4
	0x92,//5
	0x82,//6
	0xf8,//7
	0x80,//8
	0x90,//9
	0xff,//空白
	0x40};

/**
	* @brief		初始化函数，设置P3为推挽输出，并且保证初始化后数码管不亮
   	* @param		无
   	* @retval		无
*/
void led888_Init(void){
	P3M1&= 0x0F;   // 将P3M1寄存器全部清零
    P3M0|= 0xF0;   // 将P3M0寄存器全部置一
	P3&=0x0f;
	P2=0xFF;
}
	
void Nixie(unsigned char Location,Number){
	P3&=0x0f;
	
	switch(Location)
	{
		case 1: P34=1;break;	//选择数码管1
		case 2: P35=1;break;	//选择数码管2
		case 3: P36=1;break;	//选择数码管3
		case 4: P37=1;break;	//选择数码管4
	}
	P2=leddata[Number];
}


/**
 * @brief  数码管扫描显示函数
 * @param  无
 * @retval 无
 * @note   定时器每2ms调用一次，实现多位数码管的动态显示
 *         自动跳过值为10的位置（不显示），避免显示亮度不均
 *         显示密度自适应：数字多时整体偏暗，数字少时整体偏亮，但亮度均匀
 */
void Scan_888led(void){
	static unsigned char number=0,i=0;//number为自加值，i为超时判定
	P2=0xFF;
	// 跳过不显示的位置（值为10），最多查找4次避免死循环
	while(code_888led[number]==10 && i<4){
		number = (number + 1) % 4;
		i++;
	}i=0;//把i归0
	
	
	Nixie((number+1),code_888led[number]);//在对应位置显示对应数据
	number = (number + 1) % 4; //更新到下一个位置，让number循环在0~3
}


/**
	* @brief		改变某个位置的数字
	* @param		要改变的位置
	* @param		要改成的数字
	* @retval		无
	*/
void Set_888led(unsigned char Location,Number){
	code_888led[(Location-1)]=Number;
}


