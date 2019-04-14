#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>

#define CYLINDERS 5000
int no_of_requests;
int current_head;

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

int calculate_total_distance(int queue[])
{
	int total_distance = abs(current_head - queue[0]);
	for(int i = 0; i < no_of_requests - 1; i++)
	{
		total_distance += (abs(queue[i] - queue[i + 1]));
	}
	return total_distance;
}

int main()
{
	printf("Enter no cylinders requests you want in queue\n");
	scanf("%d", &no_of_requests);
	printf("Enter current head value\n");
	scanf("%d", &current_head);
	int queue[no_of_requests];
	generate_requests(queue);
	print_queue(queue);
	printf("total distance moved by disk arm is %d\n",calculate_total_distance(queue));
}