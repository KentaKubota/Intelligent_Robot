/* Motor.cpp */
#include "Function.h"
#include "QEI.h"


/* Define PinNo motor */
PwmOut      MotorRight(p23);
PwmOut      MotorLeft(p21);
DigitalOut  HBridgeRight(p24);
DigitalOut  HBridgeLeft(p22);

/* Define PinNo Encoder */
QEI Pulse_r (p29, p30, NC, 100, QEI::X2_ENCODING);
QEI Pulse_l  (p28, p27, NC, 100, QEI::X2_ENCODING);

/* Global variable */
float theta_r, theta_l;
float theta_old_r = 0.0, theta_old_l = 0.0;
float omega_r, omega_l, W;
float velocity_r, velocity_l, V;
float x0, x1, y0, y1, tht0, tht1;
float targetSpeed_r, targetSpeed_l; 
float dt = 0.02;
float T = 132;
float get_PSD0, get_PSD1, get_angle0, get_angle1; 
float timer = 0;

/* PID Control */
void PIDCtrl_R(float target, float velocity)
{
    MotorRight.period(0.00005);

    float KP = 3.6, KI = 0.26, KD = 0.001;//KP = 1.55, KI = 0.023, KD = 0.001
    float e = 0, e0 = 0;
    static float ei = 0, ed = 0;
    float CalcVelocity;
    
    e = target - velocity;
    ed = e - e0;
    ei += e;
    e0 = e;
    if(target == 0) ei = 0, ed = 0;

    CalcVelocity = (e * KP + ei * KI + ed * KD);

    if(CalcVelocity > 900) CalcVelocity = 900;
    if(CalcVelocity > 0) HBridgeRight = 0;
    if(CalcVelocity < -900) CalcVelocity = -900;
    if(CalcVelocity < -0) HBridgeRight = 1;

    MotorRight = fabs(CalcVelocity / 900);
}

void PIDCtrl_L(float target, float velocity)
{

    MotorLeft.period(0.00005);

    float KP = 3.6, KI = 0.25, KD = 0.001;
    float e = 0, e0 = 0;
    static float ei = 0, ed = 0;
    float CalcVelocity;

    e = target - velocity;
    ed = e - e0;
    ei += e;
    e0 = e;
    if(target == 0) ei = 0, ed = 0;

    CalcVelocity = (e * KP + ei * KI + ed * KD);

    if(CalcVelocity > 900) CalcVelocity = 900;
    if(CalcVelocity > 0) HBridgeLeft = 0;
    if(CalcVelocity < -900) CalcVelocity = -900;
    if(CalcVelocity < -0) HBridgeLeft = 1;

    MotorLeft = fabs(CalcVelocity / 900);
}


/* Turn using Odometry */ 
void Turn(float angle,int speed)
{
    x1 = y1 = tht1 = 0;
    x0 = y0 = tht0 = 0;
    wait(0.1);//0.3 -> 0.1

    if(angle >= 0)
        while(angle >= (tht1 * 180 / PI))
            targetSpeed_r = speed, targetSpeed_l = -speed;
    if(angle <= 0)
        while(angle <= (tht1 * 180 / PI))
            targetSpeed_r = -speed, targetSpeed_l = speed;

    targetSpeed_r = targetSpeed_l = 0;
    wait(0.1);//0.2 -> 0.1
    //printf("angle = %f\n",tht1*180/PI);
            
}

void SearchTurn_r()
{
    get_PSD0 = get_PSD1 = 0;
    get_angle0 = get_angle1 = 0; 
    x1 = y1 = tht1 = 0;
    x0 = y0 = tht0 = 0;

    wait(0.1);//0.5 -> 0.1
    while(-89 <= (tht1 * 180 / PI)){   //right side search
        targetSpeed_r = -110;
        targetSpeed_l = 110;//80 -> 110

        if(0.12 < PSD_high_Value() ){
            get_PSD0 = PSD_low_Value();
            printf("up %f down %f\n",PSD_high_Value(), get_PSD0);
        }
        get_angle0 = tht1 * 180 / PI;

        if(get_PSD1 < get_PSD0){
            get_PSD1 = get_PSD0;
            get_angle1 = get_angle0; 
        }
    }
    if(get_PSD1 < 0.240) get_angle1 = 0.0;//0.243
    //printf("psd = %f angle = %f\n",get_PSD1, get_angle1);
    targetSpeed_r = targetSpeed_l = 0;
    wait(0.1);//0.2 -> 0.1
    if(get_angle1 == 0){
        Turn(84, 150);
        x1 = y1 = tht1 = 0;
        x0 = y0 = tht0 = 0;
    }
    else Turn(88 + get_angle1, 160);//if you reduce the value, the curve is weak  - 173.5
}//90 -> 86


