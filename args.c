
#include <stdio.h>
#include <stdlib.h>

typedef struct listStr{
  char *val;
  struct listStr *next;
} listStr; 


int main(int argc, char **argv){
  int i;
  FILE *from;
  char p[1000];
  listStr *pTotal = NULL; 
  printf("argc = %d\n\n", argc);
  for(i = 0; i< argc; i++){
    printf("argv[%d]: %s\n", i, argv[i]);
  }
  
  if(argc != 3){
    printf("missing argv");
    exit(1);
  }
  if((from = fopen(argv[1], "r")) == NULL){
    printf("Cannot open file: %s", argv[1]);
    exit(1);
  } else {
    puts("5");
    while(fgets(p, sizeof(p), from) != NULL){
      if(pTotal == NULL){ 
        pTotal = (listStr*)malloc(sizeof(listStr));
        pTotal->val = p;
        pTotal->next = NULL;
      } else{
      puts("1");
        while(pTotal->next){
          pTotal = pTotal->next;
        }
      puts("2");
        pTotal->next = (listStr*)malloc(sizeof(listStr));
      puts("3");
	pTotal = pTotal->next;
        pTotal->val = p;
        pTotal->next = NULL;
      }
      printf("%s",p);
    }
    fclose(from);
  }    
   
  
  return 1;
}

