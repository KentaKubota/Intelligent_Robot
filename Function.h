/* Function.h */
#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include "mbed.h"
#include "Define.h"

void SwitchMotorCtrl(int flag);
void LineTrace(int countxline);
void MoveLineTrace(float distance);
void PIDCtrl_R(float target, float velocity);
void PIDCtrl_L(float target, float velocity);
void Turn(float angle, int speed);
void SearchTurn_r();
void SearchTurn_l();
void BallApproach();

void ServoAng(unsigned char id, int ang);
void ServoInit();
void ServoBallThrow();
void ServoForkUp();
void ServoForkDown();
void ServoForkAppeal();
void ServoForkCatch();

float PSD_Value();

int WhatColor();

#endif


