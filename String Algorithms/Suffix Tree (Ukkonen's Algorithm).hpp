#include<bits/stdc++.h>
using namespace std;
template<class T,int N,int M,T D>struct SuffixTree{
    struct node;
    struct edge{
        edge():
            l(0),r(0),t(0){
        }
        int length(){
            return r-l;
        }
        T*l,*r;
        node*t;
    }pe[2*N],*ep=pe;
    edge*newedge(T*l,T*r,node*t){
        ep->l=l;
        ep->r=r;
        ep->t=t;
        return ep++;
    }
    struct node{
        node():
            s(0),c({0}){
        }
        node*s;
        edge*c[M];
    }pn[2*N+1],*np=pn;
    SuffixTree():
        root(np++),ct(0){
    }
    void extend(T*s){
        for(;ae&&al>=ae->length();){
            s+=ae->length();
            al-=ae->length();
            an=ae->t;
            ae=al?an->c[*s-D]:0;
        }
    }
    bool extend(int c){
        if(ae){
            if(*(ae->l+al)-D-c)
                return true;
            ++al;
        }else{
            if(!an->c[c])
                return true;
            ae=an->c[c];
            al=1;
            if(pr)
                pr->s=an;
        }
        extend(ae->l);
        return false;
    }
    void insert(T*s,int n){
        ct+=n;
        an=root;
        ae=al=0;
        for(T*p=s;p!=s+n;++p)
            for(pr=0;extend(*p-D);){
                edge*x=newedge(p,s+n,np++);
                if(!ae)
                    an->c[*p-D]=x;
                else{
                    edge*&y=an->c[*ae->l-D];
                    y=newedge(ae->l,ae->l+al,np++);
                    y->t->c[*(ae->l+=al)-D]=ae;
                    y->t->c[*p-D]=x;
                    ae=y;
                }
                if(pr)
                    pr->s=ae?ae->t:an;
                pr=ae?ae->t:an;
                int r=1;
                if(an==root&&!al)
                    break;
                if(an==root)
                    --al;
                else{
                    an=an->s?an->s:root;
                    r=0;
                }
                if(al){
                    T*t=ae->l+(an==root)*r;
                    ae=an->c[*t-D];
                    extend(t);
                }else
                    ae=0;
            }
    }
    edge*ae;
    int al,ct;
    node*root,*an,*pr;
};
