#include "external.h" 
#include "api.h"
#include "propeller.h"
#include "servo.h" 
//USB通讯控制编程界面
int jsq=0;//计数器变量
int yuan=0;//计数器变量
int fang=0;//计数器变量
int cha=0;//差值变量
//初始运动速度
float one=80;//1级偏移幅度调整姿态初始速度
float two=60;//2级偏移幅度调整姿态初始速度
float three=40;//3级偏移幅度调整姿初始速度
float four=20;//4级偏移幅度调整姿态初始速度
float mind=60;//前进初始速度

//复位最大速度
float onemax=80;//1级偏移幅度调整姿态最大速度
float twomax=60;//2级偏移幅度调整姿态最大速度
float threemax=40;//3级偏移幅度调整姿态最大速度
float fourmax=20;//4级偏移幅度调整姿态最大速度
float mindmax=60;////前进最大速度

//临界限位速度
float onelimit=80;//1级偏移幅度调整姿态临界速度
float twolimit=60;//2级偏移幅度调整姿态临界速度
float threelimit=40;//3级偏移幅度调整姿态临界速度
float fourlimit=20;//4级偏移幅度调整姿态临界速度
float mindlimit=60;//前进临界速度

void sudu()
{	one=onemax;
	two=twomax;
  three=threemax;
  four=fourmax;
	mind=mindmax;
}
void onesudu()
{	
	 one=one-1;
		if(one<=onelimit)
		{one=onemax;
		}
	
}
void twosudu()
{	
	 two=two-1;
		if(two<=twolimit)
		{two=twomax;
		}		
	
}

void threesudu()
{	
	three=three-1;
		if(three<=threelimit)
		{three=threemax;
		}
	
}

