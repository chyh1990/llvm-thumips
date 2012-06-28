/*
 * =====================================================================================
 *
 *       Filename:  test1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/27/2012 04:20:21 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chen Yuheng (Chen Yuheng), chyh1990@163.com
 *   Organization:  Tsinghua Unv.
 *
 * =====================================================================================
 */

int foo(int a,int b)
{
  return a*2+b;
}

#define UART 0x1fd003f8
volatile unsigned char *uart = (unsigned char*)UART;

void init_uart()
{
  *(uart+1) = 0;
  *(uart+3) = 0x80;
  *(uart+0) = 0x03;
  *(uart+1) = 0x00;
  *(uart+3) = 0x03;
  *(uart+2) = 0xc7;
  *(uart+4) = 0x0b;
}

int main()
{
  int i = 0, sum = 0;
  init_uart();
  for(;i<100;i++){
    sum += i;
    *uart = 'A'+i;
  }
  i = foo(3,i);
  return 0;
}
