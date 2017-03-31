#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline bool is_letter(char c){
	return c>='a'&&c<='z';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
inline void apmin(long long &a,long long b){
	if(a>b){
		a=b;
	}
}
const int N=210,L=100010,logM=31,INF=0x7f7f7f7f;
const long long LINF=0x7f7f7f7f7f7f7f7fll;
int n,kmp[L],ext[L];
long long dis[logM][N][N],val[logM][N][N];
char pool[L],*names[L];
inline void extended_kmp(char *s,int *ext){
	for(int i=1,p=0;s[i];i++){
		if(i<p+ext[p]){
			ext[i]=min(p+ext[p]-i,ext[i-p]);
		}
		while(s[ext[i]]==s[i+ext[i]]){
			ext[i]++;
		}
		if(i+ext[i]>p+ext[p]){
			p=i;
		}
	}
}
inline int cal_len(char *s,char *t,int *len){
	if(s==t){
		for(int i=0;s[i];i++){
			if(s[i+len[i]]==0){
				return len[i];
			}
		}
		return 0;
	}
	for(int i=0,p=0;s[i];i++){
		if(i<p+ext[p]){
			ext[i]=min(p+ext[p]-i,len[i-p]);
		}else{
			ext[i]=0;
		}
		while(t[ext[i]]&&s[i+ext[i]]==t[ext[i]]){
			ext[i]++;
		}
		if(s[i+ext[i]]==0){
			return ext[i];
		}
		if(i+ext[i]>p+ext[p]){
			p=i;
		}
	}
	return 0;
}
inline void floyd(long long disa[N][N],long long disb[N][N],long long ndis[N][N]){
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			if(disa[i][k]<INF){
				for(int j=1;j<=n;j++){
					if(disb[k][j]<INF){
						apmin(ndis[i][j],disa[i][k]+disb[k][j]);
					}
				}
			}
		}
	}
}
int main(){
	n=ni();
	int times=ni(),p=0;
	memset(pool,0,sizeof(pool));
	memset(kmp,0,sizeof(kmp));
	char c;
	names[1]=pool;
	for(int i=2;i<=n+1;i++){
		names[i]=names[i-1];
		while(!is_letter(c=getchar()));
		while((*(names[i]++))=c,is_letter(c=getchar()));
		names[i]++;
		extended_kmp(names[i-1],kmp+(int)(names[i-1]-pool));
	}
	memset(val,127,sizeof(val));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			val[0][i][j]=(long long)(names[j+1]-names[j]-1)-cal_len(names[i],names[j],kmp+(int)(names[j]-pool));
		}
	}
	memset(dis,127,sizeof(dis));
	memset(dis[0],0,sizeof(dis[0]));
	times--;
	for(int i=0;(1<<i)<=times;i++){
		if(i){
			floyd(val[i-1],val[i-1],val[i]);
		}
		if((times>>i)&1){
			if(p){
				floyd(dis[p-1],val[i],dis[p]);
			}else{
				memcpy(dis[0],val[i],sizeof(dis[0]));
			}
			p++;
		}
	}
	p--;
	long long ans=LINF;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			apmin(ans,dis[p][i][j]+(long long)(names[i+1]-names[i]-1));
		}
	}
	printf("%d\n",ans);
}
