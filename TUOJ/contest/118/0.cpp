#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=100010,INF=0x7f7f7f7f;
int a[N],ans=INF;
struct Val{
	int v,x;
	inline friend bool operator < (const Val &a,const Val &b){
		return a.v<b.v;
	}
};
inline int dis(int i,int j){
	return a[max(i,j)]-a[min(i,j)];
}
bool used[N];
inline void work_left(const int n,const int s,int t){
	if(t<0)return;
	lint cur=dis(s,1)+dis(1,n);
	if(s>1){
		if(t<1)return;
		t-=s-1;
	}
	if(t<=0)return apmin(ans,cur);
	priority_queue<Val>q;
	for(int i=n-1;i>s;i--){
		Val tmp=(Val){2*dis(i,i+1),i};
		cur+=tmp.v,used[tmp.x]=true;
		q.push(tmp);
	}
	if(t>(int)q.size())return;
	for(;(int)q.size()>t;q.pop()){
		cur-=q.top().v,used[q.top().x]=false;
	}
	apmin(ans,cur);
	for(int i=n-1;i>s;i--){
		if(used[i]){
			cur-=dis(i,i+1),used[i]=false;
		}else for(;;){
			if(q.empty())return;
			Val tmp=q.top();
			q.pop();
			if(!used[tmp.x])continue;
			cur-=tmp.v,used[tmp.x]=false;
			cur+=dis(i,i+1);
			break;
		}
		assert((int)q.size()+(n-i)>=t);
		apmin(ans,cur);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	const int n=ni,t=ni,s=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	work_left(n,s,t);
	for(int i=1,v=a[n];i<=n;i++){
		a[i]=v-a[i];
	}
	reverse(a+1,a+n+1);
	work_left(n,n+1-s,n-1-t);
	printf("%d\n",ans<INF?ans:-1);
	return 0;
}
