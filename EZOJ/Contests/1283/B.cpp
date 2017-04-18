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
const int N=1000010;
int lnk[N];
int posx[N],posy[N];
int main(){
	memset(lnk,0,sizeof(lnk));
	lnk[1]=2,lnk[2]=1,lnk[3]=3;
	posx[0]=posy[0]=3;
	posx[1]=1,posy[1]=2;
	for(int i=4,p=2;i+p<N;i++){
		if(lnk[i]){
			continue;
		}
		assert(lnk[p+i]==0);
		lnk[i]=p+i,lnk[p+i]=i;
		posx[p]=i,posy[p]=i+p;
		p++;
	}
	for(int tot=ni(),n,m;tot--;){
		n=ni(),m=ni();
		if(n==1&&m==1){
			puts("YES 0 0");
		}else if(lnk[n]==m||lnk[m]==n){
			puts("NO");
		}else{
			if(lnk[n]&&lnk[n]<=m){
				printf("YES %d %d\n",0,m-lnk[n]);
			}else if(lnk[m]&&lnk[m]<=n){
				printf("YES %d %d\n",n-lnk[m],0);
			}else{
				int sub=n>m?(n-m):(m-n);
				int nx=posx[sub],ny=posy[sub];
				if(n>m){
					swap(nx,ny);
				}
				printf("YES %d %d\n",n-nx,m-ny);
			}
		}
	}
}
