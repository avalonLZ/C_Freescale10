#include"common.h"
#include "include.h"

volatile float  Speed_L , Speed_R , speed_Start , Speed_L_Last , Speed_R_Last ;  //左轮速度,右轮速度 , 总驱动电压 
s16 lwc,rwc;
float zwc=0;//,szwc
float sdkz=0;
float sdsd=0;
float g_fSpeedControlIntegral=0, g_fSpeedControlIntegralp=0,g_fSpeedControlOutOld=0,g_fSpeedControlOutNew=0,Velocity=0,Velocity_1=0;
u8 g_nSpeedControlPeriod=0;
extern u8 fanzhuan;
extern float rectifyT;
extern u8 tx;
float S_Kp =0;//  1.3
float S_Ki =0;//11.8
float S_Error = 0;
float S_DError = 0;
//int S_DDError = 0;
float S_Pre_Error = 0;
void ssc()
{  
  
   Speed_L =speed_Start-sdkz+direction;//左轮总速度+
   Speed_R =speed_Start-sdkz-direction;//右轮总速度-
   
   Speed_L*=10;
   Speed_R*=10;
   
 if(Speed_L > 9000) Speed_L = 9000;//9900
 if(Speed_L < -9000) Speed_L = -9000;
 if(Speed_R > 9000) Speed_R = 9000;
 if(Speed_R < -9000) Speed_R = -9000;


	 /*********************************/
    if(Speed_L > 0)    
        Speed_L_Last =Speed_L;
    else
        Speed_L_Last =- Speed_L;

    if(Speed_R > 0)     
        Speed_R_Last =Speed_R;
    else
        Speed_R_Last = - Speed_R;
 
      if(tx==1)
      {
        Speed_R_Last=0;
         Speed_L_Last =0;
      }
 /***********PWM控制******************/

 if(Speed_R >= 0) 
{
FTM_PWM_Duty(FTM0, CH0,(u32)(Speed_R_Last+MOTOR_DEAD_VAL_R));
FTM_PWM_Duty(FTM0, CH2,0); //                 
}
else
{
FTM_PWM_Duty(FTM0, CH2,(u32)(Speed_R_Last+MOTOR_DEAD_VAL_R));
FTM_PWM_Duty(FTM0, CH0,0);//
 }

 if(Speed_L >= 0) 
 
{
FTM_PWM_Duty(FTM0, CH1,(u32)(Speed_L_Last+MOTOR_DEAD_VAL_L));//
FTM_PWM_Duty(FTM0, CH3,0); //
 }
 else
 {
FTM_PWM_Duty(FTM0, CH3,(u32)(Speed_L_Last+MOTOR_DEAD_VAL_L));//
FTM_PWM_Duty(FTM0, CH1,0); //
 }
}

void speedcontrol()
{
  static u8 sudu1=0;
  float out_kp=0,out_ki=0;
  //,out_kd
  lwc=-FTM2_CNT;
  rwc=-FTM1_CNT;
  zwc=(lwc+rwc)/2;
  FTM1_CNT=FTM2_CNT=0; 
 
  Velocity=0.6*zwc+0.4*Velocity_1;
       Velocity_1=Velocity;
  
  S_Error = sdsd - Velocity;//e(k)
  S_DError = S_Error - S_Pre_Error;//e(k)-e(k-1)
  S_Pre_Error = S_Error;//存储当前偏差

  
  
   if(fanzhuan==0)
   {
     sdsd=0;
   S_Kp=S_Kpstart;
    S_Ki =S_Kistart;//35.11
   }
if(fanzhuan==1&&sudu1!=50)
{
  sudu1++;
if(sdsd<Sqiwang)
sdsd+=100;
}
  
  
if(fanzhuan==1&&sudu1==Sjishu)//f&&S_Error<300&&S_Error>0anzhuan==1
{
 sudu1=50;
   S_Kp=S_Kpend;
    S_Ki =S_Kiend;
  
}
 
  out_kp = S_Kp * S_DError/10.0;   //比例项
  out_ki = S_Ki * S_Error/10.0;    //积分项
  
  g_fSpeedControlIntegral=out_ki;//查看积分项
  g_fSpeedControlIntegralp=out_kp;
  
   g_fSpeedControlOutOld =g_fSpeedControlOutNew;
  g_fSpeedControlOutNew = out_kp + out_ki;
  
}

void speedcontrolout()
{
  float fValue;
  fValue = g_fSpeedControlOutNew - g_fSpeedControlOutOld;
  sdkz = fValue * (g_nSpeedControlPeriod + 1) /SPEED_CONTROL_PERIOD +g_fSpeedControlOutOld;
}


 void Speed_Calculate(float angle,float angle_dot)
 {
   speed_Start = (angle * zkp + angle_dot * zkd)/10;
 }

///////////