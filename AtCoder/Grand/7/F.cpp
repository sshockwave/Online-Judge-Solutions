#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <deque>
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
const int N=1000010;
char a[N],b[N];
deque<int>q;
inline int Main(){
	int n=ni;
	scanf("%s%s",a+1,b+1);
	q.push_back(n+1);
	int delta=0;
	int ans=0;
	for(int i=n,j=n+1;i>=1;i--){
		int last=j;
		for(;j>=1&&(i<j||b[i]!=a[j]);j--);
		if(j<1)return -1;
		if(last==j){
			for(;!q.empty()&&q.back()+delta>=i;q.pop_back());
			q.push_back(i-delta);
		}else{
			delta--;
			if(i!=j){
				apmax(ans,(int)q.size());
				q.push_front(j-delta);
			}
		}
	}
	return ans;
}
int main(){
	printf("%d\n",Main());
	return 0;
}
