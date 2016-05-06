#include<bits/stdc++.h>
using namespace std;
struct MaximumMatching{
    int n;
    vector<int>res,nxt,mrk,vis,top,prt,rnk;
    vector<vector<int> >to;
    queue<int>qu;
    MaximumMatching(int _n):
        n(_n),res(n+1),nxt(n+1),mrk(n+1),vis(n+1),top(n+1),to(n+1),prt(n+1),rnk(n+1){
    }
    int fd(int x){
        return x==prt[x]?x:prt[x]=fd(prt[x]);
    }
    void lk(int x,int y){
        if(rnk[x=fd(x)]>rnk[y=fd(y)])
            prt[y]=x;
        else if(rnk[x]<rnk[y])
            prt[x]=y;
        else
            prt[x]=y,++rnk[y];
    }
    int lca(int x,int y){
        static int t;
        ++t;
        for(;;swap(x,y))
            if(x){
                x=top[fd(x)];
                if(vis[x]==t)
                    return x;
                vis[x]=t;
            if(res[x])
                x=nxt[res[x]];
            else
                x=0;
            }
    }
    void uni(int x,int p){
        for(;fd(x)!=fd(p);){
            int y=res[x],z=nxt[y];
            if(fd(z)!=fd(p))
                nxt[z]=y;
            if(mrk[y]==2)
                mrk[y]=1,qu.push(y);
            if(mrk[z]==2)
                mrk[z]=1,qu.push(z);
            int t=top[fd(z)];
            lk(x,y);
            lk(y,z);
            top[fd(z)]=t;
            x=z;
        }
    }
    void aug(int s){
        for(int i=1;i<=n;++i)
            nxt[i]=0,mrk[i]=0,top[i]=i,prt[i]=i,rnk[i]=0;
        mrk[s]=1;
        qu=queue<int>();
        for(qu.push(s);!qu.empty();){
            int x=qu.front();
            qu.pop();
            for(int i=0;i<to[x].size();++i){
                int y=to[x][i];
                if(res[x]==y||fd(x)==fd(y)||mrk[y]==2)
                    continue;
                if(mrk[y]==1){
                    int z=lca(x,y);
                    if(fd(x)!=fd(z))
                        nxt[x]=y;
                    if(fd(y)!=fd(z))
                        nxt[y]=x;
                    uni(x,z);
                    uni(y,z);
                }else if(!res[y]){
                    for(nxt[y]=x;y;){
                        int z=nxt[y],mz=res[z];
                        res[z]=y;
                        res[y]=z;
                        y=mz;
                    }
                    return;
                }else{
                    nxt[y]=x;
                    mrk[res[y]]=1;
                    qu.push(res[y]);
                    mrk[y]=2;
                }
            }
        }
    }
    void add(int x,int y){
        to[x].push_back(y);
        to[y].push_back(x);
    }
    int run(){
        for(int i=1;i<=n;++i)
            if(!res[i])
                for(int j=0;j<to[i].size();++j)
                    if(!res[to[i][j]]){
                        res[to[i][j]]=i;
                        res[i]=to[i][j];
                        break;
                    }
        for(int i=1;i<=n;++i)
            if(!res[i])
                aug(i);
        int r=0;
        for(int i=1;i<=n;++i)
            if(res[i])
                ++r;
        return r/2;
    }
};
