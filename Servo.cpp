/* Servo.cpp */
#include "Function.h"
#include "Servo.h"

/* Define PinNo Servo */
Serial servo(p13, p14);
unsigned char tx1_[13][4];

void ServoAng(unsigned char id, int ang)
{
    servo.baud(115200);
    servo.format(8, Serial::Even,1);
    int i;
    tx1_[id][0] = 0x80 | id;
    tx1_[id][1] = (ang >> 7 & 0x7F);
    tx1_[id][2] = (ang & 0x7F);
    
    for (i = 0; i < 3; i++){ servo.putc(tx1_[id][i]);}
}


/***************************************************/
/*           サーボを初期姿勢にする関数            */
/***************************************************/
void ServoInit()
{ 
    ServoAng(1,4600);
    wait(0.5);
    ServoAng(0,7150);
    wait(0.5);
}


/***********************************************/
/*           ボールシュートする関数            */
/***********************************************/
void ServoBallThrow()
{
    wait(0.2);
    ServoAng(0, 10100);
    wait(0.4);
    ServoAng(0, 7150);
    wait(0.2);
}


/***********************************************/
/*         フォークハンドを下にさげる関数      */
/***********************************************/
void ServoForkDown()
{
    wait(0.2);
    ServoAng(1, 7480);
    wait(0.3);
}


/***********************************************/
/*         フォークハンドを上にあげる関数      */
/***********************************************/
void ServoForkUp()
{
    ServoAng(1, 4600);
    wait(0.2);
}


/***********************************************/
/*      フォークハンドでボールを保持する関数   */
/***********************************************/
void ServoForkCatch()
{
    ServoAng(1, 6000);
    wait(0.2);
}


/***********************************************/
/*         ゴールした際のアピール動作関数      */
/***********************************************/
void ServoForkAppeal()
{
    wait(0.3);
    ServoAng(1, 7000);
    wait(0.3);
    ServoAng(1, 4800);
    wait(0.3);
}

