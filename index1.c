#include<stdio.h>
#include<stdbool.h>

int no_of_processes;
int queue_size = 0;

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

void pop(struct Process queue[])
{
	struct Process item = queue[0];
	queue[0] = queue[size - 1];
	size--;
	heapifyDown(queue);
}

void push(struct Process queue[], struct Process item)
{
	queue[size] = item;
	size++;
	heapifyUp(queue);
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

		if(queue[index] < queue[smaller_child])
		{
			break;
		}
		else
		{
			swap(index, smaller_child);
		}
		index = smaller_child;
		left_child = 2 * index + 1;
		right_child = 2 * index + 2;
	}
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
		printf("Enter Burst time for Process %d\n", (i + 1));
		scanf("%d",&all_processes[i].burst_time);
		all_processes[i].process_id = i + 1;
	}
}

void print(struct Process all_processes[])
{
	for(int i = 0; i < no_of_processes; i++)
	{
		printf("pid - %d      AT - %d\n", all_processes[i].process_id, all_processes[i].arrival_time);
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
}