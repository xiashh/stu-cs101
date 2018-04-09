#include <iostream>
#include <string>
#include <regex>
#include <sstream>
#include <cmath>
#include <stdio.h>

using namespace std;

// max heap
template    <class T>
class   maxHeap {
    private:
        int capacity;   // total available space
        int size;       // current used space
        T * heap;       // array to store the data
        void    maintain(int k);
    
    public:
        maxHeap(int cap);
        ~maxHeap();
        int index(T data);  // return the index of data
        int Size();         // return the size
        T   top();     // show the maximum value
        void    pop();      // remove the maximum value
        void    push(T  data);     // insert a new value using bottom up
        void    print();    // print the max heap
};

// implementation
template    <class  T>
maxHeap<T>::maxHeap(int cap) {
    capacity = cap;
    size = 0;
    heap = new T[cap];
    heap[0] = 0;
}

template    <class  T>
maxHeap<T>::~maxHeap() {
    size = 0;
    capacity = 0;
    delete[] heap;
}

template    <class  T>
int maxHeap<T>::index(T data) {
    for (int i = 1; i <= size; i++) {
        if (heap[i] == data) return i;
    }
    return -1;  // not found
}

template    <class  T>
int maxHeap<T>::Size() {
    return size;
}

template    <class  T>
T   maxHeap<T>::top() {
    return heap[1]; // the first element is the root
}

template    <class  T>
void    maxHeap<T>::maintain(int k) {
    int currIndex = k;          // current index
    int lc = currIndex << 1;    // left child
    int rc = lc | 1;            // right child
    T   temp = heap[currIndex];

    if (lc <= size && rc > size && temp < heap[lc]) {
        heap[currIndex] = heap[lc];
        heap[lc] = temp;
        maintain(lc);
    }
    else if (lc <= size && rc <= size && temp < max(heap[lc], heap[rc])) {
        if (heap[lc] > heap[rc]) {
            heap[currIndex] = heap[lc];
            heap[lc] = temp;
            maintain(lc);
        }
        else {
            heap[currIndex] = heap[rc];
            heap[rc] = temp;
            maintain(rc);
        }
    }
    return;
}

template    <class  T>
void    maxHeap<T>::pop() {
    heap[1] = heap[size];
    size--;
    int currIndex = 1;          // current index
    maintain(currIndex);
}

template    <class  T>
void    maxHeap<T>::push(T  data) {
    // check if the heap is full
    // cout << "debug" << (size == capacity) << endl;
    if (size == capacity) {
        T * newHeap = new T[2*size + 1];
        T * temp = heap;
        capacity = 2*size + 1;
        newHeap[0] = 0;
        
        for (int i = 1; i <= size; i++) {
            newHeap[i] = heap[i];
        }
        heap = newHeap;
        delete[] temp;
    }

    size++;
    heap[size] = data;
    
    // maintain the heap using bottom up
    int currIndex = size;          // current index
    int parent = currIndex >> 1;        // parent index

    while (heap[currIndex] > heap[parent] && parent >= 1) {
        T   temp = heap[currIndex];
        heap[currIndex] = heap[parent];
        heap[parent] = temp;
        currIndex = parent;
        parent = currIndex >> 1;
    }
    return;
}

template    <class  T>
void    maxHeap<T>::print() {
    int k = 1;

    for (int i = 0; i <= log2(size); i++) {
        for (int j = 1; j <= pow(2,i); j++, k++) {
            if (k <= size){
                cout << heap[k];
            }
            else {
                cout << "S";
            }
            if (j < pow(2,i))   cout <<' ';
        }
        cout << endl;
    }
}

// min heap
template    <class T>
class   minHeap {
    private:
        int capacity;   // total available space
        int size;       // current used space
        T * heap;       // array to store the data
        void    maintain(int k); // maintain the property
    
    public:
        minHeap(int cap);
        ~minHeap();
        int index(T data);  // return the index of data
        int Size();         // return the size
        T   top();     // show the maximum value
        void    pop();      // remove the minimum value
        void    push(T  data);     // insert a new value using bottom up
        void    print();    // print the max heap
};

// implementation
template    <class  T>
minHeap<T>::minHeap(int cap) {
    capacity = cap;
    size = 0;
    heap = new T[cap];
    heap[0] = 0;
}

