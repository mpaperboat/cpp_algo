#include<bits/stdc++.h>
using namespace std;
namespace Geometry2D{
    double eps=1e-8;
    long double pi=acos((long double)-1);
    template<class T>T sqr(T a){
        return a*a;
    }
    template<class T>int cmp(T a,T b){
        if(typeid(T)==typeid(int)||typeid(T)==typeid(long long)){
            if(a==b)
                return 0;
            return a<b?-1:1;
        }
        if(a<b-eps)
            return -1;
        if(a>b+eps)
            return 1;
        return 0;
    }
    template<class T>struct Point{
        T x,y;
        Point(T _x=0,T _y=0):
            x(_x),y(_y){
        }
        Point<T>&operator+=(const Point<T>&a){
            return*this=*this+a;
        }
        Point<T>&operator-=(const Point<T>&a){
            return*this=*this-a;
        }
    };
    #define Vector Point
    template<class T>Point<T>operator+(const Point<T>&a,const Point<T>&b){
        return Point<T>(a.x+b.x,a.y+b.y);
    }
    template<class T>Point<T>operator-(const Point<T>&a,const Point<T>&b){
        return Point<T>(a.x-b.x,a.y-b.y);
    }
    template<class T>Point<T>operator*(T a,const Point<T>&b){
        return Point<T>(b.x*a,b.y*a);
    }
    template<class T>Point<T>operator*(const Point<T>&a,T b){
        return b*a;
    }
    template<class T>Point<T>operator/(const Point<T>&a,T b){
        return Point<T>(a.x/b,a.y/b);
    }
    template<class T>bool operator==(const Point<T>&a,const Point<T>&b){
        return !cmp(a.x,b.x)&&!cmp(a.y,b.y);
    }
    template<class T>bool operator!=(const Point<T>&a,const Point<T>&b){
        return !(a==b);
    }
    template<class T>bool operator<(const Point<T>&a,const Point<T>&b){
        int t=cmp(a.x,b.x);
        if(t)
            return t<0;
        return cmp(a.y,b.y)<0;
    }
    template<class T>bool operator>(const Point<T>&a,const Point<T>&b){
        return b<a;
    }
    template<class T>Point<T>NaP(){
        T t=numeric_limits<T>::max();
        return Point<T>(t,t);
    }
    template<class T>T det(const Point<T>&a,const Point<T>&b){
        return a.x*b.y-a.y*b.x;
    }
    template<class T>T dot(const Point<T>&a,const Point<T>&b){
        return a.x*b.x+a.y*b.y;
    }
    template<class T>T abs(const Point<T>&a){
        return sqrt(sqr(a.x)+sqr(a.y));
    }
    template<class T>T dis(const Point<T>&a,const Point<T>&b){
        return abs(a-b);
    }
    template<class T>istream&operator>>(istream&s,Point<T>&a){
        return s>>a.x>>a.y;
    }
    template<class T>ostream&operator<<(ostream&s,const Point<T>&a){
        return s<<a.x<<" "<<a.y;
    }
    template<class T>struct Segment;
    template<class T>struct Line{
        Point<T>u,v;
        Line(const Point<T>&_u=Point<T>(),const Point<T>&_v=Point<T>()):
            u(_u),v(_v){
        }
        Line(const Segment<T>&a):
            u(a.u),v(a.v){
        }
    };
    template<class T>Point<T>nor(const Line<T>&a){
        Point<T>t=a.v-a.u;
        return Point<T>(t.y,-t.x);
    }
    template<class T>Point<T>dir(const Line<T>&a){
        return a.v-a.u;
    }
    template<class T>int dir(const Line<T>a,const Point<T>b){
        return cmp(det(b-a.u,a.v-a.u),T(0));
    }
    template<class T>Point<T>operator&(const Line<T>&a,const Line<T>&b){
        T p=det(b.u-a.v,b.v-b.u),q=det(a.u-b.v,b.v-b.u);
        return (a.u*p+a.v*q)/(p+q);
    }
    template<class T>struct Segment{
        Point<T>u,v;
        Segment(const Point<T>&_u=Point<T>(),const Point<T>&_v=Point<T>()):
            u(_u),v(_v){
        }
    };
    template<class T>Point<T>nor(const Segment<T>&a){
        Point<T>t=a.v-a.u;
        return Point<T>(t.y,-t.x);
    }
    template<class T>Point<T>dir(const Segment<T>&a){
        return a.v-a.u;
    }
    template<class T>int dir(const Segment<T>a,const Point<T>b){
        return cmp(b-a.u,a.v-a.u);
    }
    template<class T>Point<T>operator&(const Line<T>&a,const Segment<T>&b){
        if(dir(a,b.u)*dir(a,b.v)<=0)
            return a&Line<T>(b);
        return NaP<T>();
    }
    template<class T>Point<T>operator&(const Segment<T>&a,const Line<T>&b){
        return b&a;
    }
    template<class T>pair<T,T>dis(const Segment<T>&a,const Point<T>&b){
        pair<T,T>d(dis(a.u,b),dis(a.v,b));
        if(d.first>d.second)
            swap(d.first,d.second);
        Point<T>t=Line<T>(b,b+nor(a))&a;
        if(t!=NaP<T>())
            d.first=dis(t,b);
        return d;
    }
    template<class T>pair<T,T>dis(const Point<T>&a,const Segment<T>&b){
        return dis(b,a);
    }
    template<class T>struct Circle{
        Point<T>c;
        T r;
        Circle(const Point<T>&_c=Point<T>(),T _r=0):
            c(_c),r(_r){
        }
    };
    template<class T>T abs(const Circle<T>&a){
        return pi*sqr(a.r);
    }
    template<class T>bool col(const Point<T>&a,const Point<T>&b,const Point<T>&c){
        return !cmp(det(a-c,b-c),T(0));
    }
}
