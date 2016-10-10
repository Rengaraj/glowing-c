/** This program is to copy string in 
 * a line of code.
 *
 **/

#include<stdio.h>

#define MAX 256

void str_cp(char *src, char *dst)
{
	while((*dst++ = *src++) != '\0');
}

int main()
{

	char input_buffer[MAX];
	char dest_buffer[MAX];
	
	printf("Enter the string: ");
	fgets(input_buffer, MAX, stdin);
	printf("input buffer %s\n", input_buffer);
	str_cp(input_buffer, dest_buffer);
	printf("Destination Buffer %s\n", dest_buffer);
}
