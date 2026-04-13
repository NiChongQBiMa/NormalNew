#include "auto.h"
#include "motorcontrol.h"
#include "sensor.h"
#include "vex.h"


#include <stdint.h>

using namespace vex;

int cnt = 0;
bool BallOut = false,BallNear = true;;
bool inTake = false;
bool storea = false;
bool RED_TEAM = true,BLUE_TEAM = false;
int intake_task_func(){
    while(true){
        while(inTake){
            if(storea){
                Intake(100,100,100,32);
            } else {
                if(Distance.objectDistance(mm) < 60){
                    storea = true;
                }
                Intake(100,100,100,32);
            }
			}
        wait(10,msec);
    }
    return 1890;
}



int main_thread_S(){
    High.open();
    wait(10,msec);
    Intake(100,100,100,100);
    wait(20,msec);
    GoForWard(50,460,900);
    
    Stop(hold);
    wait(10,sec);

    return 7258;
}

void Auto_skill(){
    task Main(main_thread_S);
	task multithread(intake_task_func);
	while(true){
		this_thread::sleep_for(10);
	}	
}

bool throw_out = false;





//240左右 PID(0.45, 0.11, 7)
//600左右 PID(0.4, 0.027, 5)
//800左右 PID(0.4, 0.016, 5)

//45deg PID(1.9,0,5)
//90 PID(1.33,0,5)


//GoTo 20Power 400dis PID(0.9,0.005,12)
//-120
//-166(-46)
int main_RedthreadL(){
    timer throw_time;
    
  //  CorrectHeading(-120,1400,PID(1.24,0.2,3.7));

  //  CorrectHeading(-166,900,PID(1.75,0,1));




   inTake = true;
    High.close();
    //吸前三球
    GoForWard(100,382,900,PID(0.3, 0, 0.7));//400~500pid
    IntakeArm.open();
    GoForWard(50,84,900,PID(0.6, 0, 0));
    Stop(brake);
    CorrectHeading(-120.2,1000,PID(1.24,0.2,3.7));


    Stop(brake);


    //去中
    
    inTake = false;
    GoForWard(100,-254,700,PID(0.3, 0, 0.7));
    Mid.open();
    Stop(brake);
    throw_time = 0;
    while(1){
        if(throw_time < 200){
            Intake(40,-30,-40,-40);
        } else {
            Intake(100,100,100,-100);
        }
        if(throw_time > 1250 || cnt >= 4) break;
    }




    
    

    

    //去高
    
    
    GoForWard(100,859,2800,PID(0.27, 0, 1.0));
    Stop(brake);
    Intake(0,0,0,0);
        ///////////////////////////////////////////////--ttt
    CorrectHeading(-165,900,PID(1.75,0,1));
    Stop(brake);




    Mid.close();

    



    


    
    //吸手填
    
    inTake = true;
    IntakeArm.open();
    GoForWard(85,285,900,PID(0.3, 0, 0.7));
    
    /*
    if(DistanceD.objectDistance(mm) > 150){
        GoTo(50,150,400,PID(1.0,0,0));
    } else {
        Move(40,40);
        wait(50,msec);
    }
        
    */
    //GoForWard(40,250,500,PID(0.35, 0, 0));
    Move(27,27);
    throw_time = 0;
    while(1){
        if(throw_time > 550 || IsSeperate(OpticalDown,RED_TEAM)) break;//////////////////////
    }
    
    
   //吐高
   Move(-20,-20);
   wait(230,msec);
    HookL.open();
    HookR.open();
    GoForWard(90,-540,900,PID(0.3, 0, 0.7));
    inTake = false;
    Intake(0,0,0,0);
    High.open();
    Move(-100,-100);
    wait(50,msec);
    IntakeArm.close();
    storea = false;
    HookL.close();
    HookR.close();
    throw_time = 0;

	while(1){	

		if(Distance.objectDistance(mm) < 50) {
            Intake(40,-30,-30,100);
        }
        else {
            Intake(100,100,100,100);
        }
        if(throw_time > 850 || IsSeperate(Optical,RED_TEAM)) break;//////////////////////
    }
    Intake(0,0,0,0);
    Move(0,0);










    //钩子（淘汰赛）
    double rot = Inertial.rotation(deg);
	CorrectHeading(rot-60,700,PID(2.9,0,0));
    
    RushGo(100,115,420,PID(0.5,0,0.4));
    Stop(brake);
	CorrectHeading(rot-17,500,PID(1.72,0,3.8));
    
	RushGo(100,-360,600);
	//Stop(hold);
	Move(0,-60);
    
	wait(200,msec);
	Stop(hold);
    High.close();
    throw_time = 3000;
    while(1){
        if(Optical.isNearObject()){
            Intake(-100,-100,-100,-20);
        } else {
            Intake(-100,-100,-100,100);
        }
        if(throw_time > 2000){
            break;
        }
    }
    Intake(0,0,0,0);
   
    return 7258;






    
}

