#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
	if(a<b){
		a=b;
	}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){
		a=b;
	}
}
const int L=10010;
int lena,lenb,lens;
char a[L],b[L],s[L];
namespace brute{
	int ftop,atop,btop;
	char f[L],na[L],nb[L];
	void expand(int n){
		if(n==0){//a
			for(int i=1;i<=lena;i++){
				f[ftop++]=a[i];
			}
		}else if(n==1){//b
			for(int i=1;i<=lenb;i++){
				f[ftop++]=b[i];
			}
		}else{
			expand(n-1),expand(n-2);
		}
	}
	int fail[L];
	inline void build(char s[]){
		fail[0]=-1;
		for(int i=0,j=-1;s[i];){
			if(j==-1||s[i]==s[j]){
				fail[++i]=++j;
			}else{
				j=fail[j];
			}
		}
	}
	inline int kmp(char s[],char t[]){//nxt is for t
		int cnt=0;
		for(int i=0,j=0;s[i];){
			if(j==-1||s[i]==t[j]){
				i++,j++;
				if(t[j]==0){
					cnt++;
					j=fail[j];
				}
			}else{
				j=fail[j];
			}
		}
		return cnt;
	}
	inline int work(int n,int lf,int rf,int ls,int rs){
		ftop=1,atop=btop=0;
		expand(n);
		for(int i=lf;i<=rf;i++){
			na[atop++]=f[i];
		}
		na[atop]=0;
		for(int i=ls;i<=rs;i++){
			nb[btop++]=s[i];
		}
		nb[btop]=0;
		build(nb);
		return kmp(na,nb);
	}
}
namespace alls{
	const int N=50;
	struct pii{
		int i,cnt;
	}f[L][N],g[L][N];
	int fail[L],flen[N];
	inline void init(){
		fail[1]=0;
		for(int i=1,j=0;s[i];i++){
			if(j==0||s[i]==s[j]){
				fail[++i]=++j;
			}else{
				j=fail[j];
			}
		}
		
	}
	inline int work(int n,int lf,int rf,int ls,int rs){
		
	}
}
int main(){
//	freopen("string.in","r",stdin);
//	freopen("string.out","w",stdout);
	scanf("%s%s%s",a+1,b+1,s+1);
	lena=strlen(a+1),lenb=strlen(b+1),lens=strlen(s+1);
	int q=ni;
	while(q--){
		int n=ni,lf=ni,rf=ni,ls=ni,rs=ni;
		printf("%d\n",brute::work(n,lf,rf,ls,rs));
	}
	return 0;
}