void SearchTurn_l()
{
    get_PSD0 = get_PSD1 = 0;
    get_angle0 = get_angle1 = 0; 
    x1 = y1 = tht1 = 0;
    x0 = y0 = tht0 = 0;

    wait(0.1);//0.5 -> 0.1
    while(89 >= (tht1 * 180 / PI)){   //right side search
        targetSpeed_r = 110;
        targetSpeed_l = -110;//80 -> 110

        if(0.12 < PSD_high_Value() )
            get_PSD0 = PSD_low_Value();
        get_angle0 = tht1 * 180 / PI;

        if(get_PSD1 < get_PSD0){
            get_PSD1 = get_PSD0;
            get_angle1 = get_angle0; 
        }
    }
    if(get_PSD1 < 0.243) get_angle1 = 0.0;
    //printf("psd = %f angle = %f\n",get_PSD1, get_angle1);
    targetSpeed_r = targetSpeed_l = 0;
    wait(0.1);//0.2 -> 0.1
    if(get_angle1 == 0){
        Turn(-84, 150);
        x1 = y1 = tht1 = 0;
        x0 = y0 = tht0 = 0;
    }
    else Turn(-88 + get_angle1, 160);//if you reduce the value, the curve is weak  - 173.5
}//120 -> 160



void BallApproach()
{
    float HandDistance = 170.0, Diff; //175.0
    float balldistance = 66.294 * pow((double)get_PSD1, -1.218);
    int waitflag;

    x1 = y1 = tht1 = 0;
    x0 = y0 = tht0 = 0;
    Diff = balldistance - HandDistance;

    if(Diff < 0)
    {
        while(x1 >= Diff - 20)
            targetSpeed_r = targetSpeed_l = -180;//100 -> 180

        targetSpeed_r = targetSpeed_l = 0;
        ServoForkDown();
        targetSpeed_r = targetSpeed_l = 140;//100 -> 140
        waitflag = ON;
        wait(1.0);//1.2 -> 1.0
    }
    else
    {
        ServoForkDown();
        while(x1 <= Diff + 40)//60 -> 40
            targetSpeed_r = targetSpeed_l = 140;//100 -> 140
            waitflag = OFF;
    }
    targetSpeed_r = targetSpeed_l = 0;
    if(cup == OFF) ServoForkUp();
    else ServoForkCatch();

    while(x1 >= 0)
        printf(""),targetSpeed_r = targetSpeed_l = -160;//100 -> 180
    targetSpeed_r = targetSpeed_l = 0;
    if(waitflag == ON) wait(0.5);//0.5 -> 0.3
}

void MotorCtrl()
{
/* Calculation of theta angular velocity, the velocity */
    theta_r = (Pulse_r.getPulses() * 2 * PI) / 4950;
    theta_l = (-Pulse_l.getPulses() * 2 * PI) / 4950;
    omega_r = (theta_r-theta_old_r)/0.02;
    omega_l = (theta_l-theta_old_l)/0.02;
    theta_old_r = theta_r;
    theta_old_l = theta_l;
    velocity_r = 25 * omega_r;
    velocity_l = 25 * omega_l;

/* Calculation of Odometry */
    V = (25 / 2) * (omega_r + omega_l);
    W = (25 / T) * (omega_r - omega_l); 
    tht1 = tht0 + W * dt;
    x0 = x1;    y0 = y1;    tht0 = tht1;
    x1 = x0 + V * dt * cos(tht1);
    y1 = y0 + V * dt * sin(tht1);

    PIDCtrl_R(targetSpeed_r, velocity_r);
    PIDCtrl_L(targetSpeed_l, velocity_l);

    timer += 0.02;
}


/* Timer Interrput */
Ticker TimerInterrupt;

void SwitchMotorCtrl(int flag)
{
    if(flag == 1)
    {
        TimerInterrupt.attach(&MotorCtrl, 0.02);
        /* Reset encoder value */
        Pulse_l.reset();
        Pulse_r.reset();
    }
    else
    {
        TimerInterrupt.detach();
        /* Reset encoder value */
        Pulse_l.reset();
        Pulse_r.reset();
    }
}

