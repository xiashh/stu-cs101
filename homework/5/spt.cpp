#include <string>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>

using namespace std;

/* data structure */
struct Node
{
    int size;
    int value;
    Node * parent;
};

struct Edge
{
    int weight;
    int sp;
    int ep;
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
        void set_union (int, int);
};

/* global variable */
static int num_cities;
static int num_roads;
static int num_regions;

void print_disjoint_set (const disjoint_set *);

int main ()
{
    // obtain parameters
    cin >> num_cities;
    cin >> num_roads;
    cin >> num_regions;

    disjoint_set * regions = new disjoint_set (num_cities);
    Edge * old_roads = new Edge [num_roads];
    
    // read old roads
    string old_road;
    int count = 0;
    while (getline (cin, old_road))
    {
        if (old_road.empty())
            continue;
        
        // append to old_reads
        Edge * road = &old_roads[count++];
        sscanf(old_road.c_str(), "%d %d %d", &road->sp, &road->ep, &road->weight);
    }

    // build new roads




    // for debugging
    // for (int i = 0; i < num_roads; i++)
    // {
    //     printf("sp:%d, ep:%d, weight:%d\n", old_roads[i].sp, old_roads[i].ep, old_roads[i].weight);
    // }

    return 0;
}
/* implementation */
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
void disjoint_set::set_union (int i, int j)
{
    Node * ni = find(i);
    Node * nj = find(j);
    if (ni->value == nj->value)
        return;
    else
        if (ni->size >= nj->size)
        {
            nj->parent = ni;
            ni->size++;
        }
        else
        {
            ni->parent = nj;
            nj->size++;
        }
    this->size--;
    return;
}