#ifndef EXPONENTIAL_FUNCTION_OF_POLYNOMIAL
#define EXPONENTIAL_FUNCTION_OF_POLYNOMIAL
#include<bits/stdc++.h>
namespace CTL{
    using namespace std;
    namespace ExponentialFunctionOfPolynomial{
        typedef long long T;
        T pow(T a,T b,T c){T r=1;for(;b;b&1?r=r*a%c:0,b>>=1,a=a*a%c);return r;}
        void ntt(vector<T>&a,int n,int s,vector<int>&rev,T p,T g){
            g=s==1?g:pow(g,p-2,p);vector<T>wm;
            for(int i=0;1<<i<=n;++i)wm.push_back(pow(g,(p-1)>>i,p));
            for(int i=0;i<n;++i)if(i<rev[i])swap(a[i],a[rev[i]]);
            for(int i=1,m=2;1<<i<=n;++i,m<<=1){
                vector<T> wmk(1,1);
                for(int k=1;k<(m>>1);++k)wmk.push_back(wmk.back()*wm[i]%p);
                for(int j=0;j<n;j+=m)for(int k=0;k<(m>>1);++k){
                    T u=a[j+k],v=wmk[k]*a[j+k+(m>>1)]%p;a[j+k]=u+v;a[j+k+(m>>1)]=u-v+p;
                    if(a[j+k]>=p)a[j+k]-=p;if(a[j+k+(m>>1)]>=p)a[j+k+(m>>1)]-=p;}}}
        void dco(vector<T>&a,vector<T>&b,int n,vector<T>&c,vector<T>&u1,vector<T>&u2,T p,T g){
            for(int i=0;i<n;++i)u1[i]=a[i];for(int i=n;i<2*n;++i)u1[i]=0;
            for(int i=0;i<n;++i)u2[i]=b[i];for(int i=n;i<2*n;++i)u2[i]=0;
            vector<int>rev(2*n);int l=round(log2(n));
            for(int i=0;i<2*n;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<l);
            ntt(u1,2*n,1,rev,p,g);ntt(u2,2*n,1,rev,p,g);
            for(int i=0;i<2*n;++i)u1[i]=u1[i]*u2[i]%p;ntt(u1,2*n,-1,rev,p,g);
            for(int i=0,t=pow(2*n,p-2,p);i<n;++i)c[i]=u1[i]*t%p;}
        struct big{big(){a[0]=1;for(int i=1;i<5;++i)a[i]=0;}T a[5];};
        void mul(big&b,T c){
            for(int i=0;i<5;++i)b.a[i]*=c;
            for(int i=0;i<5;++i)if(b.a[i]>=(1<<27)){b.a[i+1]+=(b.a[i]>>27);b.a[i]&=((1<<27)-1);}}
        void add(big&a,big&b){
            for(int i=0;i<5;++i){a.a[i]+=b.a[i];if(a.a[i]>=(1<<27))++a.a[i+1],a.a[i]&=((1<<27)-1);}}
        int cmp(big&a,big&b){
            for(int i=4;i>=0;--i){if(a.a[i]<b.a[i])return -1;if(a.a[i]>b.a[i])return 1;}return 0;}
        void div(big&a){for(int i=4;i>=0;--i){if((a.a[i]&1)&&i)a.a[i-1]+=(1<<27);a.a[i]>>=1;}}
        void mml(big&a,big&b,big&t){
            for(int i=0;i<5;++i)t.a[i]=0;
            for(int i=0;i<5;++i)for(int j=0;j<5;++j)t.a[i+j]+=a.a[i]*b.a[j];
            for(int i=0;i<5;++i)if(t.a[i]>=(1<<27)){
                if(i==4){for(int j=0;j<5;++j)t.a[j]=(1<<27)-1;return;}
                t.a[i+1]+=(t.a[i]>>27);t.a[i]&=((1<<27)-1);}}
        void mod(big&a,big&b){
            big l,r=a;int t=cmp(a,b);if(t==-1)return;if(t==0){for(int i=0;i<5;++i)a.a[i]=0;return;}
            while(1){
                big m=l;add(m,r);div(m);if(!cmp(m,l)||!cmp(m,r))break;
                big tm;mml(m,b,tm);if(cmp(tm,a)==-1)l=m;else r=m;}
            big tm;mml(l,b,tm);for(int i=0;i<5;++i)if((a.a[i]-=tm.a[i])<0)a.a[i]+=(1<<27),--a.a[i+1];}
        T cob(T c1,T c2,T c3,T p1,T p2,T p3,T p){
            big b1;mul(b1,pow(p2*p3%p1,p1-2,p1));mul(b1,c1);mul(b1,p2);mul(b1,p3);
            big b2;mul(b2,pow(p1*p3%p2,p2-2,p2));mul(b2,c2);mul(b2,p1);mul(b2,p3);
            big b3;mul(b3,pow(p1*p2%p3,p3-2,p3));mul(b3,c3);mul(b3,p1);mul(b3,p2);
            big b4;mul(b4,p1);mul(b4,p2);mul(b4,p3);add(b1,b2);add(b1,b3);mod(b1,b4);
            T u0=1,u1=(1<<27)%p,u2=(u1<<27)%p,u3=(u2<<27)%p,u4=(u3<<27)%p;
            return (u0*b1.a[0]+u1*b1.a[1]+u2*b1.a[2]+u3*b1.a[3]+u4*b1.a[4])%p;}
        void con(vector<T>&a,vector<T>&b,int n,vector<T>&c,vector<T>&u1,vector<T>&u2,T p,T g){
            if(g){dco(a,b,n,c,u1,u2,p,g);return;}
            T p1=15*(1<<27)+1,g1=31,p2=63*(1<<25)+1,g2=5,p3=127*(1<<24)+1,g3=3;
            vector<T>c1(n),c2(n),c3(n);dco(a,b,n,c1,u1,u2,p1,g1);
            dco(a,b,n,c2,u1,u2,p2,g2);dco(a,b,n,c3,u1,u2,p3,g3);
            for(int i=0;i<n;++i)c[i]=cob(c1[i],c2[i],c3[i],p1,p2,p3,p);}
        void inv(vector<T>&a,int n,vector<T>&b,vector<T>&u1,vector<T>&u2,T p,T g){
            vector<T>c(n),d(n);b[0]=pow(a[0],p-2,p);fill(b.begin()+1,b.begin()+n,0);
            for(int i=1,m=2;(1<<i)<=n;++i,m<<=1){
                con(a,b,m,c,u1,u2,p,g);
                for(int j=0;j<m;++j)if(c[j]>0)c[j]=p-c[j];
                if((c[0]+=2)>=p)c[0]-=p;con(b,c,m,d,u1,u2,p,g);
               for(int i=0;i<n;++i)b[i]=d[i];}}
        void log(vector<T>&a,int n,vector<T>&b,vector<T>&u1,vector<T>&u2,T p,T g){
            fill(b.begin(),b.begin()+n,0);for(int i=1;i<n;++i)b[i-1]=a[i]*i%p;
            vector<T>c(n),d(n);inv(a,n,c,u1,u2,p,g);
            con(b,c,n,d,u1,u2,p,g);for(int i=0;i<n;++i)b[i]=d[i];
            for(int i=n-2;i>=0;--i)b[i+1]=b[i]*pow(i+1,p-2,p)%p;b[0]=0;}
        vector<T>run(vector<T>a,T p=15*(1<<27)+1,T g=31){
            int tn,l=ceil(log2(tn=a.size())+1e-8),n=1<<l;a.resize(n);
            vector<T>b(n),u1(2*n),u2(2*n),c=b,d=c;b[0]=1;
            for(int i=1,m=2;i<=l;++i,m<<=1){
                log(b,m,c,u1,u2,p,g);for(int j=0;j<m;++j){c[j]-=a[j];if(c[j]<0)c[j]+=p;}
                con(c,b,m,d,u1,u2,p,g);for(int j=0;j<m;++j){b[j]-=d[j];if(b[j]<0)b[j]+=p;}}
            return b.resize(tn),b;}}}
#endif