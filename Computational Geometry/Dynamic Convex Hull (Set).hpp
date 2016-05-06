#include<bits/stdc++.h>
using namespace std;
template<class T>struct DynamicConvexHull{
    struct point{
        T x,y;
        point(T _x=0,T _y=0):
            x(_x),y(_y){
        }
        point operator-(const point&a)const{
            point p(x-a.x,y-a.y);
            return p;
        }
        T operator*(const point&a)const{
            return x*a.y-y*a.x;
        }
    };
    struct node{
        node**nxt;point p;
        node(node**_n,point _p):
            nxt(_n),p(_p){
        }
        node(const node&a):
            nxt(new node*(*a.nxt)),p(a.p){
        }
        ~node(){
            delete nxt;
        }
        int operator<(const node&a)const{
            if(ctp)
                return p.x==a.p.x?p.y<a.p.y:p.x<a.p.x;
            point p1,p2;
            int f=1;
            if(nxt)
                p1=*nxt?(*nxt)->p-p:point(0,-1),p2=a.p;
            else
                f=0,p1=*a.nxt?(*a.nxt)->p-a.p:point(0,-1),p2=p;
            T x=p1*p2;
            return f?x<0:x>0;
        }
    };
    static int ctp;
    set<node>nds;
    typedef typename set<node>::iterator P;
    int check(P a,P b,P c){
        return (b->p-a->p)*(c->p-b->p)>=0;
    }
    void next(P a,P b){
        *(a->nxt)=(node*)&*b;
    }
    void insert(T x,T y){
        ctp=1;
        node t(new node*(0),point(x,y));
        P it=nds.insert(t).first,itl1=it,itl2,itr1=it,itr2=it;
        if(it!=nds.begin())
            for(next(--itl1,it);itl1!=nds.begin()&&check(--(itl2=itl1),itl1,it);)
                next(itl2,it),nds.erase(itl1),itl1=itl2;
        if(++(itr1=it)!=nds.end())
            next(it,itr1);
        if(itl1!=it&&itr1!=nds.end()&&check(itl1,it,itr1)){
            next(itl1,itr1);
            nds.erase(it);
            return;
        }
        if(itr1!=nds.end())
            for(;++(itr2=itr1)!=nds.end()&&check(it,itr1,itr2);)
                next(it,itr2),nds.erase(itr1),itr1=itr2;
    }
    int size(){
        return nds.size();
    }
    pair<T,T>query(T x,T y){
        ctp=0;
        node t=*nds.lower_bound(node(0,point(x,y)));
        return make_pair(t.p.x,t.p.y);
    }
};
template<class T>int DynamicConvexHull<T>::ctp=0;
