#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=100010,INF=0x7f7f7f7f;
typedef vector<int>vi;
int lhs[N];
vi rhs[N];
int solve(int l,int r){
	if(l==r){
		if(!rhs[l].empty())throw "Too many edges.";
		return 0;
	}
	int m=-1;
	for(vi::reverse_iterator it=rhs[l].rbegin();it!=rhs[l].rend();it++){
		if(lhs[*it]==l){
			m=*it;
			break;
		}
	}
	if(m==-1)throw "Missing edges.";
	if(m-l>r-m+1)throw "Left > Right.";
	for(int v=r;v>=m;v--){
		int u=(v-m)%(m-l)+l;
		if(rhs[u].empty()||*--rhs[u].end()!=v)throw "Edges does not match partition.";
		rhs[u].pop_back();
	}
	return max(solve(l,m-1),solve(m,r))+1;
}
inline int Main(){
	int n=ni;
	for(int i=0;i<n;i++){
		lhs[i]=-1,rhs[i].clear();
	}
	for(int tot=ni;tot--;){
		int u=ni,v=ni;
		if(u>v){
			swap(u,v);
		}
		rhs[u].push_back(v);
		apmax(lhs[v],u);
	}
	for(int i=0;i<n;i++){
		sort(rhs[i].begin(),rhs[i].end());
	}
	try{
		return solve(0,n-1);
	}catch(const char str[]){
		return -1;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("gymnastics.in","r",stdin);
	freopen("gymnastics.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		printf("%d\n",Main());
	}
	return 0;
}
