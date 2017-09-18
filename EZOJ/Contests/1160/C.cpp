#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
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
const int N=1000010;
struct pii{
	int col,cnt;
	inline friend bool operator < (const pii &a,const pii &b){
		return a.cnt<b.cnt;
	}
};
priority_queue<pii>q;
int a[N];
inline void psh(pii x){
	if(x.cnt){
		q.push(x);
	}
}
int c[N];
inline int work(){
	int n=ni,m=0;
	a[1]=ni;
	{
		int ed=ni;
		for(int i=1;i<=n;i++){
			m+=c[i]=ni;
		}
		if(m==1){
			return a[1]==ed;
		}
		a[m]=ed;
		c[a[1]]--,c[a[m]]--;
		if(c[a[1]]<0||c[a[m]]<0){
			return 0;
		}
	}
	for(int i=1;i<=n;i++){
		psh((pii){i,c[i]});
	}
	for(int i=2;i<m;i++){
		pii x=q.top();
		q.pop();
		if(x.col==a[i-1]){
			if(q.empty()){
				return 0;
			}
			pii y=q.top();
			q.pop();
			a[i]=y.col,y.cnt--;
			psh(x),psh(y);
		}else{
			a[i]=x.col,x.cnt--;
			psh(x);
		}
	}
	for(int i=m-1;i>=1;i-=2){
		if(a[i]!=a[i+1]){
			return m;
		}
		if(i-1<=1){
			return 0;
		}
		swap(a[i],a[i-1]);
	}
	return 0;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("klo.in","r",stdin);
	freopen("klo.out","w",stdout);
#endif
	int ans=work();
	if(ans){
		for(int i=1;i<=ans;i++){
			printf("%d ",a[i]);
		}
		putchar('\n');
	}else{
		puts("0");
	}
	return 0;
}
