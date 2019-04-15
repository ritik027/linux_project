#include<stdio.h>
#include<stdbool.h>
#include<math.h>

int no_of_processes;
int no_of_processes_executed = 0;
int queue_size = 0;
int total_time = 0;
double average_waiting_time = 0;
double average_turnaround_time = 0;

struct Process
{
	int arrival_time;
	int burst_time;
	int process_id;
	int waiting_time;
	int turnaround_time;
};

void swap(int index1, int index2, struct Process queue[])
{
	struct Process temp = queue[index1];
	queue[index1] = queue[index2];
	queue[index2] = temp;
}

void heapifyUp(struct Process queue[])
{
	int index = queue_size - 1;
	int parent_index = (index - 1)/2;
	while(parent_index >= 0 && queue[parent_index].burst_time > queue[index].burst_time)
	{
		swap(parent_index, index, queue);
		index = parent_index;
		parent_index = (index - 1)/2;
	}
}

void heapifyDown(struct Process queue[])
{
	int index = 0;
	int left_child = 2 * index + 1;
	int right_child = 2 * index + 2;

	while(left_child < queue_size)
	{
		int smaller_child = left_child;
		if((right_child < queue_size) && queue[right_child].burst_time < queue[left_child].burst_time)
		{
			smaller_child = right_child;
		}

		if(queue[index].burst_time < queue[smaller_child].burst_time)
		{
			break;
		}
		else
		{
			swap(index, smaller_child, queue);
		}
		index = smaller_child;
		left_child = 2 * index + 1;
		right_child = 2 * index + 2;
	}
}
void print1(struct Process item);
void pop(struct Process queue[])
{
	struct Process item = queue[0];
	item.waiting_time = total_time - item.arrival_time;
	item.turnaround_time = item.waiting_time + item.burst_time;
	average_waiting_time += item.waiting_time;
	average_turnaround_time += item.turnaround_time;
	print1(item);
	total_time = total_time + item.burst_time + 2;
	queue[0] = queue[queue_size - 1];
	queue_size--;
	heapifyDown(queue);
	//queue[queue_size] = item;
}

void push(struct Process queue[], struct Process item)
{
	queue[queue_size] = item;
	queue_size++;
	heapifyUp(queue);
}

bool isEmptY()
{
	if(queue_size > 0)
		return false;
	else
		return true;
}

bool cmp(struct Process x, struct Process y)
{
	return x.arrival_time > y.arrival_time;
}

void sort(struct Process all_processes[])
{
	for(int i = 0; i < no_of_processes - 1; i++)
	{
		for(int j = 0; j < no_of_processes - i - 1; j++)
		{
			if(cmp(all_processes[j], all_processes[j + 1]))
			{
				struct Process temp = all_processes[j];
				all_processes[j] = all_processes[j + 1];
				all_processes[j + 1] = temp;
			}
		}
	}
}

void input(struct Process all_processes[])
{
	for(int i = 0; i < no_of_processes; i++)
	{
		printf("Enter Arrival time for Process %d\n", (i + 1));
		scanf("%d",&all_processes[i].arrival_time);
		if(all_processes[i].arrival_time <= 0)
		{
			printf("Arrival time cannot be 0 or less than 0\nplease enter again\n");
			i--;
			continue;
		}
		printf("Enter Burst time for Process %d\n", (i + 1));
		scanf("%d",&all_processes[i].burst_time);
		all_processes[i].process_id = i + 1;
		all_processes[i].waiting_time = -1;
		all_processes[i].turnaround_time = -1;
	}
}

int calculateNoOfDigits(int num)
{
	int digits = 0;
	if(num <= 0)
		return 1;
	
	while(num > 0)
	{
		digits += 1;
		num /= 10;
	}
	return digits;
}

void print1(struct Process item)
{
		printf("         P%d",item.process_id);
		for(int j = 0; j < (12 - calculateNoOfDigits(item.process_id)); j++)
		{
			printf(" ");
		}
		printf("%d", item.arrival_time);
		for(int j = 0; j < (16 - calculateNoOfDigits(item.arrival_time)); j++)
		{
			printf(" ");
		}
		printf("%d",item.burst_time);
		for(int j = 0; j < (19 - calculateNoOfDigits(item.burst_time)); j++)
		{
			printf(" ");
		}
		if(item.waiting_time != -1)
		printf("%d", item.waiting_time);
		else
		printf("-");
		
		for(int j = 0;j < (19 - calculateNoOfDigits(item.waiting_time)); j++)
		{
			printf(" ");
		}
		if(item.turnaround_time != -1)
		printf("%d\n", item.turnaround_time);
		else
		printf("-\n");
}

void print(struct Process all_processes[])
{
	printf("\n\n----------------Process in the order of their arrival time-------------------\n\n");
	printf("      Process     Arrival Time      Burst Time       Waiting Time       Turnaround Time\n");
	for(int i = 0; i < no_of_processes; i++)
	{
		print1(all_processes[i]);
	}
	printf("\n\n----------------Process in the order of their execution---------------------\n\n");
	printf("      Process     Arrival Time      Burst Time       Waiting Time       Turnaround Time\n");
}


int main()
{
	
	printf("Enter the no of processes you want in the device queue\n");
	scanf("%d",&no_of_processes);
	
	struct Process all_processes[no_of_processes];
	struct Process queue[no_of_processes];
	input(all_processes);
	sort(all_processes);
	print(all_processes);
	int i = 0;
	while(no_of_processes_executed < no_of_processes)
	{
		while((i < no_of_processes) && all_processes[i].arrival_time <= total_time)
		{
			push(queue, all_processes[i]);
			i++;
		}

		if(!isEmptY())
		{
			pop(queue);
			no_of_processes_executed++;
		}
		else
		{
			total_time++;
		}
	}
	
	printf("\n\nAverage Waiting Time is %.2f", (average_waiting_time/no_of_processes));
	printf("\n\nAverage Turnaround Time is %.2f", (average_turnaround_time/no_of_processes));
	printf("\n\nTotal Time taken by processor is %d\n\n", total_time);
}