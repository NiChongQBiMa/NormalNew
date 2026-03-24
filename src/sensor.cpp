#include "sensor.h"
#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

brain Brain;
controller Controller;

motor LeftMotor1(PORT11, gearSetting::ratio18_1,false);
motor LeftMotor2(PORT12, gearSetting::ratio18_1,true);
motor LeftMotor3(PORT13, gearSetting::ratio18_1,false);
motor RightMotor1(PORT15, gearSetting::ratio18_1,true);
motor RightMotor2(PORT16, gearSetting::ratio18_1,false);
motor RightMotor3(PORT17, gearSetting::ratio18_1,true);
motor intake(PORT21, gearSetting::ratio6_1,false);//吸球
motor out(PORT21, gearSetting::ratio6_1,false); //吐球

motor intake1(PORT1, gearSetting::ratio18_1,true);
motor intake2(PORT2, gearSetting::ratio18_1,false);
motor intake3(PORT3, gearSetting::ratio18_1,false);
motor intake4(PORT4, gearSetting::ratio18_1,true);


inertial Inertial(PORT21);

rotation Rotation(PORT22);

distance DistanceBlock(PORT18);
distance DistanceA(PORT2);//底部
distance DistanceB(PORT3);//中间
distance DistanceC(PORT4);


optical Optical(PORT10);
optical OpticalDown(PORT14);
optical OpticalSep(PORT18);//Optical for Seperate

distance DistanceSep(PORT19);//DIstance for Seperate
distance Distance(PORT9);
distance DistanceD(PORT8);


pneumatics High(Brain.ThreeWirePort.A);
pneumatics Throw(Brain.ThreeWirePort.E);
pneumatics IntakeArm(Brain.ThreeWirePort.G);
pneumatics HookL(Brain.ThreeWirePort.C);
pneumatics HookR(Brain.ThreeWirePort.B);
pneumatics Mid(Brain.ThreeWirePort.H);
pneumatics Door(Brain.ThreeWirePort.F);

void Show(){}