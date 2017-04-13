#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int N=1010;
int w[N],pre[N],f[N],que[N],qhead,qtail;
inline bool worse(int p,int q,int k){
	return f[q]-f[p]<k*(pre[q]-pre[p]);
}
inline bool ascend(int p,int q,int r){
	return (f[r]-f[q])*(pre[q]-pre[p])>(f[q]-f[p])*(pre[r]-pre[q]);
}
int main(){
	pre[0]=0;
	for(int tot=ni();tot--;){
		int n=ni();
		for(int i=1;i<=n;i++){
			pre[i]=pre[i-1]+ni();
			w[i]=ni();
		}
		qhead=0,qtail=0;
		que[qtail++]=0;
		for(int i=1,j;i<=n;i++){
			for(;qhead+1<qtail&&worse(que[qhead],que[qhead+1],w[i]);qhead++);
			j=que[qhead];
			f[i]=f[j]+w[i]*(pre[i]-pre[j]+10);
			for(;qhead+1<qtail&&!ascend(que[qtail-2],que[qtail-1],i);qtail--);
			que[qtail++]=i;
		}
		printf("%d\n",f[n]);
	}
}
