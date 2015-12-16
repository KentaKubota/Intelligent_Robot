/*LineTrace.cpp*/
#include "Function.h"


/* Define PinNo sensor linetrace */
DigitalIn ss1(p5),ss2(p6),ss3(p7),ss4(p8);


void LineTrace(int countxline)
{
    int sw = 0;
    int s1,s2,s3,s4;
    int count = 0;
    while(count != countxline)
    {
       s1 = ss1.read();
       s2 = ss2.read();
       s3 = ss3.read();
       s4 = ss4.read();

       if(s1 == 1 && s2 == 0 && s3 == 1 && s4 == 1) sw = 1;
       else if(s1 == 1 && s2 == 1 && s3 == 0 && s4 == 1) sw = 2;
       else if(s1 == 0 && s2 == 1 && s3 == 1 && s4 == 1) sw = 3;
       else if(s1 == 1 && s2 == 1 && s3 == 1 && s4 == 0) sw = 4;

       else if(s1 == 0 && s2 == 0 && s3 == 1 && s4 == 1) sw = 5;
       else if(s1 == 1 && s2 == 1 && s3 == 0 && s4 == 0) sw = 6;
       else if(s1 == 0 && s2 == 0 && s3 == 0 && s4 == 0) sw = 7;
       else if(s1 == 0 && s2 == 0 && s3 == 0 && s4 == 1) sw = 7;
       else if(s1 == 1 && s2 == 0 && s3 == 0 && s4 == 0) sw = 7;
       else if(s1 == 1 && s2 == 0 && s3 == 0 && s4 == 1) sw = 7;



       switch(sw)
       {
           case 1:
               targetSpeed_r = 220, targetSpeed_l = 480; 
               break;

           case 2:
               targetSpeed_r = 480, targetSpeed_l = 220;
               break;

           case 3:
               targetSpeed_r = 30, targetSpeed_l = 460;
               break;

           case 4:
               targetSpeed_r = 460, targetSpeed_l = 30;
               break;

           case 5:
               targetSpeed_r = 60, targetSpeed_l = 460;
               break;

           case 6:
               targetSpeed_r = 460, targetSpeed_l = 60;
               break;

           case 7:
               targetSpeed_r = targetSpeed_l = 380;

               count += 1;
               if(count == countxline) targetSpeed_r = targetSpeed_l = 240;
               //printf("count = %d\n",count);
               wait(0.09);//0.17???
               break;

           default:
               targetSpeed_r = targetSpeed_l = 410;
               break;
       }

    sw = 0;
    } 
    targetSpeed_r = targetSpeed_l = 0;
}





void MoveLineTrace(float distance)
{
    x1 = y1 = tht1 = 0;
    x0 = y0 = tht0 = 0;

    int sw = 0;
    int s1,s2,s3,s4;
    while(x1 <= distance)
    {
       //printf("x1 = %f\n",x1*10);
       s1 = ss1.read();
       s2 = ss2.read();
       s3 = ss3.read();
       s4 = ss4.read();

       if(s1 == 1 && s2 == 0 && s3 == 1 && s4 == 1) sw = 1;
       if(s1 == 1 && s2 == 1 && s3 == 0 && s4 == 1) sw = 2;
       if(s1 == 0 && s2 == 1 && s3 == 1 && s4 == 1) sw = 3;
       if(s1 == 1 && s2 == 1 && s3 == 1 && s4 == 0) sw = 4;

       switch(sw)
       {
           case 1:
               targetSpeed_r = 120, targetSpeed_l = 320;//230
               break;

           case 2:
               targetSpeed_r = 320, targetSpeed_l = 120;///100 70
               break;

           case 3:
               targetSpeed_r = 50, targetSpeed_l = 350;
               break;

           case 4:
               targetSpeed_r = 350, targetSpeed_l = 50;
               break;

           default:
               targetSpeed_r = targetSpeed_l = 300;
               break;
       }

    sw = 0;
    } 
    targetSpeed_r = targetSpeed_l = 0;
}
