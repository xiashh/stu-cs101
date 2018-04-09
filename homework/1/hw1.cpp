#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
using namespace std;

// define ADS for node
template    <class T>
struct  Node {
    T data;
    Node * next;
    int isOperand;
};

// define ADS for nodeStack
template    <class T>
class   nodeStack {
    private:
        Node<T> * head;
        int size;
    
    public:
        nodeStack();
        ~nodeStack();
        void push(T data);
        void pop();
        T top();
        bool isEmpty();
};

// implementation of methods in nodeStack
template    <class T>
T   nodeStack<T>::top() {
    return head -> data;
}
template    <class T>
nodeStack<T>::nodeStack(){
    head = NULL;
    size = 0;
}

template    <class T>
nodeStack<T>::~nodeStack(){
    Node<T> * temp = NULL;

    while (head != NULL) {
        temp = head;
        head = head -> next;
        delete temp;
    }

    size = 0;
}

template    <class T>
void    nodeStack<T>::push(T data) {
    Node<T> * newNode = new Node<T>;
    newNode -> data = data;
    newNode -> next = head;
    head = newNode;
    size++;
    return;
}

template    <class T>
void   nodeStack<T>::pop() {
    Node<T> * tempNode = head;
    head = head -> next;
    delete tempNode;
    size--;
    return;
}

template    <class T>
bool    nodeStack<T>::isEmpty() {
    return size == 0;
}

// priority function 
int InPriority(char op) {
    if (op == '*' || op == '/')
        return 5;
    else if (op == '+' || op == '-')
        return 3;
    else if (op == '(')
        return 1;
    else if (op == ')')
        return 6;
    else    return -1;
}

int OutPriority(char op) {
    if (op == '*' || op == '/')
        return 4;
    else if (op == '+' || op == '-')
        return 2;
    else if (op == '(')
        return 6;
    else if (op == ')')
        return 1;
    else    return -1;
}

// transfer infix to postfix
Node<string> *  infixToPostfix(string s) {
    string operand;
    Node<string> * head = NULL;
    Node<string> * current = NULL;
    nodeStack<char> * operators = new nodeStack<char>;
    s += '#';
    unsigned int sSize = s.size();
    unsigned int i = 0;
    int ind = 0;    // to indicate the first digit

    while (i < sSize) {
        operand = "";
        // digits
        if ((s[i] <= '9' && s[i] >= '0') || s[i] == '.') {
            if (ind == 0) {
                while ((s[i] <= '9' && s[i] >= '0') || s[i] == '.') {
                    operand += s[i];
                    i++;
                }
                current = new Node<string>;
                current -> data = operand;
                current -> isOperand = 1;
                head = current;
                ind = 1;
                // cout << operand << endl;
            }
            else {
                while ((s[i] <= '9' && s[i] >= '0') || s[i] == '.') {
                    operand += s[i];
                    i++;
                }
                current -> next = new Node<string>;
                current = current -> next;
                current -> data = operand;
                current -> isOperand = 1;    
                // cout << operand << endl;            
            }
        }
        // nondigits
        else if (s[i] != ' ') {
            if (operators -> isEmpty()) {
                if (i == s.size() - 1)    break;
                operators -> push(s[i]);
                i++;
            }
            else {
                char topOperator = operators -> top();
                    // cout << topOperator << ' ' << s[i] << endl;
                    // cout << InPriority(topOperator) << ' ' <<  OutPriority(s[i]) << endl;
                if (InPriority(topOperator) < OutPriority(s[i])) {
                    operators -> push(s[i]);
                    i++;
                }
                else if (InPriority(topOperator) > OutPriority(s[i])) {
                    operators -> pop();
                    current -> next = new Node<string>;
                    current = current -> next;
                    (current -> data).push_back(topOperator);
                    current -> isOperand = 0;       
                    // cout << topOperator << endl;             
                }
                else {
                    operators -> pop();
                    i++;
                }
            }
        }
        else i++;
    }
    return head;
}

// calculator the postfix expression
double  calculate(Node<string> * exp) {
    nodeStack<double> * result = new nodeStack<double>;
    double left, right;

    while (exp != NULL) {
        if (exp -> isOperand == 1) {
            result -> push(atof(&(exp -> data)[0]));
        }
        else {
            if (exp -> data == "+") {
                right = result -> top();
                result -> pop();
                if      (result -> isEmpty()) left = 0;
                else {
                left = result -> top();
                result -> pop();
                }
                result -> push(left + right);
            }
            else if (exp -> data == "-") {
                right = result -> top();
                result -> pop();
                if      (result -> isEmpty()) left = 0;
                else {
                left = result -> top();
                result -> pop();
                }
                result -> push(left - right);
            }
            else if (exp -> data == "*") {
                right = result -> top();
                result -> pop();
                left = result -> top();
                result -> pop();
                result -> push(left * right);
            }
            else if (exp -> data == "/") {
                right = result -> top();
                result -> pop();
                left = result -> top();
                result -> pop();
                result -> push(left / right);
            }
        }
        exp = exp -> next;
    }
    if (result -> top() > 2147483647)
        return 2147483647;
    else if (result -> top() < -2147483648)
        return -2147483648;
    else
        return result -> top();
}

string correcter(string exp) {
    int ss = exp.size();
    string cExp = exp;
    
    int i = 0;
    while (i < ss) {
        if (cExp[i] == ' ') {
            cExp.erase(i,1);
            ss--;
            continue;
        }
        i++;
    }
     
    for (int i = 0; i < ss; i++) {
        if (cExp[i] == '+' || cExp[i] == '-') {
            if (i == 0) cExp.insert(0,1,'0');
            else if ((cExp[i-1] > '9' || cExp[i-1] < '0') && !(cExp[i-1] == '(' || cExp[i-1] == ')')) cExp.insert(i,1,'0');
        }
    }
    return cExp;
}

// main function of calculator
int main() {
    // obtain the expression and push chars into nodeStack
    string exp;
    while (getline(cin, exp)) {
        exp = correcter(exp);
        if (exp == "") continue;
        cout << exp << endl;
        Node<string> * postFix = infixToPostfix(exp);
        printf("%f\n", calculate(postFix));
    }
}
