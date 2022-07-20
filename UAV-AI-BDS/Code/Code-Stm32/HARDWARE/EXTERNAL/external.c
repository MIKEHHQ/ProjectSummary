#include "external.h" 
#include "api.h"
#include "propeller.h"
#include "servo.h" 
//USBͨѶ���Ʊ�̽���
int jsq=0;//����������
int yuan=0;//����������
int fang=0;//����������
int cha=0;//��ֵ����
//��ʼ�˶��ٶ�
float one=80;//1��ƫ�Ʒ��ȵ�����̬��ʼ�ٶ�
float two=60;//2��ƫ�Ʒ��ȵ�����̬��ʼ�ٶ�
float three=40;//3��ƫ�Ʒ��ȵ����˳�ʼ�ٶ�
float four=20;//4��ƫ�Ʒ��ȵ�����̬��ʼ�ٶ�
float mind=60;//ǰ����ʼ�ٶ�

//��λ����ٶ�
float onemax=80;//1��ƫ�Ʒ��ȵ�����̬����ٶ�
float twomax=60;//2��ƫ�Ʒ��ȵ�����̬����ٶ�
float threemax=40;//3��ƫ�Ʒ��ȵ�����̬����ٶ�
float fourmax=20;//4��ƫ�Ʒ��ȵ�����̬����ٶ�
float mindmax=60;////ǰ������ٶ�

