#include<bits/stdc++.h>
using namespace std;
template<class T>struct DelaunayTriangulation{
    const static double E;
    struct poi{
        T x,y;
        poi(T _x=0,T _y=0):
            x(_x),y(_y){
        }
        poi operator-(poi b){
            return poi(x-b.x,y-b.y);
        }
        int operator<(poi b)const{
            if(fabs(x-b.x)<E)
                return y<b.y;
            return x<b.x;
        }
    };
    int n;
    vector<pair<poi,int> >pts;
    vector<vector<int> >egs;
    T det(poi a,poi b){
        return a.x*b.y-a.y*b.x;
    }
    T dot(poi a,poi b){
        return a.x*b.x+a.y*b.y;
    }
    int dir(poi a,poi b,poi c){
        T r=det(c-a,b-a);
        if(r<-E)
            return -1;
        return r>E?1:0;
    }
    int inc(poi a,poi b,poi c,poi d){
        a=a-d;
        b=b-d;
        c=c-d;
        T az=a.x*a.x+a.y*a.y,bz=b.x*b.x+b.y*b.y,cz=c.x*c.x+c.y*c.y;
        return a.x*b.y*cz+b.x*c.y*az+c.x*a.y*bz-a.x*bz*c.y-b.x*a.y*cz-c.x*b.y*az>E;
    }
    int crs(poi a,poi b,poi c,poi d){
        return dir(a,b,c)*dir(a,b,d)==-1&&dir(c,d,a)*dir(c,d,b)==-1;
    }
    DelaunayTriangulation():
        n(0),pts(1){
    }
    void add(T x,T y){
        poi a;
        a.x=x;
        a.y=y;
        pts.push_back(make_pair(a,++n));
    }
    poi&pot(int a){
        return pts[a].first;
    }
    void con(int a,int b){
        egs[a].push_back(b);
        egs[b].push_back(a);
    }
    void dco(int a,int b){
        egs[a].erase(find(egs[a].begin(),egs[a].end(),b));
        egs[b].erase(find(egs[b].begin(),egs[b].end(),a));
    }
    void dnc(int l,int r){
        if(r==l)
            return;
        if(r==l+1){
            con(l,r);
            return;
        }
        if(r==l+2){
            if(dir(pot(l),pot(l+1),pot(r)))
                con(l,l+1),con(l+1,r),con(l,r);
            else{
                if(dot(pot(l+1)-pot(l),pot(r)-pot(l))<0)
                    con(l,l+1),con(l,r);
                else if(dot(pot(l)-pot(l+1),pot(r)-pot(l+1))<0)
                    con(l,l+1),con(l+1,r);
                else
                    con(l,r),con(l+1,r);}
            return;
        }
        int m=(l+r)/2,pl=l,pr=r;
        dnc(l,m);
        dnc(m+1,r);
        for(int f=0;;f=0){
            for(int i=0;i<egs[pl].size();++i){
                int a=egs[pl][i],d=dir(pot(pl),pot(pr),pot(a));
                if(d>0||(d==0&&dot(pot(pl)-pot(a),pot(pr)-pot(a))<0)){
                    pl=a;
                    f=1;
                    break;
                }
            }
            for(int i=0;i<egs[pr].size();++i){
                int a=egs[pr][i],d=dir(pot(pl),pot(pr),pot(a));
                if(d>0||(d==0&&dot(pot(pl)-pot(a),pot(pr)-pot(a))<0)){
                    pr=a;
                    f=1;
                    break;
                }
            }
            if(!f)
                break;
        }
        con(pl,pr);
        for(int pn=-1,wh=0;;pn=-1,wh=0){
            for(int i=0;i<egs[pl].size();++i){
                int a=egs[pl][i],d=dir(pot(pl),pot(pr),pot(a));
                if(d<0&&(pn==-1||inc(pot(pl),pot(pr),pot(pn),pot(a))))
                    pn=a;
            }
            for(int i=0;i<egs[pr].size();++i){
                int a=egs[pr][i],d=dir(pot(pl),pot(pr),pot(a));
                if(d<0&&(pn==-1||inc(pot(pl),pot(pr),pot(pn),pot(a))))
                    pn=a,wh=1;
            }
            if(pn==-1)
                break;
            vector<int>ne;
            if(!wh){
                for(int i=0;i<egs[pl].size();++i){
                    int a=egs[pl][i];
                    if(!crs(pot(pn),pot(pr),pot(pl),pot(a)))
                        ne.push_back(a);
                    else
                        egs[a].erase(find(egs[a].begin(),egs[a].end(),pl));
                }
                egs[pl]=ne;
                con(pr,pn);
                pl=pn;
            }else{
                for(int i=0;i<egs[pr].size();++i){
                    int a=egs[pr][i];
                    if(!crs(pot(pn),pot(pl),pot(pr),pot(a)))
                        ne.push_back(a);
                    else
                        egs[a].erase(find(egs[a].begin(),egs[a].end(),pr));
                }
                egs[pr]=ne;
                con(pl,pn);
                pr=pn;
            }
        }
    }
    vector<vector<int> >run(){
        egs.resize(n+1);
        sort(pts.begin()+1,pts.end());
        dnc(1,n);
        vector<vector<int> >res(n+1);
        for(int u=1;u<=n;++u)
            for(int i=0;i<egs[u].size();++i){
                int v=egs[u][i];
                res[pts[u].second].push_back(pts[v].second);
            }
        return res;
    }
};
template<class T>const double DelaunayTriangulation<T>::E=1e-8;
