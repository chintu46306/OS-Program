
/*
Write a C program to simulate the
CPU scheduling algorithms to find
turnaround time and waiting time for
the following scheduling- Multilevel 
*/

#include <stdio.h>

struct Process
{
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
    int turnaroundTime;
    int waitingTime;
};

void multilevelScheduling(struct Process processes[], int n)
{
    // First-come, first-served (FCFS) scheduling
    int currentTime = 0;
    for (int i = 0; i < n; i++)
    {
        if (currentTime < processes[i].arrivalTime)
        {
            currentTime = processes[i].arrivalTime;
        }
        processes[i].waitingTime = currentTime - processes[i].arrivalTime;
        currentTime += processes[i].burstTime;
        processes[i].turnaroundTime = currentTime - processes[i].arrivalTime;
    }

    // Priority scheduling
    int remainingProcesses = n;
    while (remainingProcesses > 0)
    {
        int highestPriority = 9999; // Assume a high priority value
        int highestPriorityIndex = -1;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].priority != -1 && processes[i].priority < highestPriority &&
                processes[i].arrivalTime <= currentTime)
            {
                highestPriority = processes[i].priority;
                highestPriorityIndex = i;
            }
        }
        if (highestPriorityIndex == -1)
        {
            currentTime++;
            continue;
        }

        if (currentTime < processes[highestPriorityIndex].arrivalTime)
        {
            currentTime = processes[highestPriorityIndex].arrivalTime;
        }
        processes[highestPriorityIndex].waitingTime += currentTime - processes[highestPriorityIndex].arrivalTime;
        currentTime += processes[highestPriorityIndex].burstTime;
        processes[highestPriorityIndex].turnaroundTime = currentTime - processes[highestPriorityIndex].arrivalTime;
        processes[highestPriorityIndex].priority = -1;
        remainingProcesses--;
    }
}

void displayResults(struct Process processes[], int n)
{
    printf("PID\tArrival Time\tBurst Time\tPriority\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrivalTime,
               processes[i].burstTime, processes[i].priority, processes[i].turnaroundTime,
               processes[i].waitingTime);
    }
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    printf("Enter process details:\n");
    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i + 1;
        printf("Process %d:\n", processes[i].pid);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);
        printf("Priority: ");
        scanf("%d", &processes[i].priority);
    }

    multilevelScheduling(processes, n);
    displayResults(processes, n);

    return 0;
}
