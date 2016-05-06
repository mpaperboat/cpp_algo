#include<bits/stdc++.h>
using namespace std;
template<class T>struct SuffixArray{
    struct node{
        node*c[2],*p;
        T v;
        int f,s,l,h,m;
        double t;
        node(node*_p,T _v,int _l):
            f(rand()*1.0/RAND_MAX*1e9),p(_p),v(_v),s(1),l(_l),h(0),m(0),t(5e8){
            c[0]=c[1]=0;
        }
    }*root;
    vector<T>a;
    SuffixArray():
        root(new node(0,0,0)),a(1){
    }
    ~SuffixArray(){
        clear(root);
    }
    void relabel(node*x,double l,double r){
        x->t=(l+r)/2;
        if(x->c[0])
            relabel(x->c[0],l,x->t);
        if(x->c[1])
            relabel(x->c[1],x->t,r);
    }
    void update(node*x){
        x->s=1;
        x->m=x->h;
        for(int i=0;i<2;++i)
            if(x->c[i])
                x->s+=x->c[i]->s,x->m=min(x->m,x->c[i]->m);
    }
    void rotate(node*&x,int d){
        node*y=x->c[d];
        x->c[d]=y->c[!d];
        y->c[!d]=x;
        y->s=x->s;
        y->m=x->m;
        update(x);
        x=y;
    }
    void clear(node*x){
        if(!x)
            return;
        clear(x->c[0]);
        clear(x->c[1]);
        delete x;
    }
    node*insert(node*&x,node*p,T v,node*l,node*r){
        int d=x->v!=v?x->v<v:x->p->t<p->t;
        double tl=l?l->t:0,tr=r?r->t:1e9;
        node*y;
        if(d)
            l=x;
        else
            r=x;
        if(!x->c[d]){
            y=new node(p,v,p->l+1);
            y->t=((l?l->t:0)+(r?r->t:1e9))/2;
            y->m=y->h=l->v==y->v?lcp(l->p,y->p)+1:0;
            if(r)
                r->h=r->v==y->v?lcp(r->p,y->p)+1:0;
            x->c[d]=y;
        }else
            y=insert(x->c[d],p,v,l,r);
        update(x);
        if(x->c[d]->f>x->f)
            rotate(x,d),relabel(x,tl,tr);
        return y;
    }
    node*insert(node*p,T v){
        a.push_back(v);
        return insert(root,p,v,0,0);
    }
    void erase(node*&x,node*y){
        if(x==y){
            if(!x->c[0]){
                x=x->c[1];
                delete y;
            }else if(!x->c[1]){
                x=x->c[0];
                delete y;
            }else{
                int d=x->c[0]->f<x->c[1]->f;
                rotate(x,d);
                erase(x->c[!d],y);
                --x->s;
            }
        }else
            erase(x->c[x->t<y->t],y),update(x);
    }
    void erase(node*y){
        erase(root,y);
        a.pop_back();
    }
    bool check(node*x,T*y,node*&p,int&l){
        if(p){
            int t=x->c[p->t>x->t]?x->c[p->t>x->t]->m:~0u>>1;
            if(p->t>x->t)
                t=min(t,p->h);
            else
                t=min(t,x->h);
            if(t<l)
                return x->t<p->t;
        }
        for(p=x;l+1<=x->l&&y[l+1];++l)
            if(a[x->l-l]!=y[l+1])
                return a[x->l-l]<y[l+1];
        return y[l+1]!=0;
    }
    int count(node*x,T*y){
        int r=0,l=0;
        for(node*p=0;x;)
            if(check(x,y,p,l))
                r+=(x->c[0]?x->c[0]->s:0)+1,x=x->c[1];
            else
                x=x->c[0];
        return r;
    }
    int count(T*y){
        T*t=y;
        while(*(t+1))
            ++t;
        int r=-count(root,y);
        ++*t;
        r+=count(root,y);
        --*t;
        return r;
    }
    int lcp(node*x,double u,double v,double l,double r){
        if(v<l||u>r||!x)
            return ~0u>>1;
        if(u<l&&v>=r)
            return x->m;
        int t=u<x->t&&v>=x->t?x->h:~0u>>1;
        t=min(t,lcp(x->c[0],u,v,l,x->t));
        t=min(t,lcp(x->c[1],u,v,x->t,r));
        return t;
    }
    int lcp(node*x,node*y){
        if(x->t>y->t)
            swap(x,y);
        return lcp(root,x->t,y->t,0,1e9);
    }
};
