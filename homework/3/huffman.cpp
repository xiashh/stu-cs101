#include <string>
#include <regex>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>

using namespace std;

/* data structure */
class Node
{
    private:
        unsigned int frequency;
        unsigned char min_key;
        unsigned char key;
        Node * left_char;
        Node * right_char;
    
    public:
        Node () {}
        Node (unsigned int f, unsigned char c): \
            frequency (f), min_key (c), key (c) {}
        Node (Node * lc, Node * rc);
        bool operator < (const Node &);
        void add_to_cookbook (string * book, string code);
}

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

/* record frequencies of every char */
static unsigned int frequencies[256];

/* indicate to decoding or encoding */
static unsigned int decode_or_encode;

int decide_action ();
void cal_frequency ();
void print_frequency ();
void compress ();
void decompress ();

int main () {
    decide_action ();

    if (decode_or_encode == 1)
    {
        compress ();
    }
    else if (decode_or_encode == 0)
    {
        decompress ();
    }
    
    minHeap<int> * min = new minHeap<int>(256);

}

/* decide whether decode(0) the data or encode(1) the data */
int decide_action ()
{   
    unsigned char c;
    string arg;
    cin >> noskipws;

    for (int i = 0; i < 6; i++)
    {
        cin >> c;
        arg.append(1, c);
    }
    
    if (arg == "DECODE") decode_or_encode = 0;
    else if (arg == "ENCODE") decode_or_encode = 1;
}

/* compress the data and print it */
void compress ()
{
    cal_frequency ();
    print_frequency ();
    printf("now we will compress the data.\n");
}

/* calculate the frequencies of data */
void cal_frequency ()
{
    unsigned char c;

    for (int i = 0; i < 256; i++)
    {
        frequencies[i] = 0;
    }

    while (cin >> c)
    {
        frequencies[c]++;
    }
}

/* print the frequency of every char */
void print_frequency ()
{
    for (int i = 0; i < 256; i++)
    {
        printf ("frequency of char %c = %d\n", i, frequencies[i]);
    }
}

/* decompress the data and print it */
void decompress ()
{
    printf("now we will decompress the data.\n");
}

/* implementation of Node */
Node::Node (Node * lc, Node rc)
{
    frequency = lc->frequency + rc->frequency;
    left_char = lc;
    right_char = rc;
    min_key = lc->min_key > rc->min_key? rc->min_key: lc->min_key;
}

bool Node::operator < (const Node &op)
{
    if (frequency < op.frequency)
        return True;
    else if (frequency == op.frequency)
        return min_key < op.min_key;
    else
        return False;
}

void Node::add_to_cookbook (string * book, string code)
{
    if (left_char == NULL && right_char == NULL)
    {
        book[key] = code;
    }
    else if ()
}

/* implementation of min heap */
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