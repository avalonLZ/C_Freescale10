

#include "common.h"
#include "uart.h"
float OutData[4] = {0};
float sb[2];
unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT)
{
    unsigned short CRC_Temp;
    unsigned char i,j;
    CRC_Temp = 0xffff;

    for (i=0;i<CRC_CNT; i++){      
        CRC_Temp ^= Buf[i];
        for (j=0;j<8;j++) {
            if (CRC_Temp & 0x01)
                CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
            else
                CRC_Temp = CRC_Temp >> 1;
        }
    }
    return(CRC_Temp);
}
/*
****************************************************************
*    ��ϴ���ʾ���������Э�飬float �ֳ���Ϊ16λ������ע�⹤��
*    �����е���32λ!
*  1  �������4·��Ϣ��ÿ·���ݳ�����16λ��
*  2  ÿ������ֽ�����10������������ֽ�ΪУ��
*****************************************************************
*/

void OutPut_Data(void)
{
  int temp[4] = {0};
   
  unsigned int temp1[4] = {0};
  
  unsigned char databuf[10] = {0};
  unsigned char i;
  unsigned short CRC16 = 0;
  for(i=0;i<4;i++)
   {
    
    temp[i]  = (int)OutData[i];
    temp1[i] = (unsigned int)temp[i];
   }
   
  for(i=0;i<4;i++) 
  {
    databuf[i*2]   = (unsigned char)(temp1[i]%256);//////////////////ȡ��������256������,��2�ֽڵĶ������һ���ֽ���
    databuf[i*2+1] = (unsigned char)(temp1[i]/256);///////////////////ȡ��������256������
  }
  

  
  CRC16 = CRC_CHECK(databuf,8);
  databuf[8] = CRC16%256;
  databuf[9] = CRC16/256;

 for(i=0;i<10;i++)
    uart_putchar (UART5, databuf[i]);
}

////////////////////////////ͨѶЭ��
void tongxun(void)
{ 
  unsigned char i,j=3;
  unsigned int temp[2] = {0};
  unsigned char databuf[7] = {'D','H','D',0,0,0,0};
 unsigned int temp1[2] = {0};
  for(i=0;i<2;i++)
  {
     temp1[i]=(int)sb[i];
     temp[i]=(unsigned int)temp1[i];////////////////////////����С��λ�Ұ����λ��0��1����Ϊ����ֵ
     databuf[j]=(unsigned char)(temp[i]%256);
     databuf[j+1]=(unsigned char)(temp[i]/256);
     j=j+2;
  }
  for(j=0;j<7;j++)
    uart_putchar (UART5,databuf[j]); 
}
