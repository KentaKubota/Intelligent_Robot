/* PSD.cpp */
#include "Function.h"
 
#define NUM 9
AnalogIn PSD_low(p16), PSD_high(p20);     


int comp( const void *c1, const void *c2 );

float PSD_high_Value()
{
    //float value = PSD_high_Value();
    return PSD_high.read();
    //return value;
}


float PSD_low_Value()
{
    float sort[NUM] = {0};

    for(int i = 0; i < NUM; i++)
        sort[i] = PSD_low.read();
    qsort(sort, NUM, sizeof(float), comp);
    //printf("%f\n",sort[4]);

    return sort[(NUM -1) / 2 ];

}

int comp( const void *c1, const void *c2 )
{
  int tmp1 = *(int *)c1;
  int tmp2 = *(int *)c2;

  if( tmp1 < tmp2 )  return -1;
//  if( tmp1 == tmp2 ) return  0;
  if( tmp1 > tmp2 )  return  1;
  return  0;//////////////////////////////
}
