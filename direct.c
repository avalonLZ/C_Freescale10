#include"common.h"
#include "include.h"
#define DIRECTION_CONTROL_PERIOD 10

int fDValue=0;
int D_Last_fDValue=0;
float direction_pwm=0;
float direction=0;
float out_kp=0,out_kd=0;
float g_fDirectionControlOutNew=0,g_fDirectionControlOutOld=0;
u8 g_nDirectionControlPeriod=0;
float gyro;
float out_kdd=0;
void directcontrol(int ccdcenter)
{
  
  
  gyro=ad_once (ADC0,AD17,ADC_12bit);
  D_Last_fDValue = fDValue;
  g_fDirectionControlOutOld=g_fDirectionControlOutNew;
  if(Rzhangai==0&& Lzhangai==0)
  fDValue=ccdcenter-64;
  else
  {
    if(Rzhangai==1)
    fDValue=ccdcenter-74;
    else
    fDValue=ccdcenter-54;
    
  }
  out_kp = D_Kp * fDValue/10.0;      
  out_kd = D_Kd * (fDValue - D_Last_fDValue)/10.0;
   out_kdd = D_Kdd * ( gyro_DIR- gyro)/10.0;
  
     if(out_kd>=zhangaiDmax)
    out_kd=zhangaiDmax;
    if(out_kd<=-zhangaiDmax)
    out_kd=-zhangaiDmax;

  
  direction_pwm=out_kp + out_kdd+out_kd;
  
  if(direction_pwm>=direction_pwmmax)/////////////////////////¿ØÖÆÊ®×ÖÄÚÇÐ
    direction_pwm=direction_pwmmax;
  if(direction_pwm<=-direction_pwmmax)
   direction_pwm=-direction_pwmmax;

   g_fDirectionControlOutNew=direction_pwm;
}

void directcontrolout()
{
   float fValue;
   fValue=g_fDirectionControlOutNew - g_fDirectionControlOutOld;
   direction=fValue * (g_nDirectionControlPeriod + 1) /DIRECTION_CONTROL_PERIOD + g_fDirectionControlOutOld;
}