#include "auto.h"
#include "motorcontrol.h"
#include "sensor.h"
#include "vex.h"
#include <bits/stdc++.h>
#include <cstring>
#include <stdint.h>

using namespace vex;
vex::competition Competition;
using signature = vision::signature;
using code = vision::code;


void Initializing()
{ // 初始化

	Rotation.resetPosition();
	Optical.setLightPower(100);
	Brain.Screen.setFont(vex::fontType::mono40);
	int color = 0;
	timer printtime;
	while (Inertial.isCalibrating())
	{ // 正在校准，当惯性传感器正在执行请求的重新校准时返回 true。当重新校准完成时返回 false。
		Controller.Screen.setCursor(1, 1);
		Controller.Screen.print("%f", Inertial.rotation(deg));
		Controller.Screen.clearScreen();
		if (color >= 0)
		{
			Brain.Screen.setPenColor(purple);
		}
		if (color >= 50)
		{
			Brain.Screen.setPenColor(blue);
		}
		if (color >= 100)
		{
			Brain.Screen.setPenColor(cyan);
		}
		if (color >= 150)
		{
			Brain.Screen.setPenColor(green);
		}
		Brain.Screen.printAt(80, 136, "Initializing...");
		wait(10,msec);
		color++;
	}
	Brain.Screen.clearScreen();
	//IntakeArm.open();
}
// solt1:红左
// solt2:蓝左
// solt3:红右
// solt4:蓝右
// solt5:test
// solt6:
// solt7:
// solt8:skill

//////////////////分球///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
bool team = false;//true：红队 false：蓝队
bool seperate = true;//设置是否开启分球
	/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////
int Auton = 2;
/// //////////////////////////////

void runauto()
{
	while (Inertial.isCalibrating())
	{
		wait(10,msec);
	}
	switch (Auton)
	{ // 选择结构-switch语句  输入Auton,执行case (Auton).  若不加break，则接着执行下个case直到break
	case 1:
		Auto_RedleftAWP(); 
		break;
	case 2:
		Auto_BlueleftAWP(); 
		break;
	case 3:
		Auto_RedrightAWP(); 
		break;
	case 4:
		Auto_BluerightAWP(); 
		break;
	case 5:
		Auto_Redright_0plus7();
		break;
	case 6:
		//Auto_left();//
		break;
	case 7:
		//Auto_right();
		break;
	case 8:
		Auto_skill();
		break;
	} // default：当所有的case都不匹配表达式中的值的时候，默认最后执行default中语句体
}
//-----------------`  ------------------------------------------------------
void autonomous(void) { runauto(); }//自动

vex::task skill;
int skill_stage = 1;
timer ski_time1;
bool timeflag1 = true;
timer ski_time2;
bool timeflag2 = true;
timer ski_time3;
bool timeflag3 = true;
int ski()
{

	switch (skill_stage)
	{
	case 1:
	{
		timeflag3 = true;
		if (!down)
		{
		}
		else
		{
			skill_stage = 2;
		}
	}
	break;
	case 2:
	{
		timeflag1 = true;
		if (timeflag2)
		{
			timeflag2 = false;
			ski_time2 = 0;
		}
		if (!timeflag2)
		{
			if ((Rotation.angle(deg) > 45 && Rotation.angle(deg) < 100) || ski_time2 < 20)
			{
			}
			else
			{
				
				skill_stage = 3;
			}
		}
		break;
	}
	case 3:
	{
		timeflag2 = true;
		if (timeflag3)
		{
			timeflag3 = false;
			ski_time3 = 0;
		}
		if (ski_time3 < 30)
		{
			
		}
		else
		{
			skill_stage = 1;
		}
		break;
	}
	}
	return 1;
}



int count;
/*手动操作：
	//左摇杆：底盘移动
	//L1、L2:手动控制挡球气动
	//按住X:板放平，吐球，挡球气动缩回（最高的筒）
	//按住B：从中间吐
	//R1：按住R1吸球+分球，板抬起，挡球气动伸出
	//R2:反转intake电机
*/
const short unknown = 0;
const short Blue = 1;
const short Red = 2;
short get_color(short optical_num){
	/*if (optical_num == 1){
		if (OpticalDown.isNearObject()){
			if (OpticalDown.hue() < 50 || OpticalDown.hue() > 350){
				return Red;
			}
			else if (OpticalDown.hue() > 120 && OpticalDown.hue() < 300){
				return Blue;
			}
			else{
				return unknown;
			}
		}
		else{
			return unknown;
		}
	}
	else */if (optical_num == 2){
		if (Optical.isNearObject()){
			if (Optical.hue() < 50 || Optical.hue() > 350){
				return Red;
			}
			else if (Optical.hue() > 120 && Optical.hue() < 300){
				return Blue;
			}
			else{
				return unknown;
			}
		}
		else{
			return unknown;
		}
	}
	else{
		return unknown;
	}
}

