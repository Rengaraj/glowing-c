/*
 *Singley Linked List
 */

#include<stdio.h>
#include<stdlib.h>


struct node {
  int value;
  struct node *next_node_addr;
};


struct node * push(struct node *head, int data)
{
  struct node * tmp = (struct node *)malloc(sizeof(struct node));
  if (tmp == NULL)
    exit(0);

  tmp->value = data;
  tmp->next_node_addr = head;
  head = tmp;
  return head;
}

void print_list(struct node *head)
{
  struct node * new;
  new = head;
  if( new == NULL) {
    printf(" Empty List \n");
    exit(0);
  }
  
  while(new != NULL)
    {
      printf("%d, ", new->value);
      new = new->next_node_addr; 
    }
  printf("\n");
}

int main()
{
  struct node * head = NULL;
  int size, value;
  int count = 0;

  printf("Enter the no of data stored in the list \n");
  scanf("%d",&size);
  
  while(count < size)
    {
      printf("enter the value to be stored in thr list \n");
      scanf("%d", &value);
      head = push(head, value);
      print_list(head);
      count++;
    }
  while(head != NULL) {
    head = head->next_node_addr;
    free(head);
  }
  printf("The allocate memory for the list is free:\n");
}
