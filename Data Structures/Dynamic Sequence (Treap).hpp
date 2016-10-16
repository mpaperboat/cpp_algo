/*
基于信息类的平衡树
实现了一切操作
函数式treap
快速内存池
*/
#include<bits/stdc++.h>
using namespace std;
template<class IFO>
struct DynamicSequence{
    struct node{
        node(IFO _ifo):
            ifo(_ifo),val(_ifo),siz(1),rev(0){
            chd[0]=chd[1]=0;
            static int g;
            wei=g=(214013*g+2531011);
        }
        IFO ifo,val;
        int siz,rev,wei;
        node*chd[2];
    }*sl,*sr;
    struct pool{
        node*ps,*pp,**ss,**sp;
        int pm,sm;
        vector<node*>ns;
        pool():
            ps((node*)malloc(sizeof(node))),pp(ps),pm(1),ss((node**)malloc(4)),sp(ss),sm(1){
            ns.push_back(ps);
        }
        ~pool(){
            free(ss);
            for(int i=0;i<ns.size();++i)
                free(ns[i]);
        }
        node*_new(IFO a){
            if(sp!=ss){
                --sp;
                **sp=node(a);
                return*sp;
            }
            if(pp==ps+pm){
                pp=ps=(node*)malloc(sizeof(node)*(pm*=2));
                ns.push_back(ps);
            }
            *pp=node(a);
            return pp++;
        }
        void _delete(node*x){
            if(sp==ss+sm){
                node**t=(node**)malloc(8*sm);
                memcpy(t,ss,4*sm);
                free(ss);
                sp=(ss=t)+sm;
                sm<<=1;
            }
            *(sp++)=x;
        }
    }mem;
    node*build(IFO*a,int l,int r){
        if(l>r)
            return 0;
        int m=l+r>>1;
        node*t=mem._new(a[m]);
        t->ch[0]=build(a,l,m-1);
        t->ch[1]=build(a,m+1,r);
        up(t);
        return t;
    }
    void clear(node*x){
        if(x)
            clear(x->chd[0]),clear(x->chd[1]),mem._delete(x);
    }
    void down(node*x){
        for(int d=0;d<2;++d){
            if(x->chd[d])
                x->ifo>>x->chd[d]->ifo;
            if(!d)
                x->ifo>>x->val;
        }
        *x->ifo;
        *x->val;
        if(x->rev){
            -x->ifo;
            for(int d=0;d<2;++d)
                if(x->chd[d])
                    x->chd[d]->rev^=1;
            swap(x->chd[0],x->chd[1]);
            x->rev=0;
        }
    }
    void up(node*x){
        x->ifo=x->val;
        x->siz=1;
        for(int d=0;d<2;++d)
            if(x->chd[d]){
                down(x->chd[d]);
                x->siz+=x->chd[d]->siz;
                x->ifo=d?x->ifo+x->chd[d]->ifo:x->chd[d]->ifo+x->ifo;
            }
    }
    node*join(node*x,node*y){
        if(!x)
            return y;
        if(!y)
            return x;
        down(x);
        down(y);
        if(x->wei<y->wei){
            x->chd[1]=join(x->chd[1],y);
            up(x);
            return x;
        } else{
            y->chd[0]=join(x,y->chd[0]);
            up(y);
            return y;
        }
    }
    node*join(node*x){
        return join(join(sl,x),sr);
    }
    int size(node*x){
        return x?x->siz:0;
    }
    void array(node*x,vector<IFO>&r){
        if(x){
            down(x);
            array(x->chd[0],r);
            r.push_back(x->val);
            array(x->chd[1],r);
        }
    }
    auto array(node*x){
        vector<IFO>r;
        array(x,r);
        return r;
    }
    void split(node*x,int p){
        if(!x){
            sl=sr=0;
            return;
        }
        down(x);
        int t=x->chd[0]?x->chd[0]->siz:0;
        if(t<p)
            split(x->chd[1],p-t-1),x->chd[1]=sl,sl=x;
        else
            split(x->chd[0],p),x->chd[0]=sr,sr=x;
        up(x);
    }
    node*split(node*x,int l,int r){
        split(x,l-1);
        node*t=sl;
        split(sr,r-l+1);
        swap(sl,t);
        return t;
    }
    void insert(node*&x,IFO a,int p){
        x=insert(&a-1,1,p);
    }
    void insert(node*&x,IFO*a,int n,int p){
        split(x,p+1,p);
        x=join(build(a,1,n));
    }
    void erase(node*&x,int p){
        erase(x,p,p);
    }
    void erase(node*&x,int l,int r){
        clear(split(x,l,r));
        x=join(0);
    }
    IFO query(node*&x,int p){
        return query(x,p,p);
    }
    IFO query(node*&x,int l,int r){
        node*t=split(x,l,r);
        IFO i=t->i;
        x=join(t);
        return i;
    }
    void modify(node*&x,IFO a,int l){
        modify(x,a,l,l);
    }
    void modify(node*&x,IFO a,int l,int r){
        node*t=split(x,l,r);
        a>>t->i;
        x=join(t);
    }
    void reverse(node*&x,int l,int r){
        node*t=split(x,l,r);
        t->r=1;
        x=join(t);
    }
    void split(node*x,IFO p,int d=0){
        if(!x){
            sl=sr=0;
            return;
        }
        down(x);
        if((!d&&x->val<p)||(d&&!(p<x->val)))
            split(x->chd[1],p,d),x->chd[1]=sl,sl=x;
        else
            split(x->chd[0],p,d),x->chd[0]=sr,sr=x;
        up(x);
    }
    node*split(node*x,IFO l,IFO r){
        split(x,l);
        node*t=sl;
        split(sr,r,1);
        swap(sl,t);
        return t;
    }
    void insert(node*&x,IFO a){
        split(x,a);
        x=join(mem._new(a));
    }
    void insert(node*&x,IFO*a,int n,IFO p){

        x=join(build(a,1,n));
    }
    void erase(node*&x,IFO p){
        return x=erase(x,p,p);
    }
    void erase(node*&x,IFO l,IFO r){
        clear(split(x,l,r));
        x=join(0);
    }
    IFO query(node*&x,IFO p){
        return query(x,p,p);
    }
    IFO query(node*&x,IFO l,IFO r){
        node*t=split(x,l,r);
        IFO i=t?t->i:IFO();
        x=join(t);
        return i;
    }
    int count(node*&x,IFO p){
        return count(x,p,p);
    }
    int count(node*&x,IFO l,IFO r){
        node*t=split(x,l,r);
        int s=t?t->siz:0;
        x=join(t);
        return s;
    }
    void modify(node*&x,IFO a,IFO l){
        modify(x,a,l,l);
    }
    void modify(node*&x,IFO a,IFO l,IFO r){
        node*t=split(x,l,r);
        if(t)
            a>>t->ifo;
        x=join(t);
    }
    void reverse(node*&x,IFO l,IFO r){
        node*t=split(x,l,r);
        if(t)
            t->r=1;
        x=join(t);
    }
    IFO predecessor(node*x,IFO a){
        IFO t;
        while(x){
            down(x);
            if(x->val<a){
                t=x->val;
                x=x->chd[1];
            } else
                x=x->chd[0];
        }
        return t;
    }
    IFO successor(node*x,IFO a){
        IFO t;
        while(x){
            down(x);
            if(a<x->val){
                t=x->val;
                x=x->chd[0];
            } else
                x=x->chd[1];
        }
        return t;
    }
    IFO front(node*x){
        IFO t;
        while(x){
            down(x);
            t=x->val;
            x=x->chd[0];
        }
        return t;
    }
    IFO back(node*x){
        IFO t;
        while(x){
            down(x);
            t=x->val;
            x=x->chd[1];
        }
        return t;
    }
};
struct ifo{
    ifo(){
    }
    void operator*(){
    }
    void operator-(){
    }
};
ifo operator+(const ifo&a,const ifo&b){
    return ifo();
}
void operator>>(const ifo&a,ifo&b){
}
bool operator<(const ifo&a,const ifo&b){
    return true;
}