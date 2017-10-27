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
const int N=50,P=50010;
int num[N],a[N],b[N],pos[N];
bool f[N][N][P],mark[N];
inline int fpow(int x,int n,int O){
	int a=1;
	for(;n;n>>=1,(x*=x)%=O){
		if(n&1){
			(a*=x)%=O;
		}
	}
	return a;
}
inline int inv(int x,int O){
	return fpow(x,O-2,O);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
#endif
	memset(f,0,sizeof(f));
	f[0][0][0]=1;
	int n=0;
	int tot=ni,p=ni;
	if(p==2||p==5){
		for(int i=1;i<=tot;i++){
			int cur=ni;
			if(cur<32){
				pos[++n]=i;
				num[n]=cur;
			}
		}
		int pt=n;
		for(;pt>=1&&num[pt]%p;pt--);
		if(pt){
			static int f[32][32];
			memset(f,0,sizeof(f));
			f[0][0]=-1;
			for(int i=1;i<=pt;i++){
				for(int j=0;j<32;j++){
					if(f[i-1][j]){
						f[i][j]=f[i-1][j];
						f[i][j^num[i]]=i;
					}
				}
			}
			if(f[pt][0]){
				int cnt=0;
				for(int i=pt,j=0;~i;cnt++,mark[i]=true,i=f[i-1][j^=num[i]]);
				printf("Yes\n%d\n",cnt);
				for(int i=1;i<=pt;i++){
					if(mark[i]){
						printf("%d ",pos[i]);
					}
				}
				putchar('\n');
			}else{
				puts("NO");
			}
		}else{
			puts("No");
		}
		return 0;
	}
	for(int i=1;i<=tot;i++){
		int cur=ni;
		if(cur<32){
			pos[++n]=i;
			num[n]=cur;
			a[n]=1,b[n]=cur%p;
			for(int t=cur;t;t/=10,a[n]*=10);
			a[n]%=p;
			for(int j=0;j<32;j++){
				for(int k=0;k<p;k++){
					if(f[n-1][j][k]){
						f[n][j][k]=true;
						int txor=j^cur,tmod=(k*a[n]+b[n])%p;
						if(txor==0&&tmod==0){//goback
							int cnt=0;
							for(int l=n;l>=1;l--){
								int nxor=txor^num[l],nmod=(tmod-b[l]+p)%p*inv(a[l],p)%p;
								if(f[l-1][nxor][nmod]){
									cnt++;
									mark[l]=true;
									txor=nxor,tmod=nmod;
								}
							}
							printf("Yes\n%d\n",cnt);
							for(int l=1;l<=n;l++){
								if(mark[l]){
									printf("%d ",pos[l]);
								}
							}
							putchar('\n');
							return 0;
						}
						f[n][txor][tmod]=true;
					}
				}
			}
		}
	}
	puts("No");
	return 0;
}
