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
	if(b<a){
		a=b;
	}
}
const int L=15,N=110,INF=0x7f7f7f7f;
int tim=0;
struct Node{
	int dis,tag;
	bool girl;
	Node(){
		memset(this,-1,sizeof(Node));
	}
	int fa,mo,c1[2],c2[2];
}node[N*1000];//tocheck
inline int nn(){
	static int n=0;
	return ++n;
}
typedef queue<int> qi;
typedef void(*fn)(int);
qi *q1=new qi,*q2=new qi;
inline void push(int x){
	if(node[x].tag<tim){
		node[x].tag=tim;
		q2->push(x);
	}
}
namespace Transfers{
	inline int getfa(int x){
		if(node[x].fa==-1){
			int fa=node[x].fa=nn();
			node[fa].dis=node[x].dis+1;
			node[fa].girl=false;
			node[fa].c1[node[x].girl]=x;
		}
		return node[x].fa;
	}
	inline int getmo(int x){
		if(node[x].mo==-1){
			
		}
		return node[x].mo;
	}
	void tofather(int x){
		push(getfa(x));
	}
	void toMother(int x){
		push(getmo(x));
	}
	inline fn parse();
}
char s[L];
inline fn Transfers::parse(){
	switch(s[0]){
	}
	return NULL;
}
int main(){
	freopen("clan.in","r",stdin);
	freopen("clan.out","w",stdout);
	scanf("Q is U's");
	node[0].dis=0;
	node[0].girl=false;
	push(0);
	while(tim++,swap(q1,q2),scanf("%s",s)!=EOF){
		cout<<s<<endl;
		fn trans=Transfers::parse();
		while(!q1->empty()){
			trans(q1->front());
			q1->pop();
		}
	}
	return 0;
}