bool not_own(bool given_team, short optical_num){
	return ((given_team && get_color(optical_num) == Blue)||(!given_team && get_color(optical_num) == Red));
}

bool is_own(bool given_team, short optical_num){
	return ((given_team && get_color(optical_num) == Red)||(!given_team && get_color(optical_num) == Blue));
}
void drivercontrol(void)
{

	Controller.Screen.clearScreen();
	int Ch1, Ch2, Ch3, Ch4;
	bool L1, L2, R1, R2, BtnA, BtnB, BtnX, BtnY, BtnU, BtnD, BtnL, BtnR;









	bool HOOK = false;
	bool extension = true;//标记拦球气动有没有伸出来
	bool block_out = false;
	bool Arm = false;
	bool ArmOut = false;
	bool hook = false;//标记钩子是否伸出
	bool hookout = false;//标记L1是否已经按下
	bool BtnU2 = false;
	count = 0;
	timer show_time;

	int full_throw_time2 = 72;  //最大吐中时间、、
	timer throw_time2;throw_time2 = full_throw_time2;
	timer intake_time;
	timer time1;
	timer time2;
	bool store = false;
	bool ToBeSeperate = false;//upp seperate
	bool TobeSeperate = false;//door seperate
	bool LockSeperate = false;
	bool LockSeperate_Out = true;
	//std::string currColor = "unknown", nextColor = "unknown";
	bool isRed = false,isBlue = false,isUnknown = !(isRed || isBlue);
	bool isSeperate = false;
	bool IsSeperate_Down = false;
	int full_throw_time = 235;//最大分球时间//////////////////////////////////////
	timer throw_time;throw_time = full_throw_time;//分球时间timer
	
	Optical.setLightPower(100);
	OpticalDown.setLightPower(100);
	OpticalSep.setLightPower(100);
	while (true) 
	{
		wait(5,msec);
		Show();
		Ch1 = Controller.Axis1.value();  
		Ch2 = Controller.Axis2.value();
		Ch3 = -Controller.Axis3.value();
		Ch4 = Controller.Axis4.value();
		L1 = Controller.ButtonL1.pressing();
		L2 = Controller.ButtonL2.pressing();
		R1 = Controller.ButtonR1.pressing();
		R2 = Controller.ButtonR2.pressing();
		BtnA = Controller.ButtonA.pressing();
		BtnB = Controller.ButtonB.pressing();
		BtnX = Controller.ButtonX.pressing();
		BtnY = Controller.ButtonY.pressing();
		BtnU = Controller.ButtonUp.pressing();
		BtnD = Controller.ButtonDown.pressing();
		BtnL = Controller.ButtonLeft.pressing();
		BtnR = Controller.ButtonRight.pressing();

		if(Optical.isNearObject()){//红球/蓝球判断条件
			isRed = Optical.hue() < 15 || Optical.hue() > 330;//
			isBlue = Optical.hue() > 190 && Optical.hue() < 250;//
			isUnknown = !(isRed || isBlue);
		} else {
			isRed = false;
			isBlue = false;
			isUnknown = true;
		}
		
		if(seperate){
			if(team)//team为true代表红队，红队分蓝
			{
				isSeperate = isBlue;
	    	}
			else  //蓝队分红
			{
				isSeperate = isRed;
			}
		} else {
			isSeperate = false;
		}
		


		

		if (  abs(Ch3) >20  && abs(Ch4) > 20 ){
			Move((Ch3+ Ch4)*0.6, (Ch3 - Ch4)*0.6);//可根据摇杆值，灵敏地进行转向，直接使用即可
			//左前右前
		}
		/*else if (  (Ch3) < -20  && abs(Ch4) > 20 ){
			Move((Ch3- Ch4)*0.6, (Ch3 + Ch4)*0.6);//左后右后
		}
	*/
		else if (abs(Ch3) >0 && abs(Ch4) < 20){
			Move((Ch3), (Ch3));//直行死区
		}
		else if (abs(Ch3) < 20 && abs(Ch4) > 20){
			Move((Ch4), (-Ch4));//原地转死区
		}
		else{
			Stop(coast);//以coast形式停止转动
		}
		



		
		if(R1){//吸球，分球？
			HOOK = true;
			HookL.open();
			High.close();
			if((!IsSeperate(OpticalDown,team) && !IsSeperate(OpticalSep,team))){//若两个颜色都检测不到需要Seperate的球，标志变量为false
				TobeSeperate = false;
			}
			if(IsSeperate(OpticalSep,team) && !TobeSeperate) throw_time = 0;//上方颜色第一次检测到需要分的球
			if(IsSeperate(OpticalDown,team)){//下方颜色
				TobeSeperate = true;//防止throwtime反复被赋值为0
				//IsSeperate_Down = false;
				Intakea(10);//减速
				Intakeb(10);
			}
			if(IsSeperate(OpticalSep,team)){//上方颜色
				//if(!TobeSeperate) throw_time = 0;
				TobeSeperate = true;
				IsSeperate_Down = false;//将变量标记为未被分球状态
				Intakea(0);//锁死
				Intakeb(0);
				
			} 
			if(TobeSeperate){//要分球则门打开
				Door.open();
			}
			if(IsSeperate_Down && !TobeSeperate){//已分出且将要分球为否则门关闭
				Door.close();
			}
			
			if(IsSeperate(OpticalSep,team) && throw_time > 400){//待分的球持续在颜色前方等待直至门完全打开
				Intakea(10);
				Intakeb(30);
			}
			
			if(DistanceSep.objectDistance(mm) < 40){//前方激光看到球已滚落
				IsSeperate_Down = true;
			}
			

			if(!TobeSeperate && throw_time > 400) {//不用分球，也不在分球timer中
				Intakea(100);
				Intakeb(100);
			}
			//Original program//
			
			if(Distance.objectDistance(mm) < 50){
				store = true;//下球道存球状态
				Mid.close();
			}
			if(!store) {//无球
				Intakec(100);
				ThrowOut(-20,hold);
			} else {//存1球
				Intakec(100);
				ThrowOut(0,hold);
			}
			
			
			

			
			
			
		
		} else if (Ch2 > 30){//吐高
			Mid.close();
			High.open();
			store = false;
			
			if(Distance.objectDistance(mm) < 40){
				Intake(30,-50,-100,100);
			} else {
				Intake(100,100,100,100);
				
			}
	
		} else if(Ch2 < -8){//吐中
			High.close();
			Mid.open();
			Intake(0,0,0,0);
			if(Ch2 < -110){
				if(Distance.objectDistance(mm) < 50 && !block_out){
					Intake(40,-30,-30,-100);
					throw_time2 = 0;
				} else if(throw_time2 < full_throw_time2){
					Intake(40,-30,-30,-100);
				} else {
				block_out = true;
					
				Intake(-Ch2 * 0.5,-Ch2 * 0.5,-Ch2 * 0.5,Ch2 * 0.5);
				}
			
				
					
			}
			
			
		} else if(R2){//吐底
			Mid.close();
			High.close();
			store = false;
			if(Optical.isNearObject()){
				Intake(-20,-50,-50,-20);
			} else {
				Intake(-20,-50,-50,100);
			}
			
			
		} else if(BtnA){//吐底-大功率
			Mid.close();
			High.close();
			store = false;
			if(Optical.isNearObject()){
				Intake(-100,-100,-100,-20);
			} else {
				Intake(-100,-100,-100,100);
			}
			
		}
		else {
			block_out = false;
			Mid.close();
			High.close();
			Intake(0,0,0,0);
		}
		if(BtnB && ArmOut){//放手填板
			ArmOut = false;
			if(!Arm){
				IntakeArm.open();
				Arm = true;

			} else {
				IntakeArm.close();
				Arm = false;
			}
		} else if(!BtnB){
			ArmOut = true;
		}
		if(HOOK && !L1){//钩子
			HookL.open();
			HookR.open();
		} else {
			HookL.close();
			HookR.close();
		}
		if(BtnY){
			Door.open();
		} else if(!TobeSeperate && IsSeperate_Down){
			Door.close();
		}
		
	}
}

int main()
{
	Inertial.startCalibration();//初始化
	Initializing();//初始化

	Competition.autonomous(autonomous);//自动

	Competition.drivercontrol(drivercontrol);//手动
	double curR,curL;
	while (1)//停
	{
		curR = (RightMotor1.position(deg) + RightMotor2.position(deg) + RightMotor3.position(deg)) / 3;
		curL = (LeftMotor1.position(deg) + LeftMotor2.position(deg) + LeftMotor3.position(deg)) / 3;

/*

		print((curR + curL) / 2,1);
		print(Inertial.rotation(),2);
		print(DistanceD.objectDistance(mm),3);
		*/
		task::sleep(10);
	}
}
