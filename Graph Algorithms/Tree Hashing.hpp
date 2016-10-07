/*
\subsection*{Description}
给定一棵树，对于每一个节点计算出以其为根的hash值。
同构的有根树的hash值保证相同。
这个hash值是一个long long，因为用了两个质数。
冲突率非常低。
时间复杂度是O(nlgn)的。
*/
#include<bits/stdc++.h>
using namespace std;
struct TreeHashing{
	int n,p,d2;
	vector<int>hu,hd,sz;
	vector<vector<int>>adj;
	vector<long long>pw,hash;
	TreeHashing(int _n):
		n(_n),pw(2*n),hu(n+1),hd(n+1),sz(n+1,1),
		d2(0),adj(n+1),hash(n+1),p(1e9+7){
	}
	void add(int u,int v){
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	void down(int u,int d1=0,int f=0){
		vector<pair<int,int>>t;
		for(int v:adj[u])
			if(v!=f){
				down(v,d1,u);
				if(!d2)
					sz[u]+=sz[v]*(1-d1);
				t.push_back(make_pair(sz[v]*2,hd[v]));
			}
		if(d1*f)
			t.push_back(make_pair((n-sz[u])*2,hu[u]));
		sort(t.begin(),t.end());
		int l=1,&s=d1?*((int*)&hash[u]+d2):(hd[u]=0);
		for(auto i:t){
			s=(s+pw[l]*i.second)%p;
			l+=i.first;
		}
		s=(s+pw[l])%p;
	}
	void up(int u,int f=0){
		int l=0,sl=0,sr=1;
		vector<pair<pair<int,int>,int>>t;
		if(f)
			t.push_back(make_pair(make_pair((n-sz[u])*2,hu[u]),0));
		for(int i=0;i<adj[u].size();++i)
			if(adj[u][i]!=f){
				int v=adj[u][i];
				t.push_back(make_pair(make_pair(sz[v]*2,hd[v]),v));
			}
		sort(t.begin(),t.end());
		for(auto i:t){
			sl=(sl+i.first.second*pw[l])%p;
			l+=i.first.first;
		}
		for(int i=int(t.size()-1);i>=0;--i){
			sl=(sl-t[i].first.second*pw[l-=t[i].first.first]%p+p)%p;
			if(i+1<t.size())
				sr=(sr*pw[t[i+1].first.first]+t[i+1].first.second)%p;
			if(t[i].second)
				hu[t[i].second]=(sl+sr*pw[l])*pw[1]%p;
		}
		for(int v:adj[u])
			if(v!=f)
				up(v,u);
	}
	void run(){
		pw[0]=1;
		for(int i=1;i<2*n;++i)
			pw[i]=pw[i-1]*2%p;
		down(1),up(1),down(1,1);
		d2=1,p=1e9+9;
		for(int i=1;i<2*n;++i)
			pw[i]=pw[i-1]*7%p;
		down(1),up(1),down(1,1);
	}
};