#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <fstream>
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
char s[N][N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("num1.in","r",stdin);
	freopen("num1.out","w",stdout);
#endif
	scanf("%s",s[0]);
	int n=ni;
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]);
	}
	fstream fin("num1.txt");
	int x;
	int cnt=0;
	while(fin>>x){
		cnt++;
		cout<<"a+=";
		if(x<0){
			x=-x;
			cout<<s[x-2]<<endl;
		}else{
			cout<<"-"<<s[x-2]<<endl;
		}
	}
	fstream fans("num1.txt");
	printf("%d\n",cnt);
	while(fans>>x){
		if(x<0){
			x=-x;
			printf("%d\n",x-2);
		}else{
			printf("-%d\n",x-2);
		}
	}
	return 0;
}
