#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){a=b;}
}
const int N=110,C=100000010,INF=0x7f7f7f7f;
int f[N][N];//f[day][ws]:mxval
int pw[N][N];//i^j
int a[N],w[N];
bool test(int n,int cur,int last,int c){
	if(n-last>=c-cur){
		return true;
	}
	if(n==0||cur==0){
		return false;
	}
	int i=last;
	for(;i-last<n&&(lint)cur*pw[i][n]<=c;i++);
	while((--i)>=last){
		if(test(n-1-(i-last),cur*i,i,c)){
			return true;
		}
	}
	return false;
}
inline bool work(int n,int c){
	if(n>=c){
		return true;
	}
	if(test(n,1,0,c)){
		return true;
	}
	return false;
}
int main(){
	int n=ni,tot=ni,mxval=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	for(int i=1;i<=n;i++){
		w[i]=ni;
	}
	memset(pw,127,sizeof(pw));
	for(int i=0;i<=n;i++){
		long long cur=1;
		for(int j=0;j<=n&&cur<=C;j++){
			pw[i][j]=cur;
			cur*=i;
		}
	}
	pw[0][0]=0;
	memset(f,-1,sizeof(f));
	f[0][0]=mxval;
	int most=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=i;j++){
			if(f[i-1][j]>=a[i]){
				f[i][j]=f[i-1][j]-a[i];
			}
			if(f[i-1][j-1]>=a[i]){
				apmax(f[i][j],f[i-1][j-1]-a[i]+w[i]);
			}
			apmin(f[i][j],mxval);
		}
		int least=0;
		for(;f[i][least]<0&&least<=i;least++);
		apmax(most,i-least);
	}
	for(;tot--;putchar('0'+work(most,ni)),putchar('\n'));
}