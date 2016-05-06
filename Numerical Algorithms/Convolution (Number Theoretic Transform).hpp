#include<bits/stdc++.h>
using namespace std;
namespace Convolution{
    typedef long long T;
    T pow(T a,T b,T c){
        T r=1;
        for(;b;b&1?r=r*a%c:0,b>>=1,a=a*a%c);
        return r;
    }
    void ntt(vector<T>&a,int n,int s,vector<int>&rev,T p,T g){
        g=s==1?g:pow(g,p-2,p);
        vector<T>wm;
        for(int i=0;1<<i<=n;++i)
            wm.push_back(pow(g,(p-1)>>i,p));
        for(int i=0;i<n;++i)
            if(i<rev[i])
                swap(a[i],a[rev[i]]);
        for(int i=1,m=2;1<<i<=n;++i,m<<=1){
            vector<T>wmk(1,1);
            for(int k=1;k<(m>>1);++k)
                wmk.push_back(wmk.back()*wm[i]%p);
            for(int j=0;j<n;j+=m)
                for(int k=0;k<(m>>1);++k){
                    T u=a[j+k],v=wmk[k]*a[j+k+(m>>1)]%p;
                    a[j+k]=u+v;
                    a[j+k+(m>>1)]=u-v+p;
                    if(a[j+k]>=p)
                        a[j+k]-=p;
                    if(a[j+k+(m>>1)]>=p)
                        a[j+k+(m>>1)]-=p;
                }
        }
    }
    vector<T>run(vector<T>a,vector<T>b,T p=15*(1<<27)+1,T g=31){
        int tn,l=ceil(log2(tn=a.size()+b.size()-1)),n=1<<l;
        vector<int>rv;
        for(int i=(rv.resize(n),0);i<n;++i)
            rv[i]=(rv[i>>1]>>1)|((i&1)<<(l-1));
        a.resize(n);
        b.resize(n);
        ntt(a,n,1,rv,p,g);
        ntt(b,n,1,rv,p,g);
        for(int i=0;i<n;++i)
            a[i]=a[i]*b[i]%p;
        ntt(a,n,-1,rv,p,g);
        n=pow(n,p-2,p);
        for(T&v:a)
            v=v*n%p;
        return a.resize(tn),a;
    }
}
