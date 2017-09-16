#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <ctime>
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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
const int N=15;
int c[N][N],_c[N][N];
inline void init(){
	memset(c,0,sizeof(c));
	memset(_c,0,sizeof(_c));
	_c[0][0]=c[0][0]=1;
	for(int i=1;i<N;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++){
			c[i][j]=c[i-1][j-1]+c[i-1][j];
		}
		for(int j=0;j<N;j++){
			_c[i][j]=_c[i-1][j]+c[i][j];
		}
	}
}
double prob[252],pnum[7];
int cnt[7],score[252][1<<14];
inline int gscore(int id){
	if(id<=6){
		return id*cnt[id];
	}
	int sum=0;
	for(int i=1;i<=6;i++){
		sum+=i*cnt[i];
	}
	if(id==7){
		for(int i=1,j=0;i<=6;i++){
			if(cnt[i]>=2){
				if(j){
					return sum;
				}else{
					j=i;
				}
			}
		}
		return 0;
	}
	if(id==8||id==9){
		for(int i=1;i<=6;i++){
			if(cnt[i]>=id-5){
				return sum;
			}
		}
		return 0;
	}
	if(id==10){
		bool flag=false;
		for(int i=1;i<=6;i++){
			if(cnt[i]==2){
				flag=true;
				break;
			}
		}
		if(!flag){
			return 0;
		}
		for(int i=1;i<=6;i++){
			if(cnt[i]==3){
				return 25;
			}
		}
		return 0;
	}
	if(id==11||id==12){
		for(int i=1,j=0;i<=6;i++){
			if(cnt[i]){
				if(i-j>=id-7){
					return id==11?30:40;
				}
			}else{
				j=i;
			}
		}
		return 0;
	}
	if(id==13){
		for(int i=1;i<=6;i++){
			if(cnt[i]==5){
				return 50;
			}
		}
		return 0;
	}
	if(id==14){
		return sum;
	}
	assert(false);
	return -1;
}
int lst[252][15];
inline int hush(){
	int ans=0,pos=0;
	for(int i=1;i<6;i++){
		ans+=_c[10-pos-1][5-i]-_c[10-pos-cnt[i]-1][5-i];
		pos+=cnt[i]+1;
	}
	for(int i=0;i<14;i++){
		score[ans][1<<i]=gscore(i+1);
	}
	return ans;
}
void dfs(int i,double p){
	if(i>5){
		prob[hush()]+=p;
		return;
	}
	for(int a=1;a<=6;a++){
		cnt[a]++,dfs(i+1,p*pnum[a]),cnt[a]--;
	}
}
double f[1<<14];
inline int lb(int x){
	return x&(-x);
}
inline double Main(){
	for(int i=1;i<=6;i++){
		scanf("%lf",pnum+i);
	}
	memset(prob,0,sizeof(prob));
	memset(cnt,0,sizeof(cnt));
	dfs(1,1);
	for(int s=0,ts=1<<14;s<ts;s++){
		double e=0;
		for(int i=0;i<252;i++){
			double mx=0;
			for(int j=s,k;j;j^=k){
				k=lb(j);
				apmax(mx,(double)score[i][k]+f[s^k]);
			}
			e+=mx*prob[i];
		}
		f[s]=e;
	}
	return f[(1<<14)-1];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("dices.in","r",stdin);
	freopen("dices.out","w",stdout);
#endif
	init();
	for(int i=1,tot=ni;i<=tot;printf("Case #%d: %.6lf\n",i++,Main()));
	return 0;
}
