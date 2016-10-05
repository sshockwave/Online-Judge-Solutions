#include <iostream>
#include <cstdio>
#include <cstring>
#define N 35
#define G 20
using namespace std;
char seq[G*3];
int win[35],g,r,b,pre[N],nxt[N],total,n;
inline void test(){
//	seq[total]=0;
//	cout<<"TEST:"<<seq<<endl;
	for(int i=0;i<n;i++){
		pre[i]=i-1;
		nxt[i]=i+1;
	}
	pre[0]=n-1,nxt[n-1]=0;
	int p=0;
	bool counter=true;
	for(int i=0;i<total;i++){
		if(seq[i]=='r'){
			counter=!counter;
		}else if(seq[i]=='b'){
			nxt[pre[p]]=nxt[p];
			pre[nxt[p]]=pre[p];
		}
		if(counter){
			p=nxt[p];
		}else{
			p=pre[p];
		}
	}
	win[p]++;
}
void dfs(int pos){
	if(pos==total){
		test();
		return;
	}
	if(g>0){
		g--;
		seq[pos]='g';
		dfs(pos+1);
		g++;
	}
	if(r>0){
		r--;
		seq[pos]='r';
		dfs(pos+1);
		r++;
	}
	if(b>0){
		b--;
		seq[pos]='b';
		dfs(pos+1);
		b++;
	}
}
int main(){
	freopen("winner.in","r",stdin);
//	freopen("winner.out","w",stdout);
	int k;
	for(scanf("%d",&k);k--;){
		memset(win,0,sizeof(win));
		scanf("%d%d%d%d",&n,&g,&r,&b);
		total=g+r+b;
		dfs(0);
		int p=0;
		for(int i=0;i<n;i++){
			if(win[i]>win[p]){
				p=i;
			}
		}
		printf("%d\n",p);
	}
}
