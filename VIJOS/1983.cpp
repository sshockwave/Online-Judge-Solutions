//#include <iostream>
#include <cstdio>
#include <cstring>
#define N 300100
using namespace std;
inline int apmax(int &a,int b){
	if(b>a){
		a=b;
//		cout<<"\t\tMax applied."<<endl;
	}
}
inline void swap(int &a,int &b){
	int t=a;
	a=b;
	b=t;
}
int e[N][3],n,m,topl=0;
struct route{
	int u,v,l;
}plan[N];
bool plancmp(const route &a,const route &b){
	return a.l<b.l;
}
namespace tree{
	int to[N<<1],bro[N<<1],eid[N<<1],head[N],etop=0,
		fa[N],son[N],size[N],len[N],dep[N],
		pos[N],rpos[N],top[N],ptop=1,path[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(son,0,sizeof(son));
		len[0]=fa[1]=len[1]=size[0]=0;
		top[1]=dep[1]=1;
	}
	inline void link(int u,int v,int id){
		to[etop]=v;
		bro[etop]=head[u];
		eid[etop]=id;
		head[u]=etop++;
	}
	void dfs1(int x){
		size[x]=1;
		for(int i=head[x];~i;i=bro[i]){
			if(to[i]!=fa[x]){
				fa[to[i]]=x;
				len[to[i]]=len[x]+e[eid[i]][2];//3=>2
				dep[to[i]]=dep[x]+1;
				dfs1(to[i]);
				size[x]+=size[to[i]];
				if(size[to[i]]>size[son[x]]){
					son[x]=to[i];
				}
			}
		}
	}
	void dfs2(int x){
		pos[x]=ptop++;
		rpos[pos[x]]=x;
//		cout<<"Node:"<<x<<" pos="<<pos[x]<<endl;
		if(son[x]){
			top[son[x]]=top[x];
			dfs2(son[x]);
			for(int i=head[x];~i;i=bro[i]){
				if(to[i]!=fa[x]&&to[i]!=son[x]){
					top[to[i]]=to[i];
					dfs2(to[i]);//x=>to[i]
				}
			}
		}
	}
	int stack[N];
	bool vis[N];
	inline void stackdfs(){
		memset(vis,0,sizeof(vis));
		int x,stop=0;
		bool flag;
		stack[stop++]=1;
		while(stop){
			x=stack[stop-1];
			if(vis[x]){
				stop--;
				for(int i=head[x];~i;i=bro[i]){
					if(to[i]!=fa[x]){
						size[x]+=size[to[i]];
						if(size[to[i]]>size[son[x]]){
							son[x]=to[i];
						}
					}
				}
			}else{
				vis[x]=true;
				size[x]=1;
				for(int i=head[x];~i;i=bro[i]){
					if(to[i]!=fa[x]){
						fa[to[i]]=x;
						len[to[i]]=len[x]+e[eid[i]][2];//3=>2
						dep[to[i]]=dep[x]+1;
						stack[stop++]=to[i];
					}
				}
			}
		}
		stack[stop++]=1;
		memset(vis,0,sizeof(vis));
		while(stop){
			x=stack[stop-1];
			if(vis[x]){
				stop--;
				if(son[x]){
					for(int i=head[x];~i;i=bro[i]){
						if(to[i]!=fa[x]&&to[i]!=son[x]){
							top[to[i]]=to[i];
							stack[stop++]=to[i];
						}
					}
				}
			}else{
				vis[x]=true;
				pos[x]=ptop++;
				rpos[pos[x]]=x;
		//		cout<<"Node:"<<x<<" pos="<<pos[x]<<endl;
				if(son[x]){
					top[son[x]]=top[x];
					stack[stop++]=son[x];
				}
			}
		}
	}
	inline int query(int u,int v){
		int sum=0;
		while(top[u]!=top[v]){
			if(dep[top[u]]<dep[top[v]]){
				swap(u,v);
			}
			sum+=len[u]-len[fa[top[u]]];
			u=fa[top[u]];
		}
		if(u==v){
			return sum;
		}
		if(dep[u]<dep[v]){
			swap(u,v);
		}
		return sum+len[u]-len[v];
	}
	inline void mark(int u,int v){
		while(top[u]!=top[v]){
			if(dep[top[u]]<dep[top[v]]){
				swap(u,v);
			}
//			cout<<"\t\t["<<pos[top[u]]<<","<<pos[u]+1<<")++"<<endl;
			path[pos[top[u]]]++,path[pos[u]+1]--;
			u=fa[top[u]];
		}
		if(u!=v){
			if(dep[u]<dep[v]){
				swap(u,v);
			}
//			cout<<"\t\t["<<pos[v]+1<<","<<pos[u]+1<<")++"<<endl;
			path[pos[v]+1]++,path[pos[u]+1]--;//pos[v]=>pos[v]+1
		}
	}
	inline bool judge(int planl){
		memset(path,0,sizeof(path));
		int /*l=0,r=m-1,mid,*/cnt=0,maxl=0;
		/*while(r>l){//select all plan that l>=planl
			mid=l+r>>1;
			if(plan[mid].l>planl){//if plan[mid].l == planl, it should not be considered because it don't have to be shorter to fit in planl.
				r=mid;
			}else{
				l=mid+1;
			}
		}*/
//		cout<<"\tConsidering "<<m-l<<" edges."<<endl;
		for(int i=0;i<m;i++){
			if(plan[i].l>planl){
//				cout<<"\tmarking ("<<plan[i].u<<","<<plan[i].v<<") len="<<plan[i].l<<endl;
				mark(plan[i].u,plan[i].v);
				cnt--;
			}
		}
		for(int i=1;i<=n;i++){
			cnt+=path[i];//pos[i]=>i
			if(cnt==0){
//				cout<<"\tEdge to father of "<<rpos[i]<<" is valid. Applying max."<<endl;
				apmax(maxl,len[rpos[i]]-len[fa[rpos[i]]]);
			}
		}
		return topl-maxl<=planl;
	}
}
int main(){
//	ios::sync_with_stdio(false);
//	cin.tie(0);
	tree::init();
//	cin>>n>>m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
//		cin>>e[i][0]>>e[i][1]>>e[i][2];
		scanf("%d%d%d",e[i],e[i]+1,e[i]+2);
		tree::link(e[i][0],e[i][1],i);
		tree::link(e[i][1],e[i][0],i);
	}
//	tree::dfs1(1),tree::dfs2(1);
	tree::stackdfs();
	int l=0,r=0,mid;
	for(int i=0;i<m;i++){
//		cin>>plan[i].u>>plan[i].v;
		scanf("%d%d",&plan[i].u,&plan[i].v);
		plan[i].l=tree::query(plan[i].u,plan[i].v);
		if(plan[i].l>r){
			r=plan[i].l;
		}
		apmax(r,plan[i].l);
	}
	topl=r;
	while(r>l){
//		cout<<"BIN("<<l<<","<<r<<") test"<<(l+r>>1)<<endl;
		if(tree::judge(mid=l+r>>1)){
			r=mid;
		}else{
			l=mid+1;
		}
	}
//	cout<<l<<endl;
	printf("%d",l);
}
