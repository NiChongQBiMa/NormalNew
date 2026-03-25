#include "motorcontrol.h"
#include "sensor.h"

//------------PID---------------------------------------------------------------------------------------
PID::PID(float P, float I, float D)
{
	this->p = P;
	this->i = I;
	this->d = D;
}
float PID::OUT(float err, float lastErr, float totalErr)
{
	return p * err + i * totalErr + d * (err - lastErr);
}

PID GO_DEG(0.4, 0, 0); // 32
PID TURN_DEG(1.9, 0, 14); // 1.7, 0, 10
PID GO_DIS(0.13, 0, 0);

//----------------------------------------------------------------------------

void ResetMotor()
{
	LeftMotor1.setBrake(coast); // 初始停止模式
	LeftMotor2.setBrake(coast);
	LeftMotor3.setBrake(coast);
	RightMotor1.setBrake(coast);
	RightMotor2.setBrake(coast);
	RightMotor3.setBrake(coast);
	LeftMotor1.resetPosition(); // 初始编码器，重置为0
	LeftMotor2.resetPosition();
    LeftMotor3.resetPosition();
	RightMotor1.resetPosition();
	RightMotor2.resetPosition();
    RightMotor3.resetPosition();
	LeftMotor1.setMaxTorque(2, Nm); // 初始扭矩
	LeftMotor2.setMaxTorque(2, Nm);
    LeftMotor3.setMaxTorque(2, Nm);
	RightMotor1.setMaxTorque(2, Nm);
	RightMotor2.setMaxTorque(2, Nm);
    RightMotor3.setMaxTorque(2, Nm);
	LeftMotor1.setVelocity(0, pct); // 初始电机速度
	LeftMotor2.setVelocity(0, pct);
    LeftMotor3.setVelocity(0, pct);
	RightMotor1.setVelocity(0, pct);
	RightMotor2.setVelocity(0, pct);
    RightMotor3.setVelocity(0, pct);
}

void Move(float lpower, float rpower)
{
	LeftMotor1.spin(fwd, 0.128 * lpower, voltageUnits::volt);
	LeftMotor2.spin(fwd, 0.128 * lpower, voltageUnits::volt);
	LeftMotor3.spin(fwd, 0.128 * lpower, voltageUnits::volt);
	RightMotor1.spin(fwd, 0.128 * rpower, voltageUnits::volt);
	RightMotor2.spin(fwd, 0.128 * rpower, voltageUnits::volt);
	RightMotor3.spin(fwd, 0.128 * rpower, voltageUnits::volt);
}


void Stop(brakeType type)
{
	LeftMotor1.stop(type);
	LeftMotor2.stop(type);
	LeftMotor3.stop(type);
	RightMotor1.stop(type);
	RightMotor2.stop(type);
	RightMotor3.stop(type);
}




float accerr = 0;

void RushGo(float Power, float Target, float FullTime, PID pid)
{
	float curR = 0, errR = 0, LasterrR = 0, accerrR = 0, outR = 0;
	float curL = 0, errL = 0, LasterrL = 0, accerrL = 0, outL = 0;
	float out = 0;
	float gyro = Inertial.rotation(),gyro_err = 0;
	ResetMotor();
	timer time;
	while (time < FullTime)
	{
        // 更新误差
		curR = (RightMotor1.position(deg) + RightMotor2.position(deg) + RightMotor3.position(deg)) / 3;
		curL = (LeftMotor1.position(deg) + LeftMotor2.position(deg) + LeftMotor3.position(deg)) / 3;
		errR = Target - curR;
		errL = Target - curL;

        // 分段积分
		if (errL < Target * 0.1)
		{
			accerrL += errL;
		}
		if (errR < Target * 0.1)
		{
			accerrR += errR;
		}

        // 计算输出功率
		outL = pid.OUT(errL, LasterrL, accerrL);
		outR = pid.OUT(errR, LasterrR, accerrR);
		out = (outL + outR) / 2;
		out = out *  (time < 10 ? (time / 10.0) * 0.8 : 1);
        // 将功率限制在-Power~Power之间
		if (fabs(out) > Power)
		{
			if (Target > 0)
			{
				out = Power;
			}
			else
			{
				out = -Power;
			}
		}
		Move(out, out);

        // 退出条件
		if (fabs(errL) < 10 || fabs(errR) < 10)
		{
			break;
		}
        
        // 更新
		LasterrL = errL;
		LasterrR = errR;
		wait(10,msec);
	}
	Stop(coast);
}
void GoForWard(float Power, float Target, float FullTime, PID pid)
{
	float curR = 0, errR = 0, LasterrR = 0, accerrR = 0, outR = 0;
	float curL = 0, errL = 0, LasterrL = 0, accerrL = 0, outL = 0;
	float out = 0;
	float gyro = Inertial.rotation(),gyro_err = 0;
	ResetMotor();
	timer time;
	while (time < FullTime)
	{
        // 更新误差
		curR = (RightMotor1.position(deg) + RightMotor2.position(deg) + RightMotor3.position(deg)) / 3;
		curL = (LeftMotor1.position(deg) + LeftMotor2.position(deg) + LeftMotor3.position(deg)) / 3;
		errR = Target - curR;
		errL = Target - curL;

        // 分段积分
		if (errL < Target * 0.1)
		{
			accerrL += errL;
		}
		if (errR < Target * 0.1)
		{
			accerrR += errR;
		}

        // 计算输出功率
		outL = pid.OUT(errL, LasterrL, accerrL);
		outR = pid.OUT(errR, LasterrR, accerrR);
		out = (outL + outR) / 2;
		out = out *  (time < 150 ? (time / 150.0) : 1);
        // 将功率限制在-Power~Power之间
		if (fabs(out) > Power)
		{
			if (Target > 0)
			{
				out = Power;
			}
			else
			{
				out = -Power;
			}
		}
		Move(out, out);

        // 退出条件
		if (fabs(errL) < 10 || fabs(errR) < 10)
		{
			break;
		}
        
        // 更新
		LasterrL = errL;
		LasterrR = errR;
		wait(10,msec);
	}
	Stop(coast);
}



