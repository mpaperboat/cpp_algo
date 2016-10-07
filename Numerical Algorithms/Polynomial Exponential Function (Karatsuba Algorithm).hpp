#ifndef EXPONENTIAL_FUNCTION_OF_POLYNOMIAL
#define EXPONENTIAL_FUNCTION_OF_POLYNOMIAL
#include<algorithm>
#include<cmath>
#include<vector>
namespace CTL{
    using namespace std;
    template<class T>struct ExponentialFunctionOfPolynomial{
        static void kar(T*a,T*b,int n,int l,T**r){
            T*rl=r[l],*rll=r[l-1]; for(int i=0;i<2*n;++i)*(rl+i)=0;
            if(n<=30){for(int i=0;i<n;++i)for(int j=0;j<n;++j)
                *(rl+i+j)+=*(a+i)**(b+j);return;}
            kar(a,b,n>>1,l-1,r);
            for(int i=0;i<n;++i)*(rl+i)+=*(rll+i),*(rl+i+(n>>1))+=*(rll+i);
            kar(a+(n>>1),b+(n>>1),n>>1,l-1,r);
            for(int i=0;i<n;++i)*(rl+i+n)+=*(rll+i),*(rl+i+(n>>1))+=*(rll+i);
            for(int i=0;i<(n>>1);++i)
                *(rl+(n<<1)+i)=*(a+(n>>1)+i)-*(a+i),
                *(rl+i+(n>>1)*5)=*(b+i)-*(b+(n>>1)+i);
            kar(rl+(n<<1),rl+(n>>1)*5,n>>1,l-1,r);
            for(int i=0;i<n;++i)*(rl+i+(n>>1))+=*(rll+i);}
        static void inv(vector<T>&a,int n,vector<T>&b,T**r){
            vector<T>c(n);b[0]=T(1)/a[0];fill(b.begin()+1,b.begin()+n,0);
            for(int i=1,m=2;(1<<i)<=n;++i,m<<=1){
                kar(&a[0],&b[0],m,i,r);
                for(int j=0;j<m;++j)c[j]=-r[i][j];c[0]+=T(2);
                kar(&b[0],&c[0],m,i,r);
                for(int j=0;j<m;++j)b[j]=r[i][j];}}
        static void log(vector<T>&a,int n,vector<T>&b,T**r){
            fill(b.begin(),b.begin()+n,0);for(int i=1;i<n;++i)b[i-1]=a[i]*T(i);
            vector<T>c(n);inv(a,n,c,r);int l=round(log2(n));
            kar(&b[0],&c[0],n,l,r);for(int i=0;i<n;++i)b[i]=r[l][i];
            for(int i=n-2;i>=0;--i)b[i+1]=b[i]/T(i+1);b[0]=0;}
        static vector<T>run(vector<T>a){
            int tn,l=ceil(log2(tn=a.size())+1e-8),n=1<<l;a.resize(n);
            vector<T>b(n),c=b,d=c;b[0]=1;
            T**r=new T*[l+1];for(int i=0;i<=l;++i)r[i]=new T[(1<<i)*3];
            for(int i=1,m=2;i<=l;++i,m<<=1){
                copy(b.begin(),b.begin()+m,d.begin());log(b,m,c,r);
                for(int j=0;j<m;++j)c[j]-=a[j];
                kar(&d[0],&c[0],m,i,r);
                for(int j=0;j<m;++j)b[j]-=r[i][j];}
            for(int i=0;i<=l;++i)delete r[i];delete r;
            return b.resize(tn),b;}};}
#endif