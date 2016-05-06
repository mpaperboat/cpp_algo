#include<bits/stdc++.h>
using namespace std;
template<class T,class C>struct PairingHeap{
    PairingHeap():
        root(0),siz(0){
    }
    ~PairingHeap(){
        clear(root);
    }
    struct node{
        node(const T&_val):
            val(_val),ch(0),br(0),pr(0){
        }
        T val;
        node*ch,*br,*pr;
    }*root;
    int siz;
    void merge(node*&x,node*y){
        if(!x)
            x=y;
        else if(y){
            if(C()(y->val,x->val))
                swap(x,y);
            y->br=x->ch;
            if(x->ch)
                x->ch->pr=y;
            y->pr=x;
            x->ch=y;
        }
    }
    void cut(node*&x,node*y){
        if(x==y)
            x=0;
        else{
            if(y==y->pr->ch)
                y->pr->ch=y->br;
            else
                y->pr->br=y->br;
            if(y->br)
                y->br->pr=y->pr;
            y->pr=y->br=0;
        }
    }
    node*split(node*x){
        vector<node*>t;
        for(node*i=x->ch;i;i=i->br)
            t.push_back(i);
        x->ch=0;
        node*r=0;
        for(int i=0;i<t.size();++i)
            t[i]->pr=t[i]->br=0;
        for(int i=0;i+1<t.size();i+=2)
            merge(t[i],t[i+1]);
        for(int i=0;i<t.size();i+=2)
            merge(r,t[i]);
        return r;
    }
    void clear(node*x){
        if(x){
            clear(x->ch);
            clear(x->br);
            delete x;
        }
    }
    void clear(){
        clear(root);
        root=0;
        siz=0;
    }
    node*push(T a){
        node*r=new node(a);
        merge(root,r);
        ++siz;
        return r;
    }
    void erase(node*x){
        cut(root,x);
        merge(root,split(x));
        --siz;
    }
    T top(){
        return root->val;
    }
    void pop(){
        erase(root);
    }
    void merge(PairingHeap<T,C>&a){
        merge(root,a.root);
        a.root=0;
        siz+=a.siz;
        a.siz=0;
    }
    void modify(node*x,T v){
        if(C()(x->val,v))
            x->val=v,merge(root,split(x));
        else
            x->val=v,cut(root,x),merge(root,x);
    }
    int size(){
        return siz;
    }
};
