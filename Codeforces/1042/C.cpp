#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(a[0]));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(a[0]));}
const int N=200010;
int rest;
inline void deal(vector<int>&a){
	for(;a.size()>1;){
		int b=a.back();
		a.pop_back();
		rest--,printf("1 %d %d\n",b,a.back());
	}
}
int a[N];
vector<int>pos,neg,trash;
int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	const int n=ni;
	rest=n;
	for(int i=1;i<=n;i++){
		a[i]=ni;
		if(a[i]>0){
			pos.push_back(i);
		}else if(a[i]<0){
			neg.push_back(i);
		}else{
			trash.push_back(i);
		}
	}
	if(neg.size()&1){
		int p=neg[0];
		for(int i=0;i<neg.size();i++){
			if(a[neg[i]]>a[p]){
				p=neg[i];
			}
		}
		trash.push_back(p);
		for(vector<int>::iterator it=neg.begin(),ti=neg.end();it!=ti;++it){
			if(p==*it){
				neg.erase(it);
				break;
			}
		}
	}
	for(int i=0;i<neg.size();i++){
		pos.push_back(neg[i]);
	}
	neg.clear();
	deal(trash);
	if(pos.size()&&trash.size()){
		assert(trash.size()==1);
		rest--,printf("2 %d\n",trash[0]);
	}
	deal(pos);
	assert(rest==1);
	return 0;
}
