/*
\subsection*{Description}

Find the solutions to $x^2 \equiv a \pmod{n}$.

\subsection*{Methods}

\begin{tabu*} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{vector<int>run(int a,int n);}}\\
\hline
\bfseries{Description} & find all solutions to the equation that are less than n\\
\hline
\bfseries{Parameters} & \bfseries{Description}\\
\hline
$a$ & $a$ in the equation, should be less than $n$\\
\hline
$n$ & $n$ in the equation\\
\hline
\bfseries{Time complexity} & $O(\sqrt{n}\log n)$ (expected)\\
\hline
\bfseries{Space complexity} & $O(\sqrt{n}\log n)$\\
\hline
\bfseries{Return value} & all solutions in a vector, not sorted\\
\hline
\end{tabu*}




\subsection*{Performance}

\begin{tabu} to \textwidth {|X|X|X|X|X|}
\hline
\bfseries{Problem} & \bfseries{Constraints} & \bfseries{Time} & \bfseries{Memory} & \bfseries{Date}\\
\hline
{UVaOJ 1426} & $N=10^9$ & 23 ms&  & 2016-02-19\\
\hline
\end{tabu}


\subsection*{Code}
*/

#include<cmath>
#include<vector>
using namespace std;
namespace DiscreteSquareRoot{
    typedef long long ll;
    int ti[1<<16],va[1<<16],mp[1<<16],nx[1<<16],hd[1<<16],tm,nw;
    #define clr\
        int y=x&65535;\
        if(ti[y]!=tm)ti[y]=tm,hd[y]=0;
    int*get(int x){
        clr
        for(int i=hd[y];i;i=nx[i])
            if(va[i]==x)return&mp[i];
        return 0;
    }
    void ins(int x,int v){
        clr
        va[++nw]=x,mp[nw]=v;
        nx[nw]=hd[y],hd[y]=nw;
    }
    int pow(int a,int b,int n){
        int r=1;
        for(;b;b&1?r=(ll)r*a%n:0,b>>=1,a=(ll)a*a%n);
        return r;
    }
    int gcd(int a,int b){
        return b?gcd(b,a%b):a;
    }
    void exg(int a,int b,int&x,int&y){
        if(!b)x=1,y=0;
        else exg(b,a%b,y,x),y-=a/b*x;
    }
    int inv(int a,int b){
        int x,y;
        exg(a,b,x,y);
        return x+b;
    }
    int bgs(int a,int b,int n){
        ++tm,nw=0;
        int m=sqrt(n);
        for(int i=0,u=1;i<m;++i)
            ins(u,i),u=(ll)u*a%n;
        for(int i=0,u=1,v=inv(pow(a,m,n),n);i*m<=n;++i){
            int t=(ll)u*b%n,*j=get(t);
            if(j)return i*m+*j;
            u=(ll)u*v%n;
        }
        return -1;
    }
    int prt(int p,int pk){
        if(p==2)return 5;
        int pi=pk/p*(p-1);
        vector<int>t;
        for(int i=2;i*i<=pi;++i)
            if(pi%i==0)
                t.push_back(i),t.push_back(pi/i);
        for(int g=2;;++g){
            int f=1;
            for(int i=0;i<t.size();++i)
                if(pow(g,t[i],pk)==1){f=0;break;}
            if(f)return g;
        }
    }
    int phi(int p,int pk){
        return p-2?pk/p*(p-1)/2:pk/8;
    }
    vector<int>apk(int a,int p,int k,int pk){
        vector<int>r;
        if(!a)
            for(int d=pow(p,k+1>>1,pk+1),x=0;x<pk;x+=d)
                r.push_back(x);
        else if(gcd(a,pk)==1){
            if(p==2&&k<=2){
                for(int i=1;i<pk;++i)
                    if(i*i%pk==a)r.push_back(i);
            }else{
                int ia,g=prt(p,pk);
                if((ia=bgs(g,a,pk))!=-1&&ia%2==0){
                    r.push_back(pow(g,ia/2,pk));
                    r.push_back(pow(g,ia/2+phi(p,pk),pk));
                    if(p==2){
                        r.push_back(pk-pow(g,ia/2,pk));
                        r.push_back(pk-pow(g,ia/2+phi(p,pk),pk));
                    }
                }
            }
        }else{
            int l=0,pl2=1;
            for(;a%p==0;++l,a/=p,pl2*=(l%2?1:p));
            if(l%2==0)r=apk(a,p,k-l,pk/pl2/pl2);
            for(int i=r.size()-1;l%2==0&&i>=0;--i)
                for(int j=(r[i]*=pl2,1);j<pl2;++j)
                    r.push_back(r[i]+pk/pl2*j);
        }
        return r;
    }
    vector<int>mer(vector<int>a,int&n,vector<int>b,int m){
        vector<int>r;
        for(int i=0;i<a.size();++i)
            for(int j=0;j<b.size();++j){
                ll t=(ll)m*inv(m,n)*a[i]+(ll)n*inv(n,m)*b[j];
                r.push_back(t%(n*m));
            }
        return n*=m,r;
    }
    vector<int>run(int a,int n){
        vector<int>r,t;int m;
        if(n==1)return vector<int>(1);
        for(int p=2,k,pk;p*p<=n;++p)
            if(n%p==0){
                for(k=0,pk=1;n%p==0;++k,n/=p,pk*=p);
                if((t=apk(a%pk,p,k,pk)).size())
                    r=r.size()?mer(r,m,t,pk):(m=pk,t);
                else
                    return vector<int>();
            }
        if(n==1)return r;
        if((t=apk(a%n,n,1,n)).size())
            return r.size()?mer(r,m,t,n):t;
        return vector<int>();
    }
}
