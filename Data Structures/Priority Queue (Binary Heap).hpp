#include<bits/stdc++.h>
using namespace std;
template<class T,class C>struct BinaryHeap{
    struct node{
        node(int _p,T _v):
            p(_p),v(_v){
        }
        int p;
        T v;
    };
    vector<node*>a;
    BinaryHeap():
        a(1){
    }
    ~BinaryHeap(){
        clear();
    }
    void move(int i,int j){
        swap(a[i]->p,a[j]->p);
        swap(a[i],a[j]);
    }
    int check(int i,int j){
        if(!j||j>=a.size()||a[i]->v==a[j]->v)
            return 0;
        return a[i]->v<a[j]->v?-1:1;
    }
    int up(int i){
        if(check(i,i>>1)<0){
            move(i,i>>1);
            return i>>1;
        }else
            return 0;
    }
    int down(int i){
        if(check(i,i<<1)<=0&&check(i,i<<1^1)<=0)
            return a.size();
        if(check(i<<1,i<<1^1)<=0){
            move(i,i<<1);
            return i<<1;
        }else{
            move(i,i<<1^1);
            return i<<1^1;
        }
    }
    void maintain(int i){
        for(int j=up(i);j;i=j,j=up(i));
        for(int j=down(i);j<a.size();i=j,j=down(i));
    }
    void clear(){
        for(int i=1;i<a.size();++i)
            delete a[i];
        a.resize(1);
    }
    node*push(T v){
        a.push_back(new node(a.size(),v));
        node*r=a.back();
        maintain(a.size()-1);
        return r;
    }
    T top(){
        return a[1]->v;
    }
    void pop(){
        move(1,a.size()-1);
        delete a.back();
        a.pop_back();
        maintain(1);
    }
    void modify(node*x,T v){
        x->v=v;
        maintain(x->p);
    }
};
