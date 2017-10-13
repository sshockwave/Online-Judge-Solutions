#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
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
const int N=5010,MOD=1000000007;
char s[N];
int lcp[N][N];
int f[N][N];//f[i][j]:[i-j+1,i]
bool scmp[N][N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
#endif
	int n=ni;
	scanf("%s",s+1);
	for(int i=n;i>=1;i--){
		for(int j=n;j>=i;j--){
			if(s[i]==s[j]){
				if(i==n||j==n){
					lcp[i][j]=1;
					scmp[i][j]=i==n&&j!=n;
				}else{
					lcp[i][j]=lcp[i+1][j+1]+1;
					scmp[i][j]=scmp[i+1][j+1];
				}
			}else{
				lcp[i][j]=0;
				scmp[i][j]=s[i]<s[j];
			}
		}
	}
	if(s[1]=='0'){
		putchar('0'),putchar('\n');
		return 0;
	}
	memset(f,0,sizeof(f));
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		int sum=0,tmp;
		for(int j=1;j<=i;j++){
			int m=i-j+1,l=max(m-j,1);
			if(s[m]=='0'){
				f[i][j]=sum;
				continue;
			}
			if(m-l<j){
				tmp=f[m-1][m-l];
			}else if(lcp[l][m]<j&&scmp[l][m]){
				tmp=f[m-1][j];
			}else{
				tmp=f[m-1][j-1];
			}
			f[i][j]=sum=(sum+tmp)%MOD;
		}
	}
	printf("%d\n",f[n][n]);
	return 0;
}
