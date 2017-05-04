#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;bool flag=false;
	while(!isdigit(c=getchar())&&c!='-');
	if(c=='-'){
		flag=true;
		c=getchar();
	}
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
inline void apmax(int &a,const int &b){
	if(a<b){
		a=b;
	}
}
inline void apmin(int &a,const int &b){
	if(a>b){
		a=b;
	}
}
const int N=10,INF=0x7f7f7f7f;
struct Tree{
	static const int E=N*2;
	int to[E],bro[E],head[N],etop;
	Tree(){
		memset(head,-1,sizeof(head));
		etop=0;
	}
	inline void add_edge(int u,int v){
		to[etop]=v;
		bro[etop]=head[u];
		head[u]=etop++;
	}
	int color[N];
	inline void reset(int a,int b){
		memset(color,0,sizeof(color));
	}
	int update(int &ans,int v,int c){
		if(c==1){
			apmax(ans,v);
		}else{
			apmin(ans,v);
		}
	}
	int dfs(int a,int b,int k,int c,int diff){
		if(k==0){
			return diff;
		}
		color[a]=c,color[b]=-c;
		int ans=-c*INF;
		for(int i=head[a],v;~i;i=bro[i]){
			v=to[i];
			if(color[v]==c){
				update(ans,dfs(b,v,k-1,-c,diff),c);
			}else if(color[v]==-c){
				update(ans,dfs(b,v,k-1,-c,diff+(c*2)),c);
			}else{
				update(ans,dfs(b,v,k-1,-c,diff+c),c);
			}
		}
		return ans;
	}
}T;
int main(){
	int n=ni,tot=ni;
	for(int i=1;i<n;i++){
		int u=ni,v=ni;
		T.add_edge(u,v);
		T.add_edge(v,u);
	}
	while(tot--){
		int a=ni,b=ni,k=ni;
		T.reset(a,b);
		printf("%d\n",T.dfs(a,b,k,1,0));
	}
}
