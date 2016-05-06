/*
\subsection*{Description}

Construct a suffix array and it's height array from a given string using DC3 algorithm.


\subsection*{Methods}

\begin{tabu*} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{template<class T,int M,T D>SuffixArray<T,M,D>::SuffixArray(T*s,int n);}}\\
\hline
\bfseries{Description} & construct an object of SuffixArray and in the mean time construct the suffix array and height array\\
\hline
\bfseries{Parameters} & \bfseries{Description}\\
\hline
T & type of character, usually char\\
\hline
M & size of alphabet\\
\hline
D & offset of alphabet, use 'a' for lowercase letters\\
\hline
s & string from which to build a suffix array, indexed from one\\
\hline
n & length of s\\
\hline
\bfseries{Time complexity} & $\Theta(n+M)$\\
\hline
\bfseries{Space complexity} & $\Theta(10n+M)$\\
\hline
\bfseries{Return value} & an object of SuffixArray\\
\hline
\end{tabu*}


\subsection*{Fields}

\begin{tabu} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{template<class T,int M,T D>int*SuffixArray<T,M,D>::sa;}}\\
\hline
\bfseries{Description} & suffix array, indexed from one\\
\hline
\end{tabu}

\begin{tabu} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{template<class T,int M,T D>int*SuffixArray<T,M,D>::ht;}}\\
\hline
\bfseries{Description} & height array, indexed from one\\
\hline
\end{tabu}


\subsection*{Performance}

\begin{tabu} to \textwidth {|X|X|X|X|X|}
\hline
\bfseries{Problem} & \bfseries{Constraints} & \bfseries{Time} & \bfseries{Memory} & \bfseries{Date}\\
\hline
{UOJ 35} & $N=10^5, M=26$ & 416 ms (18+ cases) & 4248 kB & 2016-02-14\\
\hline
\end{tabu}


\subsection*{References}

\begin{tabu} to \textwidth {|X|X|}
\hline
\bfseries{Title} & \bfseries{Author}\\
\hline
{后缀数组——处理字符串的有力工具} & 罗穗骞\\
\hline
\end{tabu}


\subsection*{Code}
*/
#include<bits/stdc++.h>
using namespace std;
template<class T,int M,int D>struct SuffixArray{
    int*sa,*ht,*rk,*ts,*ct,*st;
    SuffixArray(T*s,int n){
        crt(st,n),crt(sa,n),crt(ht,n);
        crt(rk,n),crt(ts,n),crt(ct,max(n,M));
        for(int i=1;i<=n;++i)st[i]=s[i]-D+1;
        dc3(st,n,M,sa,rk);
        for(int i=1;i<=n;++i){
            if(rk[i]==1){ht[1]=0;continue;}
            int&d=ht[rk[i]]=max(i==1?0:ht[rk[i-1]]-1,0);
            for(;i+d<=n&&sa[rk[i]-1]+d<=n
                &&st[i+d]==st[sa[rk[i]-1]+d];++d);
        }
    }
    ~SuffixArray(){
        del(sa),del(ht),del(rk);
        del(ts),del(ct),del(st);
    }
    void crt(int*&a,int n){
        a=new int[n+1];
    }
    void del(int*a){
        delete a;
    }
    #define fc(i)(p0[i]+d>n||!p0[i]?0:s[p0[i]+d])
    int cmp(int*p0,int i,int*s,int n){
        for(int d=0;d<3;++d)
            if(fc(i)!=fc(i-1))return 1;
        return 0;
    }
    void sot(int*p0,int n0,int*s,int n,int m,int d){
        memset(ct,0,(m+1)*4);
        for(int i=1;i<=n0;++i)++ct[fc(i)];
        for(int i=1;i<=m;++i)ct[i]+=ct[i-1];
        for(int i=n0;i>=1;--i)ts[ct[fc(i)]--]=p0[i];
        memcpy(p0+1,ts+1,n0*4);
    }
    #define fc(d)\
        if(s[i+d]!=s[j+d])return s[i+d]<s[j+d];\
        if(i==n-d||j==n-d)return i==n-d;
    bool cmp(int*s,int n,int*r,int i,int j){
        fc(0)
        if(j%3==1)return r[i+1]<r[j+1];
        fc(1)
        return r[i+2]<r[j+2];
    }
    #undef fc
    void dc3(int*s,int n,int m,int*a,int*r){
        int n0=n-(n/3)+1,*a0,*s0,i,j=0,k=n/3+bool(n%3)+1,l;
        crt(s0,n0),s0[k]=1,crt(a0,n0+1),a0[k]=0;
        for(i=1;i<=n;i+=3)a0[++j]=i,a0[j+k]=i+1;
        for(i=2;i>=0;--i)sot(a0,n0,s,n,m,i);
        for(r[a0[1]]=1,i=2;i<=n0;++i)
            r[a0[i]]=r[a0[i-1]]+cmp(a0,i,s,n);
        for(i=1,j=0;i<=n;i+=3)
            s0[++j]=r[i],s0[j+k]=r[i+1];
        if(r[a0[n0]]==n0){
            memcpy(r+1,s0+1,n0*4);
            for(i=1;i<=n0;++i)a0[a[i]=r[i]]=i;
        }else
            dc3(s0,n0,r[a0[n0]],a0,a);
        for(i=1,j=0;i<=n;i+=3)
            r[i]=a[++j],r[i+1]=a[j+k];
        if(j=0,n%3==0)
            s0[++j]=n;
        for(i=1;i<=n0;++i)
            if(a0[i]>=k)
                a0[i]=(a0[i]-k)*3-1;
            else
                if((a0[i]=3*a0[i]-2)!=1)s0[++j]=a0[i]-1;
       sot(s0,j,s,n,m,0);
       for(i=1,k=2,l=0;i<=j||k<=n0;)
            if(k>n0||i<=j&&cmp(s,n,r,s0[i],a0[k]))
                a[++l]=s0[i++];
            else
                a[++l]=a0[k++];
        for(i=1;i<=n;++i)r[a[i]]=i;
        del(a0),del(s0);
    }
};