void Auto_RedleftAWP(){
    Brain.Screen.printAt(80, 136, "AL-1S");
    task Main(main_RedthreadL);
    task multithread(intake_task_func);
    while(1){
        this_thread::sleep_for(10);
    }
        
    //main_thread();
}





//Optical.hue() < 30
int main_BluethreadL(){
    timer throw_time;
    
  //  CorrectHeading(-120,1400,PID(1.24,0.2,3.7));

  //  CorrectHeading(-166,900,PID(1.75,0,1));




   inTake = true;
    High.close();
    //吸前三球
    GoForWard(100,393,900,PID(0.3, 0, 0.7));//400~500pid
    IntakeArm.open();
    GoForWard(50,76,900,PID(0.6, 0, 0));
    Stop(brake);
    CorrectHeading(-120,1000,PID(1.24,0.2,3.7));


    Stop(brake);


    //去中
    
    inTake = false;
    GoForWard(100,-257,700,PID(0.3, 0, 0.7));
    Mid.open();
    Stop(brake);
    throw_time = 0;
    while(1){
        if(throw_time < 200){
            Intake(40,-30,-40,-40);
        } else {
            Intake(100,100,100,-100);
        }
        if(throw_time > 1280 || cnt >= 4) break;
    }




    
    

    

    //去高
    
    
    GoForWard(100,865,2800,PID(0.27, 0, 1.0));
    Stop(brake);
    Intake(0,0,0,0);
        ///////////////////////////////////////////////--ttt
    CorrectHeading(-164.2,900,PID(1.75,0,1));
    Stop(brake);




    Mid.close();

    



    


    
    //吸手填
    
    inTake = true;
    IntakeArm.open();
    GoForWard(80,290,900,PID(0.3, 0, 0.7));
    
    /*
    if(DistanceD.objectDistance(mm) > 150){
        GoTo(50,150,400,PID(1.0,0,0));
    } else {
        Move(40,40);
        wait(50,msec);
    }
        
    */
    //GoForWard(40,250,500,PID(0.35, 0, 0));
    Move(27,27);
    throw_time = 0;
    while(1){
        if(throw_time > 460 || IsSeperate(OpticalDown,BLUE_TEAM)) break;//////////////////////
    }
    
    
   //吐高
    Move(-20,-20);
    wait(200,msec);
    HookL.open();
    HookR.open();
    GoForWard(90,-540,900,PID(0.3, 0, 0.7));
    inTake = false;
    Intake(0,0,0,0);
    
    Move(-100,-100);
    wait(50,msec);
    IntakeArm.close();
    storea = false;
    HookL.close();
    HookR.close();
    High.open();
    throw_time = 0;

	while(1){	

		if(Distance.objectDistance(mm) < 50) {
            Intake(40,-30,-30,100);
        }
        else {
            Intake(100,100,100,100);
        }
        if(throw_time > 550 || IsSeperate(Optical,BLUE_TEAM)) break;//////////////////////
    }
    Intake(0,0,0,0);
    Move(0,0);










    //钩子（淘汰赛）
    double rot = Inertial.rotation(deg);
	CorrectHeading(rot-60,700,PID(2.9,0,0));
    
    RushGo(100,108,420,PID(0.5,0,0.4));
    Stop(brake);
	CorrectHeading(rot-15,500,PID(1.72,0,3.8));
    
	RushGo(100,-360,600);
	//Stop(hold);
	Move(0,-60);
    
	wait(200,msec);
	Stop(hold);
    High.close();
    throw_time = 3000;
    while(1){
        if(Optical.isNearObject()){
            Intake(-100,-100,-100,-20);
        } else {
            Intake(-100,-100,-100,100);
        }
        if(throw_time > 2000){
            break;
        }
    }
    Intake(0,0,0,0);
   
    return 7258;








    




    //
}

