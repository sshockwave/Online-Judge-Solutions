#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
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
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
const int N=100010;
struct interval{
	int l,r;
}ints[N];
bool operator < (interval a,interval b){
	if(a.r==b.r){
		return a.l<b.l;
	}
	return a.r<b.r;
}
int to[N],bro[N],val[N],head[N],etop=0,f[N];
inline void add_edge(int u,int v){
	if(u<v){
		return;
	}
	if(~head[u]&&to[head[u]]==v){
		val[head[u]]++;
		return;
	}
	to[etop]=v;
	bro[etop]=head[u];
	val[etop]=1;
	head[u]=etop++;
}
int main(){
	int n=ni(),ans=0;
	for(int i=0;i<n;i++){
		ints[i].l=ni()+1;
		ints[i].r=n-ni();
	}
	sort(ints,ints+n);
	memset(head,-1,sizeof(head));
	for(int i=0;i<n;i++){
		add_edge(ints[i].r,ints[i].l);
	}
	memset(f,0,sizeof(f));
	for(int x=1;x<=n;x++){
		f[x]=f[x-1];
		for(int i=head[x];~i;i=bro[i]){
			apmax(f[x],f[to[i]-1]+min(val[i],x-to[i]+1));
		}
	}
	printf("%d",n-f[n]);
}
