#include "v5.h"
#include "v5_vcs.h"
#include <stdio.h>

using namespace vex;
using signature = vision::signature;

#ifndef SENSOR
#define SENSOR
#endif

extern brain Brain;
extern controller Controller;
extern devices  Expander;
extern motor LeftMotor1;
extern motor LeftMotor2;
extern motor LeftMotor3;
extern motor RightMotor1;
extern motor RightMotor2;
extern motor RightMotor3;
extern motor intake;
extern motor out;
extern motor lift1;
extern motor lift2;
extern motor intake1;
extern motor intake2;
extern motor intake3;
extern motor intake4;

extern rotation Rotation;
extern rotation Rotation1;

extern rotation ScrollerRotation;

extern inertial Inertial;

extern distance DistanceA;
extern distance DistanceB;
extern distance Distanceup;
extern distance Distance;
extern distance DistanceC;
extern distance DistanceD;


extern optical OpticalDown;
extern optical Optical;
extern optical Optical2;
extern gyro Gyro;
extern triport TriportA;

extern pneumatics Obstruct;
extern pneumatics Throw;
extern pneumatics Up;
extern pneumatics liftpush;
extern pneumatics extension;
extern pneumatics Hook;
extern pneumatics IntakeArm;
extern pneumatics HookL;
extern pneumatics HookR;
extern pneumatics Mid;
extern pneumatics High;


extern encoder EncoderL;
extern line LineA;
void Show();
