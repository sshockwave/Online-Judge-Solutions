#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
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
const int N=10000010;
int cnt[N];
int A,B,X,Y,Z,P,C,Q;
bool vis[2010][2010];
int len;
inline lint getcnt(lint x){
	return cnt[len]*(x/len)+cnt[x%len];
}
inline void work(){
	A=ni,B=ni,X=ni,Y=ni,Z=ni,P=ni,C=ni,Q=ni;
	cnt[0]=0;
	cnt[1]=A==C;
	cnt[2]=cnt[1]+(B==C);
	len=N-1;
	memset(vis,0,sizeof(vis));
	vis[A][B]=true;
	for(int i=3,cur,j=cnt[2];i<N;i++){
		cur=(X*B+Y*A+Z)%P;
		if(cur==C){
			j++;
		}
		cnt[i]=j;
		A=B,B=cur;
		if(P<=2000){
			if(vis[A][B]){
				len=i-2;
				break;
			}
			vis[A][B]=true;
		}
	}
	while(Q--){
		lint l=nl,r=nl;
		if(P<=2000){
			printf("%lld\n",getcnt(r)-getcnt(l-1));
		}else{
			printf("%d\n",cnt[r]-cnt[l-1]);
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("eclipse2.in","r",stdin);
	freopen("eclipse.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		work();
	}
}
