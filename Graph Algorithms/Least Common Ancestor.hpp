#include<queue>
#include<vector>
namespace lca{
    using namespace std;
    const int N=10000,LGN=20;
    struct lca{
        vector<int>to[N+1];
        int n,up[N+1][LGN+1],dp[N+1],vis[N+10];
        lca(int _n):
            n(_n){
        }
        void add(int u,int v){
            to[u].push_back(v);
            to[v].push_back(u);
        }
        void build(){
            fill(vis+1,vis+n,0);
            queue<int>qu;
            qu.push(1);
            vis[1]=1;
            for(int i=0;i<=LGN;++i)
                up[1][i]=1;
            while(!qu.empty()){
                int u=qu.front();
                qu.pop();
                for(int i=1;i<=LGN;++i)
                    up[u][i]=up[up[u][i-1]][i-1];
                for(int v:to[u])
                    if(!vis[v]){
                        vis[v]=1;
                        up[v][0]=u;
                        dp[v]=dp[u]+1;
                        qu.push(v);
                    }
            }
        }
        int query(int u,int v){
            if(dp[u]<dp[v])
                swap(u,v);
            for(int i=0;i<=LGN;++i)
                if(((dp[u]-dp[v])>>i)&1)
                    u=up[u][i];
            if(u==v)
                return u;//注意不要漏掉这句代码
            for(int i=LGN;i>=0;--i)
                if(up[u][i]!=up[v][i])
                    u=up[u][i],v=up[v][i];
            return up[u][0];
        }
    };
}