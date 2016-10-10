#ifndef K_BASED_DYNAMIC_SUBTRACTION_GAME
#define K_BASED_DYNAMIC_SUBTRACTION_GAME
#include<bits/stdc++.h>
namespace CTL{
    using namespace std;
    namespace KBasedDynamicSubtractionGame{
        int run(int n,int k){
            vector<int>a=vector<int>(1,1),b=a;
            for(int i=-1;b.back()<n;b.push_back(a.back()+b[i]*(i>=0)))
                for(a.push_back(b.back()+1);a[i+1]*k<a.back();++i);
            if(a.back()==n)return 0;
            for(int i=a.size()-1;i>=0;n-=a[i]*(n>a[i]),--i)
                if(n==a[i])return a[i];}}}
#endif