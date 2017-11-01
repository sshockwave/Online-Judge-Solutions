#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=110,A=1000000000;
int f[N];
set<int>s;
inline bool Main(){
	int a=ni;
	if(a==0){
		return true;
	}
	for(int i=1;f[i]<=a;i++){
		if(a%f[i]==0){
			if(s.find(a/f[i])!=s.end()){
				return true;
			}
		}
	}
	return false;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("fib.in","r",stdin);
	freopen("fib.out","w",stdout);
#endif
	memset(f,0,sizeof(f));
	f[1]=1;
	s.insert(1);
	for(int i=2;(f[i]=f[i-1]+f[i-2])<=A;s.insert(f[i]),i++);
	for(int i=1;f[i];i++){
		cout<<f[i]<<endl;
	}
	for(int tot=ni;tot--;puts(Main()?"Yes":"No"));
	return 0;
}
