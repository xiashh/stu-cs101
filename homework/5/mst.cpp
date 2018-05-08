#include <string>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

/* global variable */
static int num_cities;
static int num_roads;
static int num_regions;

/* data structure */
struct Edge
{
    int start, end;
    int weight;
    Edge * next;
    bool operator> (const Edge& op) const 
    {
        if (weight > op.weight)
        return true;
        else if (weight == op.weight)
        {

            if (min (start, end) > min(op.start, op.end))
                return true;
            else if (min (start, end) == min(op.start, op.end))
                if (max (start, end) > max (op.start, op.end))
                    return true;
                else
                    return false;
            else
                return false;
        }
        else
            return false;
    };
    
    bool operator< (const Edge& op) const 
    {
        if (weight < op.weight)
        return true;
        else if (weight == op.weight)
        {

            if (min (start, end) < min(op.start, op.end))
                return true;
            else if (min (start, end) == min(op.start, op.end))
                if (max (start, end) < max (op.start, op.end))
                    return true;
                else
                    return false;
            else
                return false;
        }
        else
            return false;
    };
};

struct Node 
{
    int index;
    int height = 0, size = 1;
    Node * root;
    Edge * edge;
    int min_index;
    bool operator< (const Node & op) const
    {
        if (size < op.size)
        {
            return true;
        }
        else if (size == op.size)
        {
            if (min_index < op.min_index)
                return true;
            else
                return false;
        }
        else
        {
            return false;
        }
    };
};

void edge_push_back (Node * a, Edge * b)
{
    Edge * next = a->root->edge;
    Edge * last = nullptr;

    if (next == nullptr)
    {
        a->root->edge = b;
        return;
    }

    while (next)
    {      
        last = next;
        next = next->next;
    }

    last->next = b;
}

void print_edges(Node * a)
{
    Edge * current = a->edge;
    cout <<"all edges of "<<a->index<< endl;
    while (current)
    {
        cout << current->start << ' '<< current->end;
        cout << ' '<<current->weight<<endl;
        current = current->next;
    }
}

class disjoint_set
{
    private:
        int size;
        Node ** nodes;
        
    public:
        disjoint_set (int n)
        {
            size = n;
            nodes = new Node * [n];
            for (int i = 0; i < n; i++)
            {
                nodes[i] = new Node;
                nodes[i]->index = i;
                nodes[i]->root = nodes[i];
                nodes[i]->min_index = i;
            }
        }

        ~disjoint_set ()
        {
            for (int i = 0; i < size; i++)
                delete nodes[i];
            delete[] nodes;
        }

        int get_size()
        {
            return size;
        }

        Node * get_node (int n)
        {
            return nodes[n];
        }

        Node * find (int i)
        {
            if (nodes[i]->root->index == i)
                return nodes[i]->root;
            else
            {
                nodes[i]->root = find (nodes[i]->root->index);
                return nodes[i]->root;
            }
        }

        void set_union (int i, int j)
        {
            Node * node1 = find(i);
            Node * node2 = find(j);
            // cout << node1->size << ' '<<node2->size<<endl;
            if (node1->index == node2->index)
                return;
            else
            {
                if (node1->height > node2->height)
                {
                    node2->root = node1->root;
                    edge_push_back (node1, node2->edge);
                    node1->size += node2->size;
                    node1->min_index = min(node1->min_index, node2->min_index);
                }
                else if (node1->height < node2->height)
                {
                    node1->root = node2->root;
                    edge_push_back (node2, node1->edge);                  
                    node2->size += node1->size;
                    node2->min_index = min(node1->min_index, node2->min_index);
                }
                else
                {
                    node2->root = node1->root;
                    edge_push_back (node1, node2->edge);                   
                    node1->size += node2->size;
                    node1->min_index = min(node1->min_index, node2->min_index);
                    node1->height++;
                }
            }
            size--;
            return;
        }
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

int compare_region (const void * a, const void * b)
{
    return *(Node*)a < *(Node*)b;
}

int compare_edge (const void * a, const void * b)
{
    return *(Edge*)a < *(Edge*)b;
}

void create_roads (disjoint_set * set)
{
    minHeap<Edge> * Edges = new minHeap<Edge> (num_roads);
    int sp, ep;
    int w;
    
    for (int i = 0; i < num_roads; i++)
    {
        cin >> sp >> ep >> w;
        Edge * old_road = new Edge;
        old_road->start = sp;
        old_road->end = ep;
        old_road->weight = w;
        Edges->push (old_road);
        // cout <<sp<<' '<<ep<<' '<<w<<endl;
    }

    // build new roads
    while (set->get_size () > num_regions)
    {
        Edge * new_road = Edges->top ();
        Edges->pop ();
        if (new_road == nullptr)
            break;
        sp = new_road->start;
        ep = new_road->end;
        w = new_road->weight;     
        if (set->find (sp)->index != set->find (ep)->index)
        {
            Edge * new_edge = new Edge;
            new_edge->start = sp;
            new_edge->end = ep;
            new_edge->weight = w;    
            edge_push_back (set->get_node (sp), new_edge);
            set->set_union (sp, ep);
        }
    }
}

void print_roads (disjoint_set * set)
{
    int num_real_regions = set->get_size ();
    Node region[num_real_regions];

    // obtain roots
    for (int i = 0; i < num_real_regions;)
    {
        for (int j = 0; j < num_cities; j++)
        {
            if (set->find(j)->index == j)
            {
                region[i++] = *set->get_node(j);
                // cout << region[i-1].size << endl;
            }
        }
    }

    qsort (region, num_real_regions, sizeof(Node), compare_region);
    printf("[\n");
    for (int i = 0; i < num_real_regions; i++)
    {
        printf("[\n");
        Edge * current = region[i].edge;
        int num = region[i].size-1;
        Edge roads[num];
        for (int j = 0; j < num; j++)
        {
            roads[j] = *current;
            current = current->next;
        }
        qsort (roads, num, sizeof(Edge), compare_edge);

        for (int j = 0; j < num; j++)
        {
            int s = roads[j].start;
            int e = roads[j].end;
            int w = roads[j].weight;
            if (s < e)
                printf("[%d,%d,%d]", s, e, w);
            else
                printf("[%d,%d,%d]", e, s, w);
            if (j == num-1)
                printf("\n");
            else
                printf(",\n");
        }
        if (i == num_real_regions-1)
            printf("]\n");
        else
            printf("],\n");
    }
    printf("]\n");
}

int main ()
{
    cin >> num_cities >> num_roads >> num_regions;

    disjoint_set * city_set = new disjoint_set(num_cities);

    create_roads (city_set);
    print_roads (city_set);
}