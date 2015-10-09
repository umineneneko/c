// 12456: input array size
// 12457: linked list
// 12458: binary tree  ??? why **?
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

typedef struct Node{
  int val;
  struct Node *next;
} Node;

typedef struct Tree{
  int val;
  struct Tree *left;
  struct Tree *right;
} Tree;

int* dynamicArray(int);
Node* addNode(Node *cur, int val);
Node* removeNode(Node *cur);
void printNodes(Node *cur);
void clearNodes(Node *cur);
void addTree(Tree **root, Tree *data);
void printTree(Tree *root);
signed short int isLeaf(Tree *root);

int main(){
  // 12456
  int *pArr, size;
  printf("Set size: \n");
  scanf("%d", &size);
  pArr = dynamicArray(size);
  printf("Memory allocated at: %p: \n", pArr);
  printf("0: %d\n", *(pArr+1));
  free(pArr);

  //12457
  int i = 7;
  Node *pList = NULL, *pTemp;
  pList = addNode(pList, 44);
  pTemp = pList;
  for(;i < 15; i++){
    pList = addNode(pList, i);
  }
  printNodes(pTemp);
  //  clearNodes(pTemp); // not empty list
  printNodes(pTemp);

  //12458
  Tree *pTree = NULL, *pData;
  int k = 0;
  for(k=0;k<5;k++){
    pData = (Tree*)malloc(sizeof(Tree));
    pData->val = k;//rand();
    pData->left = pData->right = NULL;
    addTree(&pTree, pData);
  }
  pData = (Tree*)malloc(sizeof(Tree));
  pData->val = -5;
  pData->left=pData->right = NULL;
  addTree(&pTree, pData);
  printTree(pTree);
  return 1;
}

int* dynamicArray(int size){
  return (int*)malloc(size*sizeof(int));
}

Node* addNode(Node *cur, int val){
  if(cur == NULL){
    cur = (struct Node *)malloc(sizeof(Node));
    cur->val = val;
    cur->next = NULL;
    return cur;
  } else {
    Node *pTemp = cur;
    while(pTemp->next != NULL){
      pTemp = pTemp->next;
    }    
    pTemp->next = (struct Node *)malloc(sizeof(Node));
    pTemp = pTemp->next;
    pTemp->val = val;
    pTemp->next = NULL;
    return pTemp;
  }
}

void printNodes(Node *cur){
  if(cur == NULL){
    printf("List is empty.\n");
  } else {
    while(cur != NULL){
      printf("%d \t", cur->val);
      cur = cur->next;
    }
    printf("\n");
  }
}

Node* removeNode(Node *cur){
 Node *pTemp = cur->next; 
 printf("Going to remove node: %d at %p\n:", cur->val, cur);
 free(cur);
 return pTemp;
}

void clearNodes(Node *cur){
 while(cur != NULL){
   cur = removeNode(cur);
 }
}

// 12458
void addTree(Tree **root, Tree *data){
  if(!(*root)){
    *root = data;
    return;
  }
  if(data->val < (*root)->val){
    addTree(&(*root)->left, data);
  }
  else if(data->val > (*root)-> val){
    addTree(&(*root)->right, data);
  }  
}

void printTree(Tree *root){
  if(root->left != NULL)  printTree(root->left);
  printf("%d \t", root->val);
  if(root->right !=NULL)  printTree(root->right);
}

signed short int isLeaf(Tree *root){
  return root!= NULL && root->left ==NULL&& root->right == NULL;
}
