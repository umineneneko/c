#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 1

main()
{
  float fahr, cels;
  cels = LOWER;
  printf("Celsius temperatures and their Fahrenheit equipvalents\n");
  while(cels < UPPER){
    fahr = 9.0*(cels+(32/9))/5.0;
    printf("%9f\t%3.1f\n", cels, fahr);
    cels = cels + STEP;
  }
}