void CorrectHeading(float Target, float FullTime, PID pid)
{
	float cur = 0;
	float err = 0;
	float Lasterr = 0;
	float accerr = 0;
	float out = 0;
	timer time;
	while (time < FullTime)
	{
        // 更新误差
		cur = Inertial.rotation();
		err = Target - cur;

        // 分段积分
		if (fabs(err) < 10)
		{
			accerr += err;
		}

        // 计算输出功率
		out = pid.OUT(err, Lasterr, accerr);
		//out = out *  (time < 100 ? (time / 100.0) : 1);
		Move(out, -out);

        // 退出条件
		if (fabs(err) < 1)
		{
			break;
		}

        // 更新
		Lasterr = err;
		wait(10,msec);
	}
	Stop(coast);
}










































//画弧--------------------------------------------------------------------------------------
void CurveForwardL(float lPower, float rPower,float Target, float FullTime, PID pid)
{
	float cur = Inertial.rotation();
	float err = 0;
	float Lasterr = 0;
	float accerr = 0;
	float out = 0;
	timer time;
	while (time < FullTime)
	{
		cur = Inertial.rotation();
		err = Target - cur;
		if (fabs(err) < 10)
		{
			accerr += err;
		}
		out = pid.OUT(err, Lasterr, accerr);
		Move(-out * (lPower / 100),-out * (rPower / 100));
		if (fabs(err) < 1)
		{
			break;
		}
		Lasterr = err;
		wait(10,msec);
	}
	Stop(coast);
}

void CurveForwardR(float lPower, float rPower,float Target, float FullTime, PID pid)
{
	float cur = 0;
	float err = 0;
	float Lasterr = 0;
	float accerr = 0;
	float out = 0;
	timer time;
	while (time < FullTime)
	{
		cur = Inertial.rotation();
		err = Target - cur;
		if (fabs(err) < 10)
		{
			accerr += err;
		}
		out = pid.OUT(err, Lasterr, accerr);
		Move(out * (lPower / 100),out * (rPower / 100));
		if (fabs(err) < 1)
		{
			break;
		}
		Lasterr = err;
		wait(10,msec);
	}
	Stop(coast);
}
//---------------------------------------------------------------------------------------------------------

void GoTo(float Power, float Target, float FullTime, PID pid)
{
	float cur = 0;
	float err = 0;
	float Lasterr = 0;
	float accerr = 0;
	float out = 0;
	timer time;
	while (time < FullTime)
	{
		cur = DistanceD.objectDistance(mm);
		err = cur - Target;

        if (fabs(err) < 20)
        {
		    accerr += err;
        }

		out = pid.OUT(err, Lasterr, accerr);
		if (fabs(out) > Power)
		{
			if (out > Power)
			{
				out = Power;
			}
			else
			{
				out = -Power;
			}
		}
		Move(out, out);
        
		if (fabs(err) < 7)
		{
			break;
		}

		Lasterr = err;
		wait(10,msec);
	}
	Stop(hold);
}


//屏幕打印-------------------------------------------------
void print(double value,short row){
	Controller.Screen.setCursor(row,1);
	Controller.Screen.print(value);
}

