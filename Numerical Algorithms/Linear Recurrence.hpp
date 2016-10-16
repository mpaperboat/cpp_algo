/*
hn = a1*h(n-1) + a2*h(n-2) + ... + ak*h(n-k)
k^2lgn
那个kara只是常数优化
*/
#include<bits/stdc++.h>
template<class T>
struct LinearRecurrence{
    static void kar(T*a,T*b,int n,int l,T*t){
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
    static auto con(vector<T>a,vector<T>b){
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
    static auto cal(long long n,int k,vector<T>&c){
        vector<T>r(2*k);
        if(n<k){
            r[n]=1;
            return r;
        }
        vector<T>u=cal(n/2,k,c);
        (r=con(u,u)).push_back(0);
        if(n&1)
            r.insert(r.begin(),0);
        for(int i=2*k-1;i>=k;--i)
            for(int j=1;j<=k;++j)
                r[i-j]+=c[j-1]*r[i];
        return vector<T>(r.begin(),r.begin()+k);
    }
    static T run(vector<T>a,vector<T>c,long long n){
        if(n<a.size())
            return a[n];
        int k=a.size();
        vector<T>b=cal(n-k+1,k,c);
        a.resize(2*k-1);
        for(int i=k;i<=2*k-2;++i){
            for(int j=0;j<k;++j)
                a[i]=a[i]+a[i-j-1]*c[j];
        }
        T r=0;
        for(int j=0;j<k;++j)
            r=r+b[j]*a[k-1+j];
        return r;
    }

};
