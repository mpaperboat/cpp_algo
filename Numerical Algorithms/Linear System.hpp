#include<bits/stdc++.h>
using namespace std;
template<class T>struct LinearSystem{
    int n;
    vector<vector<T> >a;
    vector<int>main,pos;
    vector<T>ans;
    int cmp(T a){
        if(typeid(T)==typeid(double)||typeid(T)==typeid(long double)||typeid(T)==typeid(float)){
            if(a<-1e-8)
                return -1;
            if(a>1e-8)
                return 1;
            return 0;
        }
        if(a<0)
            return -1;
        if(a>0)
            return 1;
        return 0;
    }
    T&at(int i,int j){
        return a[i][j];
    }
    vector<T>&at(int i){
        return a[i];
    }
    LinearSystem(int _n):
        n(_n),a(n+1,vector<T>(n+1)),main(n+1),pos(n+1),ans(n){
    }
    vector<T>run(){
        for(int i=1;i<=n;++i){
            int j=1;
            for(;j<=n&&!cmp(a[i][j]);++j);
            if(j<=n){
                main[i]=j;
                pos[j]=i;
                T t=a[i][j];
                for(int k=0;k<=n;++k)
                    a[i][k]/=t;
                for(int k=1;k<=n;++k)
                    if(k!=i&&cmp(a[k][j])){
                        t=a[k][j];
                        for(int l=0;l<=n;++l)
                            a[k][l]-=a[i][l]*t;
                    }
            }
        }
        for(int i=1;i<=n;++i){
            if(!pos[i])
                return vector<T>();
            ans[i-1]=a[pos[i]][0];
        }
        return ans;
    }
};
