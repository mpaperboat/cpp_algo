#include<bits/stdc++.h>
using namespace std;
namespace Convolution{
    template<class T>void kar(T*a,T*b,int n,int l,T*t){
        T*s=t-(3<<l-1);
        for(int i=0;i<2*n;++i)
            *(t+i)=0;
        if(n<=29){
            for(int i=0;i<n;++i)
                for(int j=0;j<n;++j)
                    *(t+i+j)+=*(a+i)**(b+j);
            return;
        }
        kar(a,b,n>>1,l-1,s);
        for(int i=0;i<n;++i)
            *(t+i)+=*(s+i),*(t+i+(n>>1))+=*(s+i);
        kar(a+(n>>1),b+(n>>1),n>>1,l-1,s);
        for(int i=0;i<n;++i)
            *(t+i+n)+=*(s+i),*(t+i+(n>>1))+=*(s+i);
        for(int i=0;i<(n>>1);++i){
            *(t+(n<<1)+i)=*(a+(n>>1)+i)-*(a+i);
            *(t+i+(n>>1)*5)=*(b+i)-*(b+(n>>1)+i);
        }
        kar(t+(n<<1),t+(n>>1)*5,n>>1,l-1,s);
        for(int i=0;i<n;++i)
            *(t+i+(n>>1))+=*(s+i);
    }
    template<class T>auto run(vector<T>a,vector<T>b){
        int l=ceil(log2(max(a.size(),b.size()))+1e-8);
        vector<T>r(a.size()+b.size()-1);
        a.resize(1<<l);
        b.resize(1<<l);
        T*t=new T[3<<l+1];
        kar(&a[0],&b[0],1<<l,l,t+(3<<l)-3);
        for(int i=0;i<r.size();++i)
            r[i]=*(t+(3<<l)-3+i);
        delete t;
        return r;
    }
}