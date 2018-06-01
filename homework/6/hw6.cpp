#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <cctype>

using namespace std;

// define ADS for node
template    <class T>
struct  Node {
    T data;
    Node<T> * next;
};

// define ADS for list
template    <class T>
class   list {
    private:
        Node<T> * head;
        Node<T> * tail;
        int size;
    
    public:
        list(T data);
        ~list();
        int get_size();
        void push_front(T data);
        void push_back (T data);
        void pop_front();
        void erase (T data);
        Node<T> * get_front();
        T front();
        T back();
        bool isEmpty();
};

// implementation of methods in list
template <class T>
Node<T> * list<T>::get_front() {
    return head;
}

template <class T>
int list<T>::get_size() {
    return size;
}
template <class T>
T   list<T>::front() {
    return head->data;
}

template <class T>
T list<T>::back() {
    return tail->data;
}

template <class T>
list<T>::list(T data){
    Node<T> * n = new Node<T>;
    n->data = data;
    n->next = nullptr;
    head = n;
    tail = n;
    size = 1;
}

template <class T>
list<T>::~list(){
    Node<T> * temp = nullptr;

    while (head != nullptr) {
        temp = head;
        head = head -> next;
        delete temp;
    }

    size = 0;
}

template <class T>
void    list<T>::push_front(T data) {
    Node<T> * newNode = new Node<T>;
    newNode -> data = data;
    newNode -> next = head;

    if (head == nullptr) {
        head = newNode;
        tail = head;
    }
    else
        head = newNode;
    size++;
    return;
}

template <class T>
void list<T>::push_back(T data) {
    Node<T> * newNode = new Node<T>;
    newNode->data = data;
    newNode->next = nullptr;

    if (tail == nullptr) {
        tail = newNode;
        head = newNode;
    }
    else {
        this->tail->next = newNode;
        this->tail = newNode;
    }
    size++;
    return;
}

template <class T>
void   list<T>::pop_front() {
    Node<T> * p = head;
    head = head -> next;
    delete p;
    size--;
    return;
}

template <class T>
void list<T>::erase(T data) {
    Node<T> * p = head;
    
}

template <class T>
bool    list<T>::isEmpty() {
    return size == 0;
}

list<char> ** create_adjList (int num){
    list<char> ** l = new list<char> * [26];
    int flag[26];
    int inDegree[28];

    string name[num];
    getline(cin, name[0]);
    
    for (int i = 0; i < 26; i++) {
        l[i] = new list<char>(i + 97);
        flag[i] = -1;
        inDegree[i] = 0;
    }
    
    // load names
    for (int i = 0; i < num; i++) {
        string s;
        getline(cin, s);
        
        // erase all spaces
        int pos = 0;
        pos = s.find(' ', pos);
        while (pos != -1) {
            s.replace(pos, 1, "");
            pos = s.find(' ', pos);
        }
        
        // conver all letters lower
        unsigned int sSize = s.size();
        for (int j = 0; j < sSize; j++) {
            if (s[j]>= 65 && s[j] <= 90)
                s[j] +=32;
        }

        name[i] = s;
    }

    // create graph
    for (int i = 0; i < num-1; i++) {
        string s1 = name[i];
        string s2 = name[i+1];
        int msize = max(s1.size(), s2.size());
        
        for (int j = 0; j < msize; j++) {
            if (j == s1.size())
                break;
            else if (j == s2.size())
                return nullptr;
            else {
                if (s1[j] == s2[j])
                    continue;
                else {
                    int index1 = (int)s1[j]-97;
                    int index2 = (int)s2[j]-97;
                    if (flag[index1] == 1 || flag[index2] == 1)
                        return nullptr;
                    else {
                        flag[index1] = 1;
                        inDegree[index2]++;
                        l[index1]->push_back(s2[j]);
                        break;
                    }
                }
            }
        }
    }

    // print alphalbet
    int t_order[26];
    for (int i = 0; i < 26; i++) {
        flag[i] = -1;
    }

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            if (flag[j] == -1 && inDegree[j] == 0) {
                t_order[i] = j;
                flag[j] = 1;
                for (Node<char> * n = l[j]->get_front(); n != nullptr; n = n->next) {
                    int index = n->data-97;
                    inDegree[index]--;
                }
                break;
            }
        }
    }

    for (int i = 0; i < 26; i++) {
        cout << (char)(t_order[i]+97);
    }

}

int main () {
    int num;
    cin >> num;

    list<char> ** adj_list = create_adjList(num);
    if (adj_list == nullptr)
        cout << "另请高明吧" << endl;
}