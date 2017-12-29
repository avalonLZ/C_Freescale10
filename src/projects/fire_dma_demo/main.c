#include "common.h"
#include "include.h"
#include "isr.h"
#include "ftm.h"
#include <math.h>
#include "uart.h"
#include "adc.h"
//#include "calculation.h"
void OutPut_Data(void);
void push(uint8 chanel,uint16 data);//freecarsʾ����ͨ����������
void sendDataToScope(void);//freecarsʾ����
void sendDataToCCDViewer(u8 CCDSelection,u8* CCDData);//sendDataToCCDViewer(0,Pixel1)freescarsccd��λ��
extern float sb[2]; 
extern float OutData[4];

u8 Pixel1[128];
u8 Pixel2[128];

u32 MMA7361level;
float rectifyT;
u8 tx=0;
extern u8 b;
extern u8 d;
extern u8 fanzhuan;
extern  u8 ccd;
extern  u8 fs;
extern u8 js;



u8 yz=0,yz1=0,yz2=0;///����������ֵ
u8 buxianL=0,buxianR=0;//���Ҳ���ֵ
int dandao=0;//��������ֵ
u8 zhijiao=0;//ֱ����ʱ����
u8  quanheiMAX=0;//ȫ�����ֵ
u8  quanbaiMIN=0;//ȫ����Сֵ
float dandaoBDD=0;
float dandaoHDD=0;
float zhijiaoBDpwmmax=0;
float zhijiaoBS_Kp=0;
float zhijiaoBD_Kp=0;
float zhijiaoHDpwmmax=0;
float zhijiaoHS_Kp=0;
float zhijiaoHD_Kp=0;

int zkp=0;//�廪PD��2053   ������PD��2200
int zkd=0;//44/////////////50 

float S_Kpstart=0;//  1.3
float S_Kistart=0;//11.8
float S_Kpend=0;//  1.3
float S_Kiend=0;//11.8
u16 Sqiwang =0;//  1.3
u8 Sjishu =0;//11.8



