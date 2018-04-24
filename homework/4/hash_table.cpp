#include <string>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <cmath>

using namespace std;

/* data structure */
struct Node 
{
    unsigned int count;
    string str;
    Node * next;
};

class   single_list {
    private:
        Node * head;
        int size;
    
    public:
        single_list(int n)
        {
            head = nullptr;
            size = n;
        }

        ~single_list()
        {
            Node * temp = nullptr;
            while (head != nullptr)
            {
                temp = head;
                head = head->next;
                delete temp;
            }
            size = 0;
        }

        void insert(string s)
        {
            Node * new_node = new Node;
            new_node->str = s;
            new_node->count = 1;
            new_node->next = head;
            head = new_node;
            size++;
            return;
        }

        void erase(string s)
        {
            Node * current = head;
            Node * previous = nullptr;
            while (current)
            {
                if (current->str == s)
                {
                    if (current == head)
                        head = current->next;
                    else
                        previous->next = current->next;
                    delete current;
                    break;
                }
                previous = current;
                current = current->next;
            }
        }

        Node * find (string s)
        {
            Node * current = head;
            Node * previous = nullptr;
            while (current)
            {
                if (current->str == s)
                    return current;
                current = current->next;
            }
            return nullptr;
        }

        Node * top ()
        {   
            return head;
        }
};

/* global variable */
static unsigned int table_length = 0;
static unsigned int load_factor = 0;
static unsigned int current_size = 0;
static unsigned int list_size = 100;
single_list ** hash_table;

unsigned int quick_mod (int, int, int);
bool is_number(const string & s);
void resize_hash_table ();
void insert_to_table ();
void erase_from_table ();
void print_table ();
unsigned int cal_hash_code (string, unsigned int);

int main ()
{
    // initial length and size
    cin >> load_factor;
    cin >> table_length;

    if (load_factor == 0)
        return -1;

    // initialize the hash table
    hash_table = new single_list * [table_length];
    for (int i = 0; i < table_length; i++)
        hash_table[i] = new single_list(list_size);

    insert_to_table ();
    erase_from_table ();
    print_table ();
}

unsigned int quick_mod (int n, int p, int mod)
{
    if (p == 0)
        return 1;
    
    if (p % 2 == 0)
        return (quick_mod (n, p/2, mod) * 
                quick_mod (n, p/2, mod)) % mod;
    else
        return (quick_mod(n, p-1, mod) * n) % mod;
}

bool is_number(const string & s)
{
    if (s.empty ()) return false;

    char c;
    for (int i = 0; i < s.size (); i++)
    {   
        c = s[i];
        if (isdigit(c))
            continue;
        else
            return false;
    }

    return true;
}

void resize_hash_table ()
{
    unsigned int new_length = table_length*2 + 1;
    single_list ** new_ht = new single_list * [new_length];
    for (int i = 0; i < new_length; i++)
        new_ht[i] = new single_list(list_size);
    
    for (int i = 0; i < table_length; i++)
    {
        Node * current = hash_table[i]->top();
        while (current)
        {
            string s = current->str;
            unsigned int hash_code = cal_hash_code (s, new_length);
            new_ht[hash_code]->insert(s);
            new_ht[hash_code]->top()->count = current->count;
            current = current->next;
        }
    }
    single_list ** temp = hash_table;
    hash_table = new_ht;
    for (int i = 0; i < table_length; i++)
        delete temp[i];
    delete[] temp;
    table_length = new_length;
}

void insert_to_table ()
{
    string s;
    while (cin >> s)
    {
        if (s == "************************")
            break;
        
        
        if ((current_size+1)* 100 > table_length * load_factor)
        {
            resize_hash_table ();
        }

        unsigned int hash_code = cal_hash_code (s, table_length);
        
        if (hash_table[hash_code]->find(s))
        {
            hash_table[hash_code]->find(s)->count++;
        }
        else
        {
            hash_table[hash_code]->insert(s);
            current_size++;
        }

    }
}

void print_table ()
{
    Node * current;
    printf("[\n");
    for (int i = 0; i < table_length; i++)
    {
        printf("{");
        current = hash_table[i]->top();
        while (current)
        {
            printf("\"%s\":%d", (current->str).c_str(), current->count);
            if (current->next)
                printf(",");
            current = current->next;
        }
        printf("}");
        if (i < table_length-1)
            printf(",\n");
        else
            printf("\n");
    }
    printf("]\n");
}

void erase_from_table ()
{
    string s;
    while (cin >> s)
    {
        if (s == "************************")
            break;

        unsigned int hash_code = cal_hash_code (s, table_length);
        hash_table[hash_code]->erase (s);
        current_size--;
    }
}

unsigned int cal_hash_code (string s, unsigned int mod)
{
    unsigned int hash_code = 0;

    if (is_number (s))
        {
            unsigned long int num;
            sscanf(s.c_str(), "%ld", &num);
            hash_code = num % mod;
        }
    else
    {
        for (int i = 0; i < s.size (); i++)
        {
            unsigned int n = (unsigned char)s[i];
            unsigned int m = quick_mod (2, 8*(s.size ()-i-1), mod);
            hash_code += ((n % mod) * m) % mod;
        }
        hash_code %= mod;
    }

    return hash_code;
}