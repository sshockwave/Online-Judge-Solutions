#include <iostream>
#include <cstdio>
#include <cstring>
//#include <ctime>
#define D 1010
using namespace std;
int lend[D],rend[D],bro[D],ntop,root;
void del(int &x,int a,int b){//del [a,b] in this section
	if(a>b||x==-1){
		return;
	}
	if(a==0){
		if(b<rend[x]-lend[x]){
			lend[x]+=b+1;
		}else{
			b-=rend[x]-lend[x]+1;
			x=bro[x];
			del(x,0,b);
		}
	}else if(a>rend[x]-lend[x]){
		a-=rend[x]-lend[x]+1;
		b-=rend[x]-lend[x]+1;
		del(bro[x],a,b);
	}else if(b>rend[x]-lend[x]){
		b-=rend[x]-lend[x]+1;
		rend[x]=lend[x]+a-1;
		del(bro[x],0,b);
	}else if(b<rend[x]-lend[x]){
		lend[ntop]=lend[x]+b+1,rend[ntop]=rend[x];
		bro[ntop]=bro[x];
		bro[x]=ntop++;
		rend[x]=lend[x]+a-1;
	}else{
		rend[x]=lend[x]+a-1;
	}
}
inline int query(int q){
	for(int x=root;~x;x=bro[x]){
		if(q<=rend[x]-lend[x]){
			return lend[x]+q;
		}else{
			q-=rend[x]-lend[x]+1;
		}
	}
	return -1;
}
int main(){
	freopen("removal.in","r",stdin);
	freopen("removal.out","w",stdout);
	int tot,n,m,d,lo,hi,total;
	for(scanf("%d",&tot);tot--;){
		ntop=0;
		scanf("%d%d%d",&n,&m,&d);
		lend[ntop]=1,rend[ntop]=n;
		bro[ntop]=-1;
		root=ntop++;
		while(d--){
			scanf("%d-%d",&lo,&hi);
			del(root,lo-1,hi-1);
		}
		printf("%d\n",query(m-1));
	}
//	printf("\n%dms",clock());
}
