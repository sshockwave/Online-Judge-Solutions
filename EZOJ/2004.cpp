#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline bool is_letter(char c){
	return c>='A'&&c<='Z';
}
inline char nc(){
	char c;
	while(!is_letter(c=getchar()));
	return c;
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
const int N=120010;
char s[N];
struct SuffixArray{
	int sa[N],w[N],r[2][N],*rank,*sa2;
	inline bool equal(int a,int b,int j){
		return rank[a]==rank[b]&&rank[a+j]==rank[b+j];
	}
	inline void put(char *s){
		for(int i=0;s[i];i++){
			putchar(' '),putchar(' '),putchar(s[i]);
		}
		putchar('\n');
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
			memset(w,0,n<<2);
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
	inline void work(char *s,int n,char low){
		memset(r,0,sizeof(r));
		rank=r[0],sa2=r[1];
		int high=0;
		for(int i=0;i<n;i++){
			apmax(high,rank[i]=s[i]-low);
		}
		get(n,high+1);
	}
}sa;
int main(){
	int n=ni();
	for(int i=0;i<n;i++){
		s[i]=nc();
	}
	s[n]='@';
	for(int i=n+1,j=n-1;j>=0;i++,j--){
		s[i]=s[j];
	}
	sa.work(s,2*n+1,'@');
	for(int i=0,j=n-1,tot=0;i<=j;){
		if(s[i]<s[j]){
			putchar(s[i++]);
		}else if(s[i]>s[j]){
			putchar(s[j--]);
		}else if(sa.rank[i]<sa.rank[(n<<1)-j]){
			putchar(s[i++]);
		}else{
			putchar(s[j--]);
		}
		if((++tot)%80==0){
			putchar('\n');
		}
	}
}
