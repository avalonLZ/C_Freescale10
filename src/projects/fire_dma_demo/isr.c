#include "common.h"
#include "isr.h"
#include "include.h"
u8 zlf=0;
u8 sf=0;
u8 df=0;
u8 fs=0;
u8 js=0;
u8 fanzhuan=0;
u8 b=0;
u8 d=0;
void DMA_CH4_Handler(void)
{

  
}
void PIT0_IRQHandler(void)
{
  DisableInterrupts;
  PIT_Flag_Clear(PIT0);
  zlf++; 
  sf++; 
  df++;
  if(b==1)
  {
    if(fanzhuan==0)
    {
       sdsd=700;//1350
       fanzhuan=1;
    }
  }
  if(d==1||g_fCarAngle>=35)
    while(1)
    {
    FTM_PWM_Duty(FTM0, CH0, 0);
    FTM_PWM_Duty(FTM0, CH1, 0);    
    FTM_PWM_Duty(FTM0, CH2, 0);  
    FTM_PWM_Duty(FTM0, CH3, 0);
    } 
  /////////////////////////////////////////////////////分段    
  g_nSpeedControlPeriod++;
  speedcontrolout();
  g_nDirectionControlPeriod++;
   directcontrolout();
  //////////////////////////////////////////////
  
  if(zlf>=5)
  {
    zlf=0;
    AD_Calculate();
   Speed_Calculate(g_fCarAngle,Gyro_Now);//清华
//   Speed_Calculate(angle,angle_dot);//卡尔曼
   ssc();///////////////////////////////////////////////////PWM驱动
  }
  if(df>=10)
  {
    df=0;
    g_nDirectionControlPeriod=0;
    directcontrol(Find_Mid_Place);///////////////////////////////////传入中线值
  }
   if(sf>=100)
   {
     sf=0;
     g_nSpeedControlPeriod=0;
     speedcontrol();
   }
  
 if(js==0)
      {       
       StartIntegration1();
       StartIntegration2();
       js=1;
      }
 else
   fs++; 
  EnableInterrupts;
}
void PORTA_IRQHandler(void)
{
  
}
void PORTB_IRQHandler(void)
{
  
}
