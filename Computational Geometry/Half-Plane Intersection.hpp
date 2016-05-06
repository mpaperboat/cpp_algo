#include<bits/stdc++.h>
using namespace std;
namespace HalfPlaneIntersection{
    const double E=1e-8;
    struct pot{
        pot(double a=0,double b=0):
            x(a),y(b){
        }
        double x,y;
    };
    double ag(pot p){
        return atan2(double(p.x),double(p.y));
    }
    pot operator+(pot p,pot q){
        return pot(p.x+q.x,p.y+q.y);
    }
    pot operator-(pot p,pot q){
        return pot(p.x-q.x,p.y-q.y);
    }
    pot operator*(pot p,double q){
        return pot(p.x*q,p.y*q);
    }
    pot operator/(pot p,double q){
        return pot(p.x/q,p.y/q);
    }
    double det(pot p,pot q){
        return p.x*q.y-q.x*p.y;
    }
    double dot(pot p,pot q){
        return p.x*q.x+p.y*q.y;
    }
    struct lin{
        pot p,q;
        double a;
        lin(pot a,pot b):
            p(a),q(b),a(ag(b-a)){
        }
    };
    pot operator*(lin a,lin b){
        double a1=det(b.p-a.q,b.q-b.p);
        double a2=det(a.p-b.q,b.q-b.p);
        return (a.p*a1+a.q*a2)/(a1+a2);
    }
    bool cmp(lin a,lin b){
        if(fabs(a.a-b.a)>E)
            return a.a<b.a;
        else
            return det(a.q-b.p,b.q-b.p)<-E;
    }
    bool left(lin a,lin b,lin c){
        pot t=a*b;
        return det(t-c.p,c.q-c.p)<-E;
    }
    deque<lin>run(vector<lin>lns){
        deque<lin>ans;
        sort(lns.begin(),lns.end(),cmp);
        for(int i=0;i<lns.size();++i){
            while(ans.size()>1&&!left(ans.back(),ans[ans.size()-2],lns[i]))
                ans.pop_back();
            while(ans.size()>1&&!left(ans[0],ans[1],lns[i]))
                ans.pop_front();
            if(ans.empty()||fabs(ans.back().a-lns[i].a)>E)
                ans.push_back(lns[i]);
        }
        while(ans.size()>1&&!left(ans.back(),ans[ans.size()-2],ans.front()))
            ans.pop_back();
        if(ans.size()<3)
            ans.clear();
        return ans;
    }
}
