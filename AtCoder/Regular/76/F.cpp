#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
#include <utility>
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
const int N=200010;
priority_queue<int>q;
pair<int,int>ints[N];
int rest[N],rs=0;
int main(){
	int n=ni,l=1,r=ni;
	for(int i=1;i<=n;i++){
		ints[i].first=ni,ints[i].second=ni;
	}
	sort(ints+1,ints+n+1);
	for(int i=1;i<=n;i++){
		q.push(-ints[i].second);
		if(l<=r&&l<=ints[i].first){
			l++;
		}else{
			rest[++rs]=-q.top();
			q.pop();
		}
	}
	sort(rest+1,rest+rs+1);
	int cnt=0;
	for(int i=rs;i>=1;i--){
		if(l<=r&&rest[i]<=r){
			r--;
		}else{
			cnt++;
		}
	}
	printf("%d\n",cnt);
	return 0;
}
