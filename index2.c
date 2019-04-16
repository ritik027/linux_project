#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>

int no_of_requests;
int no_of_cylinders;
int current_head;

void generate_requests(int queue[], int current_head)
{
	srand(time(0));

	for(int i = 0; i < no_of_requests; i++)
	{
		queue[i] = rand() % no_of_cylinders;
		if(queue[i] == current_head)
		{
			queue[i] = rand() % no_of_cylinders;
		}
	}
}

void input_queue(int queue[])
{
	for(int i = 0; i < no_of_requests; i++)
	{
		printf("Enter Request No %d\n", (i + 1));
		scanf("%d",&queue[i]);
		if(queue[i] < 0)
		{
			printf("Request cant be less than 0. Please enter again\n");
			i--;
			continue;
		}
	}
}

void print_queue(int queue[])
{

	printf("\n-----------------The queue of pending requests----------------------\n\n        ");
	for(int i = 0; i < no_of_requests; i++)
	{
		printf("%d ", queue[i]);
	}
	printf("\n\n");
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
	printf("Enter no of cylinders you want in a Hard Disk Drive\n");
	scanf("%d", &no_of_cylinders);
	printf("Enter no of cylinders requests you want in queue\n");
	scanf("%d", &no_of_requests);
	printf("Enter current head value\n");
	scanf("%d", &current_head);
	printf("Enter 1 if you want to give pending requests to queue and 2 if you want to give randomized request\n");
	int queue[no_of_requests];
	int ch;
	scanf("%d", &ch);
	switch(ch)
	{
		case 1:
		input_queue(queue);
		break;
		case 2:
		generate_requests(queue, current_head);
		break;
	}
	print_queue(queue);
	printf("Total Distance moved by Disk Arm is when FCFS disk scheduling algorithm followed is%d\n",calculate_total_distance(queue));
}