

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <lime/LimeSuite.h>
#include "wiringPi.h"
#include "wiringPiI2C.h"

//////////////////////////////// I2C  ////////////////
  union i2c_smbus_data{
    uint8_t  byte ;
    uint16_t word ;
    uint8_t  block [34] ;// block [0] is used for length + one more for PEC
  };
//  int devlna[5];
/// lna
  int extlnaon(int ch);// set @channal lna=ON
  int extlnaoff(int ch);// set  @channal lna=OFF
  int extlnaallon(); // set all lna=ON  att=0 filters=bypass
  int extlnaalloff(); // set all lna=OFF  att=0 filters=bypass     
/// att
  int extatton(int ch);// set  @channal att -16dB
  int extattoff(int ch); // set  @channal att 0dB
/// band/filters
  int setfilter(int ch, int n);// set bpf N @channal
  int setband(int ch, int band);// set band @channal
/// antens commutator
  int setant(int n); // 0-3
  int setshort1();   // Set antenna pair 1-2 1-4 (xS  yS)
  int setlong1();    // Set antenna pair 1-3 1-5 (xL  yL)
  int setshort2();   // Set antenna pair 8-7 8-6 (x2S y2S)
  int setlong2();    // Set antenna pair 8-5 8-3 (x2L y2L)
