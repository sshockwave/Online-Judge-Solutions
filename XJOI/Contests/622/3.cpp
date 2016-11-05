#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set> 
#define N 100010
using namespace std;
vector<int>con[N];
set<int>s;
int walk[N][20],logt[N],dfn[N],pos[N],dtop=1,dep[N];
bool occ[N];
void dfs(int x){
	dep[x]=dep[walk[x][0]]+1;
	for(int &i=logt[x];walk[x][i];i++){
		walk[x][i+1]=walk[walk[x][i]][i];
	}
	sort(con[x].begin(),con[x].end());
	for(vector<int>::iterator it=con[x].begin();it!=con[x].end();it++){
		if((*it)!=walk[x][0]){
			walk[*it][0]=x;
			dfs(*it);
		}
	}
	dfn[x]=dtop++;
	pos[dfn[x]]=x;
	s.insert(dfn[x]);
}
int main(){
	int n,t,x,y;
	scanf("%d%d",&n,&t);
	for(int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		con[x].push_back(y);
		con[y].push_back(x);
	}
	memset(walk,0,sizeof(walk));
	memset(logt,0,sizeof(logt));
	memset(occ,0,sizeof(occ));
	dep[0]=0;
	dfs(1);
	while(t--){
		scanf("%d%d",&y,&x);
		if(y==1){
			for(int i=1;i<x;i++){
				occ[*s.begin()]=true;
				s.erase(s.begin());
			}
			printf("%d\n",pos[*s.begin()]);
			occ[*s.begin()]=true;
			s.erase(s.begin());
		}else{
			int at=x;
			for(int i=logt[x];i>=0;i--){
				if(walk[at][i]&&occ[dfn[walk[at][i]]]){
					at=walk[at][i];
				}
			}
			printf("%d\n",dep[x]-dep[at]);
			occ[dfn[at]]=false;
			s.insert(dfn[at]);
		}
	}
}
