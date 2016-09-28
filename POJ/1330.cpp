#include <iostream>
#include <cstdio>
#include <cstring>
#define fort(i,n) for(int i=0;i<(n);i++)
#define clr(x) memset(x,0,sizeof(x))
#define debug(x) {cerr<<#x<<"="<<x<<endl;}
#define MAXN 10010
using namespace std;
int child[MAXN],bro[MAXN],f[MAXN],qa,qb;
bool visited[MAXN],notroot[MAXN];
int findfather(int x){
	if(f[x]){
		return f[x]=findfather(f[x]);
	}
	return x;
}
int dfs(int node){
	visited[node]=true;
	if(qa==node&&visited[qb]){
		return findfather(qb);
	}else if(qb==node&&visited[qa]){
		return findfather(qa);
	}
	int t,p=child[node];
	while(p!=0){
		t=dfs(p);
		if(t){
			return t;
		}
		f[p]=node;
		p=bro[p];
	}
	return 0;
}
int lca(int n){
	clr(child);
	clr(bro);
	clr(f);
	clr(visited);
	clr(notroot);
	int p,c;
	fort(i,n-1){
		cin>>p>>c;
		bro[c]=child[p];
		child[p]=c;
		notroot[c]=true;
	}
	cin>>qa>>qb;
	int x=1;
	for(;x<=n;x++){
		if(!notroot[x]){
			break;
		}
	}
	return dfs(x);
}
int main(){
	int tot,n;
	cin>>tot;
	while(tot--){
		cin>>n;
		cout<<lca(n)<<endl;
	}
}
