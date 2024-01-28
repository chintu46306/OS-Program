
/*
Write a C program to simulate the
contiguous memory allocation First,
worst, best fit
*/

#include <stdio.h>
#include <stdbool.h>

#define MAX_BLOCKS 100

typedef struct
{
    int id;
    int size;
    int start;
    bool allocated;
} Block;

void allocateFirstFit(Block blocks[], int numBlocks, int size)
{
    for (int i = 0; i < numBlocks; i++)
    {
        if (!blocks[i].allocated && blocks[i].size >= size)
        {
            blocks[i].allocated = true;
            printf("Allocated in block %d using First Fit.\n", blocks[i].id);
            return;
        }
    }
    printf("Unable to allocate using First Fit.\n");
}

void allocateWorstFit(Block blocks[], int numBlocks, int size)
{
    int maxIndex = -1;
    int maxSize = 0;
    for (int i = 0; i < numBlocks; i++)
    {
        if (!blocks[i].allocated && blocks[i].size >= size)
        {
            if (blocks[i].size > maxSize)
            {
                maxSize = blocks[i].size;
                maxIndex = i;
            }
        }
    }
    if (maxIndex != -1)
    {
        blocks[maxIndex].allocated = true;
        printf("Allocated in block %d using Worst Fit.\n", blocks[maxIndex].id);
    }
    else
    {
        printf("Unable to allocate using Worst Fit.\n");
    }
}

void allocateBestFit(Block blocks[], int numBlocks, int size)
{
    int minIndex = -1;
    int minSize = MAX_BLOCKS + 1;
    for (int i = 0; i < numBlocks; i++)
    {
        if (!blocks[i].allocated && blocks[i].size >= size)
        {
            if (blocks[i].size < minSize)
            {
                minSize = blocks[i].size;
                minIndex = i;
            }
        }
    }
    if (minIndex != -1)
    {
        blocks[minIndex].allocated = true;
        printf("Allocated in block %d using Best Fit.\n", blocks[minIndex].id);
    }
    else
    {
        printf("Unable to allocate using Best Fit.\n");
    }
}

int main()
{
    Block blocks[] = {
        {0, 200, 0, false},
        {1, 300, 250, false},
        {2, 400, 500, false},
        {3, 100, 750, false}};

    int numBlocks = sizeof(blocks) / sizeof(blocks[0]);

    int size;

    printf("First Fit:\n");
    size = 150;
    allocateFirstFit(blocks, numBlocks, size);

    printf("\nWorst Fit:\n");
    size = 250;
    allocateWorstFit(blocks, numBlocks, size);

    printf("\nBest Fit:\n");
    size = 200;
    allocateBestFit(blocks, numBlocks, size);

    return 0;
}
