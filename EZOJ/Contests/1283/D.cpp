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
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){
		a=b;
	}
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
const int N=300010;
int f[N],w[N],_w[N],q[N],nxt[N];
struct Value{
	int i,j,v;
	Value(int _i,int _j):i(_i),j(_j),v(f[j]+w[i]){}
	inline friend bool operator < (const Value &a,const Value &b){
		return a.v>b.v;
	}
};
priority_queue<Value>h;
int main(){
	int n=ni,lim=ni,qhead=0,qtail=0;
	f[0]=w[0]=_w[0]=0;
	for(int i=1,j=0;i<=n;i++){
		_w[i]=_w[i-1]+(w[i]=ni);
		for(;_w[i]-_w[j]>lim;j++);
		for(;qhead<qtail&&q[qhead]<j;nxt[q[qhead++]]=0);
		for(;qhead<qtail&&w[q[qtail-1]]<=w[i];nxt[q[--qtail-1]]=0);
		if(qhead<qtail){
			nxt[q[qtail-1]]=i;
			h.push(Value(i,q[qtail-1]));
		}
		q[qtail++]=i;
		f[i]=f[j]+w[q[qhead]];
		for(;!h.empty();h.pop()){
			if(nxt[h.top().j]==h.top().i){
				apmin(f[i],h.top().v);
				break;
			}
		}
	}
	printf("%d\n",f[n]);
}
