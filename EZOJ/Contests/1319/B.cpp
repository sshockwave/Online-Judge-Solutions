#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=100010;
int l[N],r[N];
#define lson(x) son[x][0]
#define rson(x) son[x][1]
int root[N];
int son[N][2],dep[N]={0};
inline void init(int n){
	memset(root+1,0,n<<2);
	memset(son+1,0,n<<3);
	memset(dep+1,0,n<<2);
}
int merge(int x,int y){
	if(x==0||y==0){
		return x|y;
	}
	if(r[x]>r[y]){
		swap(x,y);
	}
	rson(x)=merge(rson(x),y);
	if(dep[rson(x)]>dep[lson(x)]){
		swap(lson(x),rson(x));
	}
	dep[x]=dep[rson(x)]+1;
	return x;
}
int ln[N],pos[N];
inline int det(int n){
	int sig=1;
	for(int i=1;i<=n;i++){
		ln[i]=pos[i]=i;
	}
	for(int i=1;i<=n;i++){
		int x=root[i];
		if(x==0){
			return 0;
		}
		assert(r[x]>=i);
		assert(pos[ln[i]]==i);
		if(ln[i]!=x){
			sig=-sig;
			pos[ln[i]]=pos[x];
			swap(ln[i],ln[pos[x]]);
			pos[x]=i;
		}
		root[i]=merge(lson(x),rson(x));
		if(r[root[i]]==r[x]){
			return 0;
		}
		root[r[x]+1]=merge(root[r[x]+1],root[i]);
	}
	return sig;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("fiend.in","r",stdin);
	freopen("fiend.out","w",stdout);
#endif
	for(int tot=ni,n;tot--;){
		init(n=ni);
		for(int i=1;i<=n;i++){
			l[i]=ni,r[i]=ni;
			root[l[i]]=merge(root[l[i]],i);
		}
		int ans=det(n);
		if(ans>0){
			puts("Y");
		}else if(ans<0){
			puts("F");
		}else{
			puts("D");
		}
	}
}
