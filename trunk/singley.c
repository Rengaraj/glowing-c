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
	  printf(" Now the List is Empty \n");
	  exit(0);
     }
     
     while(new != NULL) {
	  printf("%d, ", new->value);
	  new = new->next_node_addr; 
     }
     printf("\n");
}

struct node *  deleteList(struct node * head, int * value)
{
     struct node * tmp = head;
     *value = tmp->value;
     head = head->next_node_addr;
     free(tmp);
     return head;
     
}

int main()
{
     struct node * head = NULL;
     int size, value;
     int count = 0;
     char ans;

     printf("Enter the no of data stored in the list \n");
     scanf("%d",&size);
     
     while(count < size) {
	  printf("enter the value to be stored in thr list \n");
	  scanf("%d", &value);
	  head = push(head, value);
	  print_list(head);
	  count++;
     }
     printf("do you want TO delete the element ? y or n");
     
     do {
	  scanf("%c",&ans);
     }while(ans == '\n');
     
     if (ans == 'y') {
	  while(head != NULL) {
	       head = deleteList(head, &value);
	       printf("%d is deleted from the list \n", value);
	       print_list(head);
	  }
     }
     
     return 0;
}
