#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
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
template<class T>inline T sqr(const T &x){return x*x;}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=100010;
int n,m,k;
vector<int>vec[N];
char s[N];
inline bool check(vector<int>&vec){
	if(vec.size()==1)return false;
	for(int i=0;i<(int)vec.size()-1;i++){
		if(s[vec[i]]=='B'&&s[vec[i+1]]=='B')return true;
	}
	if(s[vec[0]]=='B'&&s[vec.back()]=='B')return true;
	return false;
}
bool dfs(int x,int ns){
	if(x==0){
		if(ns!=m)return false;
		for(int i=1;i<=m;i++){
			if(vec[i].size()%k!=0)return false;
			if(!check(vec[i]))return false;
		}
		puts("Yes");
		for(int i=1;i<=m;i++){
			printf("%d",(int)vec[i].size());
			for(;!vec[i].empty();vec[i].pop_back()){
				printf(" %d",vec[i].back());
			}
			putchar('\n');
		}
		return true;
	}
	for(int i=1;i<=min(ns+1,m);i++){
		vec[i].push_back(x);
		if(dfs(x-1,max(i,ns)))return true;
		vec[i].pop_back();
	}
	return false;
}
inline void Main(){
	n=ni,m=ni,k=ni;
	scanf("%s",s+1);
	if(!dfs(n,0)){
		puts("No");
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	for(int tot=ni;tot--;Main());
	return 0;
}
