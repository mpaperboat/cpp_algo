#include<bits/stdc++.h>
using namespace std;
struct MaximalPlanarityTesting{
    int n,m;
    vector<set<int> >to2;
    vector<vector<int> >to;
    vector<int>dec,rmd,mrk,invc,rt;
    vector<list<int>::iterator>dpos,pos;
    bool order(int v1,int v2,int vn){
        rt[0]=v1;
        rt[1]=v2;
        rt[n-1]=vn;
        fill(invc.begin(),invc.end(),0);
        invc[v1]=1;
        invc[v2]=1;
        invc[vn]=1;
        list<int>deg;
        dpos[vn]=deg.insert(deg.begin(),vn);
        fill(dec.begin(),dec.end(),0);
        dec[v1]=2;
        dec[v2]=2;
        dec[vn]=2;
        for(int i=n-1;i>=2;--i){
            if(deg.empty())
                return false;
            int v=*deg.begin();
            deg.erase(deg.begin());
            invc[v]=-1;
            rt[i]=v;
            for(int u:to[v]){
                if(invc[u]==1){
                    if(u!=v1&&u!=v2&&dec[u]==2)
                        deg.erase(dpos[u]);
                    --dec[u];
                    if(u!=v1&&u!=v2&&dec[u]==2)
                        dpos[u]=deg.insert(deg.begin(),u);
                }else if(invc[u]==0)
                    invc[u]=2;
            }
            for(int u:to[v])
                if(invc[u]==2)
                    for(int w:to[u])
                        if(invc[w]==1){
                            if(w!=v1&&w!=v2&&dec[w]==2)
                                deg.erase(dpos[w]);
                            ++dec[w];
                            if(w!=v1&&w!=v2&&dec[w]==2)
                                dpos[w]=deg.insert(deg.begin(),w);
                            ++dec[u];
                        }else if(invc[w]==2)
                            ++dec[u];
            for(int u:to[v]){
                if(invc[u]==2){
                    invc[u]=1;
                    if(dec[u]==2)
                        dpos[u]=deg.insert(deg.begin(),u);
                }
            }
        }
        return true;
    }
    bool embed(){
        list<int>ext;
        int mker=0;
        fill(mrk.begin(),mrk.end(),0);
        pos[rt[1]]=ext.insert(ext.begin(),rt[1]);
        pos[rt[2]]=ext.insert(ext.begin(),rt[2]);
        pos[rt[0]]=ext.insert(ext.begin(),rt[0]);
        fill(rmd.begin(),rmd.end(),0);
        rmd[rt[1]]=1;
        rmd[rt[2]]=1;
        rmd[rt[0]]=1;
        for(int i=3;i<n;++i){
            int v=rt[i];
            rmd[v]=1;
            vector<int>can;
            ++mker;
            for(int u:to[v])
                if(rmd[u])
                    mrk[u]=mker,can.push_back(u);
            int start=-1,end=-1;
            for(int u:can){
                list<int>::iterator it=pos[u];
                if(it==list<int>::iterator())
                    return false;
                if(it==ext.begin()){
                    if(start!=-1)
                        return false;
                    start=u;
                }else{
                    list<int>::iterator tmp=it;
                    if(mrk[*(--tmp)]!=mker){
                        if(start!=-1)
                            return false;
                        start=u;
                    }
                }
                list<int>::iterator tmp=it;++tmp;
                if(tmp==ext.end()){
                    if(end!=-1)
                        return false;
                    end=u;
                }else{
                    if(mrk[*tmp]!=mker){
                        if(end!=-1)
                            return false;
                        end=u;
                    }
                }
            }
            if(start==-1||end==-1)
                return false;
            for(int u:can)
                if(u!=start&&u!=end)
                    ext.erase(pos[u]),pos[u]=list<int>::iterator();
            pos[v]=ext.insert(pos[end],v);
        }
        return true;
    }
    bool istri(int u,int v,int w){
        return to2[u].count(v)&&to2[v].count(w)&&to2[w].count(u);
    }
    MaximalPlanarityTesting(int _n):
        n(_n),to(n),to2(n),m(0),rt(n),invc(n),dec(n),dpos(n),pos(n),rmd(n),mrk(n){
    }
    void add(int u,int v){
        to[u-1].push_back(v-1);
        to[v-1].push_back(u-1);
        to2[u-1].insert(v-1);
        to2[v-1].insert(u-1);++m;
    }
    bool run(){
        if(n==1&&m==0)
            return true;
        if(n==2&&m==1)
            return true;
        if(n==3&&m==3)
            return true;
        if(n<=3)
            return false;
        if(m!=3*n-6)
            return false;
        int v1;
        for(v1=0;v1<n;++v1)
            if(to[v1].size()<3)
                return false;
        for(v1=0;v1<n;++v1)
            if(to[v1].size()<=5)
                break;
        if(v1>=n)
            return false;
        int v2=to[v1].back();
        for(int i=0;i+1<to[v1].size();++i){
            int vn=to[v1][i];
            if(istri(v1,v2,vn)){
                if(!order(v1,v2,vn))
                    continue;
                if(!embed())
                    continue;
                return true;
            }
        }
        return false;
    }
};
