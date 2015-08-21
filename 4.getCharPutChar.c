#include <stdio.h>

main()
{
  int c;
  long cn = 0;
  while((c = getchar())!= EOF){
    ++cn;
    printf("Counting: %2ld\n ... ", cn);
    putchar(c);
  }
/*  cels = LOWER;
  printf("Celsius temperatures and their Fahrenheit equipvalents\n");
  while(cels < UPPER){
    fahr = 9.0*(cels+(32/9))/5.0;
    printf("%9f\t%3.1f\n", cels, fahr);
    cels = cels + STEP;
  }
*/
}
