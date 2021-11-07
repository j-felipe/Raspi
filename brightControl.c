/**********************************************************************
* Filename    : LightWater02.c
* Description : Control LED by 74HC595
* Author      : www.freenove.com
* modification: 2019/12/27
**********************************************************************/
#include <wiringPi.h>
#include <stdio.h>
#include <wiringShift.h>
#include <time.h>

#define   dataPin   0   //DS Pin of 74HC595(Pin14)
#define   latchPin  2   //ST_CP Pin of 74HC595(Pin12)
#define   clockPin 3    //CH_CP Pin of 74HC595(Pin11)
#define	  outputEnable  7  // Output enable pin of  74HC595 (Pin13)

long int _mainTimer (){
    clock_t t;
    int f;
    t = clock();    
    t = clock() - t;    
    return t;
}


int main(void){
    long int exeTime ;
    exeTime = _mainTimer
	printf("No. of clicks %ld clicks (%f seconds).\n",
           exeTime, ((float)exeTime) / CLOCKS_PER_SEC);
	return 0;
}

