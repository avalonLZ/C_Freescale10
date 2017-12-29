



#ifndef  calculation_H
#define  calculation_H  



#define SI_SetVal1()   PTE12_OUT = 1
#define SI_ClrVal1()   PTE12_OUT = 0
#define CLK_ClrVal1()  PTE10_OUT = 0
#define CLK_SetVal1()  PTE10_OUT = 1

#define SI_SetVal2()   PTE3_OUT = 1
#define SI_ClrVal2()   PTE3_OUT = 0
#define CLK_ClrVal2()  PTE2_OUT = 0
#define CLK_SetVal2()  PTE2_OUT = 1



void StartIntegration1(void) ;  
void StartIntegration2(void) ;  
void ImageCapture1(unsigned char * ImageData) ;
void ImageCapture2(unsigned char * ImageData) ;
void SamplingDelay(void) ;
void CCD1_init(void) ;
void CCD2_init(void) ;
void Analyze_CCD_Data(void);


extern  int Max_Data1, Min_Data1;
extern  int L_Max_Data1,R_Max_Data1,L_Max_Data3,R_Max_Data3,L_Max_Data2,R_Max_Data2,L_Max_Data4,R_Max_Data4;
extern  u8 L_Max_Data_Place1, R_Max_Data_Place1,L_Max_Data_Place3, R_Max_Data_Place3,L_Max_Data_Place2, R_Max_Data_Place2,L_Max_Data_Place4, R_Max_Data_Place4;//����λ��
extern  int Dvalue_AD_Data_CCD1[128];
extern  int Dvalue_AD_Data_CCD2[128];
extern  volatile int Find_Mid_Place;//��ʼѲ�ߵ�λ��
extern  volatile int Find_Mid_Place1;//��ʼѲ�ߵ�λ��
extern  int ccd1_mid;
extern  u8 zhuan,zhuan1,leftzhijiao,rightzhijiao;//Ҫ��������
extern  int t,t1;
extern  u8 t2,t3,t4;
extern  int CCD1_Data_Average;//ccd1ƽ��ֵ
extern  int tt,ttt,tt1,ttt1;
extern  u8 t5,t6,t7,t8;
extern  u8 shizi;
extern  u8 Rzhangai,zhangai_t,Lzhangai;


extern u8 yz,yz1,yz2;///����������ֵ
extern u8 buxianL,buxianR;//���Ҳ���ֵ
extern  int dandao;//��������ֵ
extern u8 zhijiao;//ֱ����ʱ����
extern u8  quanheiMAX;//ȫ�����ֵ
extern u8  quanbaiMIN;//ȫ����Сֵ
extern float dandaoBDD;
extern float dandaoHDD;
extern float zhijiaoBDpwmmax;
extern float zhijiaoBS_Kp;
extern float zhijiaoBD_Kp;
extern float zhijiaoHDpwmmax;
extern float zhijiaoHS_Kp;
extern float zhijiaoHD_Kp;
#endif