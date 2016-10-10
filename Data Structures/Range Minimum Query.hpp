template<typename VALUE_TYPE,int MEMORY_SIZE>struct Memory{
		VALUE_TYPE memory_buffer[MEMORY_SIZE],*memory_pointer;
		Array<VALUE_TYPE*,MEMORY_SIZE>stack;
		inline void Construct(){
			memory_pointer=memory_buffer;
			stack.Construct();
		}
		inline void Destruct(){
			stack.Destruct();
		}
		inline VALUE_TYPE*New(){
			VALUE_TYPE*t;
			if(!stack.Empty()){
				t=stack.Back();
				stack.PopBack();
			}else
				t=memory_pointer++;
			return t;
		}
		inline void Delete(VALUE_TYPE*a){
			stack.PushBack(a);
		}
	};
	template<typename VALUE_TYPE,int VERTEX_SIZE,int EDGE_SIZE>struct AdjacencyList{
		struct node{
			node*next;
			VALUE_TYPE value;
		};
		Memory<node,EDGE_SIZE>memory;
		struct Iterator{
			node*pointer;
			inline Iterator(node*_pointer=0):
			pointer(_pointer){
			}
			inline Iterator&operator++(){
				pointer=pointer->next;
				return*this;
			}
			inline Iterator operator++(int){
				Iterator t=*this;
				pointer=pointer->next;
				return t;
			}
			inline VALUE_TYPE&operator*(){
				return pointer->value;
			}
			inline VALUE_TYPE*operator->(){
				return&pointer->value;
			}
			inline bool operator==(const Iterator&a){
				return pointer==a.pointer;
			}
			inline bool operator!=(const Iterator&a){
				return pointer!=a.pointer;
			}
		};
		node*begin[VERTEX_SIZE],*edge_pointer;
		inline void Construct(const int&vertex_count){
			std::fill(begin,begin+vertex_count,(node*)0);
			memory.Construct();
		}
		inline void Destruct(){
			memory.Destruct();
		}
		inline void AddEdge(const int&a,const VALUE_TYPE&b){
			node*t=memory.New();
			t->next=begin[a];
			t->value=b;
			begin[a]=t;
		}
		inline Iterator Begin(const int&a){
			return Iterator(begin[a]);
		}
		inline Iterator End(const int&a){
			return Iterator(0);
		}
	};
	template<int VERTEX_SIZE,int BLOCK_SIZE,int POW_BLOCK_SIZE,int BLOCK_COUNT,int LG_BLOCK_COUNT>struct LowestCommonAncestor{
		int vertex_size,root,block_size,block_count,dfs_begin[VERTEX_SIZE],lg[BLOCK_COUNT],block[POW_BLOCK_SIZE][BLOCK_SIZE][BLOCK_SIZE],block_index[BLOCK_COUNT];
		AdjacencyList<int,VERTEX_SIZE,VERTEX_SIZE*2>adjacency_list;
		std::pair<int,int>dfs_sequence[VERTEX_SIZE*2],sparse_table[LG_BLOCK_COUNT][BLOCK_COUNT];
		inline void Construct(const int&_vertex_size,const int&_root){
			vertex_size=_vertex_size;
			root=_root;
			adjacency_list.Construct(vertex_size);
		}
		inline void Destruct(){
			adjacency_list.Destruct();
		}
		inline void AddEdge(const int&a,const int&b){
			adjacency_list.AddEdge(a,b);
			adjacency_list.AddEdge(b,a);
		}
		inline void Build(){
			block_size=std::max(2,int(std::log(double(2*vertex_size-1))/(log(2.0)*2)));
			block_count=(2*vertex_size-1)%block_size?(2*vertex_size-1)/block_size+1:(2*vertex_size-1)/block_size;
			build_dfs_sequence();
			build_sparse_table();
			build_block();
		}
		inline void build_dfs_sequence(){
			static int prt[VERTEX_SIZE],dpt[VERTEX_SIZE];
			prt[root]=-1;
			dpt[root]=0;
			std::pair<int,int>*dfs=dfs_sequence;
			static Array<std::pair<int,typename AdjacencyList<int,VERTEX_SIZE,VERTEX_SIZE*2>::Iterator>,VERTEX_SIZE>stk;
			stk.Construct();
			stk.PushBack(std::make_pair(root,adjacency_list.Begin(root)));
			while(!stk.Empty()){
				int u=stk.Back().first;
				typename AdjacencyList<int,VERTEX_SIZE,VERTEX_SIZE*2>::Iterator i=stk.Back().second;
				stk.PopBack();
				if(i==adjacency_list.Begin(u))
					dfs_begin[u]=dfs-dfs_sequence;
				*dfs++=std::make_pair(dpt[u],u);
				if(i!=adjacency_list.End(u)&&*i==prt[u])
					++i;
				if(i!=adjacency_list.End(u)){
					int v=*i;
					stk.PushBack(std::make_pair(u,++i));
					prt[v]=u;
					dpt[v]=dpt[u]+1;
					stk.PushBack(std::make_pair(v,adjacency_list.Begin(v)));
				}
			}
			stk.Destruct();
		}
		inline void build_sparse_table(){
			for(int i=0;(1<<i)<=block_count;++i)
				for(int j=0;j+(1<<i)-1<block_count;++j)
					if(i==0)
						sparse_table[i][j]=*std::min_element(dfs_sequence+j*block_size,dfs_sequence+std::min((j+1)*block_size,2*vertex_size-1));
					else
						sparse_table[i][j]=std::min(sparse_table[i-1][j],sparse_table[i-1][j+(1<<(i-1))]);
			lg[1]=0;
			for(int i=2;i<=block_count;++i)
				lg[i]=lg[i-1]+((1<<(lg[i-1]+1))<=i?1:0);
		}
		inline std::pair<int,int>query_sparse_table(const int&a,const int&b){
			int t=lg[b - a + 1];
			return std::min(sparse_table[t][a],sparse_table[t][b-(1<<t)+1]);
		}
		inline void build_block(){
			for(int i=0;i<(1<<(block_size-1));++i){
				static std::pair<int,int>t[BLOCK_SIZE];
				for(int j=1;j<block_size;++j)
					if((i>>(block_size-j-1))&1)
						t[j]=std::make_pair(t[j-1].first+1,j);
					else
						t[j]=std::make_pair(t[j-1].first-1,j);
				for(int j=0;j<block_size;++j){
					std::pair<int,int>tmp=t[j];
					for(int k=j;k<block_size;++k){
						CoreLibrary::MakeMin(tmp,t[k]);
						block[i][j][k]=tmp.second;
					}
				}
			}
			for(int i=0;i<block_count;++i){
				int t=0;
				for(int j=i*block_size+1;j<(i+1)*block_size;++j)
					if(j>=2*vertex_size-1||dfs_sequence[j].first-dfs_sequence[j-1].first==1)
						t=(t<<1)+1;
					else
						t<<=1;
				block_index[i]=t;
			}
		}
		inline std::pair<int,int>query_block(const int&a,const int&b){
			int t=a/block_size;
			return dfs_sequence[block[block_index[t]][a-t*block_size][b-t*block_size]+t*block_size];
		}
		inline int Query(int a,int b){
			a=dfs_begin[a];
			b=dfs_begin[b];
			if(a>b)
				std::swap(a,b);
			int ia=a/block_size,ib=b/block_size;
			if(ia==ib)
				return query_block(a,b).second;
			if(ia+1==ib)
				return std::min(query_block(a,(ia+1)*block_size-1),query_block(ib*block_size,b)).second;
			return std::min(std::min(query_block(a,(ia+1)*block_size-1),query_block(ib*block_size,b)),query_sparse_table(ia+1,ib-1)).second;
		}
	};
	template<typename VALUE_TYPE,typename COMPARER_TYPE,int SEQUENCE_SIZE,int BLOCK_SIZE,int POW_BLOCK_SIZE,int BLOCK_COUNT,int LG_BLOCK_COUNT>struct RangeMinimumQuery{
		LowestCommonAncestor<SEQUENCE_SIZE,BLOCK_SIZE,POW_BLOCK_SIZE,BLOCK_COUNT,LG_BLOCK_COUNT>lowest_common_ancestor;
		VALUE_TYPE*sequence_begin,*sequence_end;
		inline void Construct(VALUE_TYPE*_sequence_begin,VALUE_TYPE*_sequence_end){
			sequence_begin=_sequence_begin;
			sequence_end=_sequence_end;
			static int prt[SEQUENCE_SIZE];
			Array<int,SEQUENCE_SIZE>stk;
			stk.Construct();
			for(int i=0;i<sequence_end-sequence_begin;++i){
				typename Array<int,SEQUENCE_SIZE>::Iterator j=stk.End()-1;
				while(j>=stk.Begin()&&COMPARER_TYPE()(*(sequence_begin+i),*(sequence_begin+*j)))
					--j;
				if(j<stk.Begin())
					prt[i]=-1;
				else
					prt[i]=*j;
				if(j+1!=stk.End())
					prt[*(j+1)]=i;
				while(j+1!=stk.End())
					stk.PopBack();
				stk.PushBack(i);
			}
			int root;
			for(int i=0;i<sequence_end-sequence_begin;++i)
				if(prt[i]==-1){
					root=i;
					break;
				}
				lowest_common_ancestor.Construct(sequence_end-sequence_begin,root);
				for(int i=0;i<sequence_end-sequence_begin;++i)
					if(prt[i]!=-1)
						lowest_common_ancestor.AddEdge(i,prt[i]);
				lowest_common_ancestor.Build();
				stk.Destruct();
		}
		inline void Destruct(){
			lowest_common_ancestor.Destruct();
		}
		inline int Query(const int&a,const int&b){
			return *(sequence_begin+lowest_common_ancestor.Query(a,b));
		}
	};
