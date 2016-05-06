/*
\subsection*{Description}

Find the occurrences of a pattern in a text using KMP algorithm. The prefix array is also provided.

\subsection*{Methods}

\begin{tabu*} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{template<class T>StringMatching<T>::StringMatching(T*p,int t=1);}}\\
\hline
\bfseries{Description} & construct an object of SuffixMatching for a given pattern\\
\hline
\bfseries{Parameters} & \bfseries{Description}\\
\hline
T & type of character\\
\hline
t & whether to optimize the prefix array, do not turn it on if you want to use the prefix array\\
\hline
p & pattern, indexed from one, ended by zero\\
\hline
\bfseries{Time complexity} & $\Theta(\abs{p})$\\
\hline
\bfseries{Space complexity} & $\Theta(\abs{p})$\\
\hline
\bfseries{Return value} & an object of StringMatching\\
\hline
\end{tabu*}

\begin{tabu*} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{template<class T>int StringMatching<T>::run(T*t,int k=0);}}\\
\hline
\bfseries{Description} & given an occurence of the pattern in a text, find the next occurrence\\
\hline
\bfseries{Parameters} & \bfseries{Description}\\
\hline
t & text, indexed from one, ended by zero\\
\hline
k & start index of the last occurence of the pattern, use zero if there is none\\
\hline
\bfseries{Time complexity} & $O(\abs{t})$\\
\hline
\bfseries{Space complexity} & $\Theta(1)$\\
\hline
\bfseries{Return value} & start index of the next occurence of the pattern\\
\hline
\end{tabu*}

\subsection*{Fields}

\begin{tabu} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{template<class T>vector<int>StringMatching<T>::f;}}\\
\hline
\bfseries{Description} & prefix array of KMP algorithm, indexed from one\\
\hline
\end{tabu}


\subsection*{Performance}

\begin{tabu} to \textwidth {|X|X|X|X|X|}
\hline
\bfseries{Problem} & \bfseries{Constraints} & \bfseries{Time} & \bfseries{Memory} & \bfseries{Date}\\
\hline
{POJ 3461} & $\abs{p}=10^4, \abs{t}=10^6$ & 141 ms& 1340 kB & 2016-02-14\\
\hline
\end{tabu}


\subsection*{References}

\begin{tabu} to \textwidth {|X|X|}
\hline
\bfseries{Title} & \bfseries{Author}\\
\hline
{Fast Pattern Matching in Strings} & Donald E. Knuth, James H. Morris, Vaughan R. Pratt\\
\hline
\end{tabu}


\subsection*{Code}
*/
#include<vector>
using namespace std;
template<class T>struct StringMatching{
    StringMatching(T*p,int t=1):
        b(2,p[1]),f(2),l(2){
        for(int i=0;p[l]?1:(--l,0);b.push_back(p[l++])){
            for(;i&&p[i+1]!=p[l];i=f[i]);
            f.push_back(i=i+(p[i+1]==p[l]));
        }
        for(int i=2;t&&i<l;++i)
            if(p[f[i]+1]==p[i+1])
                f[i]=f[f[i]];
    }
    int run(T*t,int k=0){
        for(int i=k?k+l:1,j=k?f[l]:0;t[i];++i){
            for(;j&&b[j+1]!=t[i];j=f[j]);
            if((j+=b[j+1]==t[i])==l)
                return i-l+1;
        }
        return 0;
    }
    int l;
    vector<T>b;
    vector<int>f;
};
