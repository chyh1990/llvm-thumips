/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/27/2012 11:29:16 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chen Yuheng (Chen Yuheng), chyh1990@163.com
 *   Organization:  Tsinghua Unv.
 *
 * =====================================================================================
 */

/*
int add(int a, int b) {
  if(a ==b )
    return a-b;
  return a+b;
}

int main() {
  char test[] = "That is good";
  long long g, i;
  short sht = 0;
  for(i = 0; i < 5; i++) {
    test[i] += test[i] + add(i,i) +33;
    if(i == 3)
      test[i]=66;
    else
      test[i]=99;
  }
  sht = sht-12;
  g = i*i*77;
  i += 23;

  return 0;
}
*/

int main() {
  int i = 1;
  i += 10;
  if(i)
    i = 23;
  return 0;
}