void Auto_BlueleftAWP(){
    Brain.Screen.printAt(80, 136, "AL-1S");
    task Main(main_BluethreadL);
    task multithread(intake_task_func);
    while(1){
        this_thread::sleep_for(10);
    }
        
    //main_thread();
}















int main_RedthreadR(){
    timer throw_time;
    //RushGo(100,100,620,PID(0.5,0,0.4));
	//CorrectHeading(60,800,PID(2.5,0,0));
   // CorrectHeading(140,1000,PID(1.2,0,3.5));
   //GoForWard(100,-730,2000,PID(0.27, 0, 1.0));//580-680
 //   Stop(brake);
 //  return 0;






    Intake(100,100,0,0);
    High.close();
    //吸前三球
    GoForWard(100,385,900,PID(0.3, 0, 0.7));//400~500pid
    IntakeArm.open();
    GoForWard(50,70,900,PID(0.6, 0, 0));
    Stop(brake);
    CorrectHeading(-57.1,900,PID(1.73,0.2,3.9));

// CorrectHeading(-57,900,PID(1.72,0.2,3.9));//不放板子
    Stop(brake);




    //去中
    IntakeArm.close();
    GoForWard(100,262,700,PID(0.3, 0, 0.7));
    Stop(brake);
    //吐低
    Intake(-50,-45,-45,0);
    wait(800,msec);
    Stop(brake);



    
    
    //return 0;
    /*
    RushGo(90,110,500,PID(0.5, 0, 0));
    
    */
    Intake(0,0,0,0);

    //去高
    
    
    GoForWard(100,-892,2800,PID(0.27, 0, 1.0));
    Stop(brake);
    
    Mid.close();

    
    /////////////////////////////////////////////////
    CorrectHeading(-192.2,1000,PID(1.23,0,3.2));

    Stop(brake);
    
   // return 0;

    
    //吸手填
    
    inTake = true;
    IntakeArm.open();
    wait(200,msec);
    GoForWard(85,245,700,PID(0.3, 0, 0.7));
    //GoForWard(90,285,900,PID(0.3, 0, 0.7));
    
    /*
    if(DistanceD.objectDistance(mm) > 150){
        GoTo(50,150,400,PID(1.0,0,0));
    } else {
        Move(40,40);
        wait(50,msec);
    }
        
    */
    //GoForWard(40,250,500,PID(0.35, 0, 0));
    Move(26,26);
    throw_time = 0;
    while(1){
        if(throw_time > 500 || IsSeperate(OpticalDown,RED_TEAM)) break;//////////////////////
    }
    wait(80,msec);
    
    
   //吐高
    HookL.open();
    HookR.open();
    GoForWard(100,-550,900,PID(0.3, 0, 0.7));
    inTake = false;
    Intake(0,0,0,0);
    High.open();
    Move(-100,-100);
    wait(150,msec);
    IntakeArm.close();
    storea = false;
    HookL.close();
    HookR.close();
    throw_time = 0;

	while(1){	

		if(Distance.objectDistance(mm) < 50) {
            Intake(40,-30,-40,100);
        }
        else {
            Intake(100,100,100,100);
        }
        if(throw_time > 550 || IsSeperate(Optical,RED_TEAM)) break;//////////////////////
    }
    
    Intake(0,0,0,0);
    Move(0,0);










    //钩子（淘汰赛）
    double rot = Inertial.rotation(deg);
	CorrectHeading(rot+60,900,PID(2.9,0,0));
    //Stop(brake);
   
    RushGo(100,107,620,PID(0.5,0,0.4));
    
   // Stop(brake);
	CorrectHeading(rot+14,800,PID(1.72,0,3.9));
    //
	RushGo(100,-360,800);
	//Stop(hold);
	Move(-60,0);
	wait(200,msec);
	Stop(hold);
    High.close();
    //Intake(-100,-100,-100,0);
    //wait(2000,msec);
    Intake(0,0,0,0);
    throw_time = 3000;
    while(1){
        if(Optical.isNearObject()){
            Intake(-100,-100,-100,-20);
        } else {
            Intake(-100,-100,-100,100);
        }
        if(throw_time > 2000){
            break;
        }
    }
    Intake(0,0,0,0);

   
    return 7258;
    
    
}

void Auto_RedrightAWP(){
    Brain.Screen.printAt(80, 136, "AL-1S    Hook");
    task Main(main_RedthreadR);
    task multithread(intake_task_func);
    while(1){
        this_thread::sleep_for(10);
    }
        
    //main_thread();
}




