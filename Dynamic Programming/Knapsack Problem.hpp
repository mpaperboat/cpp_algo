#ifndef KNAPSACK_PROBLEM
#define KNAPSACK_PROBLEM
#include<bits/stdc++.h>
namespace CTL{
    using namespace std;
    template<class T>struct KnapsackProblem{
        int n,v;vector<int>vol,vsum;vector<T>val;
        vector<vector<T> >dp;vector<vector<int> >to;
        KnapsackProblem(int _n,int _v):
            n(_n),v(_v),vol(n+1),vsum(n+1),val(n+1),to(n+1){}
        void set(int a,int p,int v,T w){
            to[p].push_back(a);vol[a]=v;val[a]=w;}
        void work(int x){
            for(int i=0;i<to[x].size();++i){
                int y=to[x][i];work(y);vector<T>tdp=dp[x];
                for(int j=0;j<=vsum[x]&&j<=v;++j){
                    for(int k=0;k<=vsum[y]&&j+k<=v;++k)
                        dp[x][j+k]=max(dp[x][j+k],tdp[j]+dp[y][k]);}
                vsum[x]+=vsum[y];}
            vsum[x]+=vol[x];
            for(int i=v;i>=0;--i)
                if(i<vol[x])dp[x][i]=0;
                else dp[x][i]=dp[x][i-vol[x]]+val[x];}
        T run(){
            dp=vector<vector<T> >(n+1,vector<T>(v+1));
            work(0);return dp[0][v];}};}
#endif