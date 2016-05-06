/*
\subsection*{Description}

Calculate the convex hull of a given 2D point set.


\subsection*{Methods}

\begin{tabu*} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{template<class T>ConvexHull2D();}}\\
\hline
\bfseries{Description} & construct an object of ConvexHull2D\\
\hline
\bfseries{Parameters} & \bfseries{Description}\\
\hline
T & type of coordinates\\
\hline
\bfseries{Time complexity} & $\Theta(1)$\\
\hline
\bfseries{Space complexity} & $\Theta(1)$\\
\hline
\bfseries{Return value} & an object of ConvexHull2D\\
\hline
\end{tabu*}


\begin{tabu*} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{void add(T x,T y);}}\\
\hline
\bfseries{Description} & add a point\\
\hline
\bfseries{Parameters} & \bfseries{Description}\\
\hline
x & x-coordinate of the point\\
\hline
y & y-coordinate of the point\\
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
\multicolumn{2}{|l|}{\bfseries{vector<pair<T,T> >run(T d);}}\\
\hline
\bfseries{Description} & calculate the convex hull\\
\hline
\bfseries{Parameters} & \bfseries{Description}\\
\hline
d & $d=1$ for upper hull and $d=-1$ for lower hull\\
\hline
\bfseries{Time complexity} & $\Theta(n\log n)$ (n is the number of points)\\
\hline
\bfseries{Space complexity} & $\Theta(n)$\\
\hline
\bfseries{Return value} & result in a vector<pair<T,T> >\\
\hline
\end{tabu*}

\subsection*{Code}
*/
#include<vector>
using namespace std;
template<class T>struct ConvexHull2D{
    struct point{
        point(T _x,T _y):x(_x),y(_y){}
        point operator-(point a){
            return point(x-a.x,y-a.y);
        }
        T operator*(point a){
            return x*a.y-y*a.x;
        }
        T x,y;
    };
    T chk(point a,point b,point c){
        return (a-c)*(b-c);
    }
    void add(T x,T y){
        a.push_back(point(x,y));
    }
    struct cmp{
        cmp(T _d):d(_d){}
        bool operator()(point a,point b){
            return a.x!=b.x?a.x<b.x:a.y*d<b.y*d;
        }
        T d;
    };
    vector<pair<T,T> >run(T d){
        sort(a.begin(),a.end(),cmp(d));
        vector<pair<T,T> >r;
        for(int i=0;i<a.size();++i){
            while(r.size()>1&&chk(a[i],r.back(),r[r.size()-2])*d<=0)
                r.pop_back();
            r.push_back(make_pair(a[i].x,a[i].y)),
        }
        return r;
    }
    vector<point>a;
};
