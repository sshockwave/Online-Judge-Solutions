#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 100010
#define M 1010
#define C 110
using namespace std;
struct course{
	int t,s,c;
}cs[M];
inline bool operator < (course a,course b){
	return a.t<b.t;
}
struct homework{
	int a,q;
}hw[N];
inline bool operator < (homework a,homework b){
	return a.q<b.q;
}
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
int f[N][C];
int main(){
	int tot,m,n,maxc=0,ans=0;
	scanf("%d%d%d",&tot,&m,&n);
	for(int i=0;i<m;){
		scanf("%d%d%d",&cs[i].t,&cs[i].s,&cs[i].c);
		if(cs[i].t+cs[i].s>tot){
			m--;
		}else{
			apmax(maxc,cs[i].c);
			i++;
		}
	}
	for(int i=0;i<n;i++){
		scanf("%d%d",&hw[i].a,&hw[i].q);
	}
	sort(cs,cs+m);
	sort(hw,hw+n);
	memset(f,-1,sizeof(f));
	f[1][1]=0;
	for(int i=1,p=0,maxhw;i<tot;i++){
		maxhw=-1;
		for(int j=1,k=0;j<=maxc;j++){
			if(f[i][j]==-1){
				continue;
			}
			apmax(maxhw,f[i][j]);
			apmax(f[i+1][j],f[i][j]);
			for(;k<n&&hw[k].q<=j;k++);
			for(int t=0;t<k;t++){
				if(i+hw[t].a<=tot){
					apmax(f[i+hw[t].a][j],f[i][j]+1);
				}
			}
		}
		for(;p<m&&i==cs[p].t;p++){
			apmax(f[i+cs[p].s][cs[p].c],maxhw);
		}
	}
	for(int i=1;i<=maxc;i++){
		apmax(ans,f[tot][i]);
	}
	printf("%d",ans);
}
