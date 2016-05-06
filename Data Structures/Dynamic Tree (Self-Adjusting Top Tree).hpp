#include<bits/stdc++.h>
using namespace std;
struct SelfAdjustingTopTree{
    const static int inf=~0u>>1;
    static void gmin(int&a,int b){
        a=min(a,b);
    }
    static void gmax(int&a,int b){
        a=max(a,b);
    }
    struct treap{
        SelfAdjustingTopTree*tr;
        treap(struct SelfAdjustingTopTree*a,int n):
            tr(a),ns(n){
        }
        struct node{
            node(){
            }
            node(int a,int b,int c,int d,int e){
                ch[0]=ch[1]=0;
                val=a;
                fix=rand();
                add=0;
                mi=vmi=b;
                mx=vmx=c;
                sum=vsum=d;
                siz=vsiz=e;
                sam=inf;
            }
            node*ch[2];
            int val,fix,vmi,vmx,vsum,vsiz,mi,mx,sum,siz,add,sam;
        };
        vector<node>ns;
        void down(node*a){
            if(a->sam!=inf){
                a->mi=a->mx=a->vmi=a->vmx=a->sam;
                a->vsum=a->sam*a->vsiz;
                a->sum=a->sam*a->siz;
                (&tr->ns[0]+(a-&ns[0]))->viradd=0;
                (&tr->ns[0]+(a-&ns[0]))->virsam=a->sam;
                (&tr->ns[0]+(a-&ns[0]))->add=0;
                (&tr->ns[0]+(a-&ns[0]))->sam=a->sam;
                for(int i=0;i<=1;++i)
                    if(a->ch[i])
                        a->ch[i]->add=0,a->ch[i]->sam=a->sam;
                a->sam=inf;
            }
            if(a->add){
                a->mi+=a->add;
                a->mx+=a->add;
                a->vmi+=a->add;
                a->vmx+=a->add;
                a->vsum+=a->add*a->vsiz;
                a->sum+=a->add*a->siz;
                (&tr->ns[0]+(a-&ns[0]))->viradd+=a->add;
                (&tr->ns[0]+(a-&ns[0]))->add+=a->add;
                for(int i=0;i<=1;++i)
                    if(a->ch[i])
                        a->ch[i]->add+=a->add;
                a->add=0;
            }
        }
        void update(node*a){
            for(int i=0;i<=1;++i)
                if(a->ch[i])
                    down(a->ch[i]);
            a->mi=a->vmi;
            for(int i=0;i<=1;++i)
                if(a->ch[i])
                    gmin(a->mi,a->ch[i]->mi);
            a->mx=a->vmx;
            for(int i=0;i<=1;++i)
                if(a->ch[i])
                    gmax(a->mx,a->ch[i]->mx);
            a->sum=a->vsum;
            for(int i=0;i<=1;++i)
                if(a->ch[i])
                    a->sum+=a->ch[i]->sum;
            a->siz=a->vsiz;
            for(int i=0;i<=1;++i)
                if(a->ch[i])
                    a->siz+=a->ch[i]->siz;
        }
        void rotate(node*&a,int d){
            node*b=a->ch[d];
            a->ch[d]=b->ch[!d];
            b->ch[!d]=a;
            update(a);
            update(b);
            a=b;
        }
        void insert(node*&a,node*b){
            if(!a)
                a=b;
            else{
                down(a);
                int d=b->val>a->val;
                insert(a->ch[d],b);
                update(a);
                if(a->ch[d]->fix<a->fix)
                    rotate(a,d);
            }
        }
        void erase(node*&a,int b){
            down(a);
            if(a->val==b){
                if(!a->ch[0])
                    a=a->ch[1];
                else if(!a->ch[1])
                    a=a->ch[0];
                else{
                    int d=a->ch[1]->fix<a->ch[0]->fix;
                    down(a->ch[d]);
                    rotate(a,d);
                    erase(a->ch[!d],b);
                    update(a);
                }
            }else{
                int d=b>a->val;
                erase(a->ch[d],b);
                update(a);
            }
        }
    };
    int n;
    SelfAdjustingTopTree(int _n,vector<int>*to,int*we,int rt):
        trp(this,_n+1),ns(_n+1),n(_n){
        build(to,we,rt);
    }
    struct node{
        node(){}
        node(int a,node*b){
            ch[0]=ch[1]=0;
            pr=b;
            vir=0;
            val=a;
            mi=mx=a;
            siz=1;
            rev=virsum=add=0;
            virmi=inf;
            virmx=-inf;
            sam=inf;
            virsam=inf;
            virsiz=0;
            viradd=0;
        }
        node*ch[2],*pr;
        int val,mi,mx,sum,virmi,virmx,virsum,virsam,viradd,virsiz,rev,sam,siz,add;
        treap::node*vir;
    };
    vector<node>ns;
    treap trp;
    int direct(node*a){
        if(!a->pr)
            return 3;
        else if(a==a->pr->ch[0])
            return 0;
        else if(a==a->pr->ch[1])
            return 1;
        else
            return 2;
    }
    void down(node*a){
        if(a->rev){
            swap(a->ch[0],a->ch[1]);
            for(int i=0;i<=1;++i)
                if(a->ch[i])
                    a->ch[i]->rev^=1;
            a->rev=0;
        }
        if(a->sam!=inf){
            a->val=a->mi=a->mx=a->sam;
            a->sum=a->sam*a->siz;
            for(int i=0;i<=1;++i)
                if(a->ch[i])a->ch[i]->sam=a->sam,a->ch[i]->add=0;
            a->sam=inf;
        }
        if(a->add){
            a->val+=a->add;
            a->mi+=a->add;
            a->mx+=a->add;
            a->sum+=a->add*a->siz;
            for(int i=0;i<=1;++i)
                if(a->ch[i])a->ch[i]->add+=a->add;
            a->add=0;
        }
        if(a->virsam!=inf){
            if(a->virsiz){
                a->virmi=a->virmx=a->virsam;
                a->virsum=a->virsam*a->virsiz;
                if(a->vir)
                    a->vir->add=0,a->vir->sam=a->virsam;
                for(int i=0;i<=1;++i)
                    if(a->ch[i])
                        a->ch[i]->viradd=0,a->ch[i]->virsam=a->virsam;
            }
            a->virsam=inf;
        }
        if(a->viradd){
            if(a->virsiz){
                a->virmi+=a->viradd;
                a->virmx+=a->viradd;
                a->virsum+=a->viradd*a->virsiz;
                if(a->vir)a->vir->add+=a->viradd;
                for(int i=0;i<=1;++i)
                    if(a->ch[i])
                        a->ch[i]->viradd+=a->viradd;
            }
            a->viradd=0;
        }
    }
    void update(node*a){
        for(int i=0;i<=1;++i)
            if(a->ch[i])
                down(a->ch[i]);
        if(a->vir)
            trp.down(a->vir);
        a->mi=a->val;
        for(int i=0;i<=1;++i)
            if(a->ch[i])
                gmin(a->mi,a->ch[i]->mi);
        a->virmi=inf;
        for(int i=0;i<=1;++i)
            if(a->ch[i])
                gmin(a->virmi,a->ch[i]->virmi);
        if(a->vir)
            gmin(a->virmi,a->vir->mi);
        a->mx=a->val;
        for(int i=0;i<=1;++i)
            if(a->ch[i])
                gmax(a->mx,a->ch[i]->mx);
        a->virmx=-inf;
        for(int i=0;i<=1;++i)
            if(a->ch[i])
                gmax(a->virmx,a->ch[i]->virmx);
        if(a->vir)
            gmax(a->virmx,a->vir->mx);
        a->sum=a->val;
        for(int i=0;i<=1;++i)
            if(a->ch[i])
                a->sum+=a->ch[i]->sum;
        a->virsum=0;
        for(int i=0;i<=1;++i)
            if(a->ch[i])
                a->virsum+=a->ch[i]->virsum;
        if(a->vir)
            a->virsum+=a->vir->sum;
        a->siz=1;
        for(int i=0;i<=1;++i)
            if(a->ch[i])
                a->siz+=a->ch[i]->siz;
        a->virsiz=0;
        for(int i=0;i<=1;++i)
            if(a->ch[i])
                a->virsiz+=a->ch[i]->virsiz;
        if(a->vir)
            a->virsiz+=a->vir->siz;
    }
    void setchd(node*a,node*b,int d){
        a->ch[d]=b;
        if(b)
            b->pr=a;
        update(a);
    }
    void connect(node*a,node*b){
        down(a);
        *(&trp.ns[0]+(a-&ns[0]))=treap::node(a-&ns[0],min(a->virmi,a->mi),max(a->virmx,a->mx),a->virsum+a->sum,a->virsiz+a->siz);
        trp.insert(b->vir,&trp.ns[0]+(a-&ns[0]));
    }
    void disconnect(node*a,node*b){
        trp.erase(b->vir,a-&ns[0]);
    }
    void rotate(node*a){
        node*b=a->pr,*c=a->pr->pr;
        int d1=direct(a),d2=direct(b);
        setchd(b,a->ch[!d1],d1);
        setchd(a,b,!d1);
        if(d2<2)
            setchd(c,a,d2);
        else if(d2==2){
            disconnect(b,c);
            connect(a,c);
            a->pr=c;
        }else
            a->pr=0;
    }
    void release(node*a){
        if(direct(a)<2)
            release(a->pr);
        else if(a->pr)
            disconnect(a,a->pr),connect(a,a->pr);
        down(a);
    }
    void splay(node*a){
        release(a);
        while(direct(a)<2){
            node*b=a->pr;
            if(!b->pr||direct(b)>1)
                rotate(a);
            else if(direct(a)==direct(b))
                rotate(b),rotate(a);
            else
                rotate(a),rotate(a);
        }
    }
    node*access(node*a){
        node*b=0;
        while(a){
            splay(a);
            if(a->ch[1])
                connect(a->ch[1],a);
            if(b)
                disconnect(b,a);
            setchd(a,b,1);
            b=a;
            a=a->pr;
        }
        return b;
    }
    void evert(node*a){
        access(a);
        splay(a);
        a->rev=1;
    }
    int qchain(node*a,node*b,int d){
        access(a);
        node*c=access(b);
        splay(c);
        splay(a);
        int ret=c->val;
        if(d==1){
            if(a!=c)
                gmin(ret,a->mi);
            if(c->ch[1])
                down(c->ch[1]),gmin(ret,c->ch[1]->mi);
        }else if(d==2){
            if(a!=c)
                gmax(ret,a->mx);
            if(c->ch[1])
                down(c->ch[1]),gmax(ret,c->ch[1]->mx);
        }else if(d==3){
            if(a!=c)
                ret+=a->sum;
            if(c->ch[1])
                down(c->ch[1]),ret+=c->ch[1]->sum;
        }
        return ret;
    }
    void mchain(node*a,node*b,int u,int d){
        access(a);
        node*c=access(b);
        splay(c);
        splay(a);
        if(d==1){
            c->val+=u;
            if(a!=c)
                a->add=u,disconnect(a,c),connect(a,c);
            if(c->ch[1])
                down(c->ch[1]),c->ch[1]->add=u;
        }else if(d==2){
            c->val=u;
            if(a!=c)
                a->sam=u,disconnect(a,c),connect(a,c);
            if(c->ch[1])
                down(c->ch[1]),c->ch[1]->sam=u;
        }
        update(c);
    }
    int qtree(node*a,int d){
        access(a);
        splay(a);
        int ret=a->val;
        if(d==1){
            if(a->vir)
                trp.down(a->vir),gmin(ret,a->vir->mi);
        }else if(d==2){
            if(a->vir)
                trp.down(a->vir),gmax(ret,a->vir->mx);
        }else if(d==3){
            if(a->vir)
                trp.down(a->vir),ret+=a->vir->sum;
        }
        return ret;
    }
    void mtree(node*a,int u,int d){
        access(a);
        splay(a);
        if(d==1){
            a->val+=u;
            if(a->vir)
                trp.down(a->vir),a->vir->add=u;
        }else if(d==2){
            a->val=u;
            if(a->vir)
                trp.down(a->vir),a->vir->sam=u;
        }
        update(a);
    }
    void stparent(node*a,node*b){
        access(b);
        if(access(a)!=a){
            splay(a);
            node*c=a->ch[0];
            down(c);
            while(c->ch[1])
                c=c->ch[1],down(c);
            splay(c);
            c->ch[1]=0;
            update(c);
            access(b);
            splay(b);
            connect(a,b);
            a->pr=b;
            update(b);
        }
    }
    void build(vector<int>*to,int*we,int rt){
        vector<int>pr(n);
        vector<int>vec;
        queue<int>qu;
        qu.push(rt);
        while(!qu.empty()){
            int u=qu.front();
            qu.pop();
            vec.push_back(u);
            for(int i=0;i<to[u].size();++i){
                int v=to[u][i];
                if(v!=pr[u])
                    qu.push(v),pr[v]=u;
            }
        }
        for(int i=0;i<n;++i){
            int u=vec[i];
            ns[u]=node(we[u],pr[u]?&ns[0]+pr[u]:0);
        }
        for(int i=n-1;i>=0;--i){
            int u=vec[i];
            update(&ns[0]+u);
            if(pr[u])
                connect(&ns[0]+u,&ns[0]+pr[u]);
        }
    }
};
