#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
const int N=100000;
template<class COST>struct SPFA{
    int n,src,vis[N],in[N];
    COST di[N];
    vector<int>to[N];
    vector<COST>we[N];
    SPFA(int _n,int _src):
        n(_n),src(_src-1){}
    void add(int u,int v,COST w){
        to[u-1].push_back(v-1);
        we[u-1].push_back(w);
    }
    void run(){
        di[src]=0;
        fill(vis,vis+n,0);
        vis[src]=1;
        fill(in,in+n,0);
        in[src]=1;
        queue<int>qu;
        qu.push(src);
        while(!qu.empty()){
            int u=qu.front();
            qu.pop();
            in[u]=0;
            for(int i=0;i<to[u].size();++i){
                int v=to[u][i];
                COST w=we[u][i];
                if(!vis[v]||di[u]+w<di[v]){
                    vis[u]=1;
                    di[v]=di[u]+w;
                    if(!in[v]){
                        in[v]=1;
                        qu.push(v);
                    }
                }
            }
        }
    }
};