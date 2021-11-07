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

void _shiftOut(int dPin,int cPin,int order,int val){   
	int i;  
    for(i = 0; i < 8; i++){
        digitalWrite(cPin,LOW);
        if(order == LSBFIRST){
            digitalWrite(dPin,((0x01&(val>>i)) == 0x01) ? HIGH : LOW);
            delayMicroseconds(10);
		}
        else {//if(order == MSBFIRST){
            digitalWrite(dPin,((0x80&(val<<i)) == 0x80) ? HIGH : LOW);
            delayMicroseconds(10);
		}
        digitalWrite(cPin,HIGH);
        delayMicroseconds(10);
	}
}


int main(void){

    printf("Program is starting ...\n");
	
	wiringPiSetup();
	
	pinMode(dataPin,OUTPUT);
	pinMode(latchPin,OUTPUT);
	pinMode(clockPin,OUTPUT);
	pinMode(outputEnable,OUTPUT);
	digitalWrite(outputEnable, LOW);

    long int shiftime = 100 ;
    long int fracOn = 50 ; 
    unsigned char x;
    unsigned char countpos = 0;
    unsigned char writeflg;
    long int timeOn = (shiftime/100)*fracOn ;
    long int timeOff = shiftime - timeOn ;
    
    clock_t initime = clock();    
    clock_t endtime ;
    x=0x01;
    writeflg = 1 ;
    while (1){
        endtime = ((float)clock() - initime)/CLOCKS_PER_SEC*1000 ;
        //printf("end time  %d ini time %d \n",endtime,initime);

        if ((endtime < timeOn) && (writeflg == 1)){
            digitalWrite(latchPin,LOW);		// Output low level to latchPin
			_shiftOut(dataPin,clockPin,LSBFIRST,x);// Send serial data to 74HC595
			digitalWrite(latchPin,HIGH);   //Output high level to latchPin, and 74HC595 will update the data to the parallel output port.
            digitalWrite(outputEnable, LOW);
            writeflg = 0;
        }

        if (endtime >= timeOn){
            digitalWrite(outputEnable, HIGH);
        }

        if (endtime > shiftime ){
            initime = clock();
            writeflg = 1;
            countpos++;
            if (countpos < 8 ){
                x<<=1;
            }
            else if (countpos >= 8 && countpos < 15){
                x>>=1;
            }
            else if (countpos >= 15){
                countpos = 0;
            }
           
        }
    }
    

	return 0;
}

