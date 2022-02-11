#ifndef SORT_H
#define SORT_H

#include <stdlib.h>

using namespace std;

static int swapCount = 0;

void swap(int* a, int* b) {
    //swapCount++;
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

/* See Knuth's shuffles https://en.wikipedia.org/wiki/Random_permutation */
// slowest O(n^2)
void insertionsort(int a[],  int n) {
    int key;
    int reference;

    for (int i = 1; i < n; i++) {
        key = a[i];
        reference = i - 1;

        while (a[reference] > key && reference >= 0) {
            a[reference + 1] = a[reference];
            reference = reference - 1;
        }
        a[reference + 1] = key;
    }
}

// Order Theta(NlogN) sorting
void mergeSort(int a[], int a_tmp[], int l, int r) {
    int i, j;
    if(r > l) {
        int mid = l + (r - l) / 2;

        mergeSort(a, a_tmp, l, mid);
        mergeSort(a, a_tmp, mid + 1, r);

        for(i = mid + 1; i > l; i--) {
            a_tmp[i - 1] = a[i - 1];
        }

        for(j = mid; j < r; j++) {
            a_tmp[r + mid - j] = a[j + 1];
        }

        for(int n = l; n <= r; n++) {
            if(a_tmp[i] < a_tmp[j]) a[n] = a_tmp[i++];
            else a[n] = a_tmp[j--];
        }
    }
}

// Improved MergeSort by wielding insertionSort
void mergeSortblend(int a[], int a_tmp[], int l, int r) {
    int elements = r - l;
    int i, j, n;
    if(elements <= 0) return;

    if(elements >= 32) {
        int m = l + (r - l) / 2;
        mergeSortblend(a, a_tmp, l, m);
        mergeSortblend(a, a_tmp, m + 1, r);

        for(i = m + 1; i > l; i--) {
            a_tmp[i - 1] = a[i - 1];
        }
        for(j = m; j < r; j++) {
            a_tmp[r + m - j] = a[j + 1];
        }
        for(n = l; n <= r; n++) {
            if(a_tmp[i] < a_tmp[j]) a[n] = a_tmp[i++];
            else a[n] = a_tmp[j--];
        }
    }

    else {
        for(i = l + 1; i <= r; i++) {
            j = i - 1;
            n = a[i];

            while(j >= l && a[j] > n) {
                a[j + 1] = a[j];
                j--;
            }
            a[j + 1] = n;
        }
    }
}

void checkInorder(int a[], int left, int right) {
    //checks  that a is in order from left to right
    for (int i = left; i < right; i++) {
        if (a[i] > a[i + 1]) {
            int tmp = i;
        }
    }
}
int findIncrement(int a[], int index) {
    int count = 0;
    while(a[index] > a[index + 1]) {
        count++;
        index++;
    }
    return count;
}

void timsort(int a[], int a_tmp[], int n) {
    int minrunsize = 32, num_in_stack = 0;
    int runstack[n / minrunsize];
    int runsize, new_run_index;
    for(int i = 0; i < n; i++) {
        runsize = findIncrement(a, i);
        i += runsize;
        if(runsize < minrunsize) {
            // insert element of a[i] into the run
            runstack[num_in_stack] = a[i];
            continue;
        }
        if(runsize >= minrunsize) {
            num_in_stack++;
            new_run_index = i + runsize;
        }

    }

}

void simpleTimsort(int a[], int a_tmp[], int n) {
    int minrunsize = 32, num_in_stack = 0;
    int runstack[n / 32];
    runstack[num_in_stack] = 0;
    int j, p, left, mid, right, key;
    int penultimate, last;

    for(int i = 1; i < n; i++) {
        if(a[i] > a[i - 1]) {
            continue;
        }

        // If run length is less than minrunsize, insert element of a[i]
        if( (i - runstack[num_in_stack]) < minrunsize) {
            // Insertion
            key = a[i];
            j = i - 1;

            while (j >= runstack[num_in_stack] && a[j] > key) {
                a[j + 1] = a[j];
                j = j - 1;
            }

            a[j + 1] = key;

            continue;
        }
        // If run length is greater than or equal to minrunsize, increment num_in_stack,
        // store the index of the new run into runstack[num_in_stack].
        else if((i - runstack[num_in_stack]) >= minrunsize) {
            num_in_stack++;
            runstack[num_in_stack] = i;

            penultimate = runstack[num_in_stack - 1] - runstack[num_in_stack - 2];
            last = runstack[num_in_stack] - runstack[num_in_stack - 1];

            while(penultimate <= last && num_in_stack > 1) {
                // Merge
                left = runstack[num_in_stack - 2];
                mid = runstack[num_in_stack - 1];
                right = i;

                for(p = mid - 1; p >= left; p--) {
                    a_tmp[p] = a[p];
                }

                p = left;
                j = mid;

                for(key = left; key < right; key++) {
                    if(p < mid && j < right) {
                        if(a_tmp[p] < a[j]) {
                            a[key] = a_tmp[p++];
                        } else {
                            a[key] = a[j++];
                        }
                    } else {
                        if(j >= right ) {
                            a[key] = a_tmp[p++];
                        } else if(p >= mid) {
                            break;
                        }
                    }
                }

                num_in_stack--;
                runstack[num_in_stack] = i;

                penultimate = runstack[num_in_stack - 1] - runstack[num_in_stack - 2];
                last = runstack[num_in_stack] - runstack[num_in_stack - 1];
            }
        }

    }

    num_in_stack++;
    runstack[num_in_stack] = n;

    while(num_in_stack >= 2) {
        // Merge
        left = runstack[num_in_stack - 2];
        mid = runstack[num_in_stack - 1];
        right = n;

        for(p = mid - 1; p >= left; p--) {
            a_tmp[p] = a[p];
        }

        p = left;
        j = mid;

        for(key = left; key < right; key++) {
            if(p < mid && j < right) {
                if(a_tmp[p] < a[j]) {
                    a[key] = a_tmp[p++];
                } else {
                    a[key] = a[j++];
                }
            } else {
                if(j >= right ) {
                    a[key] = a_tmp[p++];
                } else if(p >= mid) {
                    break;
                }
            }
        }

        num_in_stack--;
        runstack[num_in_stack] = n;
    }
}

#endif