template    <class  T>
minHeap<T>::~minHeap() {
    size = 0;
    capacity = 0;
    delete[] heap;
}

template    <class  T>
int minHeap<T>::index(T data) {
    for (int i = 1; i <= size; i++) {
        if (heap[i] == data) return i;
    }
    return -1;  // not found
}

template    <class  T>
int minHeap<T>::Size() {
    return size;
}

template    <class  T>
T   minHeap<T>::top() {
    return heap[1]; // the first element is the root
}

template    <class  T>
void    minHeap<T>::maintain(int k) {
    int currIndex = k;          // current index
    int lc = currIndex << 1;    // left child
    int rc = lc | 1;            // right child
    T   temp = heap[currIndex];

    if (lc <= size && rc > size && temp > heap[lc]) {
        heap[currIndex] = heap[lc];
        heap[lc] = temp;
        maintain(lc);
    }
    else if (lc <= size && rc <= size && temp > min(heap[lc], heap[rc])) {
        if (heap[lc] < heap[rc]) {
            heap[currIndex] = heap[lc];
            heap[lc] = temp;
            maintain(lc);
        }
        else {
            heap[currIndex] = heap[rc];
            heap[rc] = temp;
            maintain(rc);
        }
    }
    return;
}

template    <class  T>
void    minHeap<T>::pop() {
    heap[1] = heap[size];
    size--;
    int currIndex = 1;          // current index
    maintain(currIndex);
    return;
}

template    <class  T>
void    minHeap<T>::push(T  data) {
    // check if the heap is full
    // cout << "debug" << (size == capacity) << endl;
    if (size == capacity) {
        T * newHeap = new T[2*size + 1];
        T * temp = heap;
        capacity = 2*size + 1;
        newHeap[0] = 0;
        
        for (int i = 1; i <= size; i++) {
            newHeap[i] = heap[i];
        }
        heap = newHeap;
        delete[] temp;
    }

    size++;
    heap[size] = data;
    
    // maintain the heap using bottom up
    int currIndex = size;          // current index
    int parent = currIndex >> 1;        // parent index

    while (heap[currIndex] < heap[parent] && parent >= 1) {
        T   temp = heap[currIndex];
        heap[currIndex] = heap[parent];
        heap[parent] = temp;
        currIndex = parent;
        parent = currIndex >> 1;
    }
    return;
}

template    <class  T>
void    minHeap<T>::print() {
    int k = 1;
    
    for (int i = 0; i <= log2(size); i++) {
        for (int j = 1; j <= pow(2,i); j++, k++) {
            if (k <= size){
                cout << heap[k];
            }
            else {
                cout << 'S';
            }
            if (j < pow(2,i))   cout <<' ';
        }
        cout << endl;
    }
}


int main() {
    minHeap<int> *  min = new minHeap<int>(32);
    maxHeap<int> *  max = new maxHeap<int>(32);
    int n = 0;
    string s;

    while (getline(cin, s)) {
        // step 1
        if (n == 0) {
            int item1, item2;
            sscanf(s.c_str(), "%d %d", &item1, &item2);
            if (item1 > item2) {
                min -> push(item1);
                max -> push(item2);
            }
            else {
                min -> push(item2);
                max -> push(item1);
            }
        }
        else {
            int item;
            sscanf(s.c_str(), "%d", &item);
            if (item < max -> top())    max -> push(item);
            else                        min -> push(item);
        }
        // step 2
        int delta = min -> Size() - max -> Size();
        int temp;

        if (delta > 1) {
            temp = min -> top();
            min -> pop();
            max -> push(temp);
        }
        else if (delta < -1) {
            temp = max -> top();
            max -> pop();
            min -> push(temp);
        }

        delta = min -> Size() - max -> Size();
        // calculate the median
        if (delta == 0) {
            int sum = max -> top() + min -> top();
            if (sum % 2 == 0) {
                printf("%d\n", sum / 2);
            }
            else {
                printf("%.1f\n", sum / 2.0);
            }
        }
        else {
            printf("%d\n", delta > 0? min -> top(): max -> top());
        }
        
        // print heap
        min -> print();
        max -> print();

        n++;
    }

    // cout << max -> Size() << endl;
    // min -> print();
    // cout << "=========" << endl;
    // max -> print();

    // return 0;
    // min -> push(1);
    // min -> print();
    // cout << min -> top() << endl;

}