#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline int apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
const int N=110,E=110;
int pval[N];
bool vis[N],choose[N];
struct Tree{
	int to[E],bro[E],head[N],etop;
	inline void reset(){
		etop=0;
		memset(head,-1,sizeof(head));
	}
	inline void add_edge(int u,int v,bool d=true){
		to[etop]=v;
		bro[etop]=head[u];
		head[u]=etop++;
		if(d){
			add_edge(v,u,false);
		}
	}
	int ask_con(int x){
		int size=1;
		vis[x]=true;
		for(int i=head[x],y;~i;i=bro[i]){
			y=to[i];
			if(!vis[y]&&choose[y]){
				size+=ask_con(y);
			}
		}
		vis[x]=false;
		return size;
	}
}t1,t2;
inline int task1(int n){
	int ans=0,sum,root,cnt;
	for(int state=(1<<n);state>0;state--){
		sum=cnt=root=0;
		for(int i=1;i<=n;i++){
			if(choose[i]=((state>>(i-1))&1)){
				cnt++;
				sum+=pval[i];
				root=i;
			}
		}
		if(sum>ans&&t1.ask_con(root)==cnt&&t2.ask_con(root)==cnt){
			ans=sum;
		}
	}
	return ans;
}
int f[N];
void dfs(int x){
	f[x]=pval[x];
	vis[x]=true;
	for(int i=t2.head[x],y;~i;i=t2.bro[i]){
		y=t2.to[i];
		if(!vis[y]){
			dfs(y);
			if(f[y]>0){
				f[x]+=f[y];
			}
		}
	}
	vis[x]=false;
}
inline int task2(int n){
	dfs(1);
	int ans=0;
	for(int i=1;i<=n;i++){
		apmax(ans,f[i]);
	}
	return ans;
}
int main(){
	memset(vis,0,sizeof(vis));
	for(int tot=ni();tot--;){
		int n=ni();
		for(int i=1;i<=n;i++){
			scanf("%d",pval+i);
		}
		t1.reset(),t2.reset();
		for(int i=1;i<n;i++){
			t1.add_edge(ni(),ni());
		}
		for(int i=1;i<n;i++){
			t2.add_edge(ni(),ni());
		}
		if(n<=15){
			printf("%d\n",task1(n));
		}else{
			printf("%d\n",task2(n));
		}
	}
}
