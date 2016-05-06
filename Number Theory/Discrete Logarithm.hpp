#include<bits/stdc++.h>
using namespace std;
namespace DiscreteLogarithm{
    typedef long long T;
    int ti[1<<16],va[1<<16],mp[1<<16],nx[1<<16],hd[1<<16],tm,nw;
    void ins(int x,int v){
        int y=x&65535;
        if(ti[y]!=tm)
            ti[y]=tm,hd[y]=0;
        for(int i=hd[y];i;i=nx[i])
            if(va[i]==x){
                mp[i]=v;
                return;
            }
        va[++nw]=x;
        mp[nw]=v;
        nx[nw]=hd[y];
        hd[y]=nw;
    }
    int get(int x){
        int y=x&65535;
        if(ti[y]!=tm)
            ti[y]=tm,hd[y]=0;
        for(int i=hd[y];i;i=nx[i])
            if(va[i]==x){
                return mp[i];
            }
        return -1;
    }
    T pow(T a,T b,T c){
        T r=1;
        for(;b;b&1?r=r*a%c:0,b>>=1,a=a*a%c);
        return r;
    }
    T gcd(T a,T b){
        return b?gcd(b,a%b):a;
    }
    void exg(T a,T b,T&x,T&y){
        if(!b)
            x=1,y=0;
        else
            exg(b,a%b,y,x),y-=a/b*x;
    }
    T inv(T a,T b){
        T x,y;
        exg(a,b,x,y);
        return x+b;
    }
    T bgs(T a,T b,T c){
        ++tm;
        nw=0;
        T m=sqrt(c);
        for(T i=m-1,u=pow(a,i,c),v=inv(a,c);i>=0;--i,u=u*v%c)
            ins(u,i);
        for(T i=0,u=1,v=inv(pow(a,m,c),c);i*m<=c;++i,u=u*v%c){
            T t=u*b%c,j;
            if((j=get(t))!=-1)
                return i*m+j;
        }
        return -1;
    }
    T run(T a,T b,T c){
        T u=1,t=0;
        a=(a%c+c)%c;
        b=(b%c+c)%c;
        for(int i=0;i<32;++i)
            if(pow(a,i,c)==b)
                return i;
        for(T d;(d=gcd(a,c))!=1;++t,u=a/d*u%c,b/=d,c/=d)
            if(b%d)
                return -1;
        return (u=bgs(a,b*inv(u,c)%c,c))<0?-1:u+t;
    }
}
