#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
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
	if(a>b){a=b;}
}
const int N=2010,MOD=(1u<<31)-1;
inline int add(const int &a,const int &b){
	return (a+b)&MOD;
}
inline int mul(const int &a,const int &b){
	return (lint)a*b&MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
struct State{
	int a,b,c,p;//sorted
	State(int _a,int _b,int _c,int _p):a(_a),b(_b),c(_c),p(_p){}
	inline friend bool operator < (const State &a,const State &b){
		if(a.a==b.a){
			if(a.b==b.b){
				if(a.c==b.c){
					return a.p<b.p;
				}
				return a.c<b.c;
			}
			return a.b<b.b;
		}
		return a.a<b.a;
	}
};
int nxt[N];//todo
int dfs(int a,int b,int c,int p){
	if(a>b){
		swap(a,b);
	}
	if(b>c){
		swap(b,c);
	}
	if(a>b){
		swap(a,b);
	}
	if(c<p){
		return 1;
	}
	static map<State,int>cache;
	map<State,int>::iterator it=cache.find(State(a,b,c,p));
	if(it!=cache.end()){
		return it->second;
	}
	int ans=0;
	for(int i=0,_a=a;_a;i++,_a/=p){
		for(int j=0,_b=b;_b;j++,_b/=p){
			for(int k=0,_c=c;_c;k++,_c/=p){
				apadd(ans,mul(dfs(_a,_b,_c,nxt[p]),a+b+c+1));
			}
		}
	}
	return cache[State(a,b,c,p)]=ans;
}
inline bool isprime(int n){
	for(int i=2;i*i<=n;i++){
		if(n%i==0){
			return false;
		}
	}
	return true;
}
int main(){
	int last=N;
	for(int i=N-1;i>1;i--){
		if(isprime(i)){
			nxt[i]=last;
			last=i;
		}
	}
	int a=ni,b=ni,c=ni;
	printf("%d\n",dfs(a,b,c,2));
}