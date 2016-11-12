#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#define P 100010
#define K 1000010
#define MOD 998244353
using namespace std;
int a[K+P],start[P],w;
vector<int>ext[P];
vector<int>::iterator status[P];
long long fac=1,ans=0;
void dfs(int x){
	if(status[x]==ext[x].end()){
		ans=(ans+fac*x)%MOD;
		fac=(fac*w)%MOD;
		return;
	}
	int p=start[*status[x]];
	status[x]++;
	for(;a[p];p++){
		dfs(a[p]);
	}
	status[x]--;
}
int main(){
	int p,q,k,c;
	scanf("%d%d%d",&p,&q,&w);
	for(int i=1,j=0;i<=q;i++,j++){
		scanf("%d%d",&k,&c);
		ext[c].push_back(i);
		for(start[i]=j;j-start[i]<k;j++){
			scanf("%d",a+j);
		}
		a[j]=0;
	}
	for(int i=1;i<=p;i++){
		status[i]=ext[i].begin();
	}
	dfs(1);
	printf("%d",ans);
}
