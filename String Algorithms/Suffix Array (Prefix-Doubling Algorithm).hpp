#include<bits/stdc++.h>
using namespace std;
struct SuffixArray{
    int*a,*h,*r,*t,*c,n,m;
    #define lp(u,v)for(int i=u;i<=v;++i)
    #define rp(u,v)for(int i=u;i>=v;--i)
    void sort(){
        memset(c+1,0,m*4);
        lp(1,n)
            ++c[r[t[i]]];
        lp(2,m)
            c[i]+=c[i-1];
        rp(n,1)
            a[c[r[t[i]]]--]=t[i];
    }
    SuffixArray(int*s){
        for(n=m=0;s[n+1];m=max(m,s[++n]));
        a=new int[4*n+max(n,m)+3];
        h=a+n;
        r=h+n+1;
        t=r+n+1;
        c=t+n;
        lp(1,n)
            t[i]=i,r[i]=s[i];
        sort();
        for(int l=1;l<=n;l<<=1,r[a[n]]==n?l=n+1:m=r[a[n]]){
            t[0]=0;
            lp(n-l+1,n)
                t[++t[0]]=i;
            lp(1,n)
                if(a[i]>l)
                    t[++t[0]]=a[i]-l;
            sort();
            swap(r,t);
            r[a[1]]=1;
            lp(2,n)
                r[a[i]]=r[a[i-1]]+(t[a[i]]!=t[a[i-1]]||a[i]+l>n||a[i-1]+l>n||t[a[i]+l]!=t[a[i-1]+l]);
        }
        int l=0;
        a[0]=n+1;
        lp(1,n){
            if(r[i]==1)
                l=0;
            l-=(l>0);
            int j=a[r[i]-1];
            for(;s[i+l]==s[j+l];++l);
            h[r[i]]=l;
        }
    }
    #undef lp
    #undef rp
    ~SuffixArray(){
        delete a;
    }
};
