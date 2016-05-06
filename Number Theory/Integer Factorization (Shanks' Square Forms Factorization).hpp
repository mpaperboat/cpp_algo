#include<bits/stdc++.h>
using namespace std;
namespace IntegerFactorization{
    typedef long long ll;
    typedef unsigned long long ull;
    ll lim=3689348814694258326ll;
    ull srt(const ull&a){
        ull b=sqrt(a);
        b-=b*b>a;
        return b+=(b+1)*(b+1)<=a;
    }
    int sqr(const ull&a,ll&b){
        b=srt(a);
        return b*b==a;
    }
    ull gcd(const ull&a,const ull&b){
        return b?gcd(b,a%b):a;
    }
    ll amb(ll a,const ll&B,const ll&dd,const ll&D){
        for(ll q=(dd+B/2)/a,b=q*a*2-B,c=(D-b*b)/4/a,qc,qcb,a0=a,b0=a,b1=b,c0=c;;b1=b,c0=c){
            if(c0>dd)
                qcb=c0-b,b=c0+qcb,c=a-qcb;
            else{
                q=(dd+b/2)/c0;
                if(q==1)
                    qcb=c0-b,b=c0+qcb,c=a-qcb;
                else
                    qc=q*c0,qcb=qc-b,b=qc+qcb,c=a-q*qcb;
            }
            if(a=c0,b==b1)
                break;
            if(b==b0&&a==a0)
                return 0;
        }
        return a&1?a:a>>1;
    }
    ull fac(const ull&n){
        if(n&1^1)
            return 2;
        if(n%3==0)
            return 3;
        if(n%5==0)
            return 5;
        if(srt(n)*srt(n)==n)
            return srt(n);
        static ll d1,d2,a1,b1,c1,dd1,L1,a2,b2,c2,dd2,L2,a,q,c,qc,qcb,D1,D2,bl1[1<<19],bl2[1<<19];
        int p1=0,p2=0,ac1=1,ac2=1,j,nm4=n&3;
        if(nm4==1)
            D1=n,D2=5*n,d2=srt(D2),dd2=d2/2+d2%2,b2=(d2-1)|1;
        else
            D1=3*n,D2=4*n,dd2=srt(D2),d2=dd2*2,b2=d2;
        d1=srt(D1),b1=(d1-1)|1,c1=(D1-b1*b1)/4,c2=(D2-b2*b2)/4,L1=srt(d1),L2=srt(d2),dd1=d1/2+d1%2;
        for(int i=a1=a2=1;ac1||ac2;++i){
            #define m(t)\
            if(ac##t){\
                c=c##t;\
                q=c>dd##t?1:(dd##t+b##t/2)/c;\
                if(q==1)\
                    qcb=c-b##t,b##t=c+qcb,c##t=a##t-qcb;\
                else\
                    qc=q*c,qcb=qc-b##t,b##t=qc+qcb,c##t=a##t-q*qcb;\
                if((a##t=c)<=L##t)\
                    bl##t[p##t++]=a##t;\
            }
            m(1)m(2)
            if(i&1)
                continue;
            #define m(t)\
            if((ac##t=ac##t&a##t!=1)&&sqr(a##t,a)){\
                if(a<=L##t)\
                    for(j=0;j<p##t;j++)\
                        if(a==bl##t[j]){\
                            a=0;\
                            break;\
                        }\
                if(a>0){\
                    if((q=gcd(a,b##t))>1)\
                        return q*q;\
                    q=amb(a,b##t,dd##t,D##t);\
                    if(nm4==5-2*t&&(q=amb(a,b##t,dd##t,D##t))%(2*t+1)==0)\
                        q/=2*t+1;\
                    if(q>1)\
                        return q;\
                }\
            }
            m(1)m(2)
            #undef m
        }
        for(int i=3;;i+=2)
            if(n%i==0)
                return i;
    }
    ll mul(const ll&x,const ll&y,const ll&z){
        return(x*y-(ll)(((long double)x*y+0.5)/z)*z+z)%z;
    }
    ll pow(ll a,ll b,const ll&c){
        ll r=1;
        for(;b;b&1?r=mul(r,a,c):0,b>>=1,a=mul(a,a,c));
        return r;
    }
    int chk(const ll&a){
        if(a==2)
            return 1;
        if(a%2==0||a<2)
            return 0;
        static int pf[]={2,325,9375,28178,450775,9780504,1795265022};
        ll u=a-1,t=0,p;
        for(;u%2==0;u/=2,++t);
        for(int i=0;i<7;++i){
            p=pf[i]%a;
            if(!p||p==a-1)
                continue;
            ll x=pow(p,u,a);
            if(x==1)
                continue;
            for(int j=0;x!=a-1&&j<t;++j){
                x=mul(x,x,a);
                if(x==1)
                    return 0;
            }
            if(x==a-1)
                continue;
            return 0;
        }
        return 1;
    }
    vector<pair<ll,int> >run(const ll&a){
        if(a==1)
            return vector<pair<ll,int> >();
        if(chk(a))
            return vector<pair<ll,int> >(1,make_pair(a,1));
        ll b=fac(a);
        vector<pair<ll,int> >u=run(b),v=run(a/b),r;
        for(int pu=0,pv=0;pu<u.size()||pv<v.size();){
            if(pu==u.size())
                r.push_back(v[pv++]);
            else if(pv==v.size())
                r.push_back(u[pu++]);
            else if(u[pu].first==v[pv].first)
                r.push_back(make_pair(u[pu].first,(u[pu].second+v[pv].second))),++pu,++pv;
            else if(u[pu].first>v[pv].first)
                r.push_back(v[pv++]);
            else
                r.push_back(u[pu++]);}
        return r;
    }
}
