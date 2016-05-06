#include<bits/stdc++.h>
using namespace std;
template<class T,int N,int M,T D>struct FactorOracle{
    void insert(T*s,int n){
        memset(tr,(lrs[0]=0,sp[0]=-1),4*M);
        for(int i=0,j,c=s[i]-D,u,v;i<n;c=s[++i]-D){
            memset(tr+i+1,(lrs[i+1]=0)-1,4*M);
            for(j=i;j>-1&&tr[j][c]<0;tr[j][c]=i+1,j=sp[u=j]);
            if(v=sp[i+1]=j<0?0:tr[j][c]){
                for(v=v-1==sp[u]?u:v-1;sp[u]!=sp[v];v=sp[v]);
                lrs[i+1]=min(lrs[u],lrs[v])+1;
            }
        }
    }
    int sp[N+1],lrs[N+1],tr[N+1][M];
};
