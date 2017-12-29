#include "common.h"
#include "uart.h"
#include "assert.h"

#define FreeCarsUARTPort UART5
#define FreeCarsBR       115200       //������
#define CCDWidth 128
#define UartDataNum      17	
#define UartRxBufferLen  100
#define UartRxDataLen    41           //FreeCars��λ�����͸�������MCU���գ���Ҫ��
#define UartRxCmdLen     7	      //FreeCars��λ�������������ݳ��ȣ���Ҫ��
#define UartCmdNum  SerialPortRx.Buffer[SerialPortRx.Stack-3]//�����
#define UartCmdData SerialPortRx.Buffer[SerialPortRx.Stack-2]//��������

typedef struct 
{
  int Stack;
  u8 Data;
  u8 PreData;
  u8 Buffer[UartRxBufferLen];
  u8 Enable;
  u8 Check;
}SerialPortType;

u8 uSendBuf[UartDataNum*2]={0};
u8 FreeCarsDataNum=UartDataNum*2;

double UartData[9] = {0};
SerialPortType SerialPortRx;

void push(uint8 chanel,uint16 data)
{
    uSendBuf[chanel*2]=data/256;
    uSendBuf[chanel*2+1]=data%256;
}




void sendDataToCCDViewer(u8 CCDSelection,u8* CCDData)
{
  u8 i,sum=0; 
  //ʹ����ѯ�ķ�ʽ�������ݣ�������δ���ͣ�����ͣ�ڴ˴�ֱ���������
  uart_putchar(FreeCarsUARTPort,0xFC);
  uart_putchar(FreeCarsUARTPort,0x07);
  uart_putchar(FreeCarsUARTPort,0xCF);
  uart_putchar(FreeCarsUARTPort,CCDSelection);//��CCD�£�ָ�����͵����ĸ�CCD������
  sum+=(0xFC);      //ȫ�����ݼ���У��
  sum+=(0x07);
  sum+=(0xCF);
  sum+=CCDSelection;
  for(i=0;i<CCDWidth;i++)
  {
    uart_putchar(FreeCarsUARTPort,CCDData[i]);
    sum+=CCDData[i];         //ȫ�����ݼ���У��
  }
  uart_putchar(FreeCarsUARTPort,sum);
}
void sendDataToScope(void)
{
  uint8 i,sum=0; 
  //ʹ����ѯ�ķ�ʽ�������ݣ�������δ���ͣ�����ͣ�ڴ˴�ֱ���������
  uart_putchar(FreeCarsUARTPort,251);
  uart_putchar(FreeCarsUARTPort,109);
  uart_putchar(FreeCarsUARTPort,37);
  sum+=(251);      //ȫ�����ݼ���У��
  sum+=(109);
  sum+=(37);
  for(i=0;i<FreeCarsDataNum;i++)
  {
    uart_putchar(FreeCarsUARTPort,uSendBuf[i]);
    sum+=uSendBuf[i];         //ȫ�����ݼ���У��
  }
  uart_putchar(FreeCarsUARTPort,sum);
}