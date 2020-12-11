#include <iostream>
#include <stack>
#include<string.h>
#include <algorithm>
using namespace std;

typedef int EType;
typedef struct tnode
{
    EType data;
    struct tnode* left;
    struct tnode* right;
} TNode;

typedef struct tnode* BTREE;
void show_node(BTREE T);
void preorder(BTREE T);
void postorder(BTREE T);
void inorder(BTREE T);


int priority(char ch)
{
    if(ch == '+' || ch == '-')

    {
        return 1;
    }
    else if(ch == '*' || ch == '/')
    {
        return 2;
    }
    else if(ch == '^')
    {
        return 3;
    }
    else
    {
        return 0;
    }
}

string inToPost(string infix )
{
    stack<char> stk;
    stk.push('#');
    string postfix = "";
    string::iterator it;

    for(it = infix.begin(); it!=infix.end(); it++)
    {
        if(isdigit(char(*it)))
            postfix += *it;
        else if(*it == '(')
            stk.push('(');
        else if(*it == '^')
            stk.push('^');
        else if(*it == ')')
        {
            while(stk.top() != '#' && stk.top() != '(')
            {
                postfix += stk.top();
                stk.pop();
            }
            stk.pop();
        }
        else
        {
            if(priority(*it) > priority(stk.top()))
                stk.push(*it);
            else
            {
                while(stk.top() != '#' && priority(*it) <= priority(stk.top()))
                {
                    postfix += stk.top();
                    stk.pop();
                }
                stk.push(*it);
            }
        }
    }

    while(stk.top() != '#')
    {
        postfix += stk.top();
        stk.pop();
    }

    return postfix;
}

bool isOperator(char p)
{
    return p == '+' || p == '-' || p == '*' || p == '/';
}


void postToTree(string post)
{
    TNode* newNode;
    TNode *op1 ;
    TNode *op2 ;
    stack <TNode*> stk;
    string postfix = inToPost(post);
    string::iterator it;
    for(it = postfix.begin(); it!=postfix.end(); it++)
    {
        cout <<"value: " << *it <<endl;
        if(isOperator(*it))
        {
            op1 = stk.top();
            stk.pop();
            op2 = stk.top();
            stk.pop();
            newNode = (TNode*) malloc(sizeof(TNode));
            newNode->data = *it;
            newNode->left=op2;
            newNode->right=op1;
            stk.push(newNode);

        }
        else
        {
            newNode = (TNode*) malloc(sizeof(TNode));
            newNode->data = *it;
            newNode->left=NULL;
            newNode->right=NULL;
            stk.push(newNode);
        }

    }

    newNode = stk.top();
    stk.pop();
    cout<<"The preOrder Traverse : \n";
    preorder(newNode);
    cout<<"The postOrder Traverse : \n";
    postorder(newNode);
    cout<<"The inOrder Traverse : \n";
    inorder(newNode);

}


void show_node(BTREE T)
{
    cout<<char(T->data)<<endl;
}


void preorder(BTREE T)
{
    if (T != NULL)
    {
        show_node(T);
        preorder(T->left);
        preorder(T->right);
    }
}

void postorder(BTREE T)
{
    if (T != NULL)
    {
        postorder(T->left);
        postorder(T->right);
        show_node(T);
    }
}

void inorder(BTREE T)
{
    if (T != NULL)
    {
        inorder(T->left);
        show_node(T);
        inorder(T->right);
    }
}

int main()
{
    cout<< "Enter Expression: \n";
    string infix;
    cin>> infix;
    postToTree(x);

}

