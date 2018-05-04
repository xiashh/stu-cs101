#include <string>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

/* data structure */
struct Node
{
    int size;
    int value;
    Node * parent;
};

class Edge
{
    private:
        int weight;
        int start;
        int end;

    public:
        Edge () {}
        Edge (int w, int sp, int ep): \
            weight (w), start (sp), end (ep) {}
        bool operator < (const Edge &);
        bool operator > (const Edge &);
        int get_weight ();
        int get_start ();
        int get_end ();
};

template    <class T>
class   minHeap {
    private:
        int capacity;   // total available space
        int size;       // current used space
        T ** heap;       // array to store the data
        void    maintain(int k); // maintain the property
    
    public:
        minHeap(int);
        ~minHeap();
        int get_size ();         // return the size
        T   *top();     // show the maximum value
        void    pop();      // remove the minimum value
        void    push(T * data);     // insert a new value using bottom up
        void    print();    // print the max heap        
};

class disjoint_set
{
    private:
        int size;
        Node ** parent;
    
    public:
        disjoint_set (int);
        ~disjoint_set ();
        int get_size ();
        Node * find (int);
        bool set_union (int, int);
};

/* global variable */
static int num_cities;
static int num_roads;
static int num_regions;

void print_disjoint_set (disjoint_set *, Edge * edges);
void read_old_reads (minHeap<Edge> *);
Edge *  build_new_reads (disjoint_set *, minHeap<Edge> *);

int main ()
{
    // obtain parameters
    cin >> num_cities;
    cin >> num_roads;
    cin >> num_regions;

    disjoint_set * Regions = new disjoint_set (num_cities);
    minHeap<Edge> * Edges = new minHeap<Edge>(num_roads);
    Edge * new_roads;
    
    read_old_reads (Edges);
    new_roads = build_new_reads (Regions, Edges);
    print_disjoint_set (Regions, new_roads);
    return 0;
}
/* implementation of disjoint set */
disjoint_set::disjoint_set (int n)
{
    size = n;
    parent = new Node * [n];
    
    for (int i = 0; i < size; i++)
    {
        parent[i] = new Node;
        parent[i]->parent = parent[i];
        parent[i]->size = 1;
        parent[i]->value = i;
    }
}

disjoint_set::~disjoint_set ()
{
    for (int i = 0; i < size; i++)
        delete parent[i];
    delete[] parent;
}

int disjoint_set::get_size ()
{
    return size;
}

Node * disjoint_set::find (int i)
{
    if (parent[i]->parent->value == i)
        return parent[i]->parent;
    else
    {
        parent[i]->parent = find (parent[i]->parent->value);
        return parent[i]->parent;
    }
}
bool disjoint_set::set_union (int i, int j)
{
    Node * ni = find(i);
    Node * nj = find(j);
    if (ni->value == nj->value)
        return false;
    else
        if (ni->size > nj->size)
        {
            nj->parent = ni;
        }
        else if (ni->size < nj->size)
        {
            ni->parent = nj;
        }
        else
        {
            nj->parent = ni;
            ni->size++;
        }
    this->size--;
    return true;
}

/* implementation of Edge and minHeap */
bool Edge::operator < (const Edge & op)
{
    if (this->weight < op.weight)
        return true;
    else if (this->weight == op.weight)
    {

        if (min (this->start, this->end) < min(op.start, op.end))
            return true;
        else if (min (this->start, this->end) == min(op.start, op.end))
            return max (this->start, this->end) < max (op.start, op.end);
    }
    else
        return false;
}

bool Edge::operator > (const Edge & op)
{
    if (this->weight > op.weight)
        return true;
    else if (this->weight == op.weight)
    {

        if (min (this->start, this->end) > min(op.start, op.end))
            return true;
        else if (min (this->start, this->end) == min(op.start, op.end))
            return max (this->start, this->end) > max (op.start, op.end);
    }
    else
        return false;
}

int Edge::get_weight ()
{
    return this->weight;
}

int Edge::get_start ()
{
    return this->start;
}

int Edge::get_end ()
{
    return this->end;
}

template    <class  T>
minHeap<T>::minHeap(int n) {
    capacity = n;
    size = 0;
    heap = new T * [n];
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

void read_old_reads (minHeap<Edge> * edges)
{
    // read old roads
    string s;
    int count = 0;
    while (getline (cin, s))
    {
        if (s.empty())
            continue;
        
        // append to old_reads
        int sp, ep, weight;
        sscanf(s.c_str(), "%d %d %d", &sp, &ep, &weight);
        Edge * old_road = new Edge(weight, sp, ep);
        edges->push (old_road);
    }
}

Edge *  build_new_reads (disjoint_set * regions, minHeap<Edge> * edges)
{
    int start, end, weight, count;
    Edge * new_roads = new Edge [num_roads];

    while (regions->get_size () > num_regions)
    {
        Edge * new_road = edges->top ();
        start = new_road->get_start ();
        end = new_road->get_end ();
        weight = new_road->get_weight ();
        if (regions->set_union (start, end))
        {
            new_roads[count++] = Edge(weight, start, end);
        }
        edges->pop ();
    }

    return new_roads;
}

void print_disjoint_set (disjoint_set * regions, Edge * edges)
{
    int real_regions[regions->get_size ()];
    int num_real_regions,count;

    for (int i = 0; i < num_cities; i++)
    {
        if (regions->find(i)->value == i)
            real_regions[num_real_regions++] = i;
        count = regions->find(i)->value;
        printf("%d\n", count);
    }

    printf("[\n");
}