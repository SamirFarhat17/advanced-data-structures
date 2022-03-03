
#ifndef SORT_H
#define SORT_H
#include <stdlib.h>
using namespace std;

void insertSortHelper(int left, int right, int a[]) {
    int j, key;
    for(int i = left + 1; i <= right; i++) {
            j = i - 1;
            key = a[i];

            while(j >= left && a[j] > key) {
                a[j + 1] = a[j];
                j--;
            }
            a[j + 1] = key;
        }
}

void mergeHelper(int key, int left, int mid, int right, int a_tmp[], int a[]) {
    int p = left;
    int j = mid;
    for(key = left; key < right; key++) {
        if(j < right && p < mid) {
            if(a_tmp[p] < a[j]) {
                a[key] = a_tmp[p++];
            } else {
                a[key] = a[j++];
            }
            continue;
        }

        if(j >= right ) {
            a[key] = a_tmp[p++];
        } else if(p >= mid) {
            break;
        }
    }
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

    else insertSortHelper(l, r, a);
}

// Improved performance by factor of ~2
void simpleTimsort(int a[], int a_tmp[], int n) {
    // Variable initialization
    int minrunsize = 32, num_in_stack = 0;
    int runstack[n / 32];
    runstack[num_in_stack] = 0;

    int j, left, mid, right, key;
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

            // collapse the stack of runs as follows: While num_in_stack > 2
            while(penultimate <= last && num_in_stack > 2) {
                // Merge the last two runs
                left = runstack[num_in_stack - 2];
                mid = runstack[num_in_stack - 1];
                right = i;

                for(int p = mid - 1; p >= left; p--) {
                    a_tmp[p] = a[p];
                }

                mergeHelper(key, left, mid, right, a_tmp, a);

                num_in_stack--;
                runstack[num_in_stack] = i;
                penultimate = runstack[num_in_stack - 1] - runstack[num_in_stack - 2];
                last = runstack[num_in_stack] - runstack[num_in_stack - 1];
            }
        }

    }
    // if i gets to n-1, increment num_in_stack and set runstack[num_in_stack] to n
    num_in_stack++;
    runstack[num_in_stack] = n;

    //  collapse the stack of runs as follows: While num_in_stack > 1
    while(num_in_stack > 1) {
        // Merge the last two runs
        // (starting at runstack[num_in_stack-2] and runstack[num_in_stack - 1]);
        left = runstack[num_in_stack - 2];
        mid = runstack[num_in_stack - 1];
        right = n;

        for(int p = mid - 1; p >= left; p--) {
            a_tmp[p] = a[p];
        }

        mergeHelper(key, left, mid, right, a_tmp, a);

        num_in_stack--;
        runstack[num_in_stack] = n;
    }
}

#endif
