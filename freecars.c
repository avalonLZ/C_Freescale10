#include "common.h"
#include "uart.h"
#include "assert.h"

#define FreeCarsUARTPort UART5
#define FreeCarsBR       115200       //波特率
#define CCDWidth 128
#define UartDataNum      17	
#define UartRxBufferLen  100
#define UartRxDataLen    41           //FreeCars上位机发送浮点数据MCU接收，不要改
#define UartRxCmdLen     7	      //FreeCars上位机接收命令数据长度，不要改
#define UartCmdNum  SerialPortRx.Buffer[SerialPortRx.Stack-3]//命令号
#define UartCmdData SerialPortRx.Buffer[SerialPortRx.Stack-2]//命令数据

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
  //使用轮询的方式发送数据，当数据未发送，程序停在此处直到发送完成
  uart_putchar(FreeCarsUARTPort,0xFC);
  uart_putchar(FreeCarsUARTPort,0x07);
  uart_putchar(FreeCarsUARTPort,0xCF);
  uart_putchar(FreeCarsUARTPort,CCDSelection);//多CCD下，指定发送的是哪个CCD的数据
  sum+=(0xFC);      //全部数据加入校验
  sum+=(0x07);
  sum+=(0xCF);
  sum+=CCDSelection;
  for(i=0;i<CCDWidth;i++)
  {
    uart_putchar(FreeCarsUARTPort,CCDData[i]);
    sum+=CCDData[i];         //全部数据加入校验
  }
  uart_putchar(FreeCarsUARTPort,sum);
}
void sendDataToScope(void)
{
  uint8 i,sum=0; 
  //使用轮询的方式发送数据，当数据未发送，程序停在此处直到发送完成
  uart_putchar(FreeCarsUARTPort,251);
  uart_putchar(FreeCarsUARTPort,109);
  uart_putchar(FreeCarsUARTPort,37);
  sum+=(251);      //全部数据加入校验
  sum+=(109);
  sum+=(37);
  for(i=0;i<FreeCarsDataNum;i++)
  {
    uart_putchar(FreeCarsUARTPort,uSendBuf[i]);
    sum+=uSendBuf[i];         //全部数据加入校验
  }
  uart_putchar(FreeCarsUARTPort,sum);
}