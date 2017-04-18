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
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
const int N=100010,INF=0x7f7f7f7f;
char s[N];
int n,len;
inline int add(int a,int b){
	a+=b;
	if(a>=n){
		a-=n;
	}
	return a;
}
inline int sub(int a,int b){
	a-=b;
	if(a<0){
		a+=n;
	}
	return a;
}
struct RoundSA{
	int sa[N],*sa2,*rank,w[N],gap;
	inline bool equal(int a,int b,int j){
		return rank[a]==rank[b]&&rank[add(a,gap)]==rank[add(b,gap)];
	}
	inline int extend(int j,int m){
		memset(w,0,m<<2);
		gap=j%n;
		for(int i=0;i<n;i++){
			sa2[i]=sub(sa[i],gap);
			w[rank[i]]++;
		}
		for(int i=1;i<m;i++){
			w[i]+=w[i-1];
		}
		for(int i=n-1;i>=0;i--){
			sa[--w[rank[sa2[i]]]]=sa2[i];
		}
		int p=0;
		sa2[sa[0]]=0;
		for(int i=1;i<n;i++){
			sa2[sa[i]]=equal(sa[i],sa[i-1],j)?p:++p;
		}
		swap(sa2,rank);
		return p+1;
	}
	int tmp[2][N];
	inline void work(char *s){
		sa2=tmp[0],rank=tmp[1];
		memset(w,0,10<<2);
		for(int i=0;i<n;i++){
			w[rank[i]=s[i]-'0']++;
		}
		for(int i=1;i<10;i++){
			w[i]+=w[i-1];
		}
		for(int i=n-1;i>=0;i--){
			sa[--w[rank[i]]]=i;
		}
		for(int j=1,m=10;(m=extend(j,m))<n&&j<n;j<<=1);
	}
	inline int check(int rk){
		int ans=INF;
		for(int i=0;i<len;i++){
			int cnt=0;
			for(int k=i,top=n+i;k<top;cnt++){
				if(rank[k%n]<=rk){
					k+=len;
				}else{
					k+=len-1;
				}
			}
			apmin(ans,cnt);
		}
		return ans;
	}
}worker;
int main(){
	int k;
	while(scanf("%d%d",&n,&k)!=EOF){
		len=n/k;
		if(n%k){
			len++;
		}
		scanf("%s",s);
		worker.work(s);
		if(n==k){
			putchar(s[worker.sa[n-1]]);
			putchar('\n');
			continue;
		}
		int l=0,r=n-1,mid;
		while(l<r){
			mid=(l+r)>>1;
			if(worker.check(mid)>k){
				l=mid+1;
			}else{
				r=mid;
			}
		}
		for(int i=worker.sa[l],j=0;j<len;i=add(i,1),j++){
			putchar(s[i]);
		}
		putchar('\n');
	}
}
