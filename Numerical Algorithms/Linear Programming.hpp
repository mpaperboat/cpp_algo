#include<bits/stdc++.h>
using namespace std;
struct LinearProgramming{
    const double E;
    int n,m,p;
    vector<int>mp,ma,md;
    vector<vector<double>  >a;
    vector<double>res;
    LinearProgramming(int _n,int _m):
        n(_n),m(_m),p(0),a(n+2,vector<double>(m+2)),mp(n+1),ma(m+n+2),md(m+2),res(m+1),E(1e-8){
    }
    void piv(int l,int e){
        swap(mp[l],md[e]);
        ma[mp[l]]=l;
        ma[md[e]]=-1;
        double t=-a[l][e];
        a[l][e]=-1;
        vector<int>qu;
        for(int i=0;i<=m+1;++i)
            if(fabs(a[l][i]/=t)>E)
                qu.push_back(i);
        for(int i=0;i<=n+1;++i)
            if(i!=l&&fabs(a[i][e])>E){
                t=a[i][e];
                a[i][e]=0;
                for(int j=0;j<qu.size();++j)
                    a[i][qu[j]]+=a[l][qu[j]]*t;
            }
        if(-p==l)
            p=e;
        else if(p==e)
            p=-l;
    }
    int opt(int d){
        for(int l=-1,e=-1;;piv(l,e),l=-1,e=-1){
            for(int i=1;i<=m+1;++i)
                if(a[d][i]>E){
                    e=i;
                    break;
                }
            if(e==-1)
                return 1;
            double t;
            for(int i=1;i<=n;++i)
                if(a[i][e]<-E&&(l==-1||a[i][0]/-a[i][e]<t))
                    t=a[i][0]/-a[i][e],l=i;
            if(l==-1)
                return 0;
        }
    }
    double&at(int x,int y){
        return a[x][y];
    }
    vector<double>run(){
        for(int i=1;i<=m+1;++i)
            ma[i]=-1,md[i]=i;
        for(int i=m+2;i<=m+n+1;++i)
            ma[i]=i-(m+1),mp[i-(m+1)]=i;
        double t;
        int l=-1;
        for(int i=1;i<=n;++i)
            if(l==-1||a[i][0]<t)
                t=a[i][0],l=i;
        if(t<-E){
            for(int i=1;i<=n;++i)
                a[i][m+1]=1;
            a[n+1][m+1]=-1;
            p=m+1;
            piv(l,m+1);
            if(!opt(n+1)||fabs(a[n+1][0])>E)
                return vector<double>();
            if(p<0)
                for(int i=1;i<=m;++i)
                    if(fabs(a[-p][i])>E){
                        piv(-p,i);
                        break;
                    }
            for(int i=0;i<=n;++i)
                a[i][p]=0;
        }
        if(!opt(0))
            return vector<double>();
        res[0]=a[0][0];
        for(int i=1;i<=m;++i)
            if(ma[i]!=-1)
                res[i]=a[ma[i]][0];
        return res;
    }
};
