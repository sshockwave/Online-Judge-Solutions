#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
const int N=500010;
char s[N];
int num[N];
int main(){
	scanf("%s",s);
	int n=strlen(s);
	int r=0,cur=0;
	memset(num,0,sizeof(num));
	for(int i=0;i<n;i++){
		num[i]=(s[n-i-1]-'0')*9+r;
		r=num[i]/10;
		cur+=num[i]%=10;
	}
	for(;r;n++){
		cur+=num[n]=r%10;
		r/=10;
	}
	int ans=0;
	for(;cur>ans*9;ans++){
		num[0]+=9,cur+=9;
		for(int i=0,r=0;num[i]>9||r;i++){
			cur-=num[i];
			num[i]+=r;
			r=num[i]/10;
			cur+=num[i]%=10;
		}
	}
	printf("%d\n",ans);
	return 0;
}
