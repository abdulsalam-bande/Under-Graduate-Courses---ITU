//
//  main.cpp
//  HM5
//
//  Created by Abdulsalam Yazid on 12/18/16.
//  Copyright © 2016 Abdulsalam Yazid. All rights reserved.
//

#include <iostream>
#include <fstream>
using namespace std;

class Node {
public:
    
    string key;
    Node* parent;
    char color;
    Node *left;
    Node *right;
    int age;
    char gender;
    
};
class RBtree{
    Node *root;
    Node *q;
    
    public :
    RBtree(){
        q=NULL;
        root=NULL;
    }
    void insert(string s,char c,int age);
    void insertfix(Node *);
    void leftrotate(Node *);
    void rightrotate(Node *);
    void disp();
    void display( Node *);
};

void RBtree::insert(string key,char gender,int age){
    
    Node *p,*q;
  
    Node* t=new Node;
    t->key=key;
    t->age=age;
    t->gender=gender;
    
    t->left=NULL;
    t->right=NULL;
    t->parent=NULL;
    t->color='r';
    p=root;
    q=NULL;
    
    if(root==NULL){
        root=t;
        t->parent=NULL;
        
        
    }
    else
    {
        while(p!=NULL)
        {
            q=p;
            if(p->key<t->key)
                p=p->right;
            else
                p=p->left;
        }
        t->parent=q;
        if(q->key<t->key)
            q->right=t;
        else
            q->left=t;
    }
    insertfix(t);}

void RBtree::insertfix(Node *t)
{
    Node *u;
    if(root==t)
    {
        t->color='b';
        return;
    }
    while(t->parent!=NULL&&t->parent->color=='r')
    {
        Node *g=t->parent->parent;
        if(g->left==t->parent)
        {
            if(g->right!=NULL)
            {
                u=g->right;
                if(u->color=='r')
                {
                    t->parent->color='b';
                    u->color='b';
                    g->color='r';
                    t=g;
                }
            }
            else
            {
                if(t->parent->right==t)
                {
                    t=t->parent;
                    leftrotate(t);
                }
                t->parent->color='b';
                g->color='r';
                rightrotate(g);
            }
        }
        else
        {
            if(g->left!=NULL)
            {
                u=g->left;
                if(u->color=='r')
                {
                    t->parent->color='b';
                    u->color='b';
                    g->color='r';
                    t=g;
                }
            }
            else
            {
                if(t->parent->left==t)
                {
                    t=t->parent;
                    rightrotate(t);
                }
                t->parent->color='b';
                g->color='r';
                leftrotate(g);
            }
        }
        root->color='b';
    }
}
void RBtree::leftrotate(Node *p)
{
    if(p->right==NULL)
        return ;
    else
    {
        Node *y=p->right;
        if(y->left!=NULL)
        {
            p->right=y->left;
            y->left->parent=p;
        }
        else
            p->right=NULL;
        if(p->parent!=NULL)
            y->parent=p->parent;
        if(p->parent==NULL)
            root=y;
        else
        {
            if(p==p->parent->left)
                p->parent->left=y;
            else
                p->parent->right=y;
        }
        y->left=p;
        p->parent=y;
    }
}
void RBtree::rightrotate(Node *p)
{
    if(p->left==NULL)
        return ;
    else
    {
        Node *y=p->left;
        if(y->right!=NULL)
        {
            p->left=y->right;
            y->right->parent=p;
        }
        else
            p->left=NULL;
        if(p->parent!=NULL)
            y->parent=p->parent;
        if(p->parent==NULL)
            root=y;
        else
        {
            if(p==p->parent->left)
                p->parent->left=y;
            else
                p->parent->right=y;
        }
        y->right=p;
        p->parent=y;
    }
}
void RBtree::display(Node *p)
{
    if(root==NULL)
    {
        cout<<"\nEmpty Tree.";
        return ;
    }
    if(p!=NULL)
    {
        
        
        
               if(p->color=='b')
            cout<<"(B)";
        else
            cout<<"(R)";
        
        
        cout<<"  "<<p->key;
        cout<<"  "<<p->gender;
        cout<<"  "<<p->age;
        
        
        
        cout<<endl;
        if(p->left)
            display(p->left);
        
        if(p->right)
            display(p->right);
    }
}
void RBtree::disp()
{
    display(root);
}
int main(int argc,char* argv[] )
{
    
    RBtree obj;
    Node* line_ptr = new Node[21];
    int index = 0;
    
    // ifstream myfile;
    // myfile.open(argv[1]);
    
    ifstream myfile;
    myfile.open("input.txt");
    
    cout<<"\n\t RED BLACK TREE \n " ;
    
    while (!myfile.eof())
    {
        string x;
        char s1;
        int s2;
        
        string key;
        char gender;
        int age;
        
        myfile >> x;
        myfile >> s1;
        myfile >> s2;
        
        s2=s2+1;
        if (myfile.eof())
            break;
        
        key  = line_ptr[index].key=x;
        gender= line_ptr[index].gender=s1;
        age=  line_ptr[index].age=s2;
        
        obj.insert(key,gender,age);
        
        index = index + 1;
        
    }
    myfile.close();
    
    
   
    cout<<"\nNodes Inserted.\n";
    
    obj.disp();
    
    return 1;
}