void foursudu()
{	
	four=four-1;
		if(four<=fourlimit)
		{four=fourmax;
		}
	
}
void mindsudu()
{	
	mind=mind+1;
		if(mind>=mindlimit)
		{mind=mindmax;
		}		
    sudu();
	
}
	void URAT8_DATA_Analysis(u8 data)
{
	switch(data)
	{
		case 'A' :
		{//左转400转速
     jsq=jsq-1;//用来控制灯熄灭的时间
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,0,1);//右前
    TJQ_Control(T2,35,0);//右后
	  TJQ_Control(T3,0,1);//左后
    TJQ_Control(T4,35,0);//左前
    TJQ_Control(T6,0,0);//左中
    TJQ_Control(T7,0,1);//右中	
	  onesudu();
			break;
		}
		case 'S' :
		{//左转230
      //执行语句
     jsq=jsq-1;//用来控制灯熄灭的时间
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,0,1);//左后
    TJQ_Control(T2,25,0);//左前
	  TJQ_Control(T3,0,1);//右前
    TJQ_Control(T4,25,0);//右后
    TJQ_Control(T6,0,0);//左中
    TJQ_Control(T7,0,1);//右中
    twosudu();
			break;
		}
		case 'D' :
		{//左转100
			//执行语句
    jsq=jsq-1;//用来控制灯熄灭的时间
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,0,1);//左后
    TJQ_Control(T2,15,0);//左前
	  TJQ_Control(T3,0,1);//右前
    TJQ_Control(T4,15,0);//右后
    TJQ_Control(T6,0,0);//左中
    TJQ_Control(T7,0,1);//右中
		threesudu();
			break;
		}
		case 'F' :
		{//左转50
			//执行语句
		jsq=jsq-1;//用来控制灯熄灭的时间
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
	  TJQ_Control(T1,0,1);//左后
    TJQ_Control(T2,10,0);//左前
	  TJQ_Control(T3,0,1);//右前
    TJQ_Control(T4,10,0);//右后
    TJQ_Control(T6,0,0);//左中
    TJQ_Control(T7,0,1);//右中
		foursudu();
			break;
		}
		case 'G' :
		{
			//执行语句
    jsq=jsq-1;//用来控制灯熄灭的时间
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,0,1);//左后
    TJQ_Control(T2,50,0);//左前
	  TJQ_Control(T3,50,1);//右前
    TJQ_Control(T4,0,0);//右后
    TJQ_Control(T6,0,0);//左中
    TJQ_Control(T7,0,1);//右中
		mindsudu();
			break;
		}
		case 'H' :
		{//右转50速度
			//执行语句
		jsq=jsq-1;//用来控制灯熄灭的时间
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,10,1);//左后
    TJQ_Control(T2,0,0);//左前
	  TJQ_Control(T3,10,1);//右前
    TJQ_Control(T4,0,0);//右后
    TJQ_Control(T6,0,0);//左中
    TJQ_Control(T7,0,1);//右中
		foursudu();
			break;
		}
		case 'J' :
		{//右转100速度
			//执行语句
		jsq=jsq-1;//用来控制灯熄灭的时间
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,15,1);//左后
    TJQ_Control(T2,0,0);//左前
	  TJQ_Control(T3,15,1);//右前
    TJQ_Control(T4,0,0);//右后
    TJQ_Control(T6,0,0);//左中
    TJQ_Control(T7,0,1);//右中
		threesudu();
			break;
		}
		case 'K' :
		{//右转200速度
			//执行语句
    jsq=jsq-1;//用来控制灯熄灭的时间
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,25,1);//左后
    TJQ_Control(T2,0,0);//左前
	  TJQ_Control(T3,25,1);//右前
    TJQ_Control(T4,0,0);//右后
    TJQ_Control(T6,0,0);//左中
    TJQ_Control(T7,0,1);//右中
		twosudu();
			break;
		}
		case 'L' :
		{//右转400速度
			//执行语句
	   jsq=jsq-1;//用来控制灯熄灭的时间
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,35,1);//左后
    TJQ_Control(T2,0,0);//左前
	  TJQ_Control(T3,35 ,1);//右前
    TJQ_Control(T4,0,0);//右后
    TJQ_Control(T6,0,0);//左中
    TJQ_Control(T7,0,1);//右中
		onesudu();
			break;
		}
			case 'q' :
		{//检测到方块-蓝灯点亮
			//执行语句
			if(jsq<=0)
			{
		  Visual_Alarm_Light(0,0,255);
			jsq=100;//用来设置灯点亮的时间
			Servo_Set(1,90); 
			Servo_Set(3,90); 
			}
			else
			{
			 jsq=jsq-1;//用来控制灯熄灭的时间
			}
			break;
		}
		case 'y' :
		{//检测到圆形-红灯点亮
			//执行语句
			if(jsq<=0)
			{
			Visual_Alarm_Light(0,255,0);
			jsq=100;//用来设置灯点亮的时间
			Servo_Set(1,90); 
			Servo_Set(3,90); 
			}
			else
			{
			 jsq=jsq-1;//用来控制灯熄灭的时间
			}
			break;
		}
			case 'm' :
		{//检测到方块-绿灯2
			//执行语句
			if(jsq<=0)
			{
		  Visual_Alarm_Light(255,0,0);
			jsq=100;//用来设置灯点亮的时间
			Servo_Set(1,90); 
			Servo_Set(3,90); 
			}
			else
			{
			 jsq=jsq-1;//用来控制灯熄灭的时间
			}
			break;
		}
		case 'w' :
		{//检测到w
			//执行语句
			onemax=onemax-1;
			break;
		}
		case 'e' :
		{//检测到e
			//执行语句
			twomax=twomax-1;
			break;
		}
	  case 'r' :
		{//检测到r
			//执行语句
			threemax=threemax-1;
			break;
		}
		case 't' :
		{//检测到t
			//执行语句
			fourmax=fourmax-1;
			break;
		}
		case 'p' :
		{//检测到p
			//执行语句
			onemax=90;//1级偏移幅度调整姿态最大速度
      twomax=80;//2级偏移幅度调整姿态最大速度
      threemax=70;//3级偏移幅度调整姿态最大速度
      fourmax=50;//4级偏移幅度调整姿态最大速度
      mindmax=100;////前进最大速度;//速度复位
			break;
		}
		
		default:
		{
			//执行语句
			
			break;
		}
	}
}
