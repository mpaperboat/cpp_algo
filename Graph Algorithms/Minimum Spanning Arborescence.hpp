#include<bits/stdc++.h>
using namespace std;
template<class T>struct MinimumSpanningArborescence{
    struct eg{
        int u,v;
        T w;
    };
    int n,rt;
    vector<eg>egs;
    vector<int>vi,in,id;
    vector<T>inw;
    MinimumSpanningArborescence(int _n,int _rt):
        n(_n),rt(_rt),vi(n+1),in(n+1),inw(n+1),id(n+1){
    }
    void add(int u,int v,T w){
        eg e;
        e.u=u;
        e.v=v;
        e.w=w;
        egs.push_back(e);
    }
    T run(){
        int nv=0;
        for(T r=0;;n=nv,nv=0,rt=id[rt]){
            for(int i=1;i<=n;++i)
                in[i]=-1;
            for(int i=0;i<egs.size();++i)
                if(egs[i].u!=egs[i].v&&(in[egs[i].v]==-1||egs[i].w<inw[egs[i].v]))
                    in[egs[i].v]=egs[i].u,inw[egs[i].v]=egs[i].w;
            for(int i=1;i<=n;++i)
                if(i!=rt&&in[i]==-1)
                    return numeric_limits<T>::max();
            for(int i=1;i<=n;++i){
                if(i!=rt)
                    r+=inw[i];
                id[i]=-1,vi[i]=0;
            }
            for(int i=1;i<=n;++i)
                if(i!=rt&&!vi[i]){
                    int u=i;
                    do{
                        vi[u]=i;
                        u=in[u];
                    }while(!vi[u]&&u!=rt);
                    if(u!=rt&&vi[u]==i){
                        int v=u;
                        ++nv;
                        do{
                            id[v]=nv;
                            v=in[v];
                        }while(v!=u);
                    }
                }
            if(nv==0)
                return r;
            for(int i=1;i<=n;++i)
                if(id[i]==-1)
                    id[i]=++nv;
            for(int i=0;i<egs.size();++i)
                egs[i].w-=inw[egs[i].v],egs[i].u=id[egs[i].u],
                egs[i].v=id[egs[i].v];
        }
    }
};
