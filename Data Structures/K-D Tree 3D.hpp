#include<bits/stdc++.h>
using namespace std;
struct KDTree{
    struct node{
        node(int x0,int x1,int d):
            color(1),cover(0),dir(d){
                ch[0]=ch[1]=0;
                x[0]=mi[0]=mx[0]=x0;
                x[1]=mi[1]=mx[1]=x1;
        }
        node*ch[2];
        int x[2],mi[2],mx[2],color,cover,dir;
    }*root;
    KDTree(pair<int,int>*a,int n){
        root=build(a,1,n,0);
    }
    static int direct;
    static int cmp(pair<int,int>a,pair<int,int>b){
        if(direct)
            return make_pair(a.second,a.first)<make_pair(b.second,b.first);
        return a<b;
    }
    node*build(pair<int,int>*a,int l,int r,int d){
        int m=(r+l)/2;
        direct=d;
        nth_element(a+l,a+m,a+r+1,cmp);
        node*p=new node((a+m)->first,(a+m)->second,d);
        if(l!=m)
            p->ch[0]=build(a,l,m-1,!d);
        if(r!=m)
            p->ch[1]=build(a,m+1,r,!d);
        for(int i=0;i<2;++i)
            for(int j=0;j<2;++j)
                if(p->ch[j]){
                    p->mi[i]=min(p->mi[i],p->ch[j]->mi[i]);
                    p->mx[i]=max(p->mx[i],p->ch[j]->mx[i]);
                }
        return p;
    }
    void down(node*a){
        if(a->cover){
            for(int i=0;i<2;++i)
                if(a->ch[i])
                    a->ch[i]->cover=a->cover;
            a->color=a->cover;
            a->cover=0;
        }
    }
    void modify(node*a,int mi0,int mx0,int mi1,int mx1,int c){
        if(mi0>a->mx[0]||mx0<a->mi[0]||mi1>a->mx[1]||mx1<a->mi[1])
            return;
        if(mi0<=a->mi[0]&&mx0>=a->mx[0]&&mi1<=a->mi[1]&&mx1>=a->mx[1]){
            a->cover=c;
            return;
        }
        down(a);
        if(mi0<=a->x[0]&&mx0>=a->x[0]&&mi1<=a->x[1]&&mx1>=a->x[1])
            a->color=c;
        for(int i=0;i<2;++i)
            if(a->ch[i])
                modify(a->ch[i],mi0,mx0,mi1,mx1,c);
    }
    void modify(int mi0,int mx0,int mi1,int mx1,int c){
        modify(root,mi0,mx0,mi1,mx1,c);
    }
    int query(node*a,int x0,int x1){
        down(a);
        if(x0==a->x[0]&&x1==a->x[1])
            return a->color;
        direct=a->dir;
        if(cmp(make_pair(x0,x1),make_pair(a->x[0],a->x[1])))
            return query(a->ch[0],x0,x1);
        else
            return query(a->ch[1],x0,x1);
    }
    int query(int x0,int x1){
        return query(root,x0,x1);
    }
};
int KDTree::direct=0;
