#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
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
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
const int N=400010,INF=0x7f7f7f7f;
struct SuffixArray{
	int sa[N],w[N],*rank,*sa2;
	inline bool equal(int a,int b,int j){
		return rank[a]==rank[b]&&rank[a+j]==rank[b+j];
	}
	inline void get(int n,int m){
		memset(w,0,m<<2);
		for(int i=0;i<n;i++){
			w[rank[i]]++;
		}
		for(int i=1;i<m;i++){
			w[i]+=w[i-1];
		}
		for(int i=n-1;i>=0;i--){
			sa[--w[rank[i]]]=i;
		}
		for(int j=1,p;m<n;j<<=1,m=p+1){
			p=0;
			for(int i=n-j;i<n;i++){
				sa2[p++]=i;
			}
			for(int i=0;i<n;i++){
				if(sa[i]>=j){
					sa2[p++]=sa[i]-j;
				}
			}
			memset(w,0,m<<2);
			for(int i=0;i<n;i++){
				w[rank[i]]++;
			}
			for(int i=1;i<m;i++){
				w[i]+=w[i-1];
			}
			for(int i=n-1;i>=0;i--){
				sa[--w[rank[sa2[i]]]]=sa2[i];
			}
			sa2[sa[p=0]]=0;
			for(int i=1;i<n;i++){
				sa2[sa[i]]=equal(sa[i],sa[i-1],j)?p:++p;
			}
			swap(rank,sa2);
		}
	}
	int pool[2][N];
	inline void work(int* s,int n){
		rank=pool[0],sa2=pool[1];
		int high=0;
		for(int i=0;i<n;i++){
			apmax(high,rank[i]=s[i]);
		}
		get(n,high+1);
	}
}worker;
int seq[N];
int main(){
	memset(seq,0,sizeof(seq));
	int n=ni(),m,high=0;
	for(int i=0;i<n;i++){
		apmax(high,seq[i]=ni());
	}
	m=ni();
	for(int i=n+1,top=n+1+m;i<top;i++){
		apmax(high,seq[i]=ni());
	}
	seq[n]=seq[n+1+m]=high+1;
	worker.work(seq,n+2+m);
	for(int i=0,j=n+1,top=n+1+m;i<n||j<top;){
		if(i>=n){
			printf("%d ",seq[j++]);
		}else if(j>=top){
			printf("%d ",seq[i++]);
		}else if(seq[i]<seq[j]){
			printf("%d ",seq[i++]);
		}else if(seq[i]>seq[j]){
			printf("%d ",seq[j++]);
		}else if(worker.rank[i]<worker.rank[j]){
			printf("%d ",seq[i++]);
		}else{
			printf("%d ",seq[j++]);
		}
	}
}
