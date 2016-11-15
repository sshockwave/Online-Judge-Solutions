#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#define N 310
using namespace std;
int color[N][4],n;
map<int,bool>odd;
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
int dfs(int x,int cnt){
	if(x==n+1){
		for(map<int,bool>::iterator it=odd.begin();it!=odd.end();it++){
			if(it->second){
				return 0;
			}
		}
		return cnt;
	}
	int ans=0;
	odd[color[x][0]]=!odd[color[x][0]];
	odd[color[x][1]]=!odd[color[x][1]];
	apmax(ans,dfs(x+1,cnt+1));
	odd[color[x][0]]=!odd[color[x][0]];
	odd[color[x][1]]=!odd[color[x][1]];
	
	odd[color[x][2]]=!odd[color[x][2]];
	odd[color[x][3]]=!odd[color[x][3]];
	apmax(ans,dfs(x+1,cnt+1));
	odd[color[x][2]]=!odd[color[x][2]];
	odd[color[x][3]]=!odd[color[x][3]];
	
	apmax(ans,dfs(x+1,cnt));
	
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d%d",&color[i][0],&color[i][1],&color[i][2],&color[i][3]);
		odd[color[i][0]]=false;
		odd[color[i][1]]=false;
		odd[color[i][2]]=false;
		odd[color[i][3]]=false;
	}
	printf("%d",dfs(1,0));
}
