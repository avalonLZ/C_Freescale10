#include"common.h"
#include "include.h"

                           
extern u32 MMA7361level;//前小，大后
float angle, angle_dot;         //外部需要引用(输出)的变量 第一个是实际的角度，第二个是最终陀螺仪的角速度  


float Gyro_Now,angle_offset_vertical,Gyro_DIR,Gyro_DIRR;//归一化后角速度和角度
float g_fGyroscopeAngleIntegral, angle_now,g_fCarAngle ;//=-40
volatile float  MMA7361 ,ENC03,ENC03_DIR,gyro_offset,gyro_DIR;//ad读入角度，ad读入角速度， 
//-------------------------------------------------------
// 0.00015     //0.0001
const float Q_angle=0.0002, Q_gyro=0.000001, R_angle=0.5, dt=0.005;//主要参数调节const float Q_angle=0.001, Q_gyro=0.003越小越硬, R_angle=0.5, dt=0.005;

//0.0001         //0.00015        //1.2
//注意：dt的取值为kalman滤波器采样时间;         //0.8
static float P[2][2] = {
    { 1, 0 },
    { 0, 1 }
};

static float Pdot[4] ={0,0,0,0};

static const char C_0 = 1;

static float q_bias, angle_err, PCt_0, PCt_1, E, K_0, K_1, t_0, t_1;
//**************************************************************************
//   Kalman滤波
//**************************************************************************

//-------------------------------------------------------
void Kalman_Filter(float angle_m,float gyro_m)          //gyro_m:gyro_measure第一个参数是加速度计的角度 第二个是陀螺仪的角速度

{
    angle+=(gyro_m-q_bias) * dt;
    
    Pdot[0]=Q_angle - P[0][1] - P[1][0];
    Pdot[1]=- P[1][1];
    Pdot[2]=- P[1][1];
    Pdot[3]=Q_gyro;
    
    P[0][0] += Pdot[0] * dt;
    P[0][1] += Pdot[1] * dt;
    P[1][0] += Pdot[2] * dt;
    P[1][1] += Pdot[3] * dt;
    
    
    angle_err = angle_m - angle;
    
    

    PCt_0 = C_0 * P[0][0];
    PCt_1 = C_0 * P[1][0];
    
    E = R_angle + C_0 * PCt_0;
    
    K_0 = PCt_0 / E;
    K_1 = PCt_1 / E;
    
    t_0 = PCt_0;
    t_1 = C_0 * P[0][1];

    P[0][0] -= K_0 * t_0;
    P[0][1] -= K_0 * t_1;
    P[1][0] -= K_1 * t_0;
    P[1][1] -= K_1 * t_1;
    
    
    angle   += K_0 * angle_err;
    q_bias  += K_1 * angle_err;
    angle_dot = gyro_m-q_bias;
}
////////////////////清华滤波方案
 void QingHua_AngleCalaulate(float G_angle,float Gyro)
{
  float fDeltaValue;
  g_fCarAngle = g_fGyroscopeAngleIntegral;
  fDeltaValue = (G_angle - g_fCarAngle) /GRAVITY_ADJUST_TIME_CONSTANT;//GRAVITY_ADJUST_TIME_CONSTANT重力补偿系数  
  g_fGyroscopeAngleIntegral += (Gyro + fDeltaValue) * DT;//DT积分时间系数，融合角度g_fGyroscopeAngleIntegral    
}

 void Rd_Ad_Value()
 {
  ENC03=ad_once (ADC0,AD12,ADC_12bit);
  MMA7361=ad_once (ADC0,AD13,ADC_12bit);
 }


 void AD_Calculate(void)
 {
   Rd_Ad_Value();
   
   ///////////////////////ENC03,加速度计归一化
   
   Gyro_Now =(rectifyT-ENC03)*Gyro_ratio;
   angle_offset_vertical=(MMA7361level-MMA7361)*MMA7361_ratio;
   if(angle_offset_vertical > 90)angle_offset_vertical = 90;
   if(angle_offset_vertical < -90)angle_offset_vertical =-90;
   QingHua_AngleCalaulate(angle_offset_vertical,Gyro_Now);
   //Kalman_Filter(angle_offset_vertical,Gyro_Now);
 }
 