int main_RedthreadR_0plus7(){
    timer throw_time;
    //RushGo(100,100,620,PID(0.5,0,0.4));
	//CorrectHeading(60,800,PID(2.5,0,0));
   // CorrectHeading(140,1000,PID(1.2,0,3.5));
   //GoForWard(100,-730,2000,PID(0.27, 0, 1.0));//580-680
 //   Stop(brake);
 //  return 0;






    Intake(100,100,0,0);
    High.close();
    //吸前三球
    GoForWard(100,310,900,PID(0.3, 0, 0.7));//400~500pid

    GoForWard(20,160,1300,PID(0.6, 0, 0));
    Stop(brake);
    CorrectHeading(-57.1,900,PID(1.73,0.2,3.9));

// CorrectHeading(-57,900,PID(1.72,0.2,3.9));//不放板子
    Stop(brake);




    


    
    
    //return 0;
    /*
    RushGo(90,110,500,PID(0.5, 0, 0));
    
    */


    //去高
    
    
    GoForWard(100,-618,2800,PID(0.27, 0, 1.0));
    Stop(brake);
    
    Mid.close();

    
    /////////////////////////////////////////////////
    CorrectHeading(-192.2,1000,PID(1.23,0,3.2));

    Stop(brake);
    
   // return 0;

    
    //吸手填
    
    inTake = true;
    IntakeArm.open();
    wait(200,msec);
    GoForWard(70,270,800,PID(0.3, 0, 0.7));
    //GoForWard(90,285,900,PID(0.3, 0, 0.7));
    
    /*
    if(DistanceD.objectDistance(mm) > 150){
        GoTo(50,150,400,PID(1.0,0,0));
    } else {
        Move(40,40);
        wait(50,msec);
    }
        
    */
    //GoForWard(40,250,500,PID(0.35, 0, 0));
    Move(27,27);
    throw_time = 0;
    while(1){
        if(throw_time > 500 || IsSeperate(OpticalDown,RED_TEAM)) break;//////////////////////
    }
    wait(80,msec);
    
    
   //吐高
    HookL.open();
    HookR.open();
    GoForWard(100,-550,900,PID(0.3, 0, 0.7));
    inTake = false;
    Intake(0,0,0,0);
    High.open();
    Move(-100,-100);
    wait(150,msec);
    IntakeArm.close();
    storea = false;
    HookL.close();
    HookR.close();
    throw_time = 0;

	while(1){	

		if(Distance.objectDistance(mm) < 50) {
            Intake(40,-30,-40,100);
        }
        else {
            Intake(100,100,100,100);
        }
        if(throw_time > 1690 || IsSeperate(Optical,RED_TEAM)) break;//////////////////////
    }
    

    Move(0,0);










   //大炮
    RushGo(70,135,300,PID(0.3, 0, 0.7));//400~500pid
    High.close();

    RushGo(100,-385,900,PID(0.3, 0, 0.7));//400~500pid
    Move(-100,-100);
    wait(180,msec);
    Stop(hold);

   
    return 7258;
    
    
}


void Auto_Redright_0plus7(){
    Brain.Screen.printAt(80, 136, "AL-1S    0+7");
    task Main(main_RedthreadR_0plus7);
    task multithread(intake_task_func);
    while(1){
        this_thread::sleep_for(10);
    }
        
    //main_thread();
}


