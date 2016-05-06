#include<bits/stdc++.h>
using namespace std;
template<class T>struct SuffixAutomaton{
    struct node{
        node(vector<node*>&all,int m,node*_pr=0,int _ln=0,T _va=T()):
            pr(_pr),tr(m),ln(_ln),va(_va){
            all.push_back(this);
        }
        T va;
        int ln;
        node*pr;
        vector<node*>tr;
    };
    SuffixAutomaton(int _m):
        root(new node(all,m)),m(_m){
    }
    ~SuffixAutomaton(){
        for(int i=0;i<all.size();++i)
            delete all[i];
    }
    node*insert(node*lst,int c,T v){
        node*p=lst,*np=p->tr[c]?0:new node(all,m,0,lst->ln+1,v);
        for(;p&&!p->tr[c];p=p->pr)
            p->tr[c]=np;
        if(!p)np->pr=root;
        else{
            node*q=p->tr[c];
            if(p==lst)
                np=q;
            if(q->ln==p->ln+1)
                p==lst?(q->va+=v):(np->pr=q,0);
            else{
                node*nq=new node(all,m,q->pr,p->ln+1,p==lst?v:T());
                nq->tr=q->tr;
                q->pr=np->pr=nq;
                if(p==lst)
                    np=nq;
                for(;p&&p->tr[c]==q;p=p->pr)
                    p->tr[c]=nq;
            }
        }
        return np;
    }
    void count(){
        vector<int>cnt(all.size());
        vector<node*>tmp=all;
        for(int i=0;i<tmp.size();++i)
            ++cnt[tmp[i]->ln];
        for(int i=1;i<cnt.size();++i)
            cnt[i]+=cnt[i-1];
        for(int i=0;i<tmp.size();++i)
            all[--cnt[tmp[i]->ln]]=tmp[i];
        for(int i=int(all.size())-1;i>0;--i)
            all[i]->pr->va+=all[i]->va;
    }
    int m;
    node*root;
    vector<node*>all;
};
