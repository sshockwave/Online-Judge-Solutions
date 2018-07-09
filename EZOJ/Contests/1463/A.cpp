#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,sizeof(a[0])*n);}
const int N=510,A=2333333;
int k;
inline bool attempt1(){
	if(k>500)return false;
	printf("%d\n",k);
	for(int i=1;i<=k;i++){
		printf("%d ",i);
	}
	putchar('\n');
	return true;
}
inline bool attempt2(){
	for(int i=1;i<=500&&i<=k;i++){
		int base=i*(i-1)/2+1;
		if(base>k)break;
		if((k-base)%i==0&&i+(k-base)/i<=500){
			//...random... 1 1 1 1
			printf("%d\n",i+(k-base)/i);
			for(int j=1;j<=i;j++){
				printf("%d ",j&1?j+10000:(A-j));
			}
			for(int j=1;j<=(k-base)/i;j++){
				putchar('1');
				putchar(' ');
			}
			putchar('\n');
			return true;
		}
	}
	return false;
}
inline bool attempt3(){
	for(int i=1;i<=500&&i<=k;i++){
		int base=i*(i-1)/2+1;
		if(base>k)break;
		//the first time is +i
		//and then +(i+1)
		int t=k-base;
		if(t==0||(t>=i&&(t-i)%(i+1)==0)){
			int stepcnt=i;
			if(t>=i){
				stepcnt+=(t-i)/(i+1)+1;
			}
			if(stepcnt<=500){
				//...random... 1 2 3 4 5
				printf("%d\n",stepcnt);
				for(int j=1;j<=i;j++){
					printf("%d ",j&1?j+10000:(A-j));
				}
				for(int j=1;j<=(k-base)/(i+1);j++){
					printf("%d ",j);
				}
				putchar('\n');
				return true;
			}
		}
	}
	return false;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("var.in","r",stdin);
	freopen("var.out","w",stdout);
#endif
	k=ni;
	if(attempt1())return 0;
	if(attempt2())return 0;
	if(attempt3())return 0;
	return 0;
}
