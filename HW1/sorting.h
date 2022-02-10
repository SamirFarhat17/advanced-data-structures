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
    // you program this.  a_tmp can be used for merging
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


void mergeSortblend(int a[], int a_tmp[], int l, int r) {
    // You program this

}

void checkInorder(int a[], int left, int right) {
    //checks  that a is in order from left to right
    for (int i = left; i < right; i++) {
        if (a[i] > a[i + 1]) {
            int tmp = i;
        }
    }
}
void simpleTimsort(int a[], int a_tmp[], int n) {
    //You program this

}

#endif