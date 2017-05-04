#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
using namespace std;
typedef long long lint;
typedef unsigned long long ull;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
const int N=100010,Q=1000010,P=1000005;
const int head=P-2,tail=P-1;
int pre[P],nxt[P],quelen;
bool vis[P];
lint sum;
inline void push_back(int x){
	nxt[x]=tail;
	pre[x]=pre[tail];
	pre[tail]=x;
	nxt[pre[x]]=x;
	vis[x]=true;
	sum+=x;
	quelen++;
}
inline void del(int x){
	nxt[pre[x]]=nxt[x];
	pre[nxt[x]]=pre[x];
	vis[x]=false;
	sum-=x;
	quelen--;
}
inline ull work(){
	memset(vis,0,sizeof(vis));
	nxt[head]=tail,pre[tail]=head;
	ull ans=0;
	int n=ni,tot=ni,x=ni,a=ni,b=ni,p=ni;
	sum=quelen=0;
	for(int i=1;i<=tot;i++,x=((lint)a*x+b)%p){
		if(vis[x]){
			del(x);
		}else if(quelen==n){
			del(nxt[head]);
		}
		push_back(x);
		ans+=sum*i;
	}
	return ans;
}
int main(){
	for(int tot=ni;tot--;){
		cout<<work()<<endl;
	}
}
