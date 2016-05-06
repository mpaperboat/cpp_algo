#include<bits/stdc++.h>
using namespace std;
template<class T>struct LinkCutTree{
    struct node{
        node():
            ch({0,0}),pr(0),rev(0){
        }
        node*ch[2],*pr;
        T ifo;
        int rev;
    }*ptrs;
    LinkCutTree(int n):
        ptrs(new node[n]-1){
    }
    ~LinkCutTree(){
        delete ptrs;
    }
    int direct(node*x){
        if(!x->pr)
            return 2;
        if(x==x->pr->ch[0])
            return 0;
        if(x==x->pr->ch[1])
            return 1;
        return 2;
    }
    void down(node*x){
        if(x->rev){
            x->ifo.reverse();
            swap(x->ch[0],x->ch[1]);
            for(int i=0;i<2;++i)
                if(x->ch[i])
                    x->ch[i]->rev^=1;
            x->rev=0;
        }
        x->ifo.down(x->ch[0]?&x->ch[0]->ifo:0,x->ch[1]?&x->ch[1]->ifo:0);
    }
    void up(node*x){
        for(int i=0;i<2;++i)
            if(x->ch[i])
                down(x->ch[i]);
        x->ifo.up(x->ch[0]?&x->ch[0]->ifo:0,x->ch[1]?&x->ch[1]->ifo:0);
    }
    void setchild(node*x,node*y,int d){
        x->ch[d]=y;
        if(y)
            y->pr=x;
        up(x);
    }
    void rotate(node*x){
        node*y=x->pr,*z=y->pr;
        int d1=direct(x),d2=direct(y);
        setchild(y,x->ch[!d1],d1);
        setchild(x,y,!d1);
        if(d2<2)
            setchild(z,x,d2);
        else
            x->pr=z;
    }
    void release(node*x){
        if(direct(x)<2)
            release(x->pr);
        down(x);
    }
    void splay(node*x){
        for(release(x);direct(x)<2;){
            node*y=x->pr;
            if(direct(y)==2)
                rotate(x);
            else if(direct(x)==direct(y))
                rotate(y),rotate(x);
            else
                rotate(x),rotate(x);
        }
    }
    node*access(node*x){
        node*y=0;
        for(;x;y=x,x=x->pr){
            splay(x);
            setchild(x,y,1);
        }
        return y;
    }
    void evert(node*x){
        access(x);
        splay(x);
        x->rev=1;
    }
    void set(int x,T v){
        ptrs[x].ifo=v;
    }
    int linked(int a,int b){
        access((ptrs+a));
        node*z=access((ptrs+b));
        return z==access((ptrs+a));
    }
    void link(int a,int b){
        evert((ptrs+b));
        (ptrs+b)->pr=(ptrs+a);
    }
    void cut(int a,int b){
        access((ptrs+b));
        node*z=access((ptrs+a));
        if(z==(ptrs+a))
            splay((ptrs+b)),(ptrs+b)->pr=0;
        else
            access((ptrs+b)),splay((ptrs+a)),(ptrs+a)->pr=0;
    }
    int root(int a){
        access((ptrs+a));
        splay((ptrs+a));
        node*r=(ptrs+a);
        while(r->ch[1])
            r=r->ch[1];
        return r-ptrs;
    }
    void evert(int a){
        evert((ptrs+a));
    }
    int lca(int a,int b){
        access((ptrs+a));
        return access((ptrs+b))-ptrs;
    }
    T query(int a){
        splay((ptrs+a));
        T p=(ptrs+a)->ifo;
        p.up(0,0);
        return p;
    }
    T query(int a,int b){
        if((ptrs+a)==(ptrs+b))
            return query((ptrs+a));
        access((ptrs+a));
        node*c=access((ptrs+b));
        T p=c.ifo;
        if(c==(ptrs+b)){
            splay((ptrs+a));
            T q=(ptrs+a)->ifo;
            q.reverse();
            p.up(&q,0);
            return p;
        }else if(c==(ptrs+a))
            p.up(0,&(ptrs+a)->ch[1]->ifo);
        else{
            splay((ptrs+a));
            T q=(ptrs+a)->ifo;
            q.reverse();
            p.up(&q,&c->ch[1]->ifo);
        }
        return p;
    }
    T equery(int a){
        return query(a);
    }
    T equery(int a,int b){
        access((ptrs+a));
        node*c=access((ptrs+b));
        if(c==(ptrs+b)){
            splay((ptrs+a));
            T q=(ptrs+a)->ifo;
            q.reverse();
            return q;
        }else if(c==(ptrs+a))
            return (ptrs+a)->ch[1]->ifo;
        else{
            splay((ptrs+a));
            node*t=c->ch[1];
            while(t->ch[0])
                t=t->ch[0];
            splay(t);
            if(t->ch[1])
                down(t->ch[1]);
            T p=t->ifo,q=(ptrs+a)->ifo;
            q.reverse();
            p.up(&q,t->ch[1]?&t->ch[1]->ifo:0);
            return p;
        }
    }
    template<class F>void modify(int a,F f){
        splay((ptrs+a));
        f(&(ptrs+a)->ifo);
        up((ptrs+a));
    }
    template<class F>void modify(int a,int b,F f){
        if((ptrs+a)==(ptrs+b)){
            splay((ptrs+a));
            f(0,&(ptrs+a)->ifo,0);
            up((ptrs+a));
            return;
        }
        access((ptrs+a));
        node*c=access((ptrs+b));
        if(c==(ptrs+b))
            splay((ptrs+a)),f(&(ptrs+a)->ifo,&(ptrs+b)->ifo,0);
        else if(c==a)
            f(0,&(ptrs+a)->ifo,&(ptrs+a)->ch[1]->ifo);
        else
            splay(a),f(&(ptrs+a)->ifo,&c->ifo,&c->ch[1]->ifo);
        up(c);
    }
    template<class F>void emodify(int a,F f){
        modify(a,f);
    }
    template<class F>void emodify(int a,int b,F f){
        access((ptrs+a));
        node*c=access((ptrs+b));
        if(c==(ptrs+b))
            splay((ptrs+a)),f(&(ptrs+a)->ifo,0);
        else if(c==a)
            f(0,&(ptrs+a)->ch[1]->ifo);
        else
            splay(a),f(&(ptrs+a)->ifo,&c->ch[1]->ifo);
        up(c);
    }
};