//�ٽ���λ�ٶ�
float onelimit=80;//1��ƫ�Ʒ��ȵ�����̬�ٽ��ٶ�
float twolimit=60;//2��ƫ�Ʒ��ȵ�����̬�ٽ��ٶ�
float threelimit=40;//3��ƫ�Ʒ��ȵ�����̬�ٽ��ٶ�
float fourlimit=20;//4��ƫ�Ʒ��ȵ�����̬�ٽ��ٶ�
float mindlimit=60;//ǰ���ٽ��ٶ�

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
		{//��ת400ת��
     jsq=jsq-1;//�������Ƶ�Ϩ���ʱ��
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,0,1);//��ǰ
    TJQ_Control(T2,35,0);//�Һ�
	  TJQ_Control(T3,0,1);//���
    TJQ_Control(T4,35,0);//��ǰ
    TJQ_Control(T6,0,0);//����
    TJQ_Control(T7,0,1);//����	
	  onesudu();
			break;
		}
		case 'S' :
		{//��ת230
      //ִ�����
     jsq=jsq-1;//�������Ƶ�Ϩ���ʱ��
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,0,1);//���
    TJQ_Control(T2,25,0);//��ǰ
	  TJQ_Control(T3,0,1);//��ǰ
    TJQ_Control(T4,25,0);//�Һ�
    TJQ_Control(T6,0,0);//����
    TJQ_Control(T7,0,1);//����
    twosudu();
			break;
		}
		case 'D' :
		{//��ת100
			//ִ�����
    jsq=jsq-1;//�������Ƶ�Ϩ���ʱ��
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,0,1);//���
    TJQ_Control(T2,15,0);//��ǰ
	  TJQ_Control(T3,0,1);//��ǰ
    TJQ_Control(T4,15,0);//�Һ�
    TJQ_Control(T6,0,0);//����
    TJQ_Control(T7,0,1);//����
		threesudu();
			break;
		}
		case 'F' :
		{//��ת50
			//ִ�����
		jsq=jsq-1;//�������Ƶ�Ϩ���ʱ��
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
	  TJQ_Control(T1,0,1);//���
    TJQ_Control(T2,10,0);//��ǰ
	  TJQ_Control(T3,0,1);//��ǰ
    TJQ_Control(T4,10,0);//�Һ�
    TJQ_Control(T6,0,0);//����
    TJQ_Control(T7,0,1);//����
		foursudu();
			break;
		}
		case 'G' :
		{
			//ִ�����
    jsq=jsq-1;//�������Ƶ�Ϩ���ʱ��
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,0,1);//���
    TJQ_Control(T2,50,0);//��ǰ
	  TJQ_Control(T3,50,1);//��ǰ
    TJQ_Control(T4,0,0);//�Һ�
    TJQ_Control(T6,0,0);//����
    TJQ_Control(T7,0,1);//����
		mindsudu();
			break;
		}
		case 'H' :
		{//��ת50�ٶ�
			//ִ�����
		jsq=jsq-1;//�������Ƶ�Ϩ���ʱ��
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,10,1);//���
    TJQ_Control(T2,0,0);//��ǰ
	  TJQ_Control(T3,10,1);//��ǰ
    TJQ_Control(T4,0,0);//�Һ�
    TJQ_Control(T6,0,0);//����
    TJQ_Control(T7,0,1);//����
		foursudu();
			break;
		}
		case 'J' :
		{//��ת100�ٶ�
			//ִ�����
		jsq=jsq-1;//�������Ƶ�Ϩ���ʱ��
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,15,1);//���
    TJQ_Control(T2,0,0);//��ǰ
	  TJQ_Control(T3,15,1);//��ǰ
    TJQ_Control(T4,0,0);//�Һ�
    TJQ_Control(T6,0,0);//����
    TJQ_Control(T7,0,1);//����
		threesudu();
			break;
		}
		case 'K' :
		{//��ת200�ٶ�
			//ִ�����
    jsq=jsq-1;//�������Ƶ�Ϩ���ʱ��
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,25,1);//���
    TJQ_Control(T2,0,0);//��ǰ
	  TJQ_Control(T3,25,1);//��ǰ
    TJQ_Control(T4,0,0);//�Һ�
    TJQ_Control(T6,0,0);//����
    TJQ_Control(T7,0,1);//����
		twosudu();
			break;
		}
		case 'L' :
		{//��ת400�ٶ�
			//ִ�����
	   jsq=jsq-1;//�������Ƶ�Ϩ���ʱ��
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,35,1);//���
    TJQ_Control(T2,0,0);//��ǰ
	  TJQ_Control(T3,35 ,1);//��ǰ
    TJQ_Control(T4,0,0);//�Һ�
    TJQ_Control(T6,0,0);//����
    TJQ_Control(T7,0,1);//����
		onesudu();
			break;
		}
			case 'q' :
		{//��⵽����-���Ƶ���
			//ִ�����
			if(jsq<=0)
			{
		  Visual_Alarm_Light(0,0,255);
			jsq=100;//�������õƵ�����ʱ��
			Servo_Set(1,90); 
			Servo_Set(3,90); 
			}
			else
			{
			 jsq=jsq-1;//�������Ƶ�Ϩ���ʱ��
			}
			break;
		}
		case 'y' :
		{//��⵽Բ��-��Ƶ���
			//ִ�����
			if(jsq<=0)
			{
			Visual_Alarm_Light(0,255,0);
			jsq=100;//�������õƵ�����ʱ��
			Servo_Set(1,90); 
			Servo_Set(3,90); 
			}
			else
			{
			 jsq=jsq-1;//�������Ƶ�Ϩ���ʱ��
			}
			break;
		}
			case 'm' :
		{//��⵽����-�̵�2
			//ִ�����
			if(jsq<=0)
			{
		  Visual_Alarm_Light(255,0,0);
			jsq=100;//�������õƵ�����ʱ��
			Servo_Set(1,90); 
			Servo_Set(3,90); 
			}
			else
			{
			 jsq=jsq-1;//�������Ƶ�Ϩ���ʱ��
			}
			break;
		}
		case 'w' :
		{//��⵽w
			//ִ�����
			onemax=onemax-1;
			break;
		}
		case 'e' :
		{//��⵽e
			//ִ�����
			twomax=twomax-1;
			break;
		}
	  case 'r' :
		{//��⵽r
			//ִ�����
			threemax=threemax-1;
			break;
		}
		case 't' :
		{//��⵽t
			//ִ�����
			fourmax=fourmax-1;
			break;
		}
		case 'p' :
		{//��⵽p
			//ִ�����
			onemax=90;//1��ƫ�Ʒ��ȵ�����̬����ٶ�
      twomax=80;//2��ƫ�Ʒ��ȵ�����̬����ٶ�
      threemax=70;//3��ƫ�Ʒ��ȵ�����̬����ٶ�
      fourmax=50;//4��ƫ�Ʒ��ȵ�����̬����ٶ�
      mindmax=100;////ǰ������ٶ�;//�ٶȸ�λ
			break;
		}
		
		default:
		{
			//ִ�����
			
			break;
		}
	}
}
