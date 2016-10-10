/*
动态插点的最远点对
kd树需要补替罪羊
否则只能插随机的点
ans存的是距离平方
静态内存加速，请用static定义
注意如果点集形成一个圆，查询效率是很糟糕的
*/
#include<bits/stdc++.h>
using namespace std;
const int N=1000000;
struct DynamicFarthestPair{
    struct node{
        int x,y,x0,y0,x1,y1;
        node*c[2];
    }*root,pool[N],*ptr;
    long long ans;
    node*make(int x,int y){
        ptr->c[0]=ptr->c[1]=0;
        ptr->x=ptr->x0=ptr->x1=x;
        ptr->y=ptr->y0=ptr->y1=y;
        return ptr++;
    }
    DynamicFarthestPair():
        ans(0),root(0),ptr(pool){}
    void insert(node*&u,int x,int y,int d){
        if(u){
            u->x0=min(u->x0,x);
            u->x1=max(u->x1,x);
            u->y0=min(u->y0,y);
            u->y1=max(u->y1,y);
            insert(u->c[d&&y>u->y||!d&&x>u->x],x,y,1-d);
        }else
            u=make(x,y);
    }
    long long dist(long long x1,long long y1,int x2,int y2){
        return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
    }
    long long estim(node*u,int x,int y){
        if(u){
            long long p=max(dist(u->x0,u->y0,x,y),dist(u->x1,u->y0,x,y)),
                q=max(dist(u->x0,u->y1,x,y),dist(u->x1,u->y1,x,y));
            return max(p,q);
        } else
            return 0;
    }
    void query(node*u,int x,int y){
        ans=max(ans,dist(u->x,u->y,x,y));
        long long e[2];
        for(int i=0;i<2;++i)
            e[i]=estim(u->c[i],x,y);
        int d=e[0]<e[1];
        if(e[d]>ans)
            query(u->c[d],x,y);
        if(e[!d]>ans)
            query(u->c[!d],x,y);
    }
    void insert(int x,int y){
        insert(root,x,y,0);
        query(root,x,y);
    }
};