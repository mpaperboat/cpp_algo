/*
\subsection*{Description}

Maintain sets of elements whose values are in a given range. Two sets can be merged efficently. Range query is also supported.

\subsection*{Methods}

\begin{tabu*} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{template<class T,class U>MergeableSet(U l,U r);}}\\
\hline
\bfseries{Description} & construct an object of MergeableSet, it is not a set, it maintains sets\\
\hline
\bfseries{Parameters} & \bfseries{Description}\\
\hline
T & type of range information, should support $+$, $+$ is applied when two range do not intersect or they represent the same leaf\\
\hline
U & type of values of elements\\
\hline
l & minimum value of elements\\
\hline
r & maximum value of elements\\
\hline
\bfseries{Time complexity} & $\Theta(1)$\\
\hline
\bfseries{Space complexity} & $\Theta(1)$\\
\hline
\bfseries{Return value} & an object of MergeableSet\\
\hline
\end{tabu*}

\begin{tabu*} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{node*insert(node*x,T f,U v);}}\\
\hline
\bfseries{Description} & insert a element into a set\\
\hline
\bfseries{Parameters} & \bfseries{Description}\\
\hline
x & root of the set, use 0 to represent empty set\\
\hline
f & information of the element\\
\hline
v & value of the element\\
\hline
\bfseries{Time complexity} & $\Theta(\log \abs{r-l})$\\
\hline
\bfseries{Space complexity} & $\Theta(\log \abs{r-l})$\\
\hline
\bfseries{Return value} & root of the new set\\
\hline
\end{tabu*}

\begin{tabu*} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{node*erase(node*x,U v);}}\\
\hline
\bfseries{Description} & erase the element with certain value\\
\hline
\bfseries{Parameters} & \bfseries{Description}\\
\hline
x & root of the set\\
\hline
v & value of the element\\
\hline
\bfseries{Time complexity} & $\Theta(1)$ (amortized)\\
\hline
\bfseries{Space complexity} & $\Theta(1)$ (amortized)\\
\hline
\bfseries{Return value} & root of the new set\\
\hline
\end{tabu*}

\begin{tabu*} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{node*merge(node*x,node*y);}}\\
\hline
\bfseries{Description} & merge two sets\\
\hline
\bfseries{Parameters} & \bfseries{Description}\\
\hline
x & root of one set, use 0 to represent empty set\\
\hline
y & root of another set, use 0 to represent empty set\\
\hline
\bfseries{Time complexity} & $\Theta(1)$ (amortized)\\
\hline
\bfseries{Space complexity} & $\Theta(1)$ (amortized)\\
\hline
\bfseries{Return value} & root of the new set\\
\hline
\end{tabu*}

\begin{tabu*} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{vector<T>query(node*x,U ql,U qr);}}\\
\hline
\bfseries{Description} & do range query\\
\hline
\bfseries{Parameters} & \bfseries{Description}\\
\hline
x & root of the set, use 0 to represent empty set\\
\hline
ql & start of the range, itself is included\\
\hline
qr & end of the range, itself is included\\
\hline
\bfseries{Time complexity} & $O(\log \abs{r-l})$\\
\hline
\bfseries{Space complexity} & $O(\log \abs{r-l})$\\
\hline
\bfseries{Return value} & vector of information, that it is empty means no information in that range other wise the result is its first element\\
\hline
\end{tabu*}

\begin{tabu*} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{void destroy(node*x);}}\\
\hline
\bfseries{Description} & delete whole set\\
\hline
\bfseries{Parameters} & \bfseries{Description}\\
\hline
x & root of the set, use 0 to represent empty set\\
\hline
\bfseries{Time complexity} & $\Theta(1)$ (amortized)\\
\hline
\bfseries{Space complexity} & $\Theta(1)$ (amortized)\\
\hline
\bfseries{Return value} & none\\
\hline
\end{tabu*}



\subsection*{References}

\begin{tabu} to \textwidth {|X|X|}
\hline
\bfseries{Title} & \bfseries{Author}\\
\hline
{线段树的合并——不为人知的实用技巧} & 黄嘉泰\\
\hline
\end{tabu}


\subsection*{Code}
*/
#include<vector>
using namespace std;
template<class T,class U>struct MergeableSet{
    struct node{
        node(T _f):f(_f){
            c[0]=c[1]=0;
        }
        T f;
        node*c[2];
    };
    MergeableSet(U l,U r):vl(l),vr(r){
    }
    void update(node*x){
        if(x->c[0]&&x->c[1])
            x->f=x->c[0]->f+x->c[1]->f;
        else
            x->f=x->c[0]?x->c[0]->f:x->c[1]->f;
    }
    node*insert(node*x,T f,U v,U l=0,U r=0){
        if(!l&&!r)
            l=vl,r=vr;
        if(l==r){
            if(x)
                x->f=x->f+f;
            else
                x=new node(f);
        }else{
            U m=l+(r-l)/2;
            int d=v>m;
            node*y=insert(x?x->c[d]:0,f,v,d?m+1:l,d?r:m);
            if(!x)
                x=new node(y->f);
            x->c[d]=y,update(x);
        }
        return x;
    }
    node*erase(node*x,U v,U l=0,U r=0){
        if(!l&&!r)
            l=vl,r=vr;
        if(l==r){
            delete x;
            return 0;
        }
        U m=l+(r-l)/2;
        int d=v>m;
        x->c[d]=erase(x?x->c[d]:0,v,d?m+1:l,d?r:m);
        if(!x->c[0]&&!x->c[1]){
            delete x;
            return 0;
        }
        update(x);
        return x;
    }
    node*merge(node*x,node*y,U l=0,U r=0){
        if(!l&&!r)
            l=vl,r=vr;
        if(!x||!y)
            return x?x:y;
        if(l==r)
            x->f=x->f+y->f;
        else{
            U m=l+(r-l)/2;
            x->c[0]=merge(x->c[0],y->c[0],l,m);
            x->c[1]=merge(x->c[1],y->c[1],m+1,r);
            update(x);
        }
        return x;
    }
    vector<T>query(node*x,U ql,U qr,U l=0,U r=0){
        if(!l&&!r)
            l=vl,r=vr;
        if(!x||ql>r||qr<l)
            return vector<T>();
        if(ql<=l&&qr>=r)
            return vector<T>(1,x->f);
        U m=l+(r-l)/2;
        vector<T>u=query(x->c[0],ql,qr,l,m),
            v=query(x->c[1],ql,qr,m+1,r);
        if(v.size()&&u.size())
            u[0]=u[0]+v[0];
        return u.size()?u:v;
    }
    void destroy(node*x){
        if(x)
            destroy(x->c[0]),
            destroy(x->c[1]),
            delete x;
    }
};
    U vl,vr;
};
