


#ifndef  direct_H
#define  direct_H  
#define DIRECTION_CONTROL_PERIOD 10

void directcontrol(int ccdcenter);
void directcontrolout();



extern float D_Kp;
extern float D_Kd;
extern float D_Kdd;
extern int fDValue;
extern int D_Last_fDValue;
extern float direction_pwm;
extern float direction;
extern float out_kp,out_kd;
extern float g_fDirectionControlOutNew,g_fDirectionControlOutOld;
extern u8 g_nDirectionControlPeriod;
extern float gyro;
extern float zhangaiDmax;
extern float direction_pwmmax;
extern float out_kdd;
#endif