#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define L 100010
#define INF 0x7f7f7f7f
using namespace std;
int sa[L],rank[2][L],key1[L],rankp[L],sort2[L],n;
char s[L];
int main(){
	scanf("%s",s);
	int *r=rank[0],*nr=rank[1];
	memset(nr,0,sizeof(nr));
	for(n=0;s[n];n++){
		nr[s[n]]++;
	}
	for(int i=1;i<128;i++){
		nr[i]+=nr[i-1];
	}
	for(int i=0;s[i];i++){
		r[i]=nr[s[i]];
	}
	for(int i=1;i<=n;i++){
		rankp[i]=i;
	}
	for(int i=n-1;i>=0;i--){
		sa[rankp[r[i]]--]=i;
	}
	for(int j=1,cnt=INF;j<n&&cnt;j<<=1){
		//sort by key 2
		for(int i=1;i<=n;i++){
			sort2[i]=sa[i]-j;
			if(sort2[i]<0){
				sort2[i]+=n;
			}
		}
		//init rankp
		for(int i=1;i<=n;i++){
			rankp[i]=i;
		}
		//calculate sa
		for(int i=n;i>0;i--){
			sa[rankp[r[sort2[i]]]--]=sort2[i];
		}
		//calculate rank
		cnt=n;
		for(int i=n,p,l1=INF,l2=INF,r1,r2;i>0;i--){
			r1=r[sa[i]],r2=r[(sa[i]+j)%n];
			if(r1!=l1||r2!=l2){
				p=i;
				cnt--;
			}
			l1=r1,l2=r2;
			nr[sa[i]]=p;
		}
		swap(r,nr);
	}
	for(int i=1;i<=n;i++){
		putchar(s[(sa[i]-1+n)%n]);
	}
}
