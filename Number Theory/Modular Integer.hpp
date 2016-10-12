/*
16.10.12
c++14
*/
#include<bits/stdc++.h>
using namespace std;
template<class T>
struct ModularInteger{
    ModularInteger(T t=0):
        v(t){
        if(v<0||v>=p)
            v=(v%p+p)%p;
    }
    auto&operator=(T a){
        v=a;
        if(v<0||v>=p)
            v%=p;
        return*this;
    }
    auto operator-(){
        return v?p-v:0;
    }
    auto&operator+=(ModularInteger<T>a){
        return*this=*this+a;
    }
    auto&operator-=(ModularInteger<T>a){
        return*this=*this-a;
    }
    auto&operator*=(ModularInteger<T>a){
        return*this=*this*a;
    }
    auto&operator/=(ModularInteger<T>a){
        return*this=*this/a;
    }
    T v;
    static T p;
};
template<class T>
auto pow(ModularInteger<T>a,long long b){
    decltype(a)r(1);
    for(;b;b>>=1,a=a*a)
        if(b&1)
            r=r*a;
    return r;
}
template<class T>
auto inv(ModularInteger<T>a){
    return pow(a,a.p-2);
}
template<class T>
auto sqrt(ModularInteger<T>a){
    vector<decltype(a)>r;
    if(!a.v)
        r.push_back(decltype(r)(0));
    else if(pow(a,a.p-1>>1).v==1){
        int s=a.p-1,t=0;
        decltype(r)b=1;
        for(;pow(b,a.p-1>>1).v!=a.p-1;b=rand()*1.0/RAND_MAX*(a.p-1));
        for(;s%2==0;++t,s/=2);
        decltype(r)x=pow(a,(s+1)/2),e=pow(a,s);
        for(int i=1;i<t;++i,e=x*x/a)
            if(pow(e,1<<t-i-1).v!=1)
                x=x*pow(b,(1<<i-1)*s);
        r.push_back(x);
        r.push_back(-x);
    }
    return r;
}
template<class T>
auto operator+(ModularInteger<T>a,decltype(a)b){
    decltype(a)c(a.v+b.v);
    if(c.v>=a.p)
        c.v-=a.p;
    return c;
}
template<class T>
auto operator-(ModularInteger<T>a,decltype(a)b){
    decltype(a)c(a.v-b.v);
    if(c.v<0)
        c.v+=a.p;
    return c;
}
template<class T>
auto operator*(ModularInteger<T>a,decltype(a)b){
    if(typeid(T)!=typeid(int))
        return decltype(a)((a.v*b.v-(long long)(((long double)a.v*b.v+0.5)/a.p)*a.p+a.p)%a.p);
    else
        return decltype(a)((long long)a.v*b.v%a.p);
}
template<class T>
auto operator/(ModularInteger<T>a,decltype(a)b){
    return a*inv(b);
}
template<class T>
bool operator==(ModularInteger<T>a,decltype(a)b){
    return a.v==b.v;
}
template<class T>
bool operator!=(ModularInteger<T>a,decltype(a)b){
    return a.v!=b.v;
}
template<class T>
auto&operator>>(istream&s,ModularInteger<T>&a){
    s>>a.v;
    return s;
}
template<class T>
auto&operator<<(ostream&s,ModularInteger<T>a){
    s<<a.v;
    if(a.v<0||a.v>=a.p)
        a.v%=a.p;
    return s;
}
template<class T>
T ModularInteger<T>::p=1e9+7;