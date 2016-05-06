#include<bits/stdc++.h>
using namespace std;
template<class T>T PolynomialInterpolation(vector<T>x,vector<T>y,T x0){
    T r=0;
    for(int i=0;i<x.size();++i){
        T p=1,q=1;
        for(int j=0;j<x.size();++j)
            if(j!=i){
                p*=(x0-x[j]);
                q*=(x[i]-x[j]);
            }
        r+=p/q*y[i];
    }
    return r;
}
