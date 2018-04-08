#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
const int N=1010;
char mat[N][N];
int allcnt[N][N];
lint subcost[N][N];
inline lint work(int n,int m){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			allcnt[i][j]=allcnt[i][j-1]+(mat[i][j]=='#');
			subcost[i][j]=subcost[i][j-1]+allcnt[i][j-1];
		}
	}
	lint ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			subcost[i][j]+=subcost[i-1][j]+allcnt[i-1][j];
			allcnt[i][j]+=allcnt[i-1][j];
			if(mat[i][j]=='#'){
				ans+=subcost[i][j];
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mat[i][j]=='G'){
				subcost[i][j]=subcost[i-1][j]+(j-1)*2;
			}else{
				ans+=subcost[i][j]=subcost[i][j-1];
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mat[i][j]=='G'){
				subcost[i][j]=subcost[i][j-1]+(i-1)*2;
			}else{
				ans+=subcost[i][j]=subcost[i-1][j];
			}
		}
	}
	return ans;
}
lint costl[N],costr[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
#endif
	int n=ni,m=ni;
	for(int i=1;i<=n;i++){
		scanf("%s",mat[i]+1);
	}
	lint ans=0;
	ans+=work(n,m);
	for(int i=1;i<=n;i++){
		reverse(mat[i]+1,mat[i]+m+1);
	}
	ans+=work(n,m);
	ans<<=1;
	for(int i=1;i<=n;i++){
		for(int j=1,l=0,cnt=0;j<=m;j++){
			costl[j]=costl[j-1]+cnt;
			if(mat[i][j]=='G'){
				costl[j]+=(j-l-1)*2;
				l=j;
			}else{
				cnt++;
			}
		}
		for(int j=m,l=m+1,cnt=0;j>=1;j--){
			costr[j]=costr[j+1]+cnt;
			if(mat[i][j]=='G'){
				costr[j]+=(l-j-1)*2;
				l=j;
			}else{
				cnt++;
			}
		}
		for(int j=1;j<=m;j++){
			if(mat[i][j]=='#'){
				ans-=costl[j]+costr[j];
			}
		}
	}
	for(int j=1;j<=m;j++){
		for(int i=1,l=0,cnt=0;i<=n;i++){
			costl[i]=costl[i-1]+cnt;
			if(mat[i][j]=='G'){
				costl[i]+=(i-l-1)*2;
				l=i;
			}else{
				cnt++;
			}
		}
		for(int i=n,l=n+1,cnt=0;i>=1;i--){
			costr[i]=costr[i+1]+cnt;
			if(mat[i][j]=='G'){
				costr[i]+=(l-i-1)*2;
				l=i;
			}else{
				cnt++;
			}
		}
		for(int i=1;i<=n;i++){
			if(mat[i][j]=='#'){
				ans-=costl[i]+costr[i];
			}
		}
	}
	printf("%lld ",ans);
	ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			ans+=mat[i][j]=='#';
		}
	}
	printf("%lld\n",ans*ans);
	return 0;
}
