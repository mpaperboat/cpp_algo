const int N=100000;
struct UFS{
    int p[N+1],n;
    UFS(int _n):
        n(_n){
        for(int i=1;i<=n;++i)
            p[i]=i;
    }
    int find(int x){
        return p[x]==x?x:p[x]=find(p[x]);
    }
    int link(int x,int y){
        p[find(x)]=y;
    }
};