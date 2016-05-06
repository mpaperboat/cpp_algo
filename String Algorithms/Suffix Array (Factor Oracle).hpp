/*
\subsection*{Description}

Use a factor oracle to construct a suffix array and it's height array from a given string. It is theoretically slow, but usually fast in practice. Object of it should be static since it has large data members.


\subsection*{Methods}

\begin{tabu*} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{template<class T,int N,int M,T D>SuffixArray<T,N,M,D>::SuffixArray();}}\\
\hline
\bfseries{Description} & construct an object of SuffixArray\\
\hline
\bfseries{Parameters} & \bfseries{Description}\\
\hline
T & type of character, usually char\\
\hline
N & maximum length of input string\\
\hline
M & size of alphabet\\
\hline
D & offset of alphabet, use 'a' for lowercase letters\\
\hline
\bfseries{Time complexity} & $\Theta(1)$\\
\hline
\bfseries{Space complexity} & $\Theta((M+13)N)$\\
\hline
\bfseries{Return value} & an object of SuffixArray\\
\hline
\end{tabu*}

\begin{tabu*} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{template<class T,int N,int M,T D>void SuffixArray<T,N,M,D>::build(T*s,int n);}}\\
\hline
\bfseries{Description} & build suffix array and height array\\
\hline
\bfseries{Parameters} & \bfseries{Description}\\
\hline
s & string from which to build a suffix array, indexed from zero\\
\hline
n & length of s\\
\hline
\bfseries{Time complexity} & $O((M+n)n)$\\
\hline
\bfseries{Space complexity} & $\Theta(n)$\\
\hline
\bfseries{Return value} & none\\
\hline
\end{tabu*}


\subsection*{Fields}

\begin{tabu} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{template<class T,int M,T D>int SuffixArray<T,M,D>::sa[N+1];}}\\
\hline
\bfseries{Description} & suffix array, indexed from one\\
\hline
\end{tabu}

\begin{tabu} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{template<class T,int M,T D>int SuffixArray<T,M,D>::ht[N+1];}}\\
\hline
\bfseries{Description} & height array, indexed from one\\
\hline
\end{tabu}


\subsection*{Performance}

\begin{tabu} to \textwidth {|X|X|X|X|X|}
\hline
\bfseries{Problem} & \bfseries{Constraints} & \bfseries{Time} & \bfseries{Memory} & \bfseries{Date}\\
\hline
{Tyvj 1860} & $N=2\times 10^5, M=26$ & 1154 ms (10 cases) & 33012 kB & 2016-02-14\\
\hline
\end{tabu}


\subsection*{References}

\begin{tabu} to \textwidth {|X|X|}
\hline
\bfseries{Title} & \bfseries{Author}\\
\hline
{Factor Oracle, Suffix Oracle} & Cyril Allauzen, Maxime Crochemore, Mathieu Raffinot\\
\hline
{Computing Repeated Factors with a Factor Oracle} & Arnaud Lefebvre, Thierry Lecroq\\
\hline
\end{tabu}


\subsection*{Code}
*/
#include<bits/stdc++.h>
using namespace std;
template<class T,int N,int M,T D>struct SuffixArray{
    int val(int i,int d){
        return d<0?(d>-2?lrs[i]:n-1-lrs[i]):s[n-i+lrs[i]+d]-D;
    }
    void sort(int*a,int*b,int m,int d){
        static int c[N];
        memset(c,0,4*(d>=0?M:n));
        for(i=1;i<=m;++c[val(a[i],d)],++i);
        for(i=1;i<(d>=0?M:n);c[i]+=c[i-1],++i);
        for(i=m;i>=1;b[c[val(a[i],d)]--]=a[i],--i);
    }
    void sort(int a,int b,int d,int l){
        sort(z+a-1,t,b-a+1,d);
        memcpy(z+a,t+1,(b-a+1)*4);
        for(i=a,j;i<=b;i=j+1){
            for(j=i;j+1<=b&&val(z[j],d)==val(z[j+1],d);++j);
            if(j-i)
                sort(i,j,d+1,l);
        }
    }
    void add(int&b,int v){
        cv[++cp]=v,cn[cp]=b,b=cp;
    }
    void dfs(int u){
        #define m(p,q)\
            for(int i=p##b[u],j;i;){\
                for(*z=0,j=i;cn[j]&&lrs[cv[j]]==lrs[cv[cn[j]]];z[++z[0]]=cv[j],j=cn[j]);\
                z[++z[0]]=cv[j],sort(1,*z,0,q);\
                for(z[0]=1;i!=cn[j];cv[i]=z[z[0]++],i=cn[i]);\
            }
        m(l,0)
        for(int i=lb[u];i;dfs(cv[i]),i=cn[i]);
        sa[++*sa]=n+1-u,*sa-=!u;
        m(r,1)
        for(int i=rb[u];i;dfs(cv[i]),i=cn[i]);
    }
    void build(T*_s,int _n){
        n=_n,s=_s,memset(tr,(cp=*sa=*vl=*vr=*lb=*rb=*lrs=0,*z=-1),4*M);
        for(int i=0,c=s[n-1-i]-D,u,v;i<n;c=s[n-1-++i]-D){
            memset(tr+i+1,(lb[i+1]=rb[i+1]=lrs[i+1]=0)-1,4*M);
            for(j=i;j>-1&&tr[j][c]<0;tr[j][c]=i+1,j=z[u=j]);
            if(v=z[i+1]=j<0?0:tr[j][c]){
                for(v=v-1==z[u]?u:v-1;z[u]!=z[v];v=z[v]);
                lrs[i+1]=min(lrs[u],lrs[v])+1;
            }
            for(j=0;n-(z[i+1]-lrs[i+1]-j)<n&&s[n-(z[i+1]-lrs[i+1]-j)]==s[n-1-i+lrs[i+1]+j];++j);
            if(n-(z[i+1]-lrs[i+1]-j)<n&&s[n-(z[i+1]-lrs[i+1]-j)]>s[n-1-i+lrs[i+1]+j])
                vl[++*vl]=i+1;
            else
                vr[++*vr]=i+1;
        }
        sort(vl,t,*vl,-1),sort(vr,vl,*vr,-2);
        for(i=*vl;i;add(lb[z[t[i]]],t[i]),--i);
        for(i=*vr;i;add(rb[z[vl[i]]],vl[i]),--i);
        dfs(0);
        for(i=1;i<=n;++i)
            rk[sa[i]]=i;
        for(i=1;i<=n;++i){
            if(rk[i]==1){
                ht[1]=0;
                continue;
            }
            int&d=ht[rk[i]]=max(i==1?0:ht[rk[i-1]]-1,0);
            for(;i+d<=n&&sa[rk[i]-1]+d<=n&&s[i+d-1]==s[sa[rk[i]-1]+d-1];++d);
        }
    }
    T*s;
    int n,sa[N+1],ht[N+1],rk[N+1],lrs[N+1],tr[N+1][M],i,j,lb[N+1],rb[N+1],cv[N+1],cn[N+1],cp,vl[N+1],vr[N+1],t[N+1],z[N+1];
};
