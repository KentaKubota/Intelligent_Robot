/* main.cpp */
#include "Function.h"

#define AIM_NUM 15
#define RIGHT 0
#define LEFT  1

int cup = OFF;

int main()
{

    int state;
    int ballcolor_1st, ballcolor_2nd;
    int ballcount = 0;
    int deptharea = OFF;
    int distance = 157;
    int last_distance = 0;
    int end_flag;
    int search_side = RIGHT;

/* Initialization */
    wait(2.5);
    ServoInit();
    printf("\nFinish initialization\n\n");

/* Start Motor Ctrl */
    SwitchMotorCtrl(ON);    
    
    float value;
    float psd_dis;

    while(1){
        value = PSD_high_Value();
        //psd_dis = 66.294 * pow((double)value, -1.218);
        printf("%f\n", value);
        wait(0.1);
    }


    

/*
    state = FREE_BALL;
    while(1){
        switch(state){
            case FREE_BALL:
                LineTrace(4);
                ServoBallThrow();
                LineTrace(1);
                state = BALL_SEARCH;
                break;

            case BALL_SEARCH:
                
                if(cup == OFF && timer >= 330){
                    state = TIMER;
                    break;
                }

                if(search_side == RIGHT){
                     SearchTurn_r();
                     if(get_angle1 == 0){
                         search_side = LEFT;
                         break;
                     }
                }
                else{
                    SearchTurn_l();
                    if(get_angle1 == 0){
                        MoveLineTrace(distance);
                        last_distance += 157;
                        search_side = RIGHT;
                        deptharea = ON;
                        break;
                    }
                }

                state = BALL_CATCH;
                break;

            case BALL_CATCH:
                BallApproach();
                if(cup == OFF){
                    wait(1);
                    ballcolor_1st = WhatColor();
                    if(ballcolor_1st != NO_BALL) ballcount += 1;
                    if(ballcount == AIM_NUM) cup = ON;

                }

                if(ballcolor_1st == NO_BALL){
                    if(get_angle1 <= 0) Turn(-get_angle1 - 5, 130);
                    else Turn(-get_angle1 + 5, 130); 
                    state = BALL_SEARCH; 
                    break;
                }
                else if(cup == OFF){
                    if(get_angle1 <= 0) Turn(-get_angle1 - 5, 110);// 10 -> 5
                    else Turn(-get_angle1 + 5, 110); 
                    cup = ON;                            
                    state = BALL_SEARCH;                 
                    printf("color = %d\n",ballcolor_1st);
                    break;
                }

                if(search_side == RIGHT) Turn(-168 - get_angle1, 160);//175 -> 168
                else Turn(175 - get_angle1, 160);

                if(deptharea == OFF){
                    targetSpeed_r = targetSpeed_l = -150;
                    wait(0.7);
                }
                   

                //printf("ballcolor_1st = %d\n",ballcolor_1st);
                state = BALL_SHOOT;
                break;

            case BALL_SHOOT:
                if(deptharea == ON){LineTrace(ballcolor_1st + 1);}
                else LineTrace(ballcolor_1st);

                if(ballcolor_1st == BLUE){
                    Turn(167, 180);
                    ServoBallThrow();
                    ServoForkUp();
                    wait(1);//0.5 -> 0.7
                    ballcolor_2nd = WhatColor();
                    printf("color_2nd = %d\n",ballcolor_2nd);
                    if(ballcolor_2nd != NO_BALL) ballcount += 1;

                    if(ballcolor_2nd == BLUE){
                        ServoBallThrow();
                    }
                    else if(ballcolor_2nd == YELLO || ballcolor_2nd == RED){
                        Turn(173, 180);
                        LineTrace(ballcolor_2nd - ballcolor_1st);
                        Turn(80, 180);
                        ServoBallThrow();
                        Turn(80, 180);
                    }
                }


                if(ballcolor_1st == YELLO){
                    Turn(80, 180);
                    ServoBallThrow();
                    ServoForkUp();
                    wait(1);//
                    ballcolor_2nd = WhatColor();
                    printf("color_2nd = %d\n",ballcolor_2nd);
                    if(ballcolor_2nd != NO_BALL) ballcount += 1;
               
                    if(ballcolor_2nd == NO_BALL) Turn(80, 180);
                    if(ballcolor_2nd == YELLO){
                        ServoBallThrow();
                        Turn(80, 180);
                    }
                    else if(ballcolor_2nd == BLUE){
                        Turn(80, 180);
                        LineTrace(1);
                        ServoBallThrow();
                    }
                    else if(ballcolor_2nd == RED){
                        Turn(-80, 180);
                        LineTrace(1);
                        Turn(80, 180);
                        ServoBallThrow();
                        Turn(80, 180);
                    }
                }

                if(ballcolor_1st == RED){
                    Turn(80, 180);
                    ServoBallThrow();
                    ServoForkUp();
                    wait(1);//
                    ballcolor_2nd = WhatColor();
                    printf("color_2nd = %d\n",ballcolor_2nd);
                    if(ballcolor_2nd != NO_BALL) ballcount += 1;

                    if(ballcolor_2nd == NO_BALL) Turn(80, 180);
                    if(ballcolor_2nd == RED){
                        ServoBallThrow();
                        Turn(80, 180);
                    }
                    else if(ballcolor_2nd == YELLO){
                        Turn(80, 180);
                        LineTrace(1);
                        Turn(-80, 180);
                        ServoBallThrow();
                        Turn(80, 180);
                    }
                    else if(ballcolor_2nd == BLUE){
                        Turn(80, 180);
                        LineTrace(2);
                        ServoBallThrow();
                    }
                }

                if(ballcount >= AIM_NUM){ 
                    state = GO_HOME;
                    break;
                }

                if(ballcolor_2nd == NO_BALL) LineTrace(ballcolor_1st);
                else LineTrace(ballcolor_2nd);

              // printf("ballcount = %d\n",ballcount);///////@@
                cup = OFF;
                if(deptharea == ON) MoveLineTrace(last_distance);
                state = BALL_SEARCH;

                break;

            case GO_HOME:
                Turn(170,200);
                if(ballcolor_2nd != NO_BALL){
                if(ballcolor_2nd == BLUE) LineTrace(2);
                if(ballcolor_2nd == YELLO) LineTrace(1);
                if(ballcolor_2nd == RED); 
                }
                else {

                if(ballcolor_1st == BLUE) LineTrace(2);
                if(ballcolor_1st == YELLO) LineTrace(1);
                if(ballcolor_1st == RED); 

                }

                targetSpeed_l = 210;targetSpeed_r = 200; wait(2.2);
                Turn(170,200);
                for(int i = 0; i < 5; i++){
                    ServoForkAppeal();
                    targetSpeed_r = 100;
                    targetSpeed_l = -100;
                }
                targetSpeed_r = targetSpeed_l = 0;
                end_flag = ON;
                break;

            case TIMER:
                Turn(170, 200);
                if(deptharea == ON) LineTrace(4);
                else LineTrace(3);

                targetSpeed_l = 210;targetSpeed_r = 200; 
                wait(2.2);
                Turn(170,200);
                for(int i = 0; i < 5; i++){
                    ServoForkAppeal();
                    targetSpeed_r = 100;
                    targetSpeed_l = -100;
                }
                targetSpeed_r = targetSpeed_l = 0;
                end_flag = ON;
                break;

        }       

        if(end_flag == ON) break;
    }
*/
    printf("\nProgram has finished");
}

