#ifndef SYMMETRIC_GAME_OF_NO_RETURN
#define SYMMETRIC_GAME_OF_NO_RETURN
#include<bits/stdc++.h>
namespace CTL{
    using namespace std;
    struct SymmetricGameOfNoReturn{
        int n;vector<int>mh,nx,mk,vs,tp,pr,rk;
        vector<bool>wi;queue<int>qu;
        vector<vector<int> >to;
        SymmetricGameOfNoReturn(int _n):
            n(_n),mh(n+1),nx(n+1),mk(n+1),wi(n+1,true),
            vs(n+1),tp(n+1),to(n+1),pr(n+1),rk(n+1){}
        int fd(int x){return x==pr[x]?x:pr[x]=fd(pr[x]);}
        void lk(int x,int y){
            if(rk[x=fd(x)]>rk[y=fd(y)])pr[y]=x;
            else if(rk[x]<rk[y])pr[x]=y;
            else pr[x]=y,++rk[y];}
        int lca(int x,int y){
            static int t;++t;
            for(;;swap(x,y))if(x){
                x=tp[fd(x)];if(vs[x]==t)return x;vs[x]=t;
                if(mh[x])x=nx[mh[x]];else x=0;}}
        void uni(int x,int p){
            for(;fd(x)!=fd(p);){
                int y=mh[x],z=nx[y];
                if(fd(z)!=fd(p))nx[z]=y;
                if(mk[y]==2)mk[y]=1,qu.push(y);
                if(mk[z]==2)mk[z]=1,qu.push(z);
                int t=tp[fd(z)];lk(x,y);lk(y,z);
                tp[fd(z)]=t;x=z;}}
        void aug(int s,int t){
            for(int i=1;i<=n;++i)
                nx[i]=0,mk[i]=0,tp[i]=i,pr[i]=i,rk[i]=0;
            mk[s]=1;qu=queue<int>();
            for(qu.push(s);!qu.empty();){
                int x=qu.front();qu.pop();if(t)wi[x]=0;
                for(int i=0;i<to[x].size();++i){
                    int y=to[x][i];
                    if(mh[x]==y||fd(x)==fd(y)||mk[y]==2)
                        continue;
                    if(mk[y]==1){
                        int z=lca(x,y);
                        if(fd(x)!=fd(z))nx[x]=y;
                        if(fd(y)!=fd(z))nx[y]=x;
                        uni(x,z);uni(y,z);
                    }else if(!mh[y]){
                        nx[y]=x;while(y){
                            int z=nx[y],mz=mh[z];
                            mh[z]=y;mh[y]=z;y=mz;}
                        return;
                    }else{
                        nx[y]=x;mk[mh[y]]=1;
                        qu.push(mh[y]);mk[y]=2;}}}}
        void add(int x,int y){
            to[x].push_back(y);to[y].push_back(x);}
        vector<bool>run(){
            for(int i=1;i<=n;++i)if(!mh[i])
                for(int j=0;j<to[i].size();++j)
                    if(!mh[to[i][j]]){
                        mh[to[i][j]]=i;mh[i]=to[i][j];break;}
            for(int i=1;i<=n;++i)if(!mh[i])aug(i,0);
            for(int i=1;i<=n;++i)if(!mh[i])aug(i,1);
            return wi;}};}
#endif