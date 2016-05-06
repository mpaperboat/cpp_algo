/*
\subsection*{Description}

Find the length of k shortest path between two vertices in a given weighted directed graph. The path does not need to be loopless. But the edge weights must be non-negative.

\subsection*{Methods}

\begin{tabu*} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{template<class T>KShortestPath<T>::KShortestPath(int n);}}\\
\hline
\bfseries{Description} & construct an object of KShortestPath\\
\hline
\bfseries{Parameters} & \bfseries{Description}\\
\hline
T & type of edge weights, be careful since the result can be $\Theta(nkC)$\\
\hline
n & number of vertices\\
\hline
\bfseries{Time complexity} & $\Theta(n)$\\
\hline
\bfseries{Space complexity} & $\Theta(11n)$\\
\hline
\bfseries{Return value} & an object of KShortestPath\\
\hline
\end{tabu*}

\begin{tabu*} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{template<class T>void KShortestPath<T>::add(int a,int b,T c);}}\\
\hline
\bfseries{Description} & add a directed weighted edge to the graph\\
\hline
\bfseries{Parameters} & \bfseries{Description}\\
\hline
a & start vertex of the edge, indexed from one\\
\hline
b & end vertex of the edge, indexed from one\\
\hline
c & weight of the edge, should be non-negative\\
\hline
\bfseries{Time complexity} & $\Theta(1)$ (amortized)\\
\hline
\bfseries{Space complexity} & $\Theta(1)$ (amortized)\\
\hline
\bfseries{Return value} & none\\
\hline
\end{tabu*}

\begin{tabu*} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{template<class T>T KShortestPath<T>::run(int s,int t,int k);}}\\
\hline
\bfseries{Description} & find the length of k shortest path\\
\hline
\bfseries{Parameters} & \bfseries{Description}\\
\hline
s & start vertex of the path, indexed from one\\
\hline
t & end vertex of the path, indexed from one\\
\hline
k & k in 'k shortest path'\\
\hline
\bfseries{Time complexity} & $O((n+m)\log n+k\log (nmk))$\\
\hline
\bfseries{Space complexity} & $O(n\log n+m+k\log (nm))$\\
\hline
\bfseries{Return value} & length of k shortest path from s to t or -1 if it doesn't exist\\
\hline
\end{tabu*}



\subsection*{Performance}

\begin{tabu} to \textwidth {|X|X|X|X|X|}
\hline
\bfseries{Problem} & \bfseries{Constraints} & \bfseries{Time} & \bfseries{Memory} & \bfseries{Date}\\
\hline
{JDFZ 2978} & $N=10^4, M=10^5, K=10^4$ & 324 ms& 14968 kB & 2016-02-13\\
\hline
\end{tabu}


\subsection*{References}

\begin{tabu} to \textwidth {|X|X|}
\hline
\bfseries{Title} & \bfseries{Author}\\
\hline
{堆的可持久化和 k 短路} & 俞鼎力\\
\hline
\end{tabu}


\subsection*{Code}
*/
#include<bits/stdc++.h>
using namespace std;
template<class T>struct KShortestPath{
    KShortestPath(int _n):
        n(_n),m(1<<(int)ceil(log2(n)+1e-8)),from(n+1,-1),
        tov(n+1),wev(n+1),to(n+1),we(n+1),inf(numeric_limits<T>::max()),
        sg(2*m,make_pair(inf,0)),di(n+1,inf),nxt(n+1),chd(n+1),torev(n+1){
    }
    ~KShortestPath(){
        for(int i=0;i<all.size();++i)
            free(all[i]);
    }
    void add(int u,int v,T w){
        tov[v].push_back(u);
        wev[v].push_back(w);
        to[u].push_back(v);
        we[u].push_back(w);
        torev[v].push_back(to[u].size()-1);
    }
    int upd(T&a,T b,T c){
        if(b!=inf&&c!=inf&&b+c<a){
            a=b+c;
            return 1;
        }
        return 0;
    }
    void mod(int u,T d){
        for(sg[u+m-1]=make_pair(d,u),u=u+m-1>>1;u;u>>=1)
            sg[u]=min(sg[u<<1],sg[u<<1^1]);
    }
    template<class T2>struct node{
        node(T2 _v):
            v(_v),s(0),l(0),r(0){
        }
        T2 v;
        int s;
        node*l,*r;
    };
    template<class T2>node<T2>*merge(node<T2>*a,node<T2>*b){
        if(!a||!b)
            return a?a:b;
        if(a->v>b->v)
            swap(a,b);
        a->r=merge(a->r,b);
        if(!a->l||a->l->s<a->r->s)
            swap(a->l,a->r);
        a->s=(a->r?a->r->s:-1)+1;
        return a;
    }
    template<class T2>node<T2>*mak(T2 v){
        node<T2>*t=(node<T2>*)malloc(sizeof(node<T2>));
        *t=node<T2>(v);
        all.push_back(t);
        return t;
    }
    template<class T2>node<T2>*pmerge(node<T2>*a,node<T2>*b){
        if(!a||!b)
            return a?a:b;
        if(a->v>b->v)
            swap(a,b);
        node<T2>*r=mak(a->v);
        r->l=a->l;
        r->r=pmerge(a->r,b);
        if(!r->l||r->l->s<r->r->s)
            swap(r->l,r->r);
        r->s=(r->r?r->r->s:-1)+1;
        return r;
    }
    struct edge{
        edge(T _l,int _v):
            l(_l),v(_v){
        }
        bool operator>(const edge&a){
            return l>a.l;
        }
        T l;
        int v;
    };
    struct edgeheap{
        edgeheap(node<edge>*r):
            root(r){
        }
        bool operator>(const edgeheap&a){
            return root->v.l>a.root->v.l;
        }
        node<edge>*root;
    };
    edgeheap merge(edgeheap a,edgeheap b){
        return edgeheap(pmerge(a->root,b->root));
    }
    edgeheap popmin(edgeheap a){
        return edgeheap(pmerge(a.root->l,a.root->r));
    }
    node<edgeheap>*popmin(node<edgeheap>*a){
           node<edgeheap>*x=pmerge(a->l,a->r);
           a=mak(popmin(a->v));
           if(a->v.root)
               x=pmerge(x,a);
           return x;
    }
    struct path{
        path(int _vp,int _v,T _l,T _d,node<edgeheap>*_c):
            vp(_vp),v(_v),l(_l),d(_d),can(_c){
        }
        bool operator<(const path&a)const{
            return l>a.l;
        }
        int vp,v;
        T l,d;
        node<edgeheap>*can;
    };
    T run(int s,int t,int k){
        di[t]=0;
        for(int i=1;i<=n;++i)
            sg[i+m-1]=make_pair(di[i],i);
        for(int i=m-1;i>=1;--i)
            sg[i]=min(sg[i<<1],sg[i<<1^1]);
        for(int u=sg[1].second;sg[1].first!=inf;u=sg[1].second){
            mod(u,inf),tre.push_back(u);
            for(int i=0;i<tov[u].size();++i){
                int v=tov[u][i];
                T w=wev[u][i];
                if(upd(di[v],di[u],w))
                    mod(v,di[v]),nxt[v]=u,
                    from[v]=torev[u][i];
            }
        }
        for(int i=0;i<tre.size();++i){
            queue<node<edge>*>qu;
            for(int j=0;j<to[tre[i]].size();++j)
                if(di[to[tre[i]][j]]!=inf&&j!=from[tre[i]])
                    qu.push(mak(edge(we[tre[i]][j]-di[tre[i]]+di[to[tre[i]][j]],to[tre[i]][j])));
            for(node<edge>*x,*y;qu.size()>1;)
                x=qu.front(),qu.pop(),y=qu.front(),qu.pop(),
                qu.push(merge(x,y));
            if(qu.size())
                chd[tre[i]]=pmerge(mak(edgeheap(qu.front())),chd[nxt[tre[i]]]);
            else
                chd[tre[i]]=chd[nxt[tre[i]]];
        }
        priority_queue<path>pth;
        if(di[s]==inf)
            return -1;
        pth.push(path(0,s,di[s],0,0));
        for(int i=1;i<k;++i){
            if(pth.empty())
                return -1;
            path p=pth.top();
            pth.pop();
            if(p.can){
                edge t=p.can->v.root->v;
                pth.push(path(p.vp,t.v,p.l-p.d+t.l,t.l,popmin(p.can)));
            }
            if(chd[p.v]){
                edge t=chd[p.v]->v.root->v;
                pth.push(path(p.v,t.v,p.l+t.l,t.l,popmin(chd[p.v])));
            }
        }
        return pth.size()?pth.top().l:-1;
    }
    T inf;
    int n,m;
    vector<T>di;
    vector<int>nxt,tre,from;
    vector<void*>all;
    vector<node<edgeheap>*>chd;
    vector<pair<T,int> >sg;
    vector<vector<T> >wev,we;
    vector<vector<int> >tov,to,torev;
};
