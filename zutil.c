/*12.04.19*/
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <lime/LimeSuite.h>
#include "wiringPi.h"
#include "wiringPiI2C.h"



//////////////////////////////// I2C  ////////////////
//  union i2c_smbus_data{
//    uint8_t  byte ;
//    uint16_t word ;
//    uint8_t  block [34] ;// block [0] is used for length + one more for PEC
//};

  int devlna[5];
  int extlnaon(int ch){
    if (ch>0 & ch<5) {
      int reg=wiringPiI2CReadReg8(devlna[ch],9);
      if (reg>127) wiringPiI2CWriteReg8 (devlna[ch], 9, (reg-128));
    }
  }  // set @channal lna=ON
  int extlnaoff(int ch){
    if (ch>0 & ch<5) {
      int reg=wiringPiI2CReadReg8(devlna[ch],9);
      if (reg<=127) wiringPiI2CWriteReg8 (devlna[ch], 9, (reg+128));
    }
  } // set  @channal lna=OFF
  int extatton(int ch){
    if (ch>0 & ch<5) {
      int reg=wiringPiI2CReadReg8(devlna[ch],9);
      wiringPiI2CWriteReg8 (devlna[ch], 9, (reg&135));
//printf("att on reg=%d out=%d\n",reg,reg&135);
    }
  } // set  @channal att -16dB
  int extattoff(int ch){
    if (ch>0 & ch<5) {
      int reg=wiringPiI2CReadReg8(devlna[ch],9);
      wiringPiI2CWriteReg8 (devlna[ch], 9, (reg&135+120));
//printf("att off reg=%d out=%d\n",reg,reg&135+120);
    }
  } // set  @channal att 0dB

  int setfilter(int ch, int n){
    if (n<1 || n>8) n=8;
    int reg=wiringPiI2CReadReg8(devlna[ch],9);
    int bpf[9]={0,3,1,2,0,4,6,5,7};  //array of bytes for i2c reg
    wiringPiI2CWriteReg8 (devlna[ch], 9, (reg&248 + bpf[n] ) );
    return (reg&248 + bpf[n] ); // 
  }
  int setband(int ch,int band){
    int reg=wiringPiI2CReadReg8(devlna[ch],9);
    int bands[7]={3,5,20,28,8,7,1}; // array of availeble bands
    int bpf[8] = {3,1,2,0,4,6,5,7}; // array of bytes for i2c reg
    int i=0;
    while ( i<7 && bands[i]!=band) i++;
    wiringPiI2CWriteReg8 (devlna[ch], 9, (reg&248 + bpf[i] ) );
//printf(" reg=%d bpf[%d]=%d out=%d \n",reg, i, bpf[i], reg&248+bpf[i]);
    return i+1; //number of filter BPFn 1-8
  }
  int extlnaallon() {
    for (int i=1;i<5;i++) wiringPiI2CWriteReg8 (devlna[i], 9, 0x7f);
  }// set all lna=ON  att=0 filters=bypass 
  int extlnaalloff(){
    for (int i=1;i<5;i++) wiringPiI2CWriteReg8 (devlna[i], 9, 0xff);
  }// set all lna=OFF  att=0 filters=bypass     

  int setant(int n){ // 0-3
    if (n<0 || n>3) return -1;
    short reg[4]={0x18,0x1c,0x71,0x53};
    wiringPiI2CWriteReg8 (devlna[0], 9, reg[n]);
  }
  int setshort1(){wiringPiI2CWriteReg8 (devlna[0], 9, 0x18);} // Set antenna pair 1-2 1-4 (xS  yS)
  int setlong1(){wiringPiI2CWriteReg8 (devlna[0], 9, 0x0c);} // Set antenna pair 1-3 1-5 (xL  yL)
  int setshort2(){wiringPiI2CWriteReg8 (devlna[0], 9, 0x71);} // Set antenna pair 8-7 8-6 (x2S y2S)
  int setlong2(){wiringPiI2CWriteReg8 (devlna[0], 9, 0x53);} // Set antenna pair 8-5 8-3 (x2L y2L)

