/*
\subsection*{Description}

Use a suffix automaton to build a suffix tree. It has large data members, make its object static.


\subsection*{Methods}

\begin{tabu*} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{template<class T,int N,int M,T D>SuffixTree<T,N,M,D>::SuffixTree();}}\\
\hline
\bfseries{Description} & construct an object of SuffixTree\\
\hline
\bfseries{Parameters} & \bfseries{Description}\\
\hline
T & type of character, usually char\\
\hline
N & maximum length of string\\
\hline
M & size of alphabet\\
\hline
D & offset of alphabet, use 'a' for lowercase letters\\
\hline
\bfseries{Time complexity} & $\Theta(1)$\\
\hline
\bfseries{Space complexity} & $\Theta(8NM)$\\
\hline
\bfseries{Return value} & an object of SuffixTree\\
\hline
\end{tabu*}

\begin{tabu*} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{template<class T,int N,int M,T D>void SuffixTree<T,N,M,D>::build(const T*s,int n);}}\\
\hline
\bfseries{Description} & build suffix tree for a given string\\
\hline
\bfseries{Parameters} & \bfseries{Description}\\
\hline
s & string from which to build a suffix tree, indexed from zero\\
\hline
n & length of $s$\\
\hline
\bfseries{Time complexity} & $\Theta(nM)$\\
\hline
\bfseries{Space complexity} & $\Theta(1)$\\
\hline
\bfseries{Return value} & an object of SuffixTree\\
\hline
\end{tabu*}


\subsection*{Fields}

\begin{tabu} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{template<class T,int N,int M,T D>int SuffixTree<T,N,M,D>::nc;}}\\
\hline
\bfseries{Description} & number of nodes in suffix tree, they are labeled from one to $nc$, note that $nc$ can be almost 2*$\abs{s}$\\
\hline
\end{tabu}


\begin{tabu} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{template<class T,int N,int M,T D>int SuffixTree<T,N,M,D>::pr[2*N];}}\\
\hline
\bfseries{Description} & parent array of the suffix tree\\
\hline
\end{tabu}


\begin{tabu} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{template<class T,int N,int M,T D>int SuffixTree<T,N,M,D>::ch[2*N][M];}}\\
\hline
\bfseries{Description} & children array of the suffix tree\\
\hline
\end{tabu}

\begin{tabu} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{template<class T,int N,int M,T D>const T*SuffixTree<T,N,M,D>::el[2*N][M];}}\\
\hline
\bfseries{Description} & the start pointer of the string on children edge\\
\hline
\end{tabu}


\begin{tabu} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{template<class T,int N,int M,T D>const T*SuffixTree<T,N,M,D>::er[2*N][M];}}\\
\hline
\bfseries{Description} & the end pointer of the string on children edge, itself is not included\\
\hline
\end{tabu}


\begin{tabu} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{template<class T,int N,int M,T D>int SuffixTree<T,N,M,D>::tr[2*N][M];}}\\
\hline
\bfseries{Description} & $tr[u][i]$ is the node that represents $\{(D+i)+s\mid u \text{ represents } s\}$\\
\hline
\end{tabu}

\begin{tabu} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{template<class T,int N,int M,T D>int SuffixTree<T,N,M,D>::dp[2*N];}}\\
\hline
\bfseries{Description} & depth array of the suffix tree\\
\hline
\end{tabu}

\begin{tabu} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{template<class T,int N,int M,T D>int SuffixTree<T,N,M,D>::id[2*N];}}\\
\hline
\bfseries{Description} & $id[u]$ is the start of a postion where the strings $u$ represents occur\\
\hline
\end{tabu}

\begin{tabu} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{template<class T,int N,int M,T D>int SuffixTree<T,N,M,D>::sf[2*N];}}\\
\hline
\bfseries{Description} & $sf[u]$ means whether $u$ represents a suffix\\
\hline
\end{tabu}



\subsection*{References}

\begin{tabu} to \textwidth {|X|X|}
\hline
\bfseries{Title} & \bfseries{Author}\\
\hline
{后缀自动机} & 陈立杰\\
\hline
\end{tabu}


\subsection*{Code}
*/
#include<cstring>
template<class T,int N,int M,T D>struct SuffixTree{
    int node(){
        pr[++nc]=dp[nc]=sf[nc]=0;
        memset(tr[nc],0,4*M);
        return nc;
    }
    void build(const T*s,int n){
        nc=0,node();
        for(int i=n-1,c,p=1,q,np,nq;i>=0;--i,p=np){
            dp[np=node()]=dp[p]+1,id[np]=i+1,sf[np]=1;
            for(c=s[i]-D;p&&!tr[p][c];p=pr[p])
                tr[p][c]=np;
            if(p&&dp[q=tr[p][c]]!=dp[p]+1){
                dp[nq=node()]=dp[p]+1,pr[nq]=pr[q],id[nq]=i+1;
                memcpy(tr[pr[q]=pr[np]=nq],tr[q],4*M);
                for(;p&&tr[p][c]==q;p=pr[p])
                    tr[p][c]=nq;
            }else
                pr[np]=p?q:1;
        }
        for(int i=2,j,c;i<=nc;++i)
            c=s[id[i]+dp[j=pr[i]]-1]-D,
            el[j][c]=s+id[i]+dp[j]-1,
            er[j][c]=s+id[i]+dp[ch[j][c]=i]-1;
    }
    const T*el[2*N][M],*er[2*N][M];
    int nc,pr[2*N],tr[2*N][M],dp[2*N],id[2*N],sf[2*N],ch[2*N][M];
};
