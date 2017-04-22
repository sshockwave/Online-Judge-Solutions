#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
#include <ctime>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
const int N=1000010,INF=0x7f7f7f7f;//tocheck
int sigma,n,m,s[N],t[N],fail[N];
bool valid[N];
struct SAM{
	int lnk[N],val[N],pos[N],tail,pool;
	map<int,int>go[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(pos,-1,sizeof(pos));
		for(int i=1;i<pool;i++){
			go[i].erase(go[i].begin(),go[i].end());
		}
		val[1]=lnk[1]=0,etop=0,tail=1,pool=2;
	}
	inline void extend(int c,int i){
		int p=tail;
		tail=pool++;
		pos[tail]=i;
		val[tail]=val[p]+1;
		for(;p&&go[p].find(c)==go[p].end();p=lnk[p]){
			go[p][c]=tail;
		}
		if(p==0){
			lnk[tail]=1;
			return;
		}
		int q=go[p][c];
		if(val[q]==val[p]+1){
			lnk[tail]=q;
			return;
		}
		int nq=pool++;
		go[nq]=go[q];
		lnk[nq]=lnk[q];
		val[nq]=val[p]+1;
		lnk[tail]=lnk[q]=nq;
		for(;p&&go[p][c]==q;p=lnk[p]){
			go[p][c]=nq;
		}
	}
	int to[N],bro[N],head[N],etop;
	inline void add_edge(int u,int v){
		to[etop]=v;
		bro[etop]=head[u];
		head[u]=etop++;
	}
	void mark(int x){
		if(~pos[x]){
			valid[pos[x]-m+1]=true;
		}
		for(int i=head[x];~i;i=bro[i]){
			mark(to[i]);
		}
	}
	void dfs(int p,int j){
		if(j>m){
			mark(p);
			return;
		}
		for(map<int,int>::iterator it=go[p].begin();it!=go[p].end();it++){
			int c=it->first;
			if((c+j>m?INF:c)==t[j]){
				dfs(it->second,j+1);
			}
		}
	}
	inline void work(){
		for(int i=2;i<pool;i++){
			add_edge(lnk[i],i);
		}
		dfs(1,1);
	}
}sam;
inline void getnxt(int *s,int n){
	static int *nxt=new int[N];//nxt[color]
	memset(nxt+1,127,sigma<<2);
	int cur;
	for(int i=n;i>=1;i--){
		s[i]=nxt[cur=s[i]];
		if(s[i]!=INF){
			s[i]-=i;
		}
		nxt[cur]=i;
	}
}
int main(){
	int tot=ni;
	sigma=ni;
	while(tot--){
		sam.init();
		n=ni,m=ni;
		for(int i=1;i<=n;i++){
			s[i]=ni;
		}
		for(int i=1;i<=m;i++){
			t[i]=ni;
		}
		memset(valid,0,sizeof(valid));
		getnxt(s,n);
		getnxt(t,m);
		for(int i=1;i<=n;i++){
			sam.extend(s[i],i);
		}
		sam.work();
		for(int i=1,_=n-m+1;i<=_;i++){
			if(valid[i]){
				printf("%d ",i);
			}
		}
		putchar('\n');
	}
}