int main_BthreadR_0plus7(){
    timer throw_time;
    //RushGo(100,100,620,PID(0.5,0,0.4));
	//CorrectHeading(60,800,PID(2.5,0,0));
   // CorrectHeading(140,1000,PID(1.2,0,3.5));
   //GoForWard(100,-730,2000,PID(0.27, 0, 1.0));//580-680
 //   Stop(brake);
 //  return 0;






    inTake = true;
    High.close();
    //吸前三球
    GoForWard(100,270,900,PID(0.3, 0, 0.7));//400~500pid

    GoForWard(20,180,1890,PID(0.6, 0, 0));
    Stop(brake);
    wait(50,msec);
    CorrectHeading(-57.1,900,PID(1.73,0.2,3.9));

// CorrectHeading(-57,900,PID(1.72,0.2,3.9));//不放板子
    Stop(brake);




    


    
    
    //return 0;
    /*
    RushGo(90,110,500,PID(0.5, 0, 0));
    
    */


    //去高
    
    
    GoForWard(100,-680,3200,PID(0.27, 0, 1.0));
    Stop(brake);
    
    Mid.close();

    
    /////////////////////////////////////////////////
    CorrectHeading(-192.2,1000,PID(1.23,0,3.2));

    Stop(brake);
    
   // return 0;

    
    //吸手填
    
    inTake = true;
    IntakeArm.open();
    wait(200,msec);
    GoForWard(70,256,800,PID(0.3, 0, 0.7));
    //GoForWard(90,285,900,PID(0.3, 0, 0.7));
    
    /*
    if(DistanceD.objectDistance(mm) > 150){
        GoTo(50,150,400,PID(1.0,0,0));
    } else {
        Move(40,40);
        wait(50,msec);
    }
        
    */
    //GoForWard(40,250,500,PID(0.35, 0, 0));
    Move(26,26);
    throw_time = 0;
    while(1){
        if(throw_time > 500 || IsSeperate(OpticalDown,BLUE_TEAM)) break;//////////////////////
    }
    wait(80,msec);
    
    
   //吐高
    HookL.open();
    HookR.open();
    GoForWard(100,-550,900,PID(0.3, 0, 0.7));
    inTake = false;
    Intake(0,0,0,0);
    High.open();
    Move(-100,-100);
    wait(150,msec);
    IntakeArm.close();
    storea = false;
    HookL.close();
    HookR.close();
    throw_time = 0;

	while(1){	

		if(Distance.objectDistance(mm) < 50) {
            Intake(40,-30,-40,100);
        }
        else {
            Intake(100,100,100,100);
        }
        if(throw_time > 1690 || IsSeperate(Optical,BLUE_TEAM)) break;//////////////////////
    }
    

    Move(0,0);










   //大炮
    RushGo(70,135,300,PID(0.3, 0, 0.7));//400~500pid
    High.close();

    RushGo(100,-385,900,PID(0.3, 0, 0.7));//400~500pid
    Move(-100,-100);
    wait(180,msec);
    Stop(hold);

   
    return 7258;
    
    
}


void Auto_Blueright_0plus7(){
    Brain.Screen.printAt(80, 136, "AL-1S    0+7");
    task Main(main_BthreadR_0plus7);
    task multithread(intake_task_func);
    while(1){
        this_thread::sleep_for(10);
    }
        
    //main_thread();
}


int main_BluethreadR(){
    






    timer throw_time;
    //RushGo(100,100,620,PID(0.5,0,0.4));
	//CorrectHeading(60,800,PID(2.5,0,0));
   // CorrectHeading(140,1000,PID(1.2,0,3.5));
   //GoForWard(100,-730,2000,PID(0.27, 0, 1.0));//580-680
 //   Stop(brake);
 //  return 0;

    Intake(100,100,0,0);
    High.close();
    //吸前三球
    GoForWard(100,384,900,PID(0.3, 0, 0.7));//400~500pid
    IntakeArm.open();
    GoForWard(50,76,900,PID(0.6, 0, 0));
    Stop(brake);
    CorrectHeading(-57,900,PID(1.73,0.2,3.9));

// CorrectHeading(-57,900,PID(1.72,0.2,3.9));//不放板子
    Stop(brake);




    //去中
    IntakeArm.close();
    GoForWard(100,261,700,PID(0.3, 0, 0.7));
    Stop(brake);
    //吐低
    Intake(-45,-45,-45,0);
    wait(800,msec);
    Stop(brake);



    
    
    //return 0;
    /*
    RushGo(90,110,500,PID(0.5, 0, 0));
    
    */
    Intake(0,0,0,0);

    //去高
    
    
    GoForWard(100,-874,2800,PID(0.27, 0, 1.0));
    Stop(brake);
    
    Mid.close();

    
    /////////////////////////////////////////////////
    CorrectHeading(-192,1000,PID(1.23,0,3.2));

    Stop(brake);
    
   // return 0;

    
    //吸手填
    
    inTake = true;
    IntakeArm.open();
    wait(200,msec);
    GoForWard(70,235,700,PID(0.3, 0, 0.7));
    //GoForWard(90,285,900,PID(0.3, 0, 0.7));
    
    /*
    if(DistanceD.objectDistance(mm) > 150){
        GoTo(50,150,400,PID(1.0,0,0));
    } else {
        Move(40,40);
        wait(50,msec);
    }
        
    */
    //GoForWard(40,250,500,PID(0.35, 0, 0));
    Move(27,27);
    throw_time = 0;
    while(1){
        if(throw_time > 450) break;//////////////////////
    }
    Move(-20,-20);
    wait(200,msec);                                        
    
    
   //吐高

    HookL.open();
    HookR.open();
    GoForWard(100,-520,900,PID(0.3, 0, 0.7));
    inTake = false;
    HookL.close();
    HookR.close();
    Intake(0,0,0,0);
    High.open();
    Move(-100,-100);
    wait(150,msec);
    IntakeArm.close();
    storea = false;
    
    throw_time = 0;

	while(1){	

		if(Distance.objectDistance(mm) < 50) {
            Intake(40,-30,-40,100);
        }
        else {
            Intake(100,100,100,100);
        }
        if(throw_time > 550 || IsSeperate(Optical,BLUE_TEAM)) break;//////////////////////
    }
    Intake(0,0,0,0);
    Move(0,0);










    //钩子（淘汰赛）
    double rot = Inertial.rotation(deg);
	CorrectHeading(rot+60,800,PID(2.9,0,0));
    RushGo(100,84,620,PID(0.5,0,0.4));
    
  
	CorrectHeading(rot+15.5,800,PID(1.73,0.2,3.9));
    
	RushGo(100,-350,600);
	//Stop(hold);
	Move(-60,0);
	wait(200,msec);
	Stop(hold);
    High.close();
    throw_time = 3000;
    while(1){
        if(Optical.isNearObject()){
            Intake(-100,-100,-100,-20);
        } else {
            Intake(-100,-100,-100,100);
        }
        if(throw_time > 2000){
            break;
        }
    }
    Intake(0,0,0,0);

   
    return 7258;
    
}

