#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>

#define CYLINDERS 5000
int no_of_requests;

void generate_requests(int queue[])
{
	srand(time(0));

	for(int i = 0; i < no_of_requests; i++)
	{
		queue[i] = rand() % 5000;
	}
}

void print_queue(int queue[])
{

	for(int i = 0; i < no_of_requests; i++)
	{
		printf("%d ", queue[i]);
	}
}

int main()
{
	printf("Enter no cylinders requests you want in queue\n");
	scanf("%d", &no_of_requests);

	int queue[no_of_requests];
	generate_requests(queue);
	print_queue(queue);
}