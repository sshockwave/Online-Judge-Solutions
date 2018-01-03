#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
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
const int N=110;
int a[N],c[N];
int n;
void dfs(int x,int rest,int dt){
	if(x>n){
		if(dt==0)throw 1;
		return;
	}
	for(int &i=c[x]=-rest;i<=rest;i++){
		dfs(x+1,rest-abs(i),i*a[x]+dt);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("num5.in","r",stdin);
	freopen("num5.out","w",stdout);
#endif
	int dt=ni;
	n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	cout<<"read in complete"<<endl;
	try{
		dfs(1,7,-dt);
	}catch(int x){
		cout<<"caught you!"<<endl;
		int sum=0;
		for(int i=1;i<=n;i++){
			sum+=abs(c[i]);
		}
		printf("%d\n",sum);
		for(int i=1;i<=n;i++){
			if(c[i]>0){
				for(int j=1;j<=c[i];j++){
					printf("%d\n",i);
				}
			}else if(c[i]<0){
				for(int j=-1;j>=c[i];j--){
					printf("-%d\n",i);
				}
			}
		}
	}
	return 0;
}
