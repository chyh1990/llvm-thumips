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

#define UART 0x500
volatile unsigned int *uart = (unsigned int*)UART;

int main()
{
  int i = 0, sum = 0;
  for(;i<100;i++){
    sum += i;
    *uart = 'A'+i;
  }
  i = foo(3,i);
  return 0;
}
