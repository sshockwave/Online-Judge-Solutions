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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=100010,O=1000000007;
int pre[N][2],nxt[N];
bool vis[N];
int ring[N];
int f[N];
inline int Main(){
	int n=ni;
	memset(pre,0,sizeof(pre));
	for(int i=1;i<=n;i++){
		nxt[i]=ni;
		if(pre[nxt[i]][0]==0){
			pre[nxt[i]][0]=i;
		}else if(pre[nxt[i]][1]==0){
			pre[nxt[i]][1]=i;
		}else return 0;
	}
	memset(ring,0,sizeof(ring));
	lint ans=1;
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			int j=i,sz=0;
			for(;!vis[j];vis[j]=true,j=nxt[j]);
			for(int p=j,q;sz++,q=nxt[p],pre[q][0]!=p?swap(pre[q][0],pre[q][1]):void(),p=q,p!=j;);
			int p=j;
			bool flag=true;
			int cur=1;
			do if(pre[p][1]){
				flag=false;
				int a=pre[p][0],b=pre[p][1];
				for(;vis[b]=true,pre[b][0];a=pre[a][0],b=pre[b][0]){
					if(pre[a][1]||pre[b][1])return 0;
				}
				if(pre[a][1]==0){
					cur=(cur<<1)%O;
				}
			}while(p=nxt[p],p!=j);
			if(flag){
				assert(cur==1);
				ring[sz]++;
			}else{
				(ans*=cur)%=O;
			}
		}
	}
	for(int i=1;i<=n;i++){
		f[0]=1,f[1]=(i==3)+1;
		for(int j=2;j<=ring[i];j++){
			f[j]=((lint)f[j-2]*(j-1)%O*i%O+(f[j-1]<<(i==3)))%O;
		}
		(ans*=f[ring[i]])%=O;
	}
	return ans;
}
int main(){
	printf("%d\n",Main());
	return 0;
}
