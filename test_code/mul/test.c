/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/30/2012 10:47:53 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chen Yuheng (Chen Yuheng), chyh1990@163.com
 *   Organization:  Tsinghua Unv.
 *
 * =====================================================================================
 */

void mul1(long long aa)
{
  int a = 3, b= 5;
  int c = a *b;
  int d = a*4;
  long long ll = 0x23423423;
  ll = ll * aa;
}

struct foo{
  int a;
  int b;
  int* x;
};
//sizeof(foo) == 12

static struct foo foos[6];

int mul2(int idx){
  //generate idx * sizeof(foo)
  return foos[idx].a;
}

int main()
{
  mul1(0x342342);
  mul2(2);
  return 0;
}

