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
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
const int N=100010,D=10;
struct State{
	int cnt[D];
	State(){
		memset(cnt,127,sizeof(cnt));
	}
	inline friend State operator - (const State &a,const State &b){
		State c;
		for(int i=0;i<D;i++){
			c.cnt[i]=a.cnt[i]-b.cnt[i];
		}
		return c;
	}
	inline friend bool operator < (const State &a,const State &b){
		for(int i=0;i<D;i++){
			if(a.cnt[i]!=b.cnt[i]){
				return a.cnt[i]<b.cnt[i];
			}
		}
		return false;
	}
	inline void print(){
		for(int i=0;i<D;i++){
			printf("%d ",cnt[i]);
		}
		putchar('\n');
	}
}f[N],g[N];
char s[N];
int pre[N],nxt[N];
inline void del(int x){
	pre[nxt[x]]=pre[x];
	nxt[pre[x]]=nxt[x];
}
int main(){
	int n=ni,tot=ni;
	scanf("%s",s+1);
	for(int i=1;i<=n;i++){
		pre[i]=i-1,nxt[i]=i+1;
	}
	nxt[0]=1,pre[n+1]=n;
	int *pt=nxt;
	State cur;
	memset(&cur,0,sizeof(cur));
	for(int i=0;i<=n;apmin((pt==nxt?f:g)[i],cur),i=pt[i],apmin(pt==nxt?f[i-1]:g[i+1],cur)){
		if(i==0){
			pt=nxt;
			continue;
		}
		if(isdigit(s[i])){
			cur.cnt[s[i]-'0']++;
			if(s[i]=='0'){
				del(i);
			}else{
				s[i]--;
			}
		}else{
			pt=s[i]=='<'?pre:nxt;
			if(s[pt[i]]=='<'||s[pt[i]]=='>'){
				del(i);
			}
		}
	}
	for(int i=n;i>1;i--){
		apmin(f[i-1],f[i]);
	}
	for(int i=1;i<n;i++){
		apmin(g[i+1],g[i]);
	}
	while(tot--){
		int l=ni,r=ni;
		(min(f[r],g[l])-f[l-1]).print();
	}
}