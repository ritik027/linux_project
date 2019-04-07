#include<stdio.h>
int main()
{
	int no_of_processes;
	
	printf("Enter the no of processes you want in the device queue\n");
	no_of_processes = scanf("%d",&no_of_processes);
	
	int arrival_time[no_of_processes];
	int burst_time[no_of_processes];

	for(int i = 0; i < no_of_processes; i++)
	{
		printf("Enter Arrival time for Process %d\n", (i + 1));
		scanf("%d",&arrival_time[i]);
		printf("Enter Burst time for Process %d\n", (i + 1));
		scanf("%d",&burst_time[i]);
	}

	
}