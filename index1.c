#include<stdio.h>
#include<stdbool.h>
int no_of_processes;

struct Process
{
	int arrival_time;
	int burst_time;
	int process_id;
	int waiting_time;
	int turnaround_time;
};
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
	input(all_processes);
	sort(all_processes);
	print(all_processes);
}