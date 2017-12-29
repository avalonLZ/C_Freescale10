#ifndef __ZLCONTROL_H__
#define __ZLCONTROL_H__


#define DT 0.005//变大会加大过冲0.005,0.008,0.004
#define GRAVITY_ADJUST_TIME_CONSTANT 2//近似于平移波形的效果,跟踪补偿时间2
#define MMA7361_ratio 0.116//0.116
#define Gyro_ratio  0.137//0.135    卡尔曼：0.026
//0.13

void Kalman_Filter(float angle_m,float gyro_m);
void AD_Calculate(void);
void Speed_Calculate(float angle,float Rate);
void QingHua_AngleCalaulate(float G_angle,float Gyro);
void Rd_Ad_Value();
extern float rectifyT;
extern int zkp;
extern int zkd;
extern float angle, angle_dot;
extern float Gyro_Now,angle_offset_vertical,Gyro_DIR,Gyro_DIRR;
extern float g_fGyroscopeAngleIntegral, angle_now,g_fCarAngle ;
extern volatile float  MMA7361 ,ENC03,ENC03_DIR,gyro_offset,gyro_DIR;
extern const float Q_angle, Q_gyro, R_angle, dt;

#endif 