#include<bits/stdc++.h>
using namespace std;
template<class T>struct SteinerTree{
    int n,k,z;
    T inf=numeric_limits<T>::max();
    vector<vector<T> >wei,dp;
    vector<int>im;
    SteinerTree(int _n):
        n(_n),k(0),wei(n+1,vector<T>(n+1,inf)),im(n+1){
    }
    void set(int u){
        if(!im[u])
            im[z=u]=++k;
    }
    void add(int u,int v,T w){
        wei[u][v]=wei[v][u]=min(w,wei[u][v]);
    }
    int upd(T&a,T b,T c){
        if(b!=inf&&c!=inf&&b+c<a){
            a=b+c;
            return 1;
        }
        return 0;
    }
    int ins(int s,int u){
        return im[u]&&((s>>im[u]-1)&1);
    }
    T run(){
        for(int l=1;l<=n;++l)
            for(int i=1;i<=n;++i)
                for(int j=1;j<=n;++j)
                    upd(wei[i][j],wei[i][l],wei[l][j]);
        dp=vector<vector<T> >(1<<k-1,vector<T>(n+1,inf));
        fill(begin(dp[0]),end(dp[0]),0);
        for(int s=1;s<(1<<k-1);++s){
            queue<int>qu;
            vector<int>in(n+1);
            for(int u=1;u<=n;++u){
                if(ins(s,u))
                    continue;
                qu.push((u));
                in[u]=1;
                for(int t=(s-1)&s;t;t=(t-1)&s)
                    upd(dp[s][u],dp[t][u],dp[s^t][u]);
                for(int v=1;v<=n;++v)
                    if(ins(s,v))
                        upd(dp[s][u],dp[s^(1<<im[v]-1)][v],wei[u][v]);
            }
            for(int u;qu.empty()?0:(u=qu.front(),qu.pop(),in[u]=0,1);)
                for(int v=1;v<=n;++v)
                    if(!ins(s,v)&&upd(dp[s][v],dp[s][u],wei[u][v])&&!in[v])
                        in[v]=1,qu.push(v);
        }
        return k?dp[(1<<k-1)-1][z]:0;
    }
};
