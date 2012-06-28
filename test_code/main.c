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

int add(int a, int b) {
  if(a ==b )
    return a-b;
  return a+b;
}

int main() {
  char test[] = "That is good";
  int i;
  for(i = 0; i < 5; i++) {
    test[i] += add(i,i);
    if(i == 3)
      break;
  }

  return 0;
}
