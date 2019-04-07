#include<stdio.h>

int no_of_processes;

struct Process
{
	int arrival_time;
	int burst_time;
	int process_id;
	int waiting_time;
	int turnaround_time;
};

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
int main()
{
	
	printf("Enter the no of processes you want in the device queue\n");
	scanf("%d",&no_of_processes);
	
	struct Process all_processes[no_of_processes];
	input(all_processes);
}