#ifndef __SPEED_H__
#define __SPEED_H__


////////////////////PWM输出为负值,给负值变快
#define MOTOR_DEAD_VAL_R 0//
#define MOTOR_DEAD_VAL_L -88//120
#define SPEED_CONTROL_PERIOD 100
void Speed_Calculate(float angle,float angle_dot);
void speedcontrol();
void ssc();
void speedcontrolout();

extern volatile float  Speed_L , Speed_R , speed_Start , Speed_L_Last , Speed_R_Last ;
extern float g_fSpeedControlIntegral,g_fSpeedControlIntegralp,g_fSpeedControlOutOld,g_fSpeedControlOutNew,Velocity;
extern s16 lwc,rwc;
extern float zwc;//,szwc
extern float sdsd;
extern float sdkz;
extern float fDelta;
extern float S_Kp ;  
extern float S_Ki ;
//extern float S_Kd ;
extern float S_Error ;
extern float S_DError ;
//extern int S_DDError ;
extern float S_Pre_Error;
extern u8 g_nSpeedControlPeriod;



extern float S_Kpstart;//  1.3
extern float S_Kistart;//11.8
extern float S_Kpend;//  1.3
extern float S_Kiend;//11.8
extern u16 Sqiwang;//  1.3
extern u8 Sjishu;//11.8
#endif 