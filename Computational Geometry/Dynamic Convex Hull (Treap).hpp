#include<bits/stdc++.h>
using namespace std;
template<class T>struct DynamicConvexHull{
    struct point{
        T x,y;
        point(T _x,T _y):
            x(_x),y(_y){
        }
        point operator-(const point&a)const{
            point p(x-a.x,y-a.y);
            return p;
        }
        T operator*(const point&a)const{
            return x*a.y-y*a.x;
        }
        int operator<(const point&a)const{
            return x==a.x?y<a.y:x<a.x;
        }
        int operator==(const point&a)const{
            return x==a.x&&y==a.y;
        }
    };
    struct hull{
        point*pt;
        hull*ch[2],*nb[2];
        int sz,fx;
        hull(point*_pt):
            pt(_pt),sz(1),fx(rand()*1.0/RAND_MAX*1e9){
            ch[0]=ch[1]=nb[0]=nb[1]=0;
        }
        T check(point p){
            return (nb[1]?*nb[1]->pt-*pt:point(0,-1))*p;
        }
        void update(){
            sz=1;
            for(int i=0;i<2;++i)
                if(ch[i])
                    sz+=ch[i]->sz;
        }
    };
    static int sz(hull*x){
        return x?x->sz:0;
    }
    static point&pt(hull*x){
        return*x->pt;
    }
    static struct memory{
        hull*ps,*pp,**ss,**sp;
        int pm,sm;
        vector<hull*>ns;
        memory():
            ps((hull*)malloc(sizeof(hull))),pp(ps),pm(1),ss((hull**)malloc(sizeof(hull*))),sp(ss),sm(1){
            ns.push_back(ps);
        }
        ~memory(){
            free(ss);
            for(int i=0;i<ns.size();++i)
                free(ns[i]);
        }
        hull*create(const hull&x){
            if(sp!=ss){
                --sp;
                **sp=x;
                return*sp;
            }
            if(pp==ps+pm){
                pp=ps=(hull*)malloc(sizeof(hull)*(pm<<=1));
                ns.push_back(ps);
            }
            *pp=x;
            return pp++;
        }
        void destroy(hull*x){
            if(sp==ss+sm){
                hull**t=(hull**)malloc(sizeof(hull*)*sm<<1);
                memcpy(t,ss,sm*sizeof(hull*));
                free(ss);
                sp=(ss=t)+sm;
                sm<<=1;}
            *(sp++)=x;
        }
    }me;
    struct array{
        hull**ps,**pp;
        int pm;
        array():
            ps((hull**)malloc(sizeof(hull*))),pp(ps),pm(1){
        }
        ~array(){
            free(ps);
        }
        int size(){
            return pp-ps;
        }
        hull*operator[](int i){
            return ps[i];
        }
        void push(hull*x){
            if(pp==ps+pm){
                hull**t=(hull**)malloc(sizeof(hull*)*pm<<1);
                memcpy(t,ps,pm*sizeof(hull*));
                free(ps);
                pp=(ps=t)+pm;
                pm<<=1;
            }
            *(pp++)=x;
        }
    };
    static hull*link(hull*x,hull*y,hull*lb,hull*rb,int d,array&ns){
        hull*r=me.create(*x);
        if(x==lb||x==rb){
            r->nb[d]=y;
            if(y)
                y->nb[!d]=r;
        }else
            r->ch[d]=link(r->ch[d],y,lb,rb,d,ns);
        r->update();
        ns.push(r);
        return r;
    }
    static hull*merge(hull*x,hull*y,hull*lb,hull*rb,array&ns){
        if(!x)
            return y;
        if(!y)
            return x;
        int d=x->fx>y->fx;
        hull*r=me.create(d?*x:*y);
        r->ch[d]=d?merge(r->ch[1],y,lb,rb,ns):merge(x,y->ch[0],lb,rb,ns);
        if(d&&x==lb||!d&&y==rb)
            r->ch[d]=link(r->ch[d],r,lb,rb,!d,ns);
        r->update();
        ns.push(r);
        return r;
    }
    static pair<hull*,hull*>split(hull*x,int k,array&ns){
        if(!x)
            return make_pair((hull*)0,(hull*)0);
        int t=sz(x->ch[0])+1;
        hull*r=me.create(*x);
        ns.push(r);
        pair<hull*,hull*>s=split(x->ch[k>=t],k-t*(k>=t),ns);
        if(k>=t){
            r->ch[1]=s.first;r->update();
            return make_pair(r,s.second);
        }else{
            r->ch[0]=s.second;r->update();
            return make_pair(s.first,r);
        }
    }
    static void turn(hull*&x,int d,int&k){
        k+=(sz((x=x->ch[d])->ch[!d])+1)*(2*d-1);
    }
    static pair<T,T>range(hull*x){
        hull*l=x,*r=x;
        while(l->ch[0])
            l=l->ch[0];
        while(r->ch[1])
            r=r->ch[1];
        return make_pair(pt(l).x,pt(r).x);
    }
    static hull*merge(hull*x,hull*y,array&ns){
        int kp=sz(x->ch[0])+1,kq=sz(y->ch[0])+1,pd[2],qd[2];
        pair<T,T>pr=range(x),qr=range(y);
        int pf=1;
        hull*p=x,*q=y;
        if(pr.second==qr.first&&pr.first==pr.second&&p->ch[pf=0])
            turn(p,0,kp);
        for(point pq=pt(q)-pt(p);;pq=pt(q)-pt(p)){
            pd[0]=(p->nb[0]&&(pt(p->nb[0])-pt(p))*pq<=0)*pf;
            qd[1]=(q->nb[1]&&(pt(q->nb[1])-pt(q))*pq<=0);
            pd[1]=(p->nb[1]&&(pt(p->nb[1])-pt(p))*pq<0)*pf;
            qd[0]=(q->nb[0]&&(pt(q->nb[0])-pt(q))*pq<0);
            if(!(pd[0]+pd[1]+qd[0]+qd[1])){
                hull*l=split(x,kp,ns).first,*r=split(y,kq-1,ns).second,*lb=l,*rb=r;
                while(lb->ch[1])
                    lb=lb->ch[1];
                while(rb->ch[0])
                    rb=rb->ch[0];
                return merge(l,r,lb,rb,ns);
            }
            if(!(pd[0]+pd[1]))
                turn(q,qd[1],kq);
            if(!(qd[0]+qd[1]))
                turn(p,pd[1],kp);
            if(pd[0]&&qd[1])
                turn(p,0,kp),turn(q,1,kq);
            if(pd[1]&&qd[1])
                turn(q,1,kq);
            if(pd[0]&&qd[0])turn(p,0,kp);
            if(pd[1]&&qd[0]){
                point vp=pt(p->nb[1])-pt(p),vq=pt(q->nb[0])-pt(q);
                if(vp.x==0&&vq.x==0)
                    turn(p,1,kp),turn(q,0,kq);
                else if(vp.x==0)
                    turn(p,1,kp);
                else if(vq.x==0)
                    turn(q,0,kq);
                else{
                    long double m=pr.second,pb=vp.y*(m-pt(p).x),qb=vq.y*(m-pt(q).x);
                    pb=pb/vp.x+pt(p).y;
                    qb=qb/vq.x+pt(q).y;
                    if(qb>pb+1e-8)
                        turn(q,0,kq);
                    else if(pb>qb+1e-8)
                        turn(p,1,kp);
                    else if(pt(q->nb[0]).x+pt(p->nb[1]).x<2*m)
                        turn(q,0,kq);
                    else
                        turn(p,1,kp);
                }
            }
        }
    }
    hull*query(hull*x,point p){
        for(hull*y=0;;){
            T d=x->check(p);
            if(d>0)
                y=x,x=x->ch[0];
            else if(d<0)
                x=x->ch[1];
            else
                y=x;
            if(!d||!x)
                return y;
        }
    }
    struct treap{
        int fx,ct,sz;
        point pt;
        treap*ch[2];
        struct hull*ip,*hu;
        array ns;
        treap(point _pt):
            fx(rand()*1.0/RAND_MAX*1e9),ct(1),sz(1),pt(_pt),ip(me.create(hull(&pt))),hu(ip){
            ch[0]=ch[1]=0;
        }
        ~treap(){
            for(hull**i=ns.ps;i!=ns.pp;++i)
                me.destroy(*i);
            me.destroy(ip);
        }
        void update(){
            for(hull**i=ns.ps;i!=ns.pp;++i)
                me.destroy(*i);
            ns.pp=ns.ps;
            sz=1;
            hu=ip;
            if(ch[0])
                hu=merge(ch[0]->hu,hu,ns),sz+=ch[0]->sz;
            if(ch[1])
                hu=merge(hu,ch[1]->hu,ns),sz+=ch[1]->sz;
        }
    }*root;
    void rotate(treap*&x,int d){
        treap*y=x->ch[d];
        x->ch[d]=y->ch[!d];
        y->ch[!d]=x;
        x=y;
    }
    int insert(treap*&x,point p){
        if(!x)
            x=new treap(p);
        else if(p==x->pt){
            ++x->ct;
            return 0;
        }else{
            int d=x->pt<p;
            if(!insert(x->ch[d],p))
                return 0;
            if(x->ch[d]->fx>x->fx)
                rotate(x,d),x->ch[!d]->update();
            x->update();
        }
        return 1;
    }
    int erase(treap*&x,point p){
        if(p==x->pt){
            if(x->ct>1){
                --x->ct;
                return 0;
            }
            treap*y=x;
            if(!x->ch[0])
                x=x->ch[1],delete y;
            else if(!x->ch[1])
                x=x->ch[0],delete y;
            else{
                int d=x->ch[0]->fx<x->ch[1]->fx;
                rotate(x,d);
                erase(x->ch[!d],p);
                x->update();
            }
            return 1;
        }
        if(erase(x->ch[x->pt<p],p)){
            x->update();
            return 1;
        }else{
            --x->sz;
            return 0;
        }
    }
    void clear(treap*x){
        if(x)
            clear(x->ch[0]),clear(x->ch[1]),delete x;
    }
    DynamicConvexHull():
        root(0){
    }
    ~DynamicConvexHull(){
        clear(root);
    }
    int size(){
        return root?root->sz:0;
    }
    void insert(T x,T y){
        insert(root,point(x,y));
    }
    void erase(T x,T y){
        erase(root,point(x,y));
    }
    pair<T,T>query(T x,T y){
        point r=pt(query(root->hu,point(x,y)));
        return make_pair(r.x,r.y);
    }
};
template<class T>typename DynamicConvexHull<T>::memory DynamicConvexHull<T>::me;
