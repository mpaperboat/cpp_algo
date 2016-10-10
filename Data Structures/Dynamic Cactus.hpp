#include<iostream>//2015-5-7 版本？ 仙人掌差评+1 = =
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<queue>
#include<cstring>
#define PAU putchar(' ')
#define ENT putchar('\n')
#define MAXN 50005
#define MAXM 250005
#define is_NULL_tag(x) ((x)==0)
#define is_NULL_info(x) (x.size==0)
using namespace std;
inline int read(){
	int x=0,sig=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')sig=-1;ch=getchar();}
	while(isdigit(ch))x=10*x+ch-'0',ch=getchar();
	return x*=sig;
}
inline void write(int x){
	if(x==0){putchar('0');return;}if(x<0)putchar('-'),x=-x;
	int len=0,buf[15];while(x)buf[len++]=x%10,x/=10;
	for(int i=len-1;i>=0;i--)putchar(buf[i]+'0');return;
}
char ch;
inline void Pass_Pau(int x){while(x--) getchar();return;}
int n,Q;
struct Info{
	int mi,size;
	long long sum;
};
const int NULL_TAG=0;
const Info NULL_INFO=(Info){2147483647,0,0};
inline Info operator + (const Info &a,const Info &b){return (Info){std::min(a.mi,b.mi),a.size+b.size,a.sum+b.sum};}
inline Info operator * (const Info &a,const int &b){return a.size ? (Info){a.mi+b,a.size,a.sum+1LL*a.size*b}: a;}
struct splay_node{
	splay_node *ch[2],*fa;
	Info x,sum;
	int tag,tag_sum;
	inline void add_tag(int t){
		x=x*t;sum=sum*t;
		tag=tag+t;tag_sum=tag_sum+t;
		return;
	}
	inline void down(){
		if(is_NULL_tag(tag)) return;
		if(ch[0]) ch[0]->add_tag(tag);
		if(ch[1]) ch[1]->add_tag(tag);
		tag=NULL_TAG;
		return;
	}
	inline void update(){
		sum=x;
		if(ch[0]) sum=sum+ch[0]->sum;
		if(ch[1]) sum=sum+ch[1]->sum;
		return;
	}
};
splay_node _splay[MAXN+MAXM];
inline int get_parent(splay_node *x,splay_node *&fa){return (fa=x->fa) ? fa->ch[1]==x : -1;}//把父亲扔到fa里同时返回d值 
inline void rotate(splay_node *x){
	splay_node *fa,*gfa;
	int t1,t2;
	t1=get_parent(x,fa);
	t2=get_parent(fa,gfa);
	if((fa->ch[t1]=x->ch[t1^1])) fa->ch[t1]->fa=fa;
	fa->fa=x;x->fa=gfa;x->ch[t1^1]=fa;
	if(t2!=-1) gfa->ch[t2]=x;
	fa->update();
	return;
}
inline void pushdown(splay_node *x){
	static splay_node *stack[MAXN+MAXM];
	int cnt=0;
	while(x) stack[cnt++]=x,x=x->fa;
	while(cnt--) stack[cnt]->down();
	return;
}
inline splay_node * splay(splay_node *x){
	pushdown(x);
	while(1){
		splay_node *fa,*gfa;
		int t1,t2;
		t1=get_parent(x,fa);
		if(t1==-1) break;
		t2=get_parent(fa,gfa);
		if(t2==-1){
			rotate(x);break;
		}else if(t1==t2){
			rotate(fa);rotate(x);
		}else{
			rotate(x);rotate(x);
		};
	}
	x->update();
	return x;
}
inline splay_node * join(splay_node *a,splay_node *b){
	if(!a) return b;
	if(!b) return a;
	while(a->ch[1]) a->down(),a=a->ch[1];
	splay(a)->ch[1]=b;b->fa=a;
	a->update();
	return a;
}
struct lcc_node;
struct cycle{
	int A,B;
	lcc_node *ex;
};
struct lcc_node{
	lcc_node *ch[2],*fa;
	lcc_node *first,*last;
	bool rev;
	bool isedge;
	bool mpath;
	bool hasmpath;
	bool mpathtag;
	bool hasmpathtag;
	bool hascyctag;
	bool hascyc;
	cycle *cyc;
	cycle *cyctag;
	int totlen;
	int len;
	int size;
	Info x,sum,sub,ex,all;
	int chain_tag,sub_tag,ex_tag_sum;
	inline void add_rev_tag(){
		std::swap(ch[0],ch[1]);
		std::swap(first,last);
		rev^=1;
		return;
	}
	inline void add_cyc_tag(cycle *c){
		if(isedge) cyc=c;
		cyctag=c;
		hascyctag=1;
		hascyc=c;
		return;
	}
	inline void add_mpath_tag(bool t){
		mpathtag=t;
		hasmpathtag=1;
		mpath=t&isedge;
		hasmpath=t&(isedge|(size>1));
		return;
	}
	inline void add_chain_tag(int t)
	{
		if(is_NULL_tag(t)) return;
		x=x*t;sum=sum*t;
		chain_tag=chain_tag+t;
		all=sum+sub;
		return;
	};
	inline void add_sub_tag(int t);
	inline void down(){
		if(rev){
			if(ch[0]) ch[0]->add_rev_tag();
			if(ch[1]) ch[1]->add_rev_tag();
			rev=0;
		}
		if(hascyctag){
			if(ch[0]) ch[0]->add_cyc_tag(cyctag);
			if(ch[1]) ch[1]->add_cyc_tag(cyctag);
			hascyctag=0;
		}
		if(hasmpathtag){
			if(ch[0]) ch[0]->add_mpath_tag(mpathtag);
			if(ch[1]) ch[1]->add_mpath_tag(mpathtag);
			hasmpathtag=0;
		}
		if(!is_NULL_tag(chain_tag)){
			if(ch[0]) ch[0]->add_chain_tag(chain_tag);
			if(ch[1]) ch[1]->add_chain_tag(chain_tag);
			chain_tag=NULL_TAG;
		}
		if(!is_NULL_tag(sub_tag)){
			if(ch[0]) ch[0]->add_sub_tag(sub_tag);
			if(ch[1]) ch[1]->add_sub_tag(sub_tag);
			sub_tag=NULL_TAG;
		}
		return;
	}
	inline void update();
};
lcc_node lcc[MAXN+MAXM];
lcc_node *_node_tot;
splay_node *splay_root[MAXN+MAXM];
inline void lcc_node::add_sub_tag(int t){
	if(is_NULL_tag(t)) return;
	sub=sub*t;ex=ex*t;
	sub_tag=sub_tag+t;
	ex_tag_sum=ex_tag_sum+t;
	all=sum+sub;
	// add tag to splay_root
	int id=this-lcc;
	if(splay_root[id]){
		splay_root[id]->add_tag(t);
	}
}
inline void lcc_node::update(){
	totlen=len;
	hascyc=cyc;
	size=1;
	hasmpath=mpath;
	if(ch[0]) totlen+=ch[0]->totlen,hascyc|=ch[0]->hascyc,size+=ch[0]->size,hasmpath|=ch[0]->hasmpath;
	if(ch[1]) totlen+=ch[1]->totlen,hascyc|=ch[1]->hascyc,size+=ch[1]->size,hasmpath|=ch[1]->hasmpath;
	first=ch[0]?ch[0]->first:this;
	last=ch[1]?ch[1]->last:this;
	bool s0=ch[0],s1=ch[1];
	if(isedge){
		if(is_NULL_info(ex)){
			if(s0 && s1){
				sum=ch[0]->sum+ch[1]->sum;
				sub=ch[0]->sub+ch[1]->sub;
			}else if(s0){
				sum=ch[0]->sum;
				sub=ch[0]->sub;
			}else if(ch[1]){
				sum=ch[1]->sum;
				sub=ch[1]->sub;
			}else{
				sub=sum=NULL_INFO;
			}
		}else{
			if(s0 && s1){
				sum=ch[0]->sum+ch[1]->sum;
				sub=ch[0]->sub+ch[1]->sub+ex;
			}else if(s0){
				sum=ch[0]->sum;
				sub=ch[0]->sub+ex;
			}else if(ch[1]){
				sum=ch[1]->sum;
				sub=ch[1]->sub+ex;
			}else{
				sum=NULL_INFO;
				sub=ex;
			}
		}
	}else{
		splay_node *root=splay_root[this-lcc];
		if(root){
			if(s0 && s1){
				sum=ch[0]->sum+ch[1]->sum+x;
				sub=ch[0]->sub+ch[1]->sub+root->sum;
			}else if(s0){
				sum=ch[0]->sum+x;
				sub=ch[0]->sub+root->sum;
			}else if(ch[1]){
				sum=ch[1]->sum+x;
				sub=ch[1]->sub+root->sum;
			}else{
				sub=root->sum;
				sum=x;
			}
		}else{
			if(s0 && s1){
				sum=ch[0]->sum+ch[1]->sum+x;
				sub=ch[0]->sub+ch[1]->sub;
			}else if(s0){
				sum=ch[0]->sum+x;
				sub=ch[0]->sub;
			}else if(ch[1]){
				sum=ch[1]->sum+x;
				sub=ch[1]->sub;
			}else{
				sum=x;
				sub=NULL_INFO;
			}
		}
	}
	all=sum+sub;
	return;
};
inline lcc_node * new_edge_node(int u,int v,int len){
	lcc_node *ret=++_node_tot;
	ret->ch[0]=ret->ch[1]=ret->fa=NULL;
	ret->first=ret->last=ret;
	ret->rev=0;
	ret->isedge=1;
	ret->hascyctag=ret->hascyc=0;
	ret->cyc=ret->cyctag=NULL;
	ret->totlen=ret->len=len;
	ret->size=1;
	ret->x=ret->sum=ret->sub=ret->ex=ret->all=NULL_INFO;
	ret->chain_tag=ret->sub_tag=ret->ex_tag_sum=NULL_TAG;
	return ret;
}
inline int get_parent(lcc_node *x,lcc_node *&fa){return (fa=x->fa) ? fa->ch[0]==x?0:fa->ch[1]==x?1:-1 : -1;}
inline void rotate(lcc_node *x){
	int t1,t2;
	lcc_node *fa,*gfa;
	t1=get_parent(x,fa);
	t2=get_parent(fa,gfa);
	if((fa->ch[t1]=x->ch[t1^1])) fa->ch[t1]->fa=fa;
	fa->fa=x;x->fa=gfa;x->ch[t1^1]=fa;
	if(t2!=-1) gfa->ch[t2]=x;
	fa->update();
	return;
}
inline void pushdown(lcc_node *x){
	static lcc_node *stack[MAXN+MAXM];
	int cnt=0;
	while(1){
		stack[cnt++]=x;
		lcc_node *fa=x->fa;
		if(!fa || (fa->ch[0]!=x && fa->ch[1]!=x)) break;
		x=fa;
	}
	while(cnt--) stack[cnt]->down();
	return;
}
inline lcc_node * splay(lcc_node *x){
	pushdown(x);
	while(1){
		int t1,t2;
		lcc_node *fa,*gfa;
		t1=get_parent(x,fa);
		if(t1==-1) break;
		t2=get_parent(fa,gfa);
		if(t2==-1){
			rotate(x);break;
		}else if(t1==t2){
			rotate(fa);rotate(x);
		}else{
			rotate(x);rotate(x);
		}
	}
	x->update();
	return x;
}
inline int getrank(lcc_node *x){
	splay(x);
	return 1+(x->ch[0]?x->ch[0]->size:0);
}
bool _attached[MAXN+MAXM];
inline void detach_rch(lcc_node *x){
	if(!x->ch[1]) return;
	int X=x-lcc;
	int id=x->ch[1]->first-lcc;
	_attached[id]=1;
	splay_node *p=_splay+id;
	p->ch[0]=splay_root[X];
	if(splay_root[X]) splay_root[X]->fa=p;
	p->ch[1]=p->fa=NULL;
	p->x=x->ch[1]->all;
	p->tag=p->tag_sum=NULL_TAG;
	p->update();
	splay_root[X]=p;
	x->ch[1]=NULL;
	return;
}
inline void attach_rch(lcc_node *x,lcc_node *y,int id){
	int X=x-lcc;
	_attached[id]=0;
	splay_node *p=_splay+id;
	splay(p);
	if(p->ch[0]) p->ch[0]->fa=NULL;
	if(p->ch[1]) p->ch[1]->fa=NULL;
	splay_root[X]=join(p->ch[0],p->ch[1]);
	y->add_chain_tag(p->tag_sum);
	y->add_sub_tag(p->tag_sum);
	x->ch[1]=y;
	return;
}
inline void attach_rch(lcc_node *x,lcc_node *y,int id,int id2){
	if(_attached[id]) attach_rch(x,y,id);
	else attach_rch(x,y,id2);
	return;
}
inline void attach_rch(lcc_node *x,lcc_node *y){
	if(!y) return;
	attach_rch(x,y,y->first-lcc);
	return;
}
inline lcc_node * access(lcc_node *x){
	lcc_node *ret=NULL;
	int last_ex_last_id;
	while(x){
		lcc_node *t=splay(x)->ch[0];
		if(!t){
			detach_rch(x);
			if(ret) attach_rch(x,ret,ret->first-lcc,last_ex_last_id);
			ret=x;x->update();
			x=x->fa;
			continue;
		}
		while(t->ch[1]) t->down(),t=t->ch[1];
		if(!splay(t)->cyc){
			splay(x);
			detach_rch(x);
			if(ret) attach_rch(x,ret,ret->first-lcc,last_ex_last_id);
			ret=x;x->update();
			x=x->fa;
			continue;
		}
		cycle *c=t->cyc;
		lcc_node *A=lcc+c->A,*B=lcc+c->B,*ex=splay(c->ex);
		bool need_tag_down=false;
		lcc_node *B_ex;
		if(splay(B)->fa==A){
			detach_rch(B);
			B->ch[1]=ex;ex->fa=B;B->update();
			need_tag_down=true;
			B_ex=B->ch[0]->first;
		}else if(splay(A)->fa==B){
			std::swap(c->A,c->B);std::swap(A,B);ex->add_rev_tag();
			detach_rch(B);
			B->ch[1]=ex;ex->fa=B;B->update();
			need_tag_down=true;
			B_ex=B->ch[0]->last;
		}else{
			bool f=0;
			if(getrank(A)>getrank(B)){
				std::swap(c->A,c->B);std::swap(A,B);ex->add_rev_tag();
				f=1;
			}
			splay(A)->ch[1]->fa=NULL;A->ch[1]=NULL;A->update();
			splay(B);detach_rch(B);
			B->ch[1]=ex;ex->fa=B;B->update();
			B_ex=f ? B->ch[0]->last : B->ch[0]->first;
		}
		// add tag to ex
		int tag_ex=splay(B_ex)->ex_tag_sum;
		B_ex->ex=NULL_INFO;
		B_ex->update();
		ex=splay(B)->ch[1];
		ex->add_chain_tag(tag_ex);
		ex->add_sub_tag(tag_ex);
		B->update();
		splay(x);c->B=x-lcc;
		if(x->ch[1]->totlen<x->ch[0]->totlen) x->add_rev_tag();
		x->add_mpath_tag(x->ch[1]->totlen==x->ch[0]->totlen);
		x->down();
		c->ex=x->ch[1];x->ch[1]->fa=NULL;
		x->ch[1]=NULL;
		x->update();
		lcc_node *tmp=splay(x->first);
		tmp->ex=c->ex->all;
		tmp->ex_tag_sum=NULL_TAG;
		tmp->update();
		splay(x);
		if(ret) attach_rch(x,ret,ret->first-lcc,last_ex_last_id);
		x->update();
		last_ex_last_id=c->ex->last-lcc;
		if(splay(A)->ch[1]) ret=x,x=x->fa;
		else{
			if(need_tag_down) attach_rch(A,x,c->ex->last-lcc,x->first-lcc);
			A->ch[1]=x;x->fa=A;A->update();
			ret=A;x=A->fa;
		}
	}
	return ret;
}
inline void setroot(int x){access(lcc+x)->add_rev_tag();};
inline bool link(int u,int v,int len){
	if(u==v) return false;
	setroot(u);
	lcc_node *t=access(lcc+v);
	while(t->ch[0]) t->down(),t=t->ch[0];
	if(splay(t)!=lcc+u){
		lcc_node *p=new_edge_node(u,v,len);
		p->fa=splay(lcc+u);
		lcc[u].ch[0]=p;
		lcc[u].fa=lcc+v;
		lcc[u].update();
		splay(lcc+v)->ch[1]=lcc+u;
		lcc[v].update();
		return true;
	}
	if(t->hascyc) return false;
	lcc_node *ex=new_edge_node(u,v,len);
	cycle *c=new cycle((cycle){u,v,ex});
	ex->add_cyc_tag(c);
	t->add_cyc_tag(c);
	access(lcc+v);
	return true;
}
inline bool cut(int u,int v,int len){
	if(u==v) return false;
	setroot(u);
	lcc_node *t=access(lcc+v);
	while(t->ch[0]) t->down(),t=t->ch[0];
	if(splay(t)!=lcc+u) return false;
	if(!t->hascyc){
		if(t->size!=3) return false;
		if(t->totlen!=len) return false;
		t=t->ch[1];
		if(t->ch[0]) t->down(),t=t->ch[0];
		splay(t);
		t->ch[0]->fa=NULL;t->ch[1]->fa=NULL;
		return true;
	}
	t=splay(lcc+v)->ch[0];
	while(t->ch[1]) t->down(),t=t->ch[1];
	cycle *c=splay(t)->cyc;
	if(!c) return false;
	t=splay(lcc+u)->ch[1];
	while(t->ch[0]) t->down(),t=t->ch[0];
	if(splay(t)->cyc!=c) return false;
	lcc_node *ex=c->ex;
	if(ex->size==1 && ex->len==len){
		t->add_cyc_tag(NULL);
		t->add_mpath_tag(0);
		delete c;
		return true;
	}
	if(t->size!=3 || t->len!=len) return false;
	// lcc[u].mpath == 0 !
	ex->add_cyc_tag(NULL);
	ex->add_mpath_tag(0);
	ex->add_rev_tag();
	ex->add_sub_tag(t->ex_tag_sum);
	ex->add_chain_tag(t->ex_tag_sum);
	lcc[u].fa=lcc[v].fa=NULL;
	while(ex->ch[0]) ex->down(),ex=ex->ch[0];
	splay(ex)->ch[0]=lcc+u;lcc[u].fa=ex;ex->update();
	while(ex->ch[1]) ex->down(),ex=ex->ch[1];
	splay(ex)->ch[1]=lcc+v;lcc[v].fa=ex;ex->update();
	delete c;
	return true;
}
inline Info query_path(int u,int v){
	setroot(u);
	lcc_node *t=access(lcc+v);
	while(t->ch[0]) t->down(),t=t->ch[0];
	if(splay(t)!=lcc+u) return (Info){-1,-1,-1};
	if(t->hasmpath) return (Info){-2,-2,-2};
	return t->sum;
}
inline Info query_subcactus(int u,int v){
	setroot(u);
	lcc_node *t=access(lcc+v);
	while(t->ch[0]) t->down(),t=t->ch[0];
	if(splay(t)!=lcc+u) return (Info){-1,-1,-1};
	Info ret=splay(lcc+v)->x;
	if(splay_root[v]) ret=ret+splay_root[v]->sum;
	return ret;
}
inline bool modify_path(int u,int v,int tag){
	setroot(u);
	lcc_node *t=access(lcc+v);
	while(t->ch[0]) t->down(),t=t->ch[0];
	if(splay(t)!=lcc+u) return false;
	if(t->hasmpath) return false;
	t->add_chain_tag(tag);
	return true;
}
inline bool modify_subcactus(int u,int v,int tag){
	setroot(u);
	lcc_node *t=access(lcc+v);
	while(t->ch[0]) t->down(),t=t->ch[0];
	if(splay(t)!=lcc+u) return false;
	splay(lcc+v);
	lcc[v].x=lcc[v].x*tag;
	if(splay_root[v]) splay_root[v]->add_tag(tag);
	lcc[v].update();
	return true;
}
void init(){
	n=read();Q=read();
	int i;
	static int w[MAXN];
	for(i=1;i<=n;i++){
		w[i]=read();
		lcc[i].first=lcc[i].last=lcc+i;
		lcc[i].size=1;
		lcc[i].x=lcc[i].sum=lcc[i].all=(Info){w[i],1,w[i]};
		lcc[i].sub=lcc[i].ex=NULL_INFO;
		lcc[i].chain_tag=lcc[i].sub_tag=lcc[i].ex_tag_sum=NULL_TAG;
	}
	_node_tot=lcc+n;
	return;
}
void work(){
	for(int i=1;i<=Q;i++){
		char ch=getchar();
		while(ch<=32) ch=getchar();
		if(ch=='l'){
			Pass_Pau(3);
			int u=read(),v=read(),len=read();
			puts(link(u,v,len) ? "ok" : "failed");
		}else if(ch=='c'){
			Pass_Pau(2);
			int u=read(),v=read(),len=read();
			puts(cut(u,v,len) ? "ok" : "failed");
		}else if(ch=='q'){
			Pass_Pau(4);
			ch=getchar();
			int u=read(),v=read();
			Info ret;
			ret=ch=='1' ? query_path(u,v) : query_subcactus(u,v);
			printf("%d %lld\n",ret.mi,ret.sum);
		}else if(ch=='a'){
			Pass_Pau(2);
			ch=getchar();
			int u=read(),v=read(),val=read();
			puts((ch=='1'?modify_path(u,v,val):modify_subcactus(u,v,val)) ? "ok" : "failed");
		}else puts("error");
	}
	return;
}
void print(){
	return;
}
int main(){init();work();print();return 0;}