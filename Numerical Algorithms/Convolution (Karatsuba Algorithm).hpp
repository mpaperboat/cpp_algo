#include<bits/stdc++.h>
using namespace std;
namespace Convolution{
    template<class T>void kar(T*a,T*b,int n,int l,T**r){
        T*rl=r[l],*rll=r[l-1];
        for(int i=0;i<2*n;++i)
            *(rl+i)=0;
        if(n<=30){
            for(int i=0;i<n;++i)
                for(int j=0;j<n;++j)
                    *(rl+i+j)+=*(a+i)**(b+j);
            return;
        }
        kar(a,b,n>>1,l-1,r);
        for(int i=0;i<n;++i)
            *(rl+i)+=*(rll+i),*(rl+i+(n>>1))+=*(rll+i);
        kar(a+(n>>1),b+(n>>1),n>>1,l-1,r);
        for(int i=0;i<n;++i)
            *(rl+i+n)+=*(rll+i),*(rl+i+(n>>1))+=*(rll+i);
        for(int i=0;i<(n>>1);++i){
            *(rl+(n<<1)+i)=*(a+(n>>1)+i)-*(a+i);
            *(rl+i+(n>>1)*5)=*(b+i)-*(b+(n>>1)+i);
        }
        kar(rl+(n<<1),rl+(n>>1)*5,n>>1,l-1,r);
        for(int i=0;i<n;++i)
            *(rl+i+(n>>1))+=*(rll+i);}
    template<class T>vector<T>run(vector<T>a,vector<T>b){
        int l=ceil(log2(max(a.size(),b.size()))+1e-8);
        vector<T>rt(a.size()+b.size()-1);
        a.resize(1<<l);
        b.resize(1<<l);
        T**r=new T*[l+1];
        for(int i=0;i<=l;++i)
            r[i]=new T[(1<<i)*3];
        kar(&a[0],&b[0],1<<l,l,r);
        for(int i=0;i<rt.size();++i)
            rt[i]=*(r[l]+i);
        for(int i=0;i<=l;++i)
            delete r[i];
        delete r;
        return rt;
    }
}
