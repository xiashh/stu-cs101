#include <string>
#include <regex>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include "stdint.h"

using namespace std;

/* data structure */
class Node
{
    private:
        uint32_t frequency;
        unsigned char min_key;
        unsigned char key;
        Node * left_char;
        Node * right_char;
    
    public:
        Node () {}
        Node (uint32_t f, unsigned char c): \
            frequency (f), min_key (c), key (c) {}
        Node (Node * lc, Node * rc);
        bool operator < (const Node &);
        bool operator > (const Node &);
        void add_to_codebook (string code);
        // for debugging
        uint32_t get_f ();
        unsigned char get_c ();
};

template    <class T>
class   minHeap {
    private:
        int capacity;   // total available space
        int size;       // current used space
        T ** heap;       // array to store the data
        void    maintain(int k); // maintain the property
    
    public:
        minHeap();
        ~minHeap();
        int get_size ();         // return the size
        T   *top();     // show the maximum value
        void    pop();      // remove the minimum value
        void    push(T * data);     // insert a new value using bottom up
        void    print();    // print the max heap        
};

/* record frequencies of every char */
static uint32_t frequencies[256];

/* indicate to decoding or encoding */
static uint32_t decode_or_encode;

/* code book */
static string book[256];

int decide_action ();
void cal_frequency ();
void print_frequency ();
void compress ();
void decompress ();
Node * build_huffman_tree ();
void print_codebook (string *); 
void print_uncompressed_data ();
uint32_t little_endian(uint32_t );

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
    
    minHeap<Node> * min = new minHeap<Node>;

}

/* decide whether decode(0) the data or encode(1) the data */
int decide_action ()
{   
    unsigned char c;
    string arg;
    cin >> noskipws;

    decode_or_encode = -1;
    for (int i = 0; i < 6; i++)
    {
        cin >> c;
        arg.append(1, c);
        frequencies[c]++;
    }
    if (arg == "DECODE") decode_or_encode = 0;
    else if (arg == "ENCODE") decode_or_encode = 1;
}

/* compress the data and print it */
void compress ()
{
    cal_frequency ();
    // print_frequency ();
    Node * tree_root = build_huffman_tree ();
    string code;

    if (tree_root != NULL)
        tree_root->add_to_codebook (code);
    // print_codebook (book);
    print_uncompressed_data ();

}

/* calculate the frequencies of data */
void cal_frequency ()
{
    for (int i = 0; i < 256; i++)
    {
        frequencies[i] = 0;
    }

    unsigned char c;
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
        if (frequencies[i] == 0)    continue;
        printf ("frequency of char %c = %d\n", i, frequencies[i]);
    }
}

/* print codebook for debugging */
void print_codebook (string * book)
{
    for (int i = 0; i < 256; i++)
    {
        if (frequencies[i] == 0)    continue;
        printf("char:%c   Freq:%d   ", i, frequencies[i]);
        cout << "code: " << book[i] << endl;
    }
    
}

/* print the uncompressed data */
void print_uncompressed_data ()
{
    cout <<"HUFFMAN"<<'\0';

    for(unsigned int i = 0; i < 256; i++){
        printf("%c",(char) (0x000000ff & frequencies[i]));
        printf("%c",(char) ((0x0000ff00 & frequencies[i]) >> 8));
        printf("%c",(char) ((0x00ff0000 & frequencies[i]) >> 16));
        printf("%c",(char) ((0xff000000 & frequencies[i]) >> 24));
    }

    unsigned char c;
    unsigned int bits_num = 0;
    string bit_sequencies ="";
    string byte = "";
    unsigned char num = 0;
    cin.clear ();
    cin.seekg (0);
    cin >> noskipws;

    for (int i = 0; i < 6; i++)
    {
        cin >> c;
    }

    while (cin>>c)
    {
        bit_sequencies += book[c];
    }    

    if (bit_sequencies.size () % 8 > 0)
    {
        unsigned int r = 8 - bit_sequencies.size () % 8;
        bit_sequencies.append (r, '0');
    }

    while (bit_sequencies.size () > 0)
    {
        byte = bit_sequencies.substr (0,8);
        bit_sequencies.erase (0,8);

        for (int i = 0; i < 8; i++)
        {
            if (byte[i] == '1')
                num = num | (0x01 << i);
        }
        printf("%c", num);
        num = 0;
    }
}

