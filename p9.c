/*
Write a program to find safe
sequences, WAP To Deadlock
prevention 
*/

#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESS 10
#define MAX_RESOURCE 10

bool findSafeSequence(int n, int m, int available[], int maximum[][MAX_RESOURCE], int allocation[][MAX_RESOURCE])
{
    int work[m], finish[n], safeSequence[n];
    int count = 0;

    for (int i = 0; i < m; i++)
        work[i] = available[i];

    for (int i = 0; i < n; i++)
        finish[i] = 0;

    while (count < n)
    {
        bool found = false;
        for (int i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                bool canAllocate = true;
                for (int j = 0; j < m; j++)
                {
                    if (maximum[i][j] - allocation[i][j] > work[j])
                    {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate)
                {
                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];

                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }

        if (!found)
            break;
    }

    if (count == n)
    {
        printf("Safe Sequence exists: ");
        for (int i = 0; i < n; i++)
            printf("%d ", safeSequence[i]);
        printf("\n");
        return true;
    }
    else
    {
        printf("No Safe Sequence exists.\n");
        return false;
    }
}

int main()
{
    int n, m;
    int available[MAX_RESOURCE];
    int maximum[MAX_PROCESS][MAX_RESOURCE];
    int allocation[MAX_PROCESS][MAX_RESOURCE];

    printf("Enter the number of processes and resource types: ");
    scanf("%d %d", &n, &m);

    printf("Enter the available resources: ");
    for (int i = 0; i < m; i++)
        scanf("%d", &available[i]);

    printf("Enter the maximum resource allocation:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            scanf("%d", &maximum[i][j]);
    }

    printf("Enter the current resource allocation:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);
    }

    findSafeSequence(n, m, available, maximum, allocation);

    return 0;
}
