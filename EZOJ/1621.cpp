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
inline void apmax(int &a,const int &b){
	if(a<b){
		a=b;
	}
}
const int N=50010;
namespace SA{
	int sa[N],*rnk,lcp[N],w[N],*sa2,n;
	inline int same(int a,int b,int g){
		return rnk[a]==rnk[b]&&((a+g<n&&b+g<n&&rnk[a+g]==rnk[b+g])||(a+g>=n&&b+g>=n));
	}
	inline int ext(int g,int d){
		for(int i=n-g,j=0;i<n;sa2[j++]=i++);
		for(int i=0,j=g;i<n;sa2[sa[i]>=g?j++:j]=sa[i]-g,i++);
		memset(w,0,d<<2);
		for(int i=0;i<n;w[rnk[i++]]++);
		for(int i=1;i<d;w[i]+=w[i-1],i++);
		for(int i=n-1;i>=0;sa[--w[rnk[sa2[i]]]]=sa2[i],i--);
		sa2[sa[d=0]]=0;
		for(int i=1;i<n;sa2[sa[i]]=same(sa[i-1],sa[i],g)?d:++d,i++);
		swap(rnk,sa2);
		return d+1;
	}
	int tmp[2][N];
	inline void work(char s[]){
		n=strlen(s),rnk=tmp[0],sa2=tmp[1];
		int d=26;
		memset(w,0,d<<2);
		for(int i=0;i<n;i++){
			w[rnk[i]=s[i]-'a']++;
		}
		for(int i=1;i<d;i++){
			w[i]+=w[i-1];
		}
		for(int i=n-1;i>=0;i--){
			sa[--w[rnk[i]]]=i;
		}
		for(int i=1;(d=ext(i,d))<n;i<<=1);
		memset(lcp,0,n<<2);
		for(int i=0;i<n;i++){
			if(rnk[i]){
				if(i){
					apmax(lcp[rnk[i]],lcp[rnk[i-1]]-1);
				}
				for(int &j=lcp[rnk[i]],p=i,q=sa[rnk[i]-1];s[p+j]==s[q+j];j++);
			}
		}
	}
}
char s[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("sa.in","r",stdin);
	freopen("sa.out","w",stdout);
#endif
	scanf("%s",s);
	SA::work(s);
	for(int i=0;i<SA::n;i++){
		printf("%d ",SA::rnk[i]+1);
	}
	putchar('\n');
	for(int i=0;i<SA::n;i++){
		printf("%d ",SA::lcp[i]);
	}
	putchar('\n');
}
