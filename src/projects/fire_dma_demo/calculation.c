#include "include.h"

extern u8 Pixel1[128];
extern u8 Pixel2[128];
int Max_Data1=0, Min_Data1=0;
int L_Max_Data1=0,R_Max_Data1=0,L_Max_Data3=0,R_Max_Data3=0,L_Max_Data2=0,R_Max_Data2=0,L_Max_Data4=0,R_Max_Data4=0;
u8 L_Max_Data_Place1=0, R_Max_Data_Place1=0,L_Max_Data_Place3=0, R_Max_Data_Place3=0,L_Max_Data_Place2=0, R_Max_Data_Place2=0,L_Max_Data_Place4=0, R_Max_Data_Place4=0;//����λ��
int Dvalue_AD_Data_CCD1[128]={0};
int Dvalue_AD_Data_CCD2[128]={0};
volatile int Find_Mid_Place = 64;//��ʼѲ�ߵ�λ��
volatile int Find_Mid_Place1 = 64;//��ʼѲ�ߵ�λ��
int ccd1_mid=64;
u8 zhuan=0,zhuan1=0,leftzhijiao=0,rightzhijiao=0;//Ҫ��������
int t=64,t1=64;
u8 t2=0,t3=0,t4=0;
int CCD1_Data_Average = 0;//ccd1ƽ��ֵ
int tt=0,ttt=0,tt1=0,ttt1=0;
u8 t5=0,t6=0,t7=0,t8=0;
u8 shizi=0;
extern u8 fanzhuan;
extern u8 tx;
u8 Rzhangai=0,zhangai_t=0,Lzhangai=0;

/*************************************************************************
*                             ������ӹ�����
*
*  �������ƣ�CCD1_init
*  ����˵����CCD��ʼ��
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
*************************************************************************/
void CCD1_init(void)
{
  gpio_init (PORTE , 10, GPO,HIGH);
  gpio_init (PORTE , 12, GPO,HIGH);
  adc_init(ADC1, AD12) ;
}
void CCD2_init(void)
{
  gpio_init (PORTE , 2, GPO,HIGH);
  gpio_init (PORTE ,3, GPO,HIGH);
  adc_init(ADC1, AD14) ;
}