/* build the huffman tree according to frequencies */
Node * build_huffman_tree ()
{   
    Node * current_node;
    minHeap<Node>  heap;
    
    for (int i =0; i < 256; i++)
    {
        if (frequencies[i] == 0)    continue;
        current_node = new Node(frequencies[i], i);
        heap.push(current_node);
    }

    Node * node1;
    Node * node2;
    Node * node12;

    while (heap.get_size () > 1)
    {
        node1 = heap.top ();
        heap.pop ();
        node2 = heap.top ();
        heap.pop ();
        node12 = new Node(node2, node1);
        heap.push (node12);
    }                 
    
    return heap.top ();
}

/* decompress the data and print it */
void decompress ()
{
    printf("now we will decompress the data.\n");
    
}

/* implementation of Node */
Node::Node (Node * lc, Node * rc)
{
    frequency = lc->frequency + rc->frequency;
    left_char = lc;
    right_char = rc;
    min_key = lc->min_key > rc->min_key? rc->min_key: lc->min_key;
}

/* overload the operator > */
bool Node::operator > (const Node &op)
{
    if (frequency > op.frequency)
        return true;
    else if (frequency == op.frequency)
        return min_key > op.min_key;
    else
        return false;
}

bool Node::operator < (const Node &op)
{
    if (frequency < op.frequency)
        return true;
    else if (frequency == op.frequency)
        return min_key < op.min_key;
    else
        return false;
}


void Node::add_to_codebook (string code)
{
    if (left_char == NULL && right_char == NULL)
    {
        book[key] = code;
        return;
    } 

    if (left_char != NULL)
    {
        left_char->add_to_codebook (code + '0');
    }

    if (right_char != NULL)
    {
        right_char->add_to_codebook (code + '1');
    }

    return;
}

uint32_t Node::get_f ()
{
    return frequency;
}

unsigned char Node::get_c ()
{
    return key;
}

/* implementation of min heap */
template    <class  T>
minHeap<T>::minHeap() {
    capacity = 256;
    size = 0;
    heap = new T * [256];
}

template    <class  T>
minHeap<T>::~minHeap() {
    size = 0;
    capacity = 0;
    delete[] heap;
}

template    <class  T>
int minHeap<T>::get_size () {
    return size;
}

template    <class  T>
T   * minHeap<T>::top() {
    return heap[1];
}

template    <class  T>
void    minHeap<T>::maintain(int k) {
    int currIndex = k;          // current index
    int lc = currIndex << 1;    // left child
    int rc = lc | 1;            // right child
    T   *temp = heap[currIndex];

    if (lc <= size && rc > size && *heap[lc] < *temp) {
        heap[currIndex] = heap[lc];
        heap[lc] = temp;
        maintain(lc);
    }
    else if (lc <= size && rc <= size && (*temp > *heap[lc] || *temp > *heap[rc])) {
        if (*heap[lc] < *heap[rc]) {
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
    int currIndex = 1;       
    maintain(currIndex);
    return;
}

template    <class  T>
void    minHeap<T>::push(T  * data) {
    size++;
    heap[size] = data;
    
    int currIndex = size;          // current index
    int parent = currIndex >> 1;        // parent index
    
    while (parent >= 1 && *heap[currIndex] < *heap[parent]) {
        T   *temp = heap[currIndex];
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
                cout << heap[k]->get_c ();
            }
            else {
                cout << 'S';
            }
            if (j < pow(2,i))   cout <<' ';
        }
        cout << endl;
    }
}