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
const int N=100010,logN=20;
char s[N];
int n,len;
inline int add(int a,int b){
	a+=b;
	if(a>b){
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
	int sa[N],*sa2,*rank,w[N];
	inline bool equal(int a,int b,int j){
		return rank[a]==rank[b]&&rank[add(a,j)]==rank[add(b,j)];
	}
	inline int extend(int j,int m){
		memset(w,0,m<<2);
		for(int i=0;i<n;i++){
			sa2[i]=sub(sa[i],j);
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
	inline void check(int p){
		bool flag=false;
		int j=p,cnt=0;
		while(true){
			if(j>=p&&flag){
				break;
			}
			if(rank[j]<=rank[p]){
				j+=len;
			}else{
				j+=len-1;
			}
			cnt++;
			if(j>=n){
				j=0;
				flag=true;
			}
		}
		return cnt;
	}
}worker;
int main(){
	n=ni();
	int k=ni();
	len=n/k;
	if(n%k){
		len++;
	}
	scanf("%s",s);
	worker.work(s);
	int l=0,r=n-1,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(worker.check(worker.sa[mid])>k){
			l=mid+1;
		}else{
			r=mid;
		}
	}
}