/*************************************************************************
*                           ������ӹ�����
*
*  �������ƣ�StartIntegration
*  ����˵����CCD�������򡢡�������������CCD��ʱ������
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
*************************************************************************/
void StartIntegration1(void)
{
    unsigned char i;
    SI_SetVal1();            /* SI  = 1 */
    SamplingDelay();
    CLK_SetVal1();           /* CLK = 1 */
    SamplingDelay();
    SI_ClrVal1();            /* SI  = 0 */
    SamplingDelay();
    CLK_ClrVal1();           /* CLK = 0 */
    for(i=0; i<127; i++)
    {
        SamplingDelay();
        SamplingDelay();
        CLK_SetVal1();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        CLK_ClrVal1();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CLK_SetVal1();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CLK_ClrVal1();           /* CLK = 0 */
}
void StartIntegration2(void) 
{
    unsigned char i;
    SI_SetVal2();            /* SI  = 1 */
    SamplingDelay();
    CLK_SetVal2();           /* CLK = 1 */
    SamplingDelay();
    SI_ClrVal2();            /* SI  = 0 */
    SamplingDelay();
    CLK_ClrVal2();           /* CLK = 0 */
    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        CLK_SetVal2();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        CLK_ClrVal2();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CLK_SetVal2();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CLK_ClrVal2();           /* CLK = 0 */
}


/*************************************************************************
*                           ������ӹ�����
*
*  �������ƣ�StartIntegration
*  ����˵����CCD��������
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
*ImageData =  ad_once(ADC1, AD6a, ADC_8bit);
*************************************************************************/

void ImageCapture1(unsigned char * ImageData) //CCD1�ɼ�
{   
    unsigned char i;
    SI_SetVal1();            /* SI  = 1 */
    SamplingDelay();
    CLK_SetVal1();           /* CLK = 1 */
    SamplingDelay();
    SI_ClrVal1();            /* SI  = 0 */
    SamplingDelay();
    //Delay 10us for sample the first pixel
    /**/
    for(i = 0; i <250; i++)
    {
      SamplingDelay() ;  //200ns
    }
    //Sampling Pixel 1
    *ImageData =  ad_once(ADC1,AD12, ADC_8bit);
    ImageData ++ ;
    CLK_ClrVal1();           /* CLK = 0 */
    for(i=0; i<127; i++)
    {
        SamplingDelay();
        SamplingDelay();
        CLK_SetVal1();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        //Sampling Pixel 2~128
       *ImageData =  ad_once(ADC1, AD12, ADC_8bit);
        ImageData ++ ;
        CLK_ClrVal1();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CLK_SetVal1();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CLK_ClrVal1();           /* CLK = 0 */ 
}
void ImageCapture2(unsigned char * ImageData)//CCD2�ɼ�
{ 
    unsigned char i;
    SI_SetVal2();            /* SI  = 1 */
    SamplingDelay();
    CLK_SetVal2();           /* CLK = 1 */
    SamplingDelay();
    SI_ClrVal2();            /* SI  = 0 */
    SamplingDelay();
    //Delay 10us for sample the first pixel
    /**/
    for(i = 0; i <250; i++) 
    {
      SamplingDelay() ;  //200ns
    }
    *ImageData =  ad_once(ADC1,AD14, ADC_8bit);
    ImageData ++ ;
    CLK_ClrVal2();           /* CLK = 0 */
    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        CLK_SetVal2();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        //Sampling Pixel 2~128
       *ImageData =  ad_once(ADC1, AD14, ADC_8bit);
        ImageData ++ ;
        CLK_ClrVal2();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CLK_SetVal2();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CLK_ClrVal2();           /* CLK = 0 */ 
}




/*************************************************************************
*                           ������ӹ�����
*
*  �������ƣ�SamplingDelay
*  ����˵����CCD��ʱ���� 200ns
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2012-10-20
*  ��    ע��
*************************************************************************/
 void SamplingDelay(void){
   volatile u8 i ;
   for(i=0;i<1;i++)
   {
    asm("nop");
    asm("nop");
   }
   
}
/*uint32_t Int_Abs(int Data)
{
	if(Data>0)
		return Data;
	else if(Data<0)
		return (-Data);
	else 
		return 0;
}
*/
void Analyze_CCD_Data(void)
{
        u8 i=0,k=0,flag_left1=0,flag_right1=0,flag_left3=0,flag_right3=0;    
	for(i=20,Max_Data1=0,Min_Data1=255,CCD1_Data_Average = 0;i<108;i++) 
	{ 
		CCD1_Data_Average +=Pixel1[i]; //�ۼ�/////////û��
		
		if(Pixel1[i]>=Max_Data1)//�ɼ������ֵ
		{
			Max_Data1 = Pixel1[i];		   
		}
		if(Pixel1[i]<=Min_Data1)//�ɼ�����Сֵ
		{
			Min_Data1 =Pixel1[i];		  
		}
	}
	CCD1_Data_Average /= 88;  //128���ɼ����ƽ��ֵ
        ///////////////////////////////////////////////////////////////////////////////////////ccd1
	Dvalue_AD_Data_CCD1[0] = (int)(Pixel1[0]-Pixel1[1]);
	for(i=1;i<127;i++)
	{
		Dvalue_AD_Data_CCD1[i] = (int)((Pixel1[i-1]-Pixel1[i+1]))>>1;
	}
	Dvalue_AD_Data_CCD1[127] = (int)(Pixel1[126]-Pixel1[127]);
	for(i= Find_Mid_Place1, L_Max_Data1=0; i>19;i--)		  
	{
		if(Dvalue_AD_Data_CCD1[i]<= L_Max_Data1)
		{
			L_Max_Data1 = Dvalue_AD_Data_CCD1[i];
			    
		}
	}
        ttt=(int)(L_Max_Data1*0.6);
        for(k=Find_Mid_Place1; k>19;k--)		  
	{
          
          
          if(L_Max_Data1<=-yz1)
          {
		if(Dvalue_AD_Data_CCD1[k] <=ttt)
		{
			L_Max_Data_Place1 = k;
                        flag_left1=1;
			break;
		}   
          }
          else
          {
           L_Max_Data_Place1=20;
            flag_left1=0;
          }
	}
	for(i=Find_Mid_Place1, R_Max_Data1=0; i<108; i++)
	{
		if(Dvalue_AD_Data_CCD1[i] >= R_Max_Data1)
		{
			R_Max_Data1 = Dvalue_AD_Data_CCD1[i];
			
		}
	}
        tt=(int)(R_Max_Data1*0.6);
      for(k= Find_Mid_Place1; k<108; k++)
	{
          if(R_Max_Data1>=yz)
          {
		if(Dvalue_AD_Data_CCD1[k] >= tt)
		{
			R_Max_Data_Place1 = k;
                        flag_right1=1;
			break;
		}   
          }
          else
          {
            R_Max_Data_Place1=107;
            flag_right1=0;
          }
            
	}

///////////////////////����////////////////////////////////////////////////////
       for(i=30, L_Max_Data3=0; i<=97 ; i++)
	{
		if(Dvalue_AD_Data_CCD1[i] >= L_Max_Data3)
		{
			L_Max_Data3 = Dvalue_AD_Data_CCD1[i];
			
		}
	}
        for(k=30; k<=97 ; k++)
	{
          
              if(L_Max_Data3>=10)//15
              {
		if(Dvalue_AD_Data_CCD1[k] >= L_Max_Data3)
		{
			L_Max_Data_Place3 = k;
                        flag_left3=1;
			break;
		}  
              }
              else
              {
                L_Max_Data_Place3=30;
                flag_left3=0;
              }
                
	}
       for(i= 97, R_Max_Data3=0; i>=L_Max_Data_Place3 ;i--)		  
	{
		if(Dvalue_AD_Data_CCD1[i]<= R_Max_Data3)
		{
			R_Max_Data3 = Dvalue_AD_Data_CCD1[i];
			
		}
	}
      for(k= 97; k>=L_Max_Data_Place3 ;k--)	  
	{
          if(R_Max_Data3<=-10)//15
          {
		if(Dvalue_AD_Data_CCD1[k] <= R_Max_Data3)
		{
			R_Max_Data_Place3 = k;
                        flag_right3=1;
			break;
		}
          }
          else
          {
            R_Max_Data_Place3=97;
            flag_right3=0;
          }
              
	}
    
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////ccd2      
       Dvalue_AD_Data_CCD2[0] = (int)(Pixel2[0]-Pixel2[1]);
	for(i=1;i<127;i++)
	{
		Dvalue_AD_Data_CCD2[i] = (int)((Pixel2[i-1]-Pixel2[i+1]))>>1;
	}
	Dvalue_AD_Data_CCD2[127] = (int)(Pixel2[126]-Pixel2[127]);
       for(i= 64, L_Max_Data2=0; i>4;i--)		  
	{
		if(Dvalue_AD_Data_CCD2[i]<= L_Max_Data2)
		{
			L_Max_Data2 = Dvalue_AD_Data_CCD2[i];    
		}
	}
        ttt1=(int)(L_Max_Data2*0.6);
        for(k=64; k>4;k--)		  
	{
          
          
          if(L_Max_Data2<=-yz2)//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
          {
		if(Dvalue_AD_Data_CCD2[k] <=ttt1)
		{
			L_Max_Data_Place2 = k;
                       
			break;
		}   
          }
          else
          {
           L_Max_Data_Place2=5;
          }
	}
	
 /////////////////////////////////////////////Ѱ�ұߺ����½���     ��ֵ
	for(i=64, R_Max_Data2=0; i<123; i++)
	{
		if(Dvalue_AD_Data_CCD2[i] >= R_Max_Data2)
		{
			R_Max_Data2 = Dvalue_AD_Data_CCD2[i];
			
		}
	}
        tt1=(int)(R_Max_Data2*0.6);
      for(k= 64; k<123; k++)
	{
          if(R_Max_Data2>=yz2)/////////////////////////////////////////////////////////////////////////////////////////////////////////////
          {
		if(Dvalue_AD_Data_CCD2[k] >= tt1)
		{
			R_Max_Data_Place2 = k;
                       
			break;
		}   
          }
          else
          {
            R_Max_Data_Place2=122;
           
          }
            
	} 
     for(i=5, L_Max_Data4=0; i<=L_Max_Data_Place2 ; i++)
	{
		if(Dvalue_AD_Data_CCD2[i] >= L_Max_Data4)
		{
			L_Max_Data4 = Dvalue_AD_Data_CCD2[i];
			
		}
	}
        for(k=5; k<=L_Max_Data_Place2 ; k++)
	{
          
              if(L_Max_Data4>=yz2)
              {
		if(Dvalue_AD_Data_CCD2[k] >= L_Max_Data4)
		{
			L_Max_Data_Place4= k;
                       
			break;
		}  
              }
              else
              {
                L_Max_Data_Place4=5;
                
              }
                
	}
       for(i= 122, R_Max_Data4=0; i>=R_Max_Data_Place2 ;i--)		  
	{
		if(Dvalue_AD_Data_CCD2[i]<= R_Max_Data4)
		{
			R_Max_Data4 = Dvalue_AD_Data_CCD2[i];
			
		}
	}
      for(k= 122; k>=R_Max_Data_Place2 ;k--)	  
	{
          if(R_Max_Data4<=-yz2)
          {
		if(Dvalue_AD_Data_CCD2[k] <= R_Max_Data4)
		{
			R_Max_Data_Place4 = k;
                        
			break;
		}
          }
          else
          {
            R_Max_Data_Place4=122;
          
          }
              
	}

///////////////////////////////////////////////////////////////////////////////       
 //����Ϊ���ε����ֻ���������ֱ���������ҵ�λ��ˢ������
 //////////////ֱ������///////////////////////////////   
      
      
      if(flag_left3==1&&flag_right3==1&&(R_Max_Data_Place3-L_Max_Data_Place3)<=6&&R_Max_Data_Place3!=L_Max_Data_Place3&&L_Max_Data_Place3!=97)/////////////��ֵ������ֵ
      {
        
        ccd1_mid=((L_Max_Data_Place3+R_Max_Data_Place3)>>1)+dandao;//8
  
         D_Kdd=dandaoBDD;
      }
      else
      {   
       if (flag_left1==1&&flag_right1==1)
              //���ұ�Ե����⵽
       {     
         
           if(R_Max_Data_Place4!=122)
          {
            if((R_Max_Data_Place4-R_Max_Data_Place2)>22&&(R_Max_Data_Place4-R_Max_Data_Place2)<=30)///////////////////////���ϰ�
              {

                Rzhangai=1;
               
              }
            else
            {
              ccd1_mid=((L_Max_Data_Place1+R_Max_Data_Place1)>>1);       
               D_Kdd=dandaoHDD;
            }
           
              
             
         }
           else if(L_Max_Data_Place4!=5)
          {
            if((L_Max_Data_Place2-L_Max_Data_Place4)>22&&(L_Max_Data_Place2-L_Max_Data_Place4)<=30)///////////////////////���ϰ�
              {

                Lzhangai=1;
                 
              }
              else
            {
              ccd1_mid=((L_Max_Data_Place1+R_Max_Data_Place1)>>1);
               D_Kdd=dandaoHDD;
            }
           
             
         }
           
          else
           {     
             if(Rzhangai==1|| Lzhangai==1)
                  zhangai_t++;
                   if(zhangai_t>=20)
                   {
                     zhangai_t=0;
                     Rzhangai=0;
                     Lzhangai=0;
                   }
             
            ccd1_mid=((L_Max_Data_Place1+R_Max_Data_Place1)>>1);//�������ߵ�λ��
            D_Kdd=dandaoHDD;
          }
         
        }
        
 ////////////////��������//////////////////////////////////  
       else
     {    
           if (flag_left1==1&&flag_right1==0)//
         
         {        
         
               
                 ccd1_mid=(L_Max_Data_Place1+buxianL);
                 D_Kdd=dandaoHDD;
                                
         }
         if (flag_left1==0&&flag_right1==1)
      //ֻ��⵽�ұ�Ե������߶�ʧ��Ӧ���߿�����ֱ�ǡ�
         {
        
               ccd1_mid=(R_Max_Data_Place1-buxianR);
               D_Kdd=dandaoHDD;
               
                                   
       }
//////////////////ʮ�ִ���//////////////////////////////////////////
        if(flag_left1==0&&flag_right1==0)                
            {               
              ccd1_mid=64;  
              if(Min_Data1>=quanbaiMIN) 
              {      
                shizi=1;
                  
              } 
              else
              {
                if(Max_Data1<=quanheiMAX)//90
                {
                if(fanzhuan==1)
                {
                  if(zhuan==0)
                  {
                  zhuan1=1;
                  }
                  else
                    zhuan1=2;
               
                }
                }
             
                }
            }
}

      }
  
 /////////////ֱ�Ǵ���//////////////////////////////////////////
if(zhuan1==1)
{
    t2++;
}
else
   t2=0;
if( zhuan1==1&&t2>=8)
 {     
                  
       t2=8;
    if (R_Max_Data_Place2!=122&&L_Max_Data_Place2==5&&rightzhijiao!=1)///flag_left1==0&&flag_right1==1
     {       
          
          if(zhuan==0)
          {   
           
             leftzhijiao=1;//��ת��־λ
                              
          }
        
      }
              
          
    if (R_Max_Data_Place2==122&&L_Max_Data_Place2!=5&&leftzhijiao!=1)//flag_left1==1&&flag_right1==0
     {
         if(zhuan==0)
          {                                   
           rightzhijiao=1;//��ת��־λ
                           
          }
                      
                             
     }                                  
 }   
 /////////////////ֱ��ת�Ǵ���/////////////////////////////
if( rightzhijiao==1)
{     
    t5++;
    if(t5>=zhijiao)
    {   
      t5=zhijiao;
      if(t<=89&&t>=64&&t7!=2)
        {
           
        if(t7==1)
        {
          Find_Mid_Place=t;
          ccd1_mid=t;
          t=t-1;
          if(t==70)
          t7=2;
   
        }
          
         else
         {
          Find_Mid_Place=t;
          ccd1_mid=t;
          t=t+1;
          if(t==89)
            t7=1;
         }
          direction_pwmmax=zhijiaoBDpwmmax;
          S_Kp=zhijiaoBS_Kp;
           D_Kp =zhijiaoBD_Kp;
          }
     
        
    else
       {
         t3++;
        Find_Mid_Place=ccd1_mid;
         if(t3>=20)
         {
           t3=0;
          zhuan=1;
          rightzhijiao=0;     
          zhuan1=0;
         direction_pwmmax=zhijiaoHDpwmmax;
       S_Kp=zhijiaoHS_Kp;
       D_Kp =zhijiaoHD_Kp;
       }
       }
    }
 }     
else  if( leftzhijiao==1)
{        t6++;
     if(t6>=zhijiao)//////////////////////////////////////////////////////////////
     {    t6=zhijiao;
       if(t1>=39&&t1<=64&&t8!=2)
      {     
             if(t8==1)
        {
          Find_Mid_Place=t1;
          ccd1_mid=t1;
          t1=t1+1;
          if(t1==59)
            t8=2;
        }
          
         else
         {
          Find_Mid_Place=t1;
          ccd1_mid=t1;
          t1=t1-1;
          if(t1==39)
            t8=1; 
         }
          direction_pwmmax=zhijiaoBDpwmmax;
          S_Kp=zhijiaoBS_Kp;
          D_Kp =zhijiaoBD_Kp;
       }
      
      else
      {
        t3++;
         Find_Mid_Place=ccd1_mid;
        if(t3>=20)//////////////////////////////////////////////////////////////////////////////////////////////
        {
          t3=0;
         leftzhijiao=0;
         zhuan=1;
         zhuan1=0;
         direction_pwmmax=zhijiaoHDpwmmax;
         S_Kp=zhijiaoHS_Kp;
        D_Kp =zhijiaoHD_Kp;
      }  
      }
      }
     
}
      
  
 ///////////////////ֱ��ת�����λ//////////////////////////////  
 else
 {  
            Find_Mid_Place=ccd1_mid;
         
              Find_Mid_Place1=ccd1_mid;
   
            
                if(Find_Mid_Place1<=20)
            {
              Find_Mid_Place1=20;
            }
               if(Find_Mid_Place1>=107)
            {
              Find_Mid_Place1=107;
            }
      
     
                   
                  
    
        
           
} 
if(zhuan1==2)
{
    t4++;
}
else
   t4=0;
if( zhuan1==2&&t4>=8)            
          
          {    
             
               zhuan=0;
               zhuan1=0;                       
               leftzhijiao=0; 
               rightzhijiao=0;
               t=64;
               t1=64;
               t4=8; 
              t5=0;
               t6=0;
               t7=0;
               t8=0;
             }
         if(tx==1)
      {
        
             LCD_CLS();//����
             LCD_Char(10,0,'M'); LCD_Char(18,0,'I');LCD_Char(26,0,'N');
             LCD_PrintValueI(40, 0,Min_Data1);
             LCD_Char(10,3,'M'); LCD_Char(18,3,'A');LCD_Char(26,3,'X');
             LCD_PrintValueI(40, 3,Max_Data1);
             LCD_PrintValueI(8, 6,CCD1_Data_Average);
      }
               push(0,R_Max_Data_Place4);//////////////////////////////////������R_Max_Data_Place1��L_Max_Data_Place1,R_Max_Data_Place3��L_Max_Data_Place3
               push(1,L_Max_Data_Place4);/////////////////////////////////////�ϰ���R_Max_Data_Place2��L_Max_Data_Place2,R_Max_Data_Place4��L_Max_Data_Place4
              
             push(2,R_Max_Data_Place2);
               push(3,L_Max_Data_Place2);/* */
               
               
               
              
            
               
                 
                 
             
               
                    
             
 }
