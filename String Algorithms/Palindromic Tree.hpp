#include<bits/stdc++.h>
using namespace std;
template<class T>struct PalindromicTree{
    struct node{
        node(int m,node*f,int l):
            nxt(m),fail(f),len(l){
        }
        vector<node*>nxt;
        node*fail;
        T val;
        int len;
    }*root;
    int m;
    vector<int>str;
    vector<node*>all;
    PalindromicTree(int _m):
        m(_m){
        node*n0=new node(m,0,-2),*n1=new node(m,n0,-1),*n2=new node(m,n1,0);
        all.push_back(n0);
        all.push_back(n1);
        all.push_back(n2);
        fill(n0->nxt.begin(),n0->nxt.end(),n2);
        root=n1;
    }
    ~PalindromicTree(){
        for(int i=0;i<all.size();++i)
            delete all[i];
    }
    node*find(node*x){
        while(x->fail&&str[str.size()-x->len-2]!=str[str.size()-1])
            x=x->fail;
        return x;
    }
    node*insert(node*p,int c,T v){
        if(p==root)
            str=vector<int>(1,-1);
        str.push_back(c);
        p=find(p);
        if(!p->nxt[c]){
            node*np=(p->nxt[c]=new node(m,find(p->fail)->nxt[c],p->len+2));
            all.push_back(np);
        }
        p->nxt[c]->val+=v;
        return p->nxt[c];
    }
    void count(){
        for(int i=all.size()-1;i>=1;--i)
            all[i]->fail->val+=all[i]->val;
    }
};
