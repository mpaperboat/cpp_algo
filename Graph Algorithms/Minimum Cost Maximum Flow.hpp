#include<bits/stdc++.h>
using namespace std;
template<class F=int,class C=int>struct MinimumCostMaximumFlow{
    struct edge{
        edge(int _v,F _c,C _w):
            v(_v),c(_c),w(_w){
        }
        int v;
        F c;
        C w;
    };
    MinimumCostMaximumFlow(int _n,int _src,int _snk,F _all):
        n(_n),src(_src-1),snk(_snk-1),bg(_n),vis(n),dis(n),all(_all),flow(0),cost(0){}
    void add(int u,int v,F c,C w){
        bg[u-1].push_back(eg.size());
        eg.push_back(edge(v-1,c,w));
        bg[v-1].push_back(eg.size());
        eg.push_back(edge(u-1,0,-w));
    }
    int spfa(){
        vector<int>in(n,0);
        queue<int>qu;
        fill(vis.begin(),vis.end(),0);
        dis[src]=0;
        vis[src]=in[src]=1;
        qu.push(src);
        while(!qu.empty()){
            int u=qu.front();
            qu.pop();
            in[u]=0;
            for(int i=0;i<bg[u].size();++i){
                edge&e=eg[bg[u][i]];
                if(e.c!=0&&(!vis[e.v]||dis[u]+e.w<dis[e.v])){
                    dis[e.v]=dis[u]+e.w;
                    vis[e.v]=1;
                    if(!in[e.v]){
                        in[e.v]=1;
                        qu.push(e.v);
                    }
                }
            }
        }
        return vis[snk]&&dis[snk]<0;
    }
    F dfs(int u,F f){
        if(u==snk)
            return f;
        F g=f;
        vis[u]=1;
        for(int i=0;i<bg[u].size();++i){
            edge&e=eg[bg[u][i]],&ev=eg[bg[u][i]^1];
            if(e.c!=0&&dis[e.v]==dis[u]+e.w&&!vis[e.v]){
                F t=dfs(e.v,min(g,e.c));
                g-=t;
                e.c-=t;
                ev.c+=t;
                cost+=t*e.w;
                if(g==0)
                    return f;
            }
        }
        return f-g;
    }
    pair<F,C>run(){
        while(all!=0&&spfa()){
            F t;
            do{
                fill(vis.begin(),vis.end(),0);
                flow+=(t=dfs(src,all));
                all-=t;
            }while(t!=0);
        }
        return make_pair(flow,cost);
    }
    int n,src,snk;
    vector<vector<int> >bg;
    vector<edge>eg;
    vector<int>vis;
    vector<C>dis;
    F all,flow;
    C cost;
};
