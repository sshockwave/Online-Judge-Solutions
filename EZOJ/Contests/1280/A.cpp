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
const int N=2010;
int perm[N],pos[N];
bool valid[N][N];
void dfs1(int,int,int,int);
void dfs2(int l,int r,int a,int b,int c,int d){
	if(l+1>=r||valid[l][r]){
		return;
	}
	if(a>b){
		dfs1(l,r,c,d);
		return;
	}
	if(c>d){
		dfs1(l,r,a,b);
		return;
	}
	valid[l][r]=true;
	if(pos[l]==a){
		dfs2(l+1,r,a+1,b,c,d);
	}else if(pos[l]==b){
		dfs2(l+1,r,a,b-1,c,d);
	}else if(pos[l]==c){
		dfs2(l+1,r,a,b,c+1,d);
	}else if(pos[l]==d){
		dfs2(l+1,r,a,b,c,d-1);
	}
	if(pos[r]==a){
		dfs2(l,r-1,a+1,b,c,d);
	}else if(pos[r]==b){
		dfs2(l,r-1,a,b-1,c,d);
	}else if(pos[r]==c){
		dfs2(l,r-1,a,b,c+1,d);
	}else if(pos[r]==d){
		dfs2(l,r-1,a,b,c,d-1);
	}
}
void dfs1(int l,int r,int a,int b){
	if(l+1>=r||valid[l][r]){
		return;
	}
	assert(a<=b);
	valid[l][r]=true;
	dfs2(l+1,r,a,pos[l]-1,pos[l]+1,b);
	dfs2(l,r-1,a,pos[r]-1,pos[r]+1,b);
}
bool isset[N];
inline int brute(int n){
	int ans=0;
	isset[0]=false;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			memset(isset+1,0,n<<2);
			for(int k=i;k<=j;k++){
				isset[pos[k]]=true;
			}
			int ent=0;
			for(int k=1;k<=n;k++){
				if(!isset[k-1]&&isset[k]){
					ent++;
				}
			}
			if(ent<=2){
				ans++;
			}
		}
	}
	return ans;
}
int main(){
	int n=ni();
	bool flag=true;
	for(int i=1;i<=n;i++){
		pos[perm[i]=ni()]=i;
		if(perm[i]!=i){
			flag=false;
		}
	}
	if(flag){
		printf("%lld\n",(lint)n*(n-1)/2);
		return 0;
	}
	if(n<=20){
		printf("%d\n",brute(n));
		return 0;
	}
	memset(valid,0,sizeof(valid));
	dfs1(1,n,1,n);
	lint ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(valid[i][j]){
				ans++;
			}
		}
	}
	printf("%lld",ans+n-1);
}
