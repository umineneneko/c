// 12453: read an array using pointer
// 12454: count word in a sentence
// 12455: swap(a,b,c) -> a=b, b=c, c=a
#include<stdio.h>

void print(int*, int);
void printChar(char*);
int find(int*, int, int);
int findWord(char*, char*);
void swap(int*, int*, int*);

int main(){
  int arr[8] = {1, 2, 4, 5, 6, 7, 8, 99}, idx, idxWord;
  char *arrChar = "abcdef haha kjfslk hahha hhh haha 00 jhdhfkshf hahahaha hhhhaha";
  int s = sizeof(arr)/sizeof(arr[0]);
  printf("Size array: %d\n",s);    
  int *p = &arr[0];
  print(p, s);
  idx = find(p, s, 4);
  printf("\nIndex: %d \n", idx);

  printChar(arrChar);
  idxWord = findWord(arrChar, "haha");
  printf("\nIndex: %d \n", idxWord);
  printf("\n");

  swap(&arr[0], &arr[1], &arr[2]);
  printf("%p", &arr[0]);
  return 1;
}

void print(int *p, int size){
   int *pBegin = p;
   while(p < pBegin + size){
     printf("%d\t", *p);  
     p++;
   }
}

void printChar(char *p){
  while(*p!='\0'){
    printf("%c", *p);
    p++;
  }
}

int find(int *p, int size, int val){
  int i = 0;
  for(;i < size; i++){
    if(*(p+i) == val){
      return i;
    }
  }
  return -1; // not found
}

int findWord(char *sentence, char *word){
  int rs = 0, i = 0;
  char *temp;
  while(*sentence != '\0'){
    printf("#1 %c:\t",*sentence);
    temp = word;
    if(*sentence == *temp){ 
      printf("#2 %c:\t",*sentence);
      while(*temp!= '\0'){
        if(*++sentence != *++temp){
	  printf("#3 %c:\t",*sentence);
          break;
        }
        printf("#4 %c:\t",*sentence);
      }      
      if(*temp== '\0'){
        rs++;
      }
    } else {	    
      sentence++;
    }
  }
  return rs;
}          
void swap(int *a, int *b, int *c){
  printf("%d-%d-%d\n", *a, *b, *c);  
  int temp = *b;
  *b = *c;
  *c = *a;
  *a = temp; 
  printf("\n%d-%d-%d", *a, *b, *c);  
}



