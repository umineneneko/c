#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
  int value;
  struct _node *next;
} Node, *pNode;

int splitLinkedList(Node *original, Node **child);
void printList(Node *head);
int size(Node *head);
Node *delete(Node *currP, int value);
Node *copy(Node *target);
void push(Node **head, int v);

main(){
  //============== Case 1: 1 2 3 4 5
  printf("\nCASE 1\n");
  Node *original, *head;
  Node *temp = NULL;
  Node ** child = &temp;
  int i = 5;
  head = NULL;
  while(i > 0){
    original = malloc(sizeof(Node));
    original->value = i;
    original->next = head;
    head = original;
    i--;
  }
  printf("Begin Original:\n");
  printList(original);

  int rs = splitLinkedList(original, child);
  printf("Guard Index: %d", rs);
  printf("\n\toriginal:\n\t");
  printList(original);
  printf("\n\tchild:\n\t");
  printList(*child);
  free(*child);
  free(original);
  free(temp);
  free(head);

  //============== Copy above only for case 2: 10 11 12 13
  printf("\nCASE 2\n");
  Node *original1, *head1;
  Node *temp1 = NULL;
  Node ** child1 = &temp1;
  int i1 = 13;
  head1 = NULL;
  while(i1 > 9){
    original1 = malloc(sizeof(Node));
    original1->value = i1;
    original1->next = head1;
    head1 = original1;
    i1--;
  }
  printf("Begin Original:\n");
  printList(original1);

  int rs1 = splitLinkedList(original1, child1);
  printf("Guard Index: %d", rs1);
  printf("\n\toriginal:\n\t");
  printList(original1);
  printf("\n\tchild:\n\t");
  printList(*child1);
  free(original1);
  free(*child1);
  free(temp1);
  free(head1);
}

void printList(Node *head){
  while(head){
    printf("%d\t", head->value);
    head = head->next;
  }
  printf("\n");
}

int size(Node *head){
  int i = 0;
  while(head){
    head = head->next;
    i++;
  }
  return i;
}

Node *delete(Node *current, int value)
{
  if (current == NULL)
    return NULL;
  if (current->value == value) {
    Node *temp = current->next;
    free(current);
    return temp;
  }
  current->next = delete(current->next, value);
  return current;
}

Node *copy(Node *target)
{
  Node *rs, *head;
  head = NULL;
  while(target){
    rs = malloc(sizeof(Node));
    rs->value = target->value;
    rs->next = head;
    head = rs;
    target=target->next;
  }
  return rs;
}

void push(Node **head, int v)
{
    Node *temp = malloc(sizeof(Node));
    temp->value = v;
    temp->next = *head;
    *head = temp;    
}

// the final boss
int splitLinkedList(Node *original, Node **child){
  int l = size(original);
  int i = 0;
  int guard = l/2;
  Node *current = copy(original);
  while(i<l){
   if(i < guard){
       push(child, current->value);
       original = delete(original, current->value);
    }
    i++;
    current = current->next;
  }
  free(current);
  return guard;
 }
