#include<bits/stdc++.h>
using namespace std;
template<class T,class C>struct RedBlackTree{
    struct node{
        node(T _v,node*l,node*r,node*_p,int _b,int _s):
            v(_v),p(_p),b(_b),s(_s){
            c[0]=l;
            c[1]=r;
        }
        T v;
        node*c[2],*p;
        int b,s;
    }*root,*nil;
    void clear(node*x){
        if(x!=nil){
            clear(x->c[0]);
            clear(x->c[1]);
            delete x;
        }
    }
    void rotate(node*x,int d){
        node*y=x->c[!d];
        x->c[!d]=y->c[d];
        if(y->c[d]!=nil)
            y->c[d]->p=x;
        y->p=x->p;
        if(x->p==nil)
            root=y;
        else
            x->p->c[x!=x->p->c[0]]=y;
        y->c[d]=x;
        x->p=y;
        y->s=x->s;
        x->s=x->c[0]->s+x->c[1]->s+1;
    }
    void insert_fixup(node*z){
        while(!z->p->b){
            int d=z->p==z->p->p->c[0];
            node*y=z->p->p->c[d];
            if(!y->b)
                z->p->b=1,y->b=1,(z=z->p->p)->b=0;
            else{
                if(z==z->p->c[d])
                    rotate(z=z->p,!d);
                z->p->b=1;
                z->p->p->b=0;
                rotate(z->p->p,d);
            }
        }
        root->b=1;
    }
    void erase(node*z){
        node*y;
        for(y=z;y!=nil;y=y->p)
            --y->s;
        if(z->c[0]==nil||z->c[1]==nil)
            y=z;
        else{
            for(y=z->c[1];y->c[0]!=nil;)
                y=y->c[0];
            z->v=y->v;
            y=z->c[1];
            while(y->c[0]!=nil)
                --y->s,y=y->c[0];
        }
        node*x=y->c[y->c[0]==nil];
        x->p=y->p;
        if(y->p==nil)
            root=x;
        else
            y->p->c[y!=y->p->c[0]]=x;
        if(y->b)
            erase_fixup(x);
        delete y;
    }
    void erase_fixup(node*x){
        while(x!=root&&x->b){
            int d=x==x->p->c[0];
            node*w=x->p->c[d];
            if(!w->b){
                w->b=1;
                x->p->b=0;
                rotate(x->p,!d);
                w=x->p->c[d];
            }
            if(w->c[0]->b&&w->c[1]->b)
                w->b=0,x=x->p;
            else{
                if(w->c[d]->b)
                    w->c[!d]->b=1,w->b=0,rotate(w,d),w=x->p->c[d];
                w->b=x->p->b;
                x->p->b=1;
                w->c[d]->b=1;
                rotate(x->p,!d);
                x=root;
            }
        }
        x->b=1;
    }
    node*clone(node*x,node*y){
        if(x.size==0)
            return nil;
        node*z=new node(*x);
        z->c[0]=clone(x->c[0],z);
        z->c[1]=clone(x->c[1],z);
        z->p=y;
        return z;
    }
    node*precursor(node*x){
        if(x->c[0]->count){
            for(x=x->c[0];x->c[1]->count;)
                x=x->c[1];
            return x;
        }else{
            node*y=x->p;
            while(y->count&&x==y->c[0])
                x=y,y=y->p;
            return y;
        }
    }
    node*successor(node*x){
        if(x->c[1]->count){
            for(x=x->c[1];x->c[0]->count;)
                x=x->c[0];
            return x;
        }else{
            node*y=x->p;
            while(y->count&&x==y->c[1])
                x=y,y=y->p;
            return y;
        }
    }
    RedBlackTree(){
        root=nil=(node*)malloc(sizeof(node));
        nil->b=1;
        nil->s=0;
    }
    RedBlackTree(const RedBlackTree&a){
        nil=new node(*a.nil);
        root=clone(a.root,nil);
    }
    ~RedBlackTree(){
        clear(root);
        free(nil);
    }
    RedBlackTree&operator=(const RedBlackTree&a){
        clear(root);
        root=clone(a.root,nil);
        return*this;
    }
    node*begin(){
        node*z=root;
        while(z!=nil&&z->c[0]!=nil)
            z=z->c[0];
        return z;
    }
    node*reverse_begin(){
        node*z=root;
        while(z!=nil&&z->c[1]!=nil)
            z=z->c[1];
        return z;
    }
    node*end(){
        return nil;
    }
    node*reverse_end(){
        return nil;
    }
    void clear(){
        clear(root);
        root=nil;
    }
    void insert(T a){
        node*y=nil,*x=root;
        while(x!=nil)
            y=x,++x->s,x=x->c[C()(x->v,a)];
        node*z=new node(a,nil,nil,y,0,1);
        if(y==nil)
            root=z;
        else
            y->c[C()(y->v,z->v)]=z;
        insert_fixup(z);
    }
    void erase(T a){
        node*z=root;
        for(;;)
            if(C()(a,z->v))
                z=z->c[0];
            else if(C()(z->v,a))
                z=z->c[1];
            else
                break;
        erase(z);
    }
    int count(T a){
        return count_less_equal(a)-count_less(a);
    }
    int count_less(T a){
        int r=0;
        node*z=root;
        while(z!=nil)
            if(C()(z->v,a))
                r+=z->c[0]->s+1,z=z->c[1];
            else
                z=z->c[0];
        return r;
    }
    int count_less_equal(T a){
        int r=0;
        node*z=root;
        while(z!=nil){
            if(!C()(a,z->v))
                r+=z->c[0]->s+1,z=z->c[1];
            else
                z=z->c[0];
        }
        return r;
    }
    int count_greater(T a){
        int r=0;
        node*z=root;
        while(z!=nil)
            if(C()(a,z->v))
                r+=z->c[1]->s+1,z=z->c[0];
            else
                z=z->c[1];
        return r;
    }
    int count_greater_equal(T a){
        int r=0;
        node*z=root;
        while(z!=nil)
            if(!C()(z->v,a))
                r+=z->c[1]->s+1,z=z->c[0];
            else
                z=z->c[1];
        return r;
    }
    node*nth_element(int a){
        node*z=root;
        for(;;)
            if(z->c[0]->s>=a)
                z=z->c[0];
            else if((z->c[0]->s+1)<a)
                a-=z->c[0]->s+1,z=z->c[1];
            else
                return z;
    }
    node*precursor(T a){
        node*z=root,*r=nil;
        while(z!=nil)
            if(C()(z->v,a))
                r=z,z=z->c[1];
            else
                z=z->c[0];
        return r;
    }
    node*successor(T a){
        node*z=root,*r=nil;
        while(z!=nil)
            if(C()(a,z->v))
                r=z,z=z->c[0];
            else
                z=z->c[1];
        return r;
    }
    node*find(T a){
        node*z=root,*r=nil;
        while(z!=nil)
            if(C()(a,z->v))
                z=z->c[0];
            else if(C()(z->v,a))
                z=z->c[1];
            else
                break;
        return r;
    }
    node*lower_bound(T a){
        node*z=root,*r=nil;
        while(z!=nil)
            if(C()(z->v,a))
                r=z,z=z->c[1];
            else if(C()(a,z->v))
                z=z->c[0];
            else
                r=z,z=z->c[0];
        return r;
    }
    node*upper_bound(T a){
        return successor(a);
    }
    pair<node*,node*> equal_range(T a){
        return make_pair(lower_bound(a),upper_bound(a));
    }
    int size(){
        return root->s;
    }
    int empty(){
        return !root->s;
    }
    T front(){
        return*begin();
    }
    T back(){
        return*reverse_begin();
    }
};
