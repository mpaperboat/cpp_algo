#include<bits/stdc++.h>
using namespace std;
template<class T>struct MaximumFlow{
    struct edge{
        int v;
        T c,l;
        edge(int _v,T _c):
            v(_v),c(_c),l(_c){
        }
    };
    int n,src,snk;
    vector<edge>egs;
    vector<vector<int> >bge;
    vector<int>hei,gap,cur,frm;
    MaximumFlow(int _n,int _src,int _snk):
        bge(_n),hei(_n,_n),gap(_n+1),n(_n),cur(_n),frm(_n),src(_src-1),snk(_snk-1){
    }
    void lab(){
        hei[snk]=0;
        queue<int>qu;
        qu.push(snk);
        for(int u;qu.empty()?0:(u=qu.front(),qu.pop(),1);)
            for(int i=0;i<bge[u].size();++i){
                edge&e=egs[bge[u][i]],&ev=egs[bge[u][i]^1];
                if(ev.c>0&&hei[e.v]==n)
                    hei[e.v]=hei[u]+1,qu.push(e.v);
            }
        for(int i=0;i<n;++i)
            ++gap[hei[i]];
    }
    T aug(){
        T f=0;
        for(int u=snk;u!=src;u=egs[frm[u]^1].v)
            if(f<=0||f>egs[frm[u]].c)
                f=egs[frm[u]].c;
        for(int u=snk;u!=src;u=egs[frm[u]^1].v)
            egs[frm[u]].c-=f,egs[frm[u]^1].c+=f;
        return f;
    }
    void add(int u,int v,T c){
        bge[u-1].push_back(egs.size());
        egs.push_back(edge(v-1,c));
        bge[v-1].push_back(egs.size());
        egs.push_back(edge(u-1,0));
    }
    T run(){
        lab();
        T r=0;
        for(int u=src;hei[src]!=n;){
            if(u==snk)
                r+=aug(),u=src;
            int f=0;
            for(int i=cur[u];i<bge[u].size();++i){
                edge&e=egs[bge[u][i]];
                if(e.c>0&&hei[u]==hei[e.v]+1){
                    f=1;
                    frm[e.v]=bge[u][i];
                    u=e.v;
                    break;
                }
            }
            if(!f){
                int mh=n-1;
                for(int i=0;i<bge[u].size();++i){
                    edge&e=egs[bge[u][i]];
                    if(e.c>0&&mh>hei[e.v])
                        mh=hei[e.v];
                }
                if(!--gap[hei[u]])
                    break;
                ++gap[hei[u]=mh+1];
                cur[u]=0;
                if(u!=src)
                    u=egs[frm[u]^1].v;
            }
        }
        return r;
    }
};
