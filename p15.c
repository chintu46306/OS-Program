
/*
Write a program to simulate OPTIMAL
page replacement algorithm Ms.
*/

#include <stdio.h>

int main() {
    int capacity;
    printf("Enter the number of frames: ");
    scanf("%d", &capacity);

    int n;
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    int frame[capacity];
    int page_faults = 0;

    for (int i = 0; i < capacity; i++) {
        frame[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int page_found = 0;

        for (int j = 0; j < capacity; j++) {
            if (frame[j] == page) {
                page_found = 1;
                break;
            }
        }

        if (!page_found) {
            int farthest = i + 1;
            int replace_index = 0;

            for (int j = 0; j < capacity; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frame[j] == pages[k]) {
                        if (k > farthest) {
                            farthest = k;
                            replace_index = j;
                        }
                        break;
                    }
                }

                if (k == n) {
                    replace_index = j;
                    break;
                }
            }

            frame[replace_index] = page;
            page_faults++;
        }

        printf("Page: %d\nFrame: ", page);
        for (int j = 0; j < capacity; j++) {
            printf("%d ", frame[j]);
        }
        printf("\n");
    }

    printf("Page Faults: %d\n", page_faults);

    return 0;
}
