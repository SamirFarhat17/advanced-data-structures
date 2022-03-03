#ifndef BINARY_HEAP_H_
#define BINARY_HEAP_H_

using namespace std;

const int MAX_SIZE = 100000; //the maximum amount of elements our heap should have.

template <typename Object>
class Heap {
  public:
    Heap() {
        elements = 0;
    };

    void insert(Object* item) { // Add the object pointer item to the heap
        if (elements >= MAX_SIZE) {
            cout << "Heap is full; can't insert " << endl;
            // FILL IN THE REST
            return;
        }
        // Insert then upHeap
        // Increment the number of elements
        elements++;
        // Place the object in the array correcting the position
        array[elements - 1] = item;  
        array[elements - 1]->position = elements - 1; 
        // upHeap
        upHeap(array[elements-1]->position);

    };

    Object* remove_min() {
        if (elements == 0) {
            cout << "empty heap error, can't delete" << endl;
        }
        Object* temp = array[0];
        // FILL IN THE REST
        // Shrink arraysize by 1
        elements--;
        // Remove element in array[0] and move largest element into array[0] 
        temp->position = -1;
        array[0] = array[elements];
        // correcting position
        array[0]->position = 0;
        // downHeap
        downHeap(array[0]->position);
        return temp;
    };       // Remove the smallest element in the heap & restructure heap

    void decreaseKey(int pos, int val) { // Decreases Key in pos to val
        // Find key and change value, upheap
        array[pos]->key = val;
        upHeap(array[pos]->position);
    };


    bool IsEmpty() const {
        return (elements <= 0);
    };
    bool IsFull() const {
        return (elements >= MAX_SIZE );
    };
    int count() const {
        return elements;
    };
    Object* value(int pos) const { //return a pointer to an object in heap position
        if (pos >= elements) {
            cout << "Out of range of heap " << pos << "elements " << elements << endl;
        }
        return (array[pos]);
    };

  protected:
    Object* array[MAX_SIZE];
    int elements;       //  how many elements are in the heap

  private:

    void downHeap(int pos) { 
        // starting with element in position pos, sift it down the heap
        // until it is in final min-heap position
        Object* item = array[pos];
        // Slide 29 pseudocode
        int left_child = (2 * pos + 1);
        while(left_child <= elements) {
            if(left_child < elements-1 && array[left_child]->key > array[left_child+1]->key) {
                left_child = left_child + 1;
            }
            if(array[pos]->key > array[left_child]->key) {
                array[pos] = array[left_child];
                array[pos]->position = pos;
                
                array[left_child] = item;
                array[left_child]->position = left_child;
                pos = left_child;

                left_child = (2 * pos + 1);

            }
            else break;
        }

    };

    void upHeap(int new_pos) { // starting with element in position int, sift it up the heap
        // until it is in final min-heap position
        Object* item = array[new_pos];
        // Slide 27 pseudocode
        if(new_pos == 0) return;
        if(array[new_pos]->key < array[(new_pos - 1) / 2]->key) {
            Object* temp = array[(new_pos - 1) / 2];
            array[(new_pos - 1) / 2] = item;
            array[(new_pos - 1) / 2]->position = (new_pos - 1) / 2;

            array[new_pos] = temp;
            array[new_pos]->position = new_pos;

            new_pos = (new_pos - 1) / 2;
            upHeap(new_pos);
        }
        else return;
    };
};
#endif