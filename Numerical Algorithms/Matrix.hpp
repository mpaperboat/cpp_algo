/*
16.10.12
c++14
Î¬¶È¶¯Ì¬»¯
*/
#include<bits/stdc++.h>
template<class T>
struct Matrix{
    Matrix(int _n,T t=0):
        n(_n),v(n,vector<T>(n)){
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                v[i][j]=i==j?t:0;
    }
    int n;
    vector<vector<T>>v;    
};
template<class T>
auto operator+(const Matrix<T>&a,decltype(a)b){
    Matrix<T>c;
    for(int i=0;i<a.n;++i)
        for(int j=0;j<a.n;++j)
            c.v[i][j]=a.v[i][j]+b.v[i][j];
    return c;
}
template<class T>
auto operator*(const Matrix<T>&a,decltype(a)b){
    Matrix<T>c(a.n);
    for(int i=0;i<a.n;++i)
        for(int j=0;j<a.n;++j)
            for(int k=0;k<a.n;++k)
                c.v[i][j]+=a.v[i][k]*b.v[k][j];
    return c;
}
template<class T>
auto operator*(const Matrix<T>&a,const T&b){
    Matrix<T>c=a;
    for(int i=0;i<a.n;++i)
        for(int j=0;j<a.n;++j)
            c.v[i][j]*=b;
    return c;
}
template<class T>
Matrix<T>operator/(const Matrix<T>&a,const T&b){
    Matrix<T>c=a;
    for(int i=0;i<a.n;++i)
        for(int j=0;j<a.n;++j)
            c.v[i][j]/=b;
    return c;
}
template<class T>
Matrix<T>pow(Matrix<T>a,long long b){
    Matrix<T>r(a.n,1);
    for(;b;a=a*a,b>>=1)
        if(b&1)
            r=r*a;
    return r;
}