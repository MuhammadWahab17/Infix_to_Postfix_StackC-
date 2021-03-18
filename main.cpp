//
//  main.cpp
//  Stack_infix_to_postfix
//
//  Created by Ch Muhammad Wahab on 06/11/2020.
//  Copyright © 2020 Ch Muhammad Wahab. All rights reserved.
//

#include <iostream>
#include<fstream>
using namespace std;

template<class t>
struct Node
{
    t data;
    struct Node<t>* next;
};
template<class t>
class stack{
    struct Node<t>* top;
    
public:
    stack(){
        top=NULL;
    }
    void push(const t &data)
    {
        struct Node<t>* temp;
        temp = new Node<t>;
        if (!temp)
        {
            cout << "\nHeap Overflow";
            exit(1);
        }
        cout<<data<<" pushed into stack\n";
        temp->data = data;
        
        temp->next = top;
        
        top = temp;
    }
    
    bool empty() const
    {
        return top == NULL;
    }
    t top_value() const
    {
        if (!empty())
        {
            return top->data;
        }
        else
        return 0;
    }
    void pop()
    {
        struct Node<t>* temp;
        if (top == NULL)
        {
            cout << "\nStack Underflow" << endl;
        }
        else
        {
             cout<<top_value()<<" poped out of stack!\n";
            temp = top;
            top = top->next;
            temp->next = NULL;
            delete temp;
        }
        
    }
    void stack_status(){
        cout<<"Stack:\n";
        struct Node<t> *temp;
        temp=top;
        if(temp==NULL){
            cout<<"Stack Underflow!\n";
        }
        while(temp!=NULL){
            cout<<temp->data<<endl;
            temp=temp->next;
        }
    }
    ~stack(){
        while(!empty()){
            pop();
        }
    }
};

bool Brackets_Check(string expr)
{    stack<char> s;
    char x;
    int i;
    for ( i = 0; i < expr.length(); i++)
    {
        if(expr[i] != '(' && expr[i] != '['
           && expr[i] != '{' && expr[i] != ')' && expr[i] != ']'
           && expr[i] != '}' ){
            continue;
        }
        if (expr[i] == '(' || expr[i] == '['
            || expr[i] == '{')
        {
            s.push(expr[i]);
            s.stack_status();
            continue;
        }
        if (s.empty())
        {
            cout<<"No opening bracket against "<<expr[i]<<" found in stack\n";
            return false;
        }
        switch (expr[i]) {
            case ')':
                x = s.top_value();
                cout<<x<<" poped out of stack\n";
                s.pop();
                s.stack_status();
                if (x == '{' || x == '[')
                {
                    cout<<"No opening bracket against "<<expr[i]<<" found in stack\n";
                    return false;
                }break;
            case '}':
                x = s.top_value();
                cout<<x<<" poped out of stack\n";
                s.pop();
                s. stack_status();
                if (x == '(' || x == '[')
                {
                    cout<<"No opening bracket against "<<expr[i]<<" found in stack\n";
                    return false;
                }
                break;
            case ']':
                x = s.top_value();
                cout<<x<<" poped out of stack\n";
                s.pop();
                s. stack_status();
                if (x == '(' || x == '{')
                {
                    cout<<"No opening bracket against "<<expr[i]<<" found in stack\n";
                    return false;
                }
                break;
        }
    }
    if(!s.empty()){
        cout<<"No closing bracket(s) for\n";
        while(!s.empty()){
            x = s.top_value();
            s.pop();
            cout<<x<<endl;
        }
        cout<<"was(were) found!!\n";
        return false;
    }
    else return true;
}
void infix_to_postfix(string str){
    stack<char> s;
    string postfix="";
    for(int i=0;i<str.length();i++){
    if(isdigit(str[i]) || (str[i]>='A' && str[i]<='Z') || (str[i]>='a' && str[i]<='z') ){
        postfix=postfix+str[i];
        cout<<"Output:"<<postfix<<endl;
    }
    else{
        if(s.top_value()=='(' || s.top_value()=='{' || s.top_value()=='['){
            s.push(str[i]);
            s.stack_status();
            continue;
        }
            switch (str[i]) {
                case '(':
                    s.push(str[i]);
                    s.stack_status();
                    break;
                    
                case '{':
                  s.push(str[i]);
                    s.stack_status();
                    break;
                    
                case '[':
                   s.push(str[i]);
                    s.stack_status();
                    break;
                case ')':
                    s.push(str[i]);
                    s.pop();
                    while(!s.empty() && s.top_value()!='(')
                    {
                    postfix=postfix+s.top_value();
                    s.pop();
                    }
                    s.pop();
                    cout<<"Output:"<<postfix<<endl;
                    break;
                    
                case '}':
                    s.push(str[i]);
                    s.pop();
                    while(!s.empty() && s.top_value()!='{')
                    {
                        postfix=postfix+s.top_value();
                        s.pop();
                    }
                    s.pop();
                      cout<<"Output:"<<postfix<<endl;
                    break;
                    
                case ']':
                    s.push(str[i]);
                    s.pop();
                    while(!s.empty() && s.top_value()!='[')
                    {
                        postfix=postfix+s.top_value();
                        s.pop();
                    }
                    s.pop();
                    cout<<"Output:"<<postfix<<endl;
                    break;
                case '*':
                    if(!s.empty()){
                        while(!s.empty() && (s.top_value()!='+' && s.top_value()!='-')){
                            postfix=postfix+s.top_value();
                            s.pop();
                            cout<<"Output:"<<postfix<<endl;
                        }
                        s.push(str[i]);
                        s.stack_status();
                    }
                    else
                        s.push(str[i]);
                    s.stack_status();
                    break;
                case '-':
                    while(!s.empty()){
                        if(s.top_value()=='/' || s.top_value()=='*' || s.top_value()=='+' || s.top_value()=='-'){
                            postfix=postfix+ s.top_value();
                            cout<<"Output:"<<postfix<<endl;
                        }
                        s.pop();
                    }
                    s.push(str[i]);
                    s.stack_status();
                    break;
                case '+':
                    while(!s.empty()){
                        if(s.top_value()=='/' || s.top_value()=='*' || s.top_value()=='-' || s.top_value()=='+'){
                            postfix=postfix+ s.top_value();
                            cout<<"Output:"<<postfix<<endl;
                        }
                    s.pop();
                    }
                    s.push(str[i]);
                    s.stack_status();
                    break;
                case '/':
                    if(!s.empty()){
                        while(!s.empty() && s.top_value()!='+' && s.top_value()!='-'){
                            postfix=postfix+s.top_value();
                            s.pop();
                            cout<<"Output:"<<postfix<<endl;
                        }
                        s.push(str[i]);
                        s.stack_status();
                    }
                    else
                        s.push(str[i]);
                    s.stack_status();
                    break;
            }
    }
}
    s.stack_status();
    while(!s.empty()){
        postfix+=s.top_value();
        s.pop();
    }
      cout<<"Postfix Expression:"<<postfix;
    cout<<endl;
}
int main(int argc, const char * argv[]) {
//    if(argc<2){
//        cout<<"No command line argument found!";
//        exit(1);
//    }
//    if(Brackets_Check(argv[1])){
//        cout<<"Infix expression is valid.\nProceding to convertion...\n";
        infix_to_postfix("1+8/2*5-4+6-3");
//    }
//    else{
//        cout<<"Brackets in the read infix notation are not balanced !\n";
//    }
}
