
/*
WAP to avoid deadlock avoidance
using Bankers algorithms
*/

#include <stdio.h>

#define MAX_PROCESS 10
#define MAX_RESOURCE 10

int main()
{
    int i, j, k;
    int n, m;

    int allocation[MAX_PROCESS][MAX_RESOURCE];
    int max_claim[MAX_PROCESS][MAX_RESOURCE];
    int available[MAX_RESOURCE];
    int need[MAX_PROCESS][MAX_RESOURCE];
    int finish[MAX_PROCESS] = {0};

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of resources: ");
    scanf("%d", &m);

    printf("Enter the allocation matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the maximum claim matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &max_claim[i][j]);
        }
    }

    printf("Enter the available resources:\n");
    for (i = 0; i < m; i++)
    {
        scanf("%d", &available[i]);
    }

    // Calculate the need matrix
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            need[i][j] = max_claim[i][j] - allocation[i][j];
        }
    }

    // Safety algorithm
    int safe_sequence[MAX_PROCESS];
    int count = 0;
    int safe = 0;

    while (count < n)
    {
        safe = 0;
        for (i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                int resource_available = 1;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > available[j])
                    {
                        resource_available = 0;
                        break;
                    }
                }
                if (resource_available)
                {
                    for (k = 0; k < m; k++)
                    {
                        available[k] += allocation[i][k];
                    }
                    finish[i] = 1;
                    safe_sequence[count] = i;
                    count++;
                    safe = 1;
                }
            }
        }
        if (!safe)
        {
            break;
        }
    }

    if (count == n)
    {
        printf("Safe sequence found: ");
        for (i = 0; i < n; i++)
        {
            printf("%d ", safe_sequence[i]);
        }
        printf("\n");
    }
    else
    {
        printf("Unsafe state detected.\n");
    }

    return 0;
}
