/*Write a program to simulate FIFO and
LRU page replacement algorithm */

#include<stdio.h>

void FIFO(int pages[], int n, int capacity) {
    int frame[capacity], count = 0, page_faults = 0, front = 0, rear = 0, i, j, flag;

    for(i = 0; i < n; i++) {
        flag = 0;
        for(j = 0; j < capacity; j++) {
            if(frame[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        if(flag == 0) {
            page_faults++;
            frame[rear] = pages[i];
            rear = (rear + 1) % capacity;

            if(count < capacity)
                count++;
            else {
                front = (front + 1) % capacity;
                rear = (rear + 1) % capacity;
            }
        }
    }

    printf("FIFO Page Replacement Algorithm:\n");
    printf("Page Faults: %d\n", page_faults);
}

void LRU(int pages[], int n, int capacity) {
    int frame[capacity], count = 0, page_faults = 0, i, j, k, flag, least_recently_used;

    for(i = 0; i < n; i++) {
        flag = 0;
        for(j = 0; j < count; j++) {
            if(frame[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        if(flag == 0) {
            page_faults++;
            if(count < capacity) {
                frame[count] = pages[i];
                count++;
            }
            else {
                least_recently_used = 0;
                for(k = 1; k < capacity; k++) {
                    if(frame[k] < frame[least_recently_used])
                        least_recently_used = k;
                }
                frame[least_recently_used] = pages[i] ;
            }
        }
    }

    printf("LRU Page Replacement Algorithm:\n");
    printf("Page Faults: %d\n", page_faults);
}

int main() {
    int n, capacity;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];

    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &capacity);

    FIFO(pages, n, capacity);
    LRU(pages, n, capacity);

    return 0;
}
