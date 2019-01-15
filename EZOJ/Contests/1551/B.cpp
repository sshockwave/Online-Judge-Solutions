#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
using namespace std;
typedef long long lint;
typedef vector<int>vi;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	for(;!isdigit(c=getchar())&&c!='-';);
	bool neg=c=='-';
	neg?c=getchar():0;
	for(;i=i*10-'0'+c,isdigit(c=getchar()););
	return neg?-i:i;
}
template<class A,class B>inline void apmax(A &a,const B &b){if(a<b)a=b;}
template<class A,class B>inline void apmin(A &a,const B &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(a));}
template<class T>inline void mcpy(T a[],const T b[],int n){memcpy(a,b,n*sizeof(a));}
const int N=100010;
int n;
int a[N];
vi lst[N*3];
int ans[4][N];
int curlen;
int restlen;
int curid=0;
inline void getedge(){
	for(;lst[curlen].empty();curlen--);
	curid=lst[curlen].back(),lst[curlen].pop_back();
	restlen=curlen;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	int n=ni,m=ni;
	if(m<n){
		puts("no");
		return 0;
	}
	if(m==1){
		puts("yes");
		puts("1");
		puts("1");
		puts("1");
		return 0;
	}
	for(int i=1;i<=m;i++){
		lst[ni].push_back(i);
	}
	curlen=n*3;
	bool isup=true;
	for(int rpt=n;rpt>0;rpt--){
		if(restlen==0){
			getedge();
		}
		if(restlen==3){
			ans[1][rpt]=ans[2][rpt]=ans[3][rpt]=curid;
			restlen=0;
			continue;
		}
		if(restlen==1){
			if(isup){
				ans[1][rpt]=curid;
			}else{
				ans[3][rpt]=curid;
			}
			getedge();
			ans[2][rpt]=curid;
			restlen--;
			if(restlen==0){
				getedge();
			}
			if(isup){
				ans[3][rpt]=curid;
			}else{
				ans[1][rpt]=curid;
			}
			restlen--;
			continue;
		}
		if(restlen==2){
			if(isup){
				ans[1][rpt]=curid;
			}else{
				ans[3][rpt]=curid;
			}
			ans[2][rpt]=curid;
			getedge();
			if(isup){
				ans[3][rpt]=curid;
			}else{
				ans[1][rpt]=curid;
			}
			restlen-=1;
			isup^=1;
			continue;
		}
		if(!lst[1].empty()){
			if(isup){
				ans[1][rpt]=curid;
				ans[3][rpt]=lst[1].back();
			}else{
				ans[3][rpt]=curid;
				ans[1][rpt]=lst[1].back();
			}
			lst[1].pop_back();
			ans[2][rpt]=curid;
			isup^=1;
			restlen-=2;
			continue;
		}
		if(!lst[2].empty()){
			int x=lst[2].back();
			lst[2].pop_back();
			if(isup){
				ans[1][rpt]=curid;
				ans[3][rpt]=x;
			}else{
				ans[3][rpt]=curid;
				ans[1][rpt]=x;
			}
			ans[2][rpt]=x;
			restlen-=1;
			continue;
		}
		assert(false);
	}
	for(int i=1;i<=3;i++){
		for(int j=1;j<=n;j++){
			printf("%d ",ans[i][j]);
		}
		putchar('\n');
	}
	return 0;
}
