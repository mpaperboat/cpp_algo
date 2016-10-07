#include<bits/stdc++.h>
using namespace std;
template<class T,class C>struct Set{
    struct node{
        node(T u){
            c[0]=c[1]=0,v=u,s=1;
            f=rand()*1.0/RAND_MAX*2e9;
        }
        T v;
        node*c[2];
        int s,f;
    }*j,*k;
    int size(node*x){
        return x?x->s:0;
    }
    void update(node*x){
        x->s=1;
        for(int i=0;i<2;++i)
            x->s+=size(x->c[i]);
    }
    node*merge(node*x,node*y){
        if(!x||!y)
            return x?x:y;
        if(x->f<y->f)
            x->c[1]=merge(x->c[1],y),y=x;
        else
            y->c[0]=merge(x,y->c[0]);
        update(y);
        return y;
    }
    void split(node*x,int t){
        if(x){
            int s=size(x->c[0]);
            if(s>=t)
                split(x->c[0],t),
                x->c[0]=k,k=x;
            else
                split(x->c[1],t-s-1),
                x->c[1]=j,j=x;
            update(x);
        }else
            j=k=0;
    }
    void clear(node*x){
        if(x){
            clear(x->c[0]);
            clear(x->c[1]);
            delete x;
        }
    }
    node*find(node*z,T a){
        node*r=0;
        while(z)
            if(C()(a,z->v))
                z=z->c[0];
            else if(C()(z->v,a))
                z=z->c[1];
            else
                break;
        return r;
    }
    node*select(node*z,int a){
        for(;;)
            if(size(z->c[0])>=a)
                z=z->c[0];
            else if(size(z->c[0])+1<a)
                a-=size(z->c[0])+1,z=z->c[1];
            else
                return z;
    }
    pair<node*,int>count(node*z,T a,int d){
        int c=0;
        node*r=0;
        while(z)
            if(C()(d?a:z->v,d?z->v:a))
                r=z,c+=size(z->c[d])+1,
                z=z->c[!d];
            else
                z=z->c[d];
        return make_pair(r,c);
    }
    node*erase(node*x,T v){
        split(x,count(x,v,0).second);
        node*y=j;split(k,1);delete j;
        return merge(y,k);
    }
    node*insert(node*x,T v){
        split(x,count(x,v,0).second);
        return merge(merge(j,new node(v)),k);
    }
};