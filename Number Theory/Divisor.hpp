#ifndef DIVISOR
#define DIVISOR
#include<bits/stdc++.h>
namespace CTL{
    namespace Divisor{
        template<class T>void dfs(vector<pair<T,int> >&a,
            int i,T now,vector<T>&r){
            if(i==a.size()){r.push_back(now);return;}
            for(int j=0;j<=a[i].second;++j,now*=a[i].first){
                dfs(a,i+1,now,r);}}
        template<class T>vector<T>run(vector<pair<T,int> >a){
            vector<T> r;dfs(a,0,1,r);return r;}}}
#endif