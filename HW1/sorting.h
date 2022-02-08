#ifndef SORT_H
#define SORT_H

#include <stdlib.h>

using namespace std;

static int swapCount = 0;

void swap(int* a, int* b)
{
    //swapCount++;
    int temp;
    temp = *a; 
    *a = *b; 
    *b = temp; 
}


/* See Knuth's shuffles https://en.wikipedia.org/wiki/Random_permutation */



void insertionsort(int a[],  int n)
{ 
// You program this
}



// Order Theta(NlogN) sorting


void mergeSort(int a[], int a_tmp[], int l, int r)
{
    // you program this.  a_tmp can be used for merging 
  }

// 
void mergeSortblend(int a[], int a_tmp[], int l, int r)
{
 // You program this
}

void checkInorder(int a[],int left, int right){
  //checks  that a is in order from left to right
  for (int i = left;i <right; i++){
    if (a[i] > a[i+1]){
      int tmp = i;
    }
  }
}
void simpleTimsort(int a[], int a_tmp[], int n)
{ 
   //You program this

}// end function





#endif 
