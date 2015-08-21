#include <stdio.h>

main(){
  int x, y;
  x = y = 2;
  x = x << 2;
  y = y >> 2;
  printf("%d\n\n%d\n\n",x, y);
}
