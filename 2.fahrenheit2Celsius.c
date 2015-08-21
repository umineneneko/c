#include <stdio.h>

main()
{
  float fahr, cels;
  float lower, upper, step;
  lower = 0;
  upper = 300;
  step = 20; /*a..*/ 
  fahr = lower;
  printf("Fahrenheit temperatures and their centigrade or Celsius equipvalents\n");
  while(fahr < upper){
    cels = 5.0*(fahr-32)/9.0;
    printf("%3.0f\t%9.2f\n", fahr, cels);
    fahr = fahr + step;
  }
}
