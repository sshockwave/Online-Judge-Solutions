#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
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
	if(a<b){
		a=b;
	}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){
		a=b;
	}
}
const int N=200010;
int n;
struct Edge{
	int a,b;
	lint c;
	inline friend bool operator < (const Edge &a,const Edge &b){
		return a.c>b.c;
	}
};
priority_queue<Edge>q;
int fa[N];
int root(int x){
	if(fa[x]==-1){
		return x;
	}
	return fa[x]=root(fa[x]);
}
inline int add(const int &a,const int &b){
	return (a+b)%n;
}
inline int sub(const int &a,const int &b){
	return add(a,n-b);
}
int main(){
	memset(fa,-1,sizeof(fa));
	n=ni;
	for(int tot=ni;tot--;){
		q.push((Edge){ni,ni,nl});
	}
	lint ans=0;
	for(int i=1;i<n;){
		int a=q.top().a,b=q.top().b;
		lint c=q.top().c;
		q.pop();
		if(root(a)!=root(b)){
			i++;
			ans+=c;
			fa[root(a)]=root(b);
		}
		q.push((Edge){b,add(a,1),c+1});
	}
	printf("%lld\n",ans);
}