float D_Kp =0;   //504.25
float D_Kd =0;//
float D_Kdd=0;//12.05
float zhangaiDmax=0;
float direction_pwmmax=0;



 void main()
{  
 DisableInterrupts;
      
   volatile u8 i;
   u32 bianliang;  
 
  flash_init();
  gpio_init (PORTA, 24, GPI_UP_PF,1);///////����
  gpio_init (PORTA, 25, GPI_UP_PF,1);
  gpio_init (PORTA, 6, GPI_UP_PF,1);
  gpio_init (PORTA, 10, GPI_UP_PF,1);///////����
  gpio_init (PORTA, 12, GPI_UP_PF,1);
  gpio_init (PORTA, 8, GPI_UP_PF,1);
  
  if(gpio_get(PORTA,24)==1&&gpio_get(PORTA,25)==1&&gpio_get(PORTA,6)==0)
   {    
     
      LCD_Init();
   //flash_erase_sector(255);
 //  flash_write(255,0x004,0x03e8);/////////////////////////////��Ҫ������ֵʱ
     while(1&&tx==0)
     {
       if(gpio_get(PORTA,10)==0)
       {
         delayms(100);
         if(gpio_get(PORTA,10)==0)/////////ȷ�����¼Ӽ���
         { 
           bianliang=flash_read(255,0x004,u32);
           delayms(50);
           bianliang+=5;
           flash_erase_sector(255);
           delayms(50);
           flash_write(255,0x004, (u32)bianliang);
           delayms(50);
           LCD_CLS();
           LCD_PrintValueI(8, 4, bianliang);
         } 
       }

     if(gpio_get(PORTA,12)==0)
     {
        delayms(100);
         if(gpio_get(PORTA,12)==0)
         {
        
             bianliang=flash_read(255,0x004,u32);
             delayms(50);
             bianliang-=5;
             flash_erase_sector(255);
             delayms(50);
             flash_write(255,0x004,(u32)bianliang); 
             delayms(50);
             LCD_CLS();//����
             LCD_PrintValueI(8, 4,bianliang);
         }
      }
      
     if(gpio_get(PORTA,8)==0)
     {
        delayms(100);
        if(gpio_get(PORTA,8)==0)
        {          
            tx=1;   
        }
        else
          tx=0;
     }

  
     }
   }
  /////////////////////////////////////////////////////////////////////////////////////////�������õ�
  if(gpio_get(PORTA,24)==0&&gpio_get(PORTA,25)==1&&gpio_get(PORTA,6)==0)//////////////��ת��ֵ
  {
    LCD_Init();
    while(1)
   {
    if(gpio_get(PORTA,10)==0)
       {
         delayms(100);
         if(gpio_get(PORTA,10)==0)/////////������ת
         {
           delayms(50);
           flash_erase_sector(254);
           delayms(50);
           flash_write(254,0x004, (u32)6);
           delayms(50);
           LCD_Char( 10,3,'R');
           LCD_Char(26 ,3,'+') ;
           LCD_Char(32 ,3,'6') ;
         }
       }
    if(gpio_get(PORTA,12)==0)
       {
         delayms(100);
         if(gpio_get(PORTA,12)==0)/////////������ת
         {
           delayms(50);
           flash_erase_sector(254);
           delayms(50);
           flash_write(254,0x004, (u32)(-6));
           delayms(50);
           LCD_CLS();
           LCD_Char( 10,3,'L');
           LCD_Char(26 ,3,'-') ;
           LCD_Char(32 ,3,'6') ;
         }
       }  
    if(gpio_get(PORTA,8)==0)
       {
         delayms(100);
         if(gpio_get(PORTA,8)==0)/////////����ֱ��
         {
           delayms(50);
           flash_erase_sector(254);
           delayms(50);
           flash_write(254,0x004, (u32)0);
           delayms(50);
           LCD_CLS();
           LCD_Char(32 ,3,'0');
         }
       }  
   }
  }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////�ٶȵ�λ  
  
  if(gpio_get(PORTA,24)==1&&gpio_get(PORTA,25)==1&&gpio_get(PORTA,6)==1)/////////////////////
   {    
       yz=10,yz1=6,yz2=3;///����������ֵ
      buxianL=25,buxianR=27;//���Ҳ���ֵ
      dandao=(int)flash_read(254,0x004,u32);
      zhijiao=8;//ֱ����ʱ����
      quanheiMAX=60;//ȫ�����ֵ
      quanbaiMIN=80;//ȫ����Сֵ
      dandaoBDD=9.455;////////////////////////////////////////////////////////////
      dandaoHDD=9.455;////////////////////////////////////////////////////////////
      zhijiaoBDpwmmax=500.0;
      zhijiaoBS_Kp=10.0;
      zhijiaoBD_Kp=378.25;
      zhijiaoHDpwmmax=300.0;
      zhijiaoHS_Kp=42.0;//50��΢��
      zhijiaoHD_Kp=305.25;//299.25

      zkp=2200;//�廪PD��2053   ������PD��2200
      zkd=47;//44/////////////50 
      
      S_Kpstart=10.0;//  1.3
      S_Kistart=33.91;//11.8
      S_Kpend=42.0;///////////////29.0
      S_Kiend=32.01;//11.8
      Sqiwang =1400;//  1.3
      Sjishu =7;//11.8
        
      D_Kp =305.25;   //299.25
      D_Kd =300.0;//
      D_Kdd=9.455;//12.05
      zhangaiDmax=300.0;
      direction_pwmmax=300.0;
   }
  
  if(gpio_get(PORTA,24)==0&&gpio_get(PORTA,25)==1&&gpio_get(PORTA,6)==1)/////////////////////
  {
        yz=10,yz1=6,yz2=3;///����������ֵ
      buxianL=25,buxianR=27;//���Ҳ���ֵ
      dandao=(int)flash_read(254,0x004,u32);
      zhijiao=10;//ֱ����ʱ����
      quanheiMAX=60;//ȫ�����ֵ
      quanbaiMIN=80;//ȫ����Сֵ
      dandaoBDD=9.455;////////////////////////////////////////////////////////////
      dandaoHDD=9.455;////////////////////////////////////////////////////////////
      zhijiaoBDpwmmax=500.0;
      zhijiaoBS_Kp=10.0;
      zhijiaoBD_Kp=378.25;
      zhijiaoHDpwmmax=300.0;
      zhijiaoHS_Kp=42.0;//50��΢��
      zhijiaoHD_Kp=305.25;//299.25

      zkp=2200;//�廪PD��2053   ������PD��2200
      zkd=47;//44/////////////50 
      
      S_Kpstart=10.0;//  1.3
      S_Kistart=33.91;//11.8
      S_Kpend=42.0;///////////////29.0
      S_Kiend=32.01;//11.8
      Sqiwang =1400;//  1.3
      Sjishu =7;//11.8
        
      D_Kp =305.25;   //299.25
      D_Kd =300.0;//
      D_Kdd=9.455;//12.05
      zhangaiDmax=300.0;
      direction_pwmmax=300.0;
  }
  
  
  
   if(gpio_get(PORTA,24)==1&&gpio_get(PORTA,25)==0&&gpio_get(PORTA,6)==1)/////////////////////
   {     
       yz=10,yz1=6,yz2=3;///����������ֵ
      buxianL=25,buxianR=27;//���Ҳ���ֵ
      dandao=(int)flash_read(254,0x004,u32);
      zhijiao=12;//ֱ����ʱ����
      quanheiMAX=60;//ȫ�����ֵ
      quanbaiMIN=80;//ȫ����Сֵ
      dandaoBDD=9.455;////////////////////////////////////////////////////////////
      dandaoHDD=9.455;////////////////////////////////////////////////////////////
      zhijiaoBDpwmmax=500.0;
      zhijiaoBS_Kp=10.0;
      zhijiaoBD_Kp=378.25;
      zhijiaoHDpwmmax=300.0;
      zhijiaoHS_Kp=42.0;//50��΢��
      zhijiaoHD_Kp=305.25;//299.25

      zkp=2200;//�廪PD��2053   ������PD��2200
      zkd=47;//44/////////////50 
      
      S_Kpstart=10.0;//  1.3
      S_Kistart=33.91;//11.8
      S_Kpend=42.0;///////////////29.0
      S_Kiend=32.01;//11.8
      Sqiwang =1400;//  1.3
      Sjishu =7;//11.8
        
      D_Kp =305.25;   //299.25
      D_Kd =300.0;//
      D_Kdd=9.455;//12.05
      zhangaiDmax=300.0;
      direction_pwmmax=300.0;
   }
  
  if(gpio_get(PORTA,24)==0&&gpio_get(PORTA,25)==0&&gpio_get(PORTA,6)==1)//////////////////////�����     1400
  {
       yz=10,yz1=6,yz2=3;///����������ֵ
      buxianL=25,buxianR=27;//���Ҳ���ֵ
      dandao=(int)flash_read(254,0x004,u32);
      zhijiao=14;//ֱ����ʱ����
      quanheiMAX=60;//ȫ�����ֵ
      quanbaiMIN=80;//ȫ����Сֵ
      dandaoBDD=9.455;////////////////////////////////////////////////////////////
      dandaoHDD=9.455;////////////////////////////////////////////////////////////
      zhijiaoBDpwmmax=500.0;
      zhijiaoBS_Kp=10.0;
      zhijiaoBD_Kp=378.25;
      zhijiaoHDpwmmax=300.0;
      zhijiaoHS_Kp=42.0;//50��΢��
      zhijiaoHD_Kp=305.25;//299.25

      zkp=2200;//�廪PD��2053   ������PD��2200
      zkd=47;//44/////////////50 
      
      S_Kpstart=10.0;//  1.3
      S_Kistart=33.91;//11.8
      S_Kpend=42.0;///////////////29.0
      S_Kiend=32.01;//11.8
      Sqiwang =1400;//  1.3
      Sjishu =7;//11.8
        
      D_Kp =305.25;   //299.25
      D_Kd =300.0;//
      D_Kdd=9.455;//12.05
      zhangaiDmax=300.0;
      direction_pwmmax=300.0; 
  }
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////�����ٶȵ�
      if(gpio_get(PORTA,24)==0&&gpio_get(PORTA,25)==0&&gpio_get(PORTA,6)==0)
  {
      yz=10,yz1=6,yz2=3;///����������ֵ
      buxianL=25,buxianR=27;//���Ҳ���ֵ
      dandao=(int)flash_read(254,0x004,u32);
      zhijiao=14;//ֱ����ʱ����
      quanheiMAX=60;//ȫ�����ֵ
      quanbaiMIN=80;//ȫ����Сֵ
      dandaoBDD=9.455;////////////////////////////////////////////////////////////
      dandaoHDD=9.455;////////////////////////////////////////////////////////////
      
      zhijiaoBDpwmmax=500.0;
      zhijiaoBS_Kp=10.0;
      zhijiaoBD_Kp=378.25;
      zhijiaoHDpwmmax=300.0;
      zhijiaoHS_Kp=42.0;//50��΢��
      zhijiaoHD_Kp=305.25;//299.25

      zkp=2400;//�廪PD��2053   ������PD��2200
      zkd=47;//44/////////////50 
      
      S_Kpstart=10.0;//  1.3
      S_Kistart=31.91;//11.8
      S_Kpend=42.0;///////////////29.0
      S_Kiend=30.01;//11.8
      Sqiwang =1400;//  1.3
      Sjishu =7;//11.8
        
      D_Kp =305.25;   //299.25
      D_Kd =300.0;//
      D_Kdd=9.455;//12.05
      zhangaiDmax=300.0;
      direction_pwmmax=300.0;
  }
  
    if(gpio_get(PORTA,24)==1&&gpio_get(PORTA,25)==0&&gpio_get(PORTA,6)==0)//////////////////////////��ֵ̫��
  {
   
      yz=10,yz1=6,yz2=3;///����������ֵ
      buxianL=25,buxianR=27;//���Ҳ���ֵ
      dandao=(int)flash_read(254,0x004,u32);
      zhijiao=16;//ֱ����ʱ����
      quanheiMAX=60;//ȫ�����ֵ
      quanbaiMIN=80;//ȫ����Сֵ
      dandaoBDD=9.455;////////////////////////////////////////////////////////////
      dandaoHDD=9.455;////////////////////////////////////////////////////////////
      
      zhijiaoBDpwmmax=500.0;
      zhijiaoBS_Kp=10.0;
      zhijiaoBD_Kp=378.25;
      zhijiaoHDpwmmax=300.0;
      zhijiaoHS_Kp=42.0;//50��΢��
      zhijiaoHD_Kp=305.25;//299.25

      zkp=2400;//�廪PD��2053   ������PD��2200
      zkd=47;//44/////////////50 
      
      S_Kpstart=10.0;//  1.3
      S_Kistart=31.91;//11.8
      S_Kpend=42.0;///////////////29.0
      S_Kiend=30.01;//11.8
      Sqiwang =1400;//  1.3
      Sjishu =7;//11.8
        
      D_Kp =305.25;   //299.25
      D_Kd =300.0;//
      D_Kdd=9.455;//12.05
      zhangaiDmax=300.0;
      direction_pwmmax=300.0;
  }

   /**/
  
     //���ڳ�ʼ��
 asm("nop");
  asm("nop");
asm("nop");
  asm("nop");
asm("nop");
  asm("nop");


asm("nop");
  asm("nop");

  if(tx==1)
     uart_init(UART5,115200);
  else
  uart_init(UART5,9600); 
 asm("nop");
  asm("nop");

   //CCD��������ų�ʼ��
   CCD1_init() ;
   CCD2_init() ;
asm("nop");
  asm("nop");



   //PWM�����ʼ��
    FTM_PWM_init(FTM0, CH0, 10000, 0);  //R����        
    FTM_PWM_init(FTM0, CH1, 10000, 0);   //Rǰ��         
    FTM_PWM_init(FTM0, CH2, 10000, 0);   //L����        
    FTM_PWM_init(FTM0, CH3, 10000, 0); //Lǰ��
   //�����ʼ��
   // gpio_init (PORTA, 7, GPI_UP_PF,1);
    
asm("nop");
asm("nop");

    gpio_init (PORTE, 1, GPI,0);
    gpio_init (PORTD, 15, GPI,0); 
    gpio_init (PORTD, 14, GPI,0);
    gpio_init (PORTD, 12,GPI,0);
    
asm("nop");
asm("nop");
asm("nop");
  asm("nop");
    //���������ʼ��
    FTM1_QUAD_Iint();
    FTM2_QUAD_Iint();
asm("nop");
asm("nop");    
asm("nop");
asm("nop");
    //�����жϳ�ʼ��
 pit_init_ms(PIT0, 1);
   asm("nop");
asm("nop");
asm("nop");
asm("nop");

    // �����Ǽ����ٶȼƳ�ʼ��
    adc_init(ADC0, AD12);      //////  PTB2    ENC      
    adc_init(ADC0, AD12);      ///PTB3      Z
    adc_init(ADC0, AD17);       ///PTE24     DIR_ENC

    /////////////////////////////////////////////////�����ǿ����Լ�
  
        delayms(1000);
        gpio_init (PORTA, 17, GPO, 0);
         MMA7361level=flash_read(255,0x004,u32);
        rectifyT = ad_ave(ADC0,SE12,ADC_12bit,10);
    gyro_DIR=ad_ave(ADC0,SE17,ADC_12bit,10);
   // gyro_DIR=gyro_DIR/20;
      /////////////////////////////////////////////////        
//  gpio_init (PORTC, 0, GPI,0);��֪��Ҫ�÷�
        delayms(1500); 
        EnableInterrupts;
        
    while(1)
     
    {  
       if((gpio_get(PORTD,12)==0)&&(gpio_get(PORTD,14)==0))//||(gpio_get(PORTE,1)==1)
         {b=1;d=0;}
    if(fs>=1)
     {
          DisableInterrupts;
         fs=0;js=0;
        ImageCapture1(Pixel1);
        ImageCapture2(Pixel2);
       EnableInterrupts;
       Analyze_CCD_Data();      
    }
     
    if(tx==1)
    {
   sendDataToCCDViewer(0,Pixel1);//////////////////////////////////////
        sendDataToCCDViewer(1,Pixel2); 
        sendDataToScope();
    }
  
    else
    {
OutData[0]=Min_Data1;//L_Max_Data_Place3
OutData[1]=Max_Data1;//R_Max_Data_Place1
OutData[2]=L_Max_Data_Place1; //L_Max_Data_Place1
OutData[3]=R_Max_Data_Place1;//
OutPut_Data();
    }//
//sb[0]=FTM1_CNT; 
//sb[1]=MMA7361; 
// tongxun();
    }     
    }
 
 
