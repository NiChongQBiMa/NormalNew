#include <vex.h>

#define WHEEL_DIAMETER_R 4
#define WHEEL_DIAMETER_S 4

extern bool abcde;//为了报复上一个起变量名的，我也起abcde
extern bool delay_time;
extern bool aBool;
extern bool color2;
typedef class PID
{
private:
  float p;
  float i;
  float d;

public:
  PID(float p, float i, float d);
  float P();
  float I();
  float D();
  float OUT(float err, float Lasterr, float accerr);
} PID;

extern PID GO_DEG;
extern PID GO_MM;
extern PID GO_V;
extern PID TURN_DEG;

typedef class Pos
{
public:
  float a;
  float y;
  float x;

  float Last_right;
  float Last_back;

  Pos(int A, int X, int Y);
} Pos;

extern Pos Position;

typedef class pneu
{
private:
  pneumatics *pne;
  bool flag;

public:
  pneu(pneumatics *pne, bool flag);
  bool state;
  void Open();
  void Close();

} pneu;

float Getlength(Pos A, Pos B);
float GetAngle(Pos A, Pos B);
void TrackPostation(float right, float back);

//--------------------------------------------
extern bool down;
extern float down_num;
void Update();

void shoot();
extern int Tar;

void ResetMotor();
void Move(float lpower, float rpower);
void Stop(vex::brakeType type = vex::brake);

void DiskIntake(float Power);
void Scroller(float Power,brakeType type = vex::coast);
void IntakeA(float Power,bool sjhsb = false);
void Lift(float Power, brakeType type = vex::hold);
void Pick(float Power);


void vo();


int LiftUpDegree(float Power, float Target, float FullTime);
void ScrollerUpDegree(float Power, float Target, float counter,float FullTime,PID pid);
void GoTo1(float Power, float Target, float FullTime, PID pid,void (*func)()=vo,float funcbegin=0);

void GoTo_move(float Power, float Target, float FullTime, PID pid,void (*func)()=vo,float funcbegin=0);
//void ScrollerToReadyPosition(float Power);

void BlockIntake(float Power);
void SeperateThrow(int Power, bool throw_option);


void SeperateThrow_mid(int Power,bool throw_option);
double getCurrentScrollerAngle();

bool isDiskIn();


void print(double value,short row);
void printStr(char* str,short row);
void CurveForwardR(float lPower, float rPower,float Target, float FullTime, PID pid);
void CurveForwardL(float lPower, float rPower,float Target, float FullTime, PID pid);
void GoTo(float Power, float Target, float FullTime, PID pid);
//
void GoForWard(float Power, float Target, float FullTime,PID pid = GO_DEG);
void RushGo(float Power, float Target, float FullTime,PID pid = GO_DEG);
void CorrectHeading(float Target, float FullTime, PID pid = TURN_DEG);
//
void Intake(float Powera,float Powerb,float Powerc,float Powerd);
void Intakea(float powera);
void Intakeb(float powerb);
void Intakec(float powerc);
void ThrowOut(float Power, brakeType type);
bool IsSeperate(optical Opt,bool team);
void CorrectHeading_OneSide(float Target, float FullTime, PID pid);