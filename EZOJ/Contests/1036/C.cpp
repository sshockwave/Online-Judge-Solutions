#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
const int N=210,M=410;
int lst[N][N],rnk[N][N];
int cur[N],lnk[N],dcd[N];
int que[N];
inline void Main(){
	int n=ni,m=ni;
	for(int i=1;i<=n;i++){
		for(int j=1,k=1;j<=m;j++){
			lst[i][k]=ni;
			if(lst[i][k]){
				rnk[i][lst[i][k]]=k;
				k++;
			}
		}
	}
	int qh=0,qt=0;
	for(int i=1;i<=n;i++){
		que[qt++]=i;
		cur[i]=1;
	}
	memset(lnk+1,0,n<<2);
	while(qh!=qt){
		int x=que[qh++];
		if(qh==N){
			qh=0;
		}
		for(;;cur[x]++){
			int v=lst[x][cur[x]],u=lnk[v];
			if(u==0){
				lnk[v]=x;
				break;
			}else if(rnk[u][v]>rnk[x][v]){
				que[qt++]=u;
				if(qt==N){
					qt=0;
				}
				lnk[v]=x;
				break;
			}
		}
	}
	for(int i=1;i<=n;i++){
		dcd[lnk[i]]=i;
	}
	for(int i=1;i<=n;i++){
		printf("%d ",dcd[i]);
	}
	putchar('\n');
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("matrix.in","r",stdin);
	freopen("matrix.out","w",stdout);
#endif
	for(int tot=ni;tot--;Main());
	return 0;
}
