#include<bits/stdc++.h>
using namespace std;
template<class T>struct DynamicSequence{
    struct node{
        node(T _i):
            i(_i),v(_i),s(1),r(0){
                c[0]=c[1]=0;
                static int g;
                w=g=(214013*g+2531011);
        }
        T i,v;
        int s,r,w;
        node*c[2];
    }*rt,*sl,*sr;
    struct pool{
        node*ps,*pp,**ss,**sp;
        int pm,sm;
        vector<node*>ns;
        pool():
            ps((node*)malloc(sizeof(node))),pp(ps),pm(1),ss((node**)malloc(sizeof(node*))),sp(ss),sm(1){
                ns.push_back(ps);
        }
        ~pool(){
            free(ss);
            for(int i=0;i<ns.size();++i)
                free(ns[i]);
        }
        node*crt(T a){
            if(sp!=ss){
                --sp;
                **sp=node(a);
                return*sp;
            }
            if(pp==ps+pm){
                pp=ps=(node*)malloc(sizeof(node)*(pm<<=1));
                ns.push_back(ps);
            }
            *pp=node(a);
            return pp++;
        }
        void des(node*x){
            if(sp==ss+sm){
                node**t=(node**)malloc(sizeof(node*)*sm<<1);
                memcpy(t,ss,sm*sizeof(node*));
                free(ss);
                sp=(ss=t)+sm;
                sm<<=1;
            }
            *(sp++)=x;
        }
    }me;
    node*bud(T*a,int l,int r){
        if(l>r)
            return 0;
        int m=l+r>>1;
        node*t=me.crt(a[m]);
        t->c[0]=bud(a,l,m-1);
        t->c[1]=bud(a,m+1,r);
        pup(t);
        return t;
    }
    void pdw(node*x){
        for(int d=0;d<2&&(x->i>x->v,1);++d)
            if(x->c[d])
                x->i>x->c[d]->i;
        *x->i;
        *x->v;
        if(x->r){
            -x->i;
            for(int d=0;d<2;++d)
                if(x->c[d])
                    x->c[d]->r^=1;
            swap(x->c[0],x->c[1]);
            x->r=0;
        }
    }
    void pup(node*x){
        x->i=x->v;
        x->s=1;
        for(int d=0;d<2;++d)
            if(x->c[d])
                pdw(x->c[d]),x->s+=x->c[d]->s,x->i=d?x->i+x->c[d]->i:x->c[d]->i+x->i;
    }
    void jon(node*x){
        rt=jon(jon(sl,x),sr);
    }
    node*jon(node*x,node*y){
        if(!x)
            return y;
        if(!y)
            return x;
        pdw(x);
        pdw(y);
        if(x->w<y->w){
            x->c[1]=jon(x->c[1],y);
            pup(x);
            return x;
        }else{
            y->c[0]=jon(x,y->c[0]);
            pup(y);
            return y;
        }
    }
    node*spt(int l,int r){
        spt(rt,l-1);
        node*t=sl;
        spt(sr,r-l+1);
        swap(sl,t);
        return t;
    }
    void spt(node*x,int p){
        if(!x){
            sl=sr=0;
            return;
        }
        pdw(x);
        int t=x->c[0]?x->c[0]->s:0;
        if(t<p)
            spt(x->c[1],p-t-1),x->c[1]=sl,sl=x;
        else
            spt(x->c[0],p),x->c[0]=sr,sr=x;
        pup(x);
    }
    void clr(node*x){
        if(x)
            clr(x->c[0]),clr(x->c[1]),me.des(x);
    }
    DynamicSequence(T*a=0,int n=0){
        rt=bud(a,1,n);
    }
    ~DynamicSequence(){
        clr(rt);
    }
    void clear(){
        clr(rt);
        rt=0;
    }
    void insert(T a,int p){
        insert(&a-1,1,p);
    }
    void insert(T*a,int n,int p){
        spt(p+1,p);
        jon(bud(a,1,n));
    }
    void erase(int p){
        erase(p,p);
    }
    void erase(int l,int r){
        clr(spt(l,r));
        jon(0);
    }
    T query(int p){
        return query(p,p);
    }
    T query(int l,int r){
        node*t=spt(l,r);
        T i=t->i;
        jon(t);
        return i;
    }
    void modify(T a,int l){
        modify(a,l,l);
    }
    void modify(T a,int l,int r){
        node*t=spt(l,r);
        a>t->i;
        jon(t);
    }
    void reverse(int l,int r){
        node*t=spt(l,r);
        t->r=1;
        jon(t);
    }
    int length(){
        return rt?rt->s:0;
    }
};
