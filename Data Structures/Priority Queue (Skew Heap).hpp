#include<bits/stdc++.h>
using namespace std;
template<class T,class C>struct SkewHeap{
    SkewHeap():
        root(0),siz(0){
    }
    ~SkewHeap(){
        clear(root);
    }
    struct node{
        node(T _val):
            val(_val){
            ch[0]=ch[1]=0;
        }
        T val;
        node*ch[2];
    }*root;
    int siz;
    node*merge(node*x,node*y){
        if(!x)
            return y;
        if(!y)
            return x;
        if(C()(y->val,x->val))
            swap(x,y);
        swap(x->ch[0],x->ch[1]=merge(x->ch[1],y));
        return x;
    }
    void clear(node*x){
        if(x){
            clear(x->ch[0]);
            clear(x->ch[1]);
            delete x;
        }
    }
    void clear(){
        clear(root);
        root=0;
        siz=0;
    }
    void push(T a){
        root=merge(root,new node(a));
        ++siz;
    }
    T top(){
        return root->val;
    }
    void pop(){
        root=merge(root->ch[0],root->ch[1]);
        --siz;
    }
    void merge(SkewHeap<T,C>&a){
        root=merge(root,a.root);
        a.root=0;
        siz+=a.siz;
        a.siz=0;
    }
    int size(){
        return siz;
    }
};