void Auto_BluerightAWP(){
    Brain.Screen.printAt(80, 136, "AL-1S    Hook");
    task Main(main_BluethreadR);
    task multithread(intake_task_func);
    while(1){
        this_thread::sleep_for(10);
    }
        
    //main_thread();
}
/*PID::PID(float P, float I, float D)
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
PID GO_DIS(0.13, 0, 0);*/







int main_threadR(){
    timer throw_time;
    Throw.close();
    inTake = true;
    wait(50,msec);


    //吸前3球
    GoForWard(100,259,500,PID(0.5, 0, 10));
    GoForWard(15,450,600,PID(0.5, 0, 15));
    GoForWard(40,90,500,PID(0.5, 0, 8));
    wait(220,msec);


    //去低
    CorrectHeading(-63,700,PID(1.9,0,10));
    Stop(brake);
    wait(40,msec);
    inTake = false;
    GoForWard(15,60,300);
    GoForWard(40,400,500,PID(0.5, 0, 12));
    Stop(brake);


    //吐低
    wait(60,msec);
    Intake(-30,-20,0,0);
    wait(700,msec);
    Intake(-25,0,0,0);
    wait(200,msec);
    //去高
    inTake = true;
    GoForWard(100,-640,700,PID(0.7,0,18));
    GoForWard(30,-200,600);
    inTake = false;
    wait(90,msec);
    CorrectHeading(69,800,PID(1.9,0,10));
    Stop(brake);
    wait(50,msec);




    //扫围板
    GoTo(-30,397,1020,PID(0.13,0,0));
    wait(200,msec);
    CorrectHeading(166.5,800);
    Stop(brake);
    wait(140,msec);
    
    //return 0;

    //吸手填
    IntakeArm.open();
    inTake = true;
    GoForWard(50,250,1000);
    Move(30,30);
    wait(1200,msec);
    Move(30,30);
    wait(200,msec);
    Move(0,0);
    wait(100,msec);


    //吐高
    Move(-30,-30);
    wait(100,msec);
    GoForWard(100,-500,800);
    inTake = false;
    Intake(0,0,0,0);
    Move(-50,-50);
    wait(160,msec);
    Intake(100,100,100,100);
    IntakeArm.close();
    wait(1850,msec);


    //大炮（资格赛）
    GoForWard(100,200,500);
    Move(-100,-100);
    wait(1,sec);

    return 7258;
}
void Auto_rightAWP(){
    Brain.Screen.printAt(80, 136, "AL-1S");
    task Main(main_threadR);
    task multithread(intake_task_func);
    while(1){
        this_thread::sleep_for(10);
    }
}
/*void GoForWard(float Power, float Target, float FullTime, PID pid)
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
		out = out *  (time < 300 ? (time / 300.0) * 0.8 : 1);
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
		out = out *  (time < 100 ? (time / 100.0) * 0.8 : 1);
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
}*/