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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
inline void apmin(int &a,const int &b){
	if(b<a){
		a=b;
	}
}
const int N=4010,D=26,INF=0x7f7f7f7f;
char s[N],t[N];
int f[N][N],_s[D],_t[D];
int main(){
#ifndef ONLINE_JUDGE
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
#endif
	int a=ni,b=ni,c=ni,d=ni;
	scanf("%s%s",s+1,t+1);
	int lens=strlen(s+1),lent=strlen(t+1);
	memset(f,127,sizeof(f));
	for(int i=0;i<=lens;i++){
		f[i][0]=i*b;
	}
	for(int i=0;i<=lent;i++){
		f[0][i]=i*a;
	}
	memset(_s,0,sizeof(_s));
	for(int i=1;i<=lens;i++){
		memset(_t,0,sizeof(_t));
		for(int j=1;j<=lent;j++){
			int &F=f[i][j];
			apmin(F,f[i][j-1]+a);
			apmin(F,f[i-1][j]+b);
			if(s[i]==t[j]){
				apmin(F,f[i-1][j-1]);
			}else{
				apmin(F,f[i-1][j-1]+c);
			}
			int p=_s[t[j]-'a'],q=_t[s[i]-'a'];
			if(p&&q){
				apmin(F,f[p-1][q-1]+(j-q-1)*a+(i-p-1)*b+d);
			}
			_t[t[j]-'a']=j;
		}
		_s[s[i]-'a']=i;
	}
	printf("%d\n",f[lens][lent]);
}
