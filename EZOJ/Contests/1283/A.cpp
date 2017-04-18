#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int N=2010;
char s[N],store[N];
struct intl{
	int l,r;
}f[N][N];
inline bool operator < (intl a,intl b){
	if(a.r-a.l==b.r-b.l){
		for(int i=a.l,j=b.l;i<=a.r;i++,j++){
			if(s[i]!=s[j]){
				return s[i]<s[j];
			}
		}
	}
	return a.r-a.l<b.r-b.l;
}
char ans[N];
int anslen;
inline bool judge(intl f){
	if(f.r-f.l+1<anslen){
		return true;
	}
	
}
int main(){
	int n=ni(),k=ni();
	scanf("%s",store);
	store[n/k]=0;
	puts(store);
	return 0;
	anslen=100000000;
	for(int i=1;i<=n;i++){
		for(int j=0;j<n;j++){
			s[(i+j-1)%n+1]=store[j];
		}
		for(int k=0,j=1;j<=n;j++){
			f[j]=(intl){k+1,j};
			for(;k<j&&f[k]<(intl){k+1,j};k++){
				f[j]=min(f[j],max(f[k],(intl){k+1,j}));
			}
		}
		if(judge(f[n][k])){
			anslen=f[n][k].r-f[n][k].l+1;
			memcpy(ans,s+f[n][k].l,anslen);
		}
	}
	ans[anslen]=0;
	puts(ans);
}
