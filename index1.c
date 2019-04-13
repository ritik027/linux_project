#include<stdio.h>
#include<stdbool.h>

int no_of_processes;
int no_of_processes_executed = 0;
int queue_size = 0;
int total_time = 0;

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

void pop(struct Process queue[])
{
	struct Process item = queue[0];
	item.waiting_time = total_time - item.arrival_time;
	item.turnaround_time = item.waiting_time + item.burst_time;
	total_time = total_time + item.burst_time + 2;
	queue[0] = queue[queue_size - 1];
	queue_size--;
	heapifyDown(queue);
	queue[queue_size] = item;
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
			printf("Arrival time cant be 0 or less than 0\nplease enter again");
			i--;
			continue;
		}
		printf("Enter Burst time for Process %d\n", (i + 1));
		scanf("%d",&all_processes[i].burst_time);
		all_processes[i].process_id = i + 1;
	}
}

void print(struct Process all_processes[])
{
	for(int i = 0; i < no_of_processes; i++)
	{
		printf("pid - %d      AT - %d   BT - %d\n", all_processes[i].process_id, all_processes[i].arrival_time, all_processes[i].burst_time);
	}
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
	double average_waiting_time = 0;
	double average_turnaround_time = 0;
	for(int i = no_of_processes - 1; i >= 0; i--)
	{
		printf("pid- %d  Arr time- %d  Wt- %d TT- %d\n", queue[i].process_id, queue[i].arrival_time,queue[i].waiting_time,queue[i].turnaround_time);
		average_waiting_time += queue[i].waiting_time;
		average_turnaround_time += queue[i].turnaround_time;
	}
	average_turnaround_time /= no_of_processes;
	average_waiting_time /= no_of_processes;
	printf("average waiting time- %f\naverage turnaround time- %f\ntotal time- %d", average_waiting_time, average_turnaround_time, total_time);
}