void printStr(char* str,short row){
	Controller.Screen.setCursor(row,1);
	Controller.Screen.print(str);
}
//--------------------------------------------------------



//吸球Intake---------------------------------------------------------------------
void Intakea(float Powera)
{
	if (Powera == 0)
	{
		intake1.stop(hold);
	}
	
	else
	{
		intake1.spin(fwd,0.128 * Powera, voltageUnits::volt);
		
	}
}
void Intakeb(float Powerb)
{

	if (Powerb == 0)
	{
		intake2.stop(hold);
	}
	else
	{
		intake2.spin(fwd,0.128 * Powerb, voltageUnits::volt);
	}
}
void Intakec(float Powerc)
{

	if (Powerc == 0)
	{
		intake3.stop(hold);
	}
	else
	{

		intake3.spin(fwd,0.128 * Powerc, voltageUnits::volt);
	}
}
void ThrowOut(float Power, brakeType type)//coast、brake、hold
{
	if (Power == 0)
	{
		intake4.stop(type);
	}
	else
	{
		intake4.spin(fwd, 0.128 * Power, voltageUnits::volt);
	}
}
void Intake(float Powera,float Powerb,float Powerc,float Powerd){
	Intakea(Powera);
	Intakeb(Powerb);
	Intakec(Powerc);
	ThrowOut(Powerd,hold);
}
//-------------------------------------------------------------------------------




bool IsSeperate(optical Opt,bool team){
	bool isRed = false,isBlue = false,isUnknown = false,isSeperate = false;
	if(Opt.isNearObject()){//红球/蓝球判断条件
		isRed = Opt.hue() < 15 || Opt.hue() > 345;//
		isBlue = Opt.hue() > 200 && Opt.hue() < 250;//
		isUnknown = !(isRed || isBlue);
	} else {
		isRed = false;
		isBlue = false;
		isUnknown = true;
	}
	
	if(team)isSeperate = isBlue;//team为true代表红队，红队分蓝
	else  isSeperate = isRed;//蓝队分红
	return isSeperate;
}




/*
void GoToFront(float Power, float Target, float FullTime, PID pid)
{
	float cur = 0;
	float err = 0;
	float Lasterr = 0;
	float accerr = 0;
	float out = 0;
	timer time;
	while (time < FullTime)
	{
		cur = DistanceFront.objectDistance(mm);
		err = cur - Target;

        if (fabs(err) < 30)
        {
		    accerr += err;
        }

		out = pid.OUT(err, Lasterr, accerr);
		if (fabs(out) > Power)
		{
			if (out > Power)
			{
				out = Power;
			}
			else
			{
				out = -Power;
			}
		}
		Move(out, out);
        
		if (fabs(err) < 30)
		{
			break;
		}

		Lasterr = err;
		wait(10,msec);
	}
	Stop(brake);
}

void GoToBack(float Power, float Target, float FullTime, PID pid)
{
	float cur = 0;
	float err = 0;
	float Lasterr = 0;
	float accerr = 0;
	float out = 0;
	timer time;
	while (time < FullTime)
	{
		cur = DistanceBack.objectDistance(mm);
		err = Target - cur;
        
        if (fabs(err) < 30)
        {
		    accerr += err;
        }

		out = pid.OUT(err, Lasterr, accerr);
		if (fabs(out) > Power)
		{
			if (out > Power)
			{
				out = Power;
			}
			else
			{
				out = -Power;
			}
		}
		Move(out, out);

		if (fabs(err) < 30)
		{
			break;
		}

		Lasterr = err;
		wait(10,msec);
	}
	Stop(brake);
}
*/
/*
void Intake(short motor_number, float Power){
	if (Power == 0){
		if (motor_number == 1){
			intake1.stop(hold);
		}
		if (motor_number == 2){
			intake2.stop(hold);
		}
		if (motor_number == 3){
			intake3.stop(hold);
		}
		if (motor_number == 4){
			intake4.stop(hold);
		}
	}
	else{
		if (motor_number == 1){
			intake1.spin(fwd, 0.128 * Power, voltageUnits::volt);
		}
		if (motor_number == 2){
			intake2.spin(fwd, 0.128 * Power, voltageUnits::volt);
		}
		if (motor_number == 3){
			intake3.spin(fwd, 0.128 * Power, voltageUnits::volt);
		}
		if (motor_number == 4){
			intake4.spin(fwd, 0.128 * Power, voltageUnits::volt);
		}
	}
}

void BlockIntake(float Power){
	Intake(1,Power);
	Intake(2,Power);
	Intake(3,Power);
}

void AllIntake(float Power){
	Intake(1,Power);
	Intake(2,Power);
	Intake(3,Power);
	Intake(4,Power);
}
*/
//----------------------------------------------------------
