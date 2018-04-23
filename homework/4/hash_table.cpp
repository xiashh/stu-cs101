#include <string>
#include <regex>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>

using namespace std;

/* data structure */
struct Node 
{
    int type;       // 1 is num ,2 is string
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
static int table_length = 0;
static int list_size = 0;
static int current_size = 0;
single_list ** hash_table;

int quick_mod (int, int, int);
bool is_number(const string & s);
void resize_hash_table ();
void insert_to_table ();
void erase_from_table ();
void print_table ();

int main ()
{
    // initial length and size
    cin >> list_size;
    cin >> table_length;

    // initialize the hash table
    hash_table = new single_list * [table_length];
    for (int i = 0; i < table_length; i++)
        hash_table[i] = new single_list(list_size);

    insert_to_table ();
    erase_from_table ();
    print_table ();
}

int quick_mod (int n, int p, int mod)
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
    int new_length = table_length*2 + 1;
    single_list ** new_ht = new single_list * [new_length];
    for (int i = 0; i < new_length; i++)
        new_ht[i] = new single_list(list_size);
    
    for (int i = 0; i < table_length; i++)
    {
        Node * current = hash_table[i]->top();
        while (current)
        {
            int hash_code = 0;
            string s = current->str;
            if (current->type == 1)
            {
                hash_code = stoi(s, nullptr, 10) % new_length;
            }
            else
            {
                for (int i = 0; i < s.size (); i++)
                    hash_code += (s[i] * quick_mod (2, 8*(s.size ()-i-1), new_length)) % new_length;
                hash_code %= new_length;
            }
            new_ht[hash_code]->insert(s);
            new_ht[hash_code]->top()->count = current->count;
            new_ht[hash_code]->top()->type = current->type;
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
        
        if (current_size * 100 > table_length * list_size)
        {
            resize_hash_table ();
        }

        int hash_code = 0;
        int t = 0;
        if (is_number (s))
        {
            hash_code = stoi(s, nullptr, 10) % table_length;
            t = 1;
        }
        else
        {
            for (int i = 0; i < s.size (); i++)
                hash_code += (s[i] * quick_mod (2, 8*(s.size ()-i-1), table_length)) % table_length;
            t = 2;
            hash_code %= table_length;
        }
        
        if (hash_table[hash_code]->find(s))
        {
            hash_table[hash_code]->find(s)->count++;
        }
        else
        {
            hash_table[hash_code]->insert(s);
            hash_table[hash_code]->find(s)->type = t;                
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

        int hash_code = 0;
        if (is_number (s))
        {
            hash_code = stoi(s, nullptr, 10) % table_length;
        }
        else
        {
            for (int i = 0; i < s.size (); i++)
                hash_code += (s[i] * quick_mod (2, 8*(s.size ()-i-1), table_length)) % table_length;
            hash_code %= table_length;
        }
        hash_table[hash_code]->erase (s);
        current_size--;
    }
}