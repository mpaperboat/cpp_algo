#ifndef N_TH_ROOT_MODULO_M
#define N_TH_ROOT_MODULO_M
#include<bits/stdc++.h>
namespace CTL{
    using namespace std;
    namespace NthRootModuloM{
        typedef long long T;
        T pow(T a,T b,T c){
            T r=1;
            for(;b;b&1?r=r*a%c:0,b>>=1,a=a*a%c);
            return r;}
        int chk(T a,int c=10){
            if(a==1)return 0;
            T u=a-1,t=0;for(;u%2==0;u/=2,++t);
            for(int i=0;i<c;++i){
                T x=pow(rand()*1.0/RAND_MAX*(a-2)+1,u,a),y;
                for(int j=0;j<t;++j){
                    y=x,x=x*x%a;
                    if(x==1&&y!=1&&y!=a-1)return 0;}
                if(x!=1)return 0;}
            return 1;}
        T gcd(T a,T b){
            if(a<0)a=-a;if(b<0)b=-b;return b?gcd(b,a%b):a;}
        T rho(T a,T c){
            T x=double(rand())/RAND_MAX*(a-1),y=x;
            for(int i=1,k=2;;){
                x=(x*x%a+c)%a;T d=gcd(y-x,a);
                if(d!=1&&d!=a)return d;
                if(y==x)return a;
                if(++i==k)y=x,k=2*k;}}
        vector<pair<T,int> >fac(T a){
            if(a==1)
                return vector<pair<T,int> >();
            if(chk(a))
                return vector<pair<T,int> >(1,make_pair(a,1));
            T b=a;
            while((b=rho(b,double(rand())/RAND_MAX*(a-1)))
                ==a);
            vector<pair<T,int> >u=fac(b),v=fac(a/b),r;
            for(int pu=0,pv=0;pu<u.size()||pv<v.size();){
                if(pu==u.size())r.push_back(v[pv++]);
                else if(pv==v.size())r.push_back(u[pu++]);
                else if(u[pu].first==v[pv].first)
                    r.push_back(make_pair(u[pu].first,
                        (u[pu].second+v[pv].second))),++pu,++pv;
                else if(u[pu].first>v[pv].first)r.push_back(v[pv++]);
                else r.push_back(u[pu++]);}
            return r;}
        void dfs(vector<pair<T,int> >&f,int i,T now,vector<T>&r){
            if(i==f.size()){r.push_back(now);return;}
            for(int j=0;j<=f[i].second;++j,now*=f[i].first){
                dfs(f,i+1,now,r);}}
        T prt(T a){
            T pa=a-1;
            vector<pair<T,int> >fpa=fac(pa);vector<T>fs;
            dfs(fpa,0,1,fs);
            for(T g=1,f=0;;++g,f=0){
                for(int i=0;i<fs.size();++i)
                    if(fs[i]!=pa&&pow(g,fs[i],a)==1){f=1;break;}
                if(!f)return g;}}
        int ti[1<<16],va[1<<16],mp[1<<16],nx[1<<16],hd[1<<16],tm,nw;
        void ins(int x,int v){
            int y=x&65535;if(ti[y]!=tm)ti[y]=tm,hd[y]=0;
            for(int i=hd[y];i;i=nx[i])if(va[i]==x){mp[i]=v;return;}
            va[++nw]=x;mp[nw]=v;nx[nw]=hd[y];hd[y]=nw;}
        int get(int x){
            int y=x&65535;if(ti[y]!=tm)ti[y]=tm,hd[y]=0;
            for(int i=hd[y];i;i=nx[i])if(va[i]==x){return mp[i];}
            return -1;}
        void exg(T a,T b,T&x,T&y){
            if(!b)x=1,y=0;else exg(b,a%b,y,x),y-=a/b*x;}
        T inv(T a,T b){T x,y;exg(a,b,x,y);return x+b;}
        T bgs(T a,T b,T c){
            ++tm;nw=0;T m=sqrt(c);
            for(T i=m-1,u=pow(a,i,c),v=inv(a,c);i>=0;--i,u=u*v%c)
                ins(u,i);
            for(T i=0,u=1,v=inv(pow(a,m,c),c);i*m<=c;++i,u=u*v%c){
                T t=u*b%c,j;if((j=get(t))!=-1)return i*m+j;}
            return -1;}
        T pow(T a,T b){return b?pow(a,b-1)*a:1;}
        T spk(T a,T b,T p,T k){
            T pk=1;for(int i=1;i<=k;++i)pk*=p;b%=pk;
            if(!b)return pow(p,k-1-(k-1)/a);
            T c0=0,b0=b;while(b0%p==0)b0/=p,++c0,pk/=p;
            if(c0%a)return 0;
            T g=prt(p),ib0=bgs(g,b0,pk),
                ppk=pk/p*(p-1),d=gcd(a,ppk);
            return ib0%d?0:d*pow(p,c0-c0/a);}
        T run(T a,T b,T c){
            b=(b%c+c)%c;if(c==1)return 1;
            if(a==0)return b==1?c:0;
            T r=1;vector<pair<T,int> >fa=fac(c);
            for(int i=0;i<fa.size();++i)
                if(!(r*=spk(a,b,fa[i].first,fa[i].second)))
                    return 0;
            return r;}}}
#endif