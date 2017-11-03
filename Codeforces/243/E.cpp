#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=510;
char mat[N][N],*s;
int perm[N],ps=0;
namespace T{
	const int N=510<<3;
	vector<int>son[N];
	int tp[N],rt,n;//0:any 1:sort
	inline int nn(){
		return ++n;
	}
	int stat[N];//0:none 1:partial 2:full
	int dfs(int x){
		if(tp[x]==-1){
			stat[x]=(s[x]=='1')<<1;
			return x;
		}
		if(son[x].size()==0){
			return 0;
		}
		if(son[x].size()==1){
			return dfs(son[x][0]);
		}
		vector<int>vec=son[x];
		son[x].clear();
		unsigned int cnt[3]={0};
		for(int i=0,n=vec.size();i<n;i++){
			int v=dfs(vec[i]);
			if(v){
				son[x].push_back(v);
				cnt[stat[v]]++;
			}
		}
		stat[x]=cnt[0]==vec.size()?0:cnt[2]==vec.size()?2:1;
		return son[x].size()==1?son[x][0]:x;
	}
	inline bool valid(vector<int>&vec){
		int phase=1;
		for(int i=0,n=vec.size();i<n;i++){
			int v=vec[i];
			if(stat[v]==0){
				phase=2;
			}else{
				if(phase==2){
					return false;
				}
				if(stat[v]==1){
					phase=2;
				}
			}
		}
		return true;
	}
	void tie(int x,int side,int q){//1:left 2:right 3:both
		int node[]={nn(),nn(),nn()};
		for(int i=0,n=son[x].size();i<n;i++){
			son[node[stat[son[x][i]]]].push_back(son[x][i]);
		}
		if(side==3&&son[node[1]].size()==1&&son[node[2]].size()==0){
			tie(son[node[1]][0],3,son[node[1]][0]);
			return;
		}
		if(tp[x]==0){
			tp[node[0]]=tp[node[2]]=0;
			son[x].clear();
			if(side==2||side==3){
				son[q].push_back(node[0]);
			}
			if(x==q){
				assert(side==3);
				q=nn();
				tp[q]=1;
				son[x].push_back(q);
			}
			if((side==2||side==3)&&!son[node[1]].empty()){
				tie(son[node[1]][son[node[1]].size()-1],2,q);
				son[node[1]].pop_back();
			}
			son[q].push_back(node[2]);
			if((side==1||side==3)&&!son[node[1]].empty()){
				tie(son[node[1]][son[node[1]].size()-1],1,q);
				son[node[1]].pop_back();
			}
			if(!son[node[1]].empty()){
				throw 1;
			}
			if(side==1){
				son[q].push_back(node[0]);
			}
		}else{
			int phase=0;
			if(side!=3){
				if(!valid(son[x])){
					reverse(son[x].begin(),son[x].end());
					if(!valid(son[x])){
						throw 1;
					}
				}
				if(side==2){
					reverse(son[x].begin(),son[x].end());
				}
			}
			vector<int>vec=son[x];
			son[x].clear();
			for(int i=0,n=vec.size();i<n;i++){
				int v=vec[i];
				if(stat[v]==0){
					son[q].push_back(v);
					if(phase){
						phase=2;
					}
				}else if(stat[v]==1){
					if(phase==0){
						tie(v,2,q);
						phase=1;
					}else if(phase==1){
						tie(v,1,q);
						phase=2;
					}else throw 1;
				}else{
					son[q].push_back(v);
					if(phase==0){
						phase=1;
					}else if(phase==2){
						throw 1;
					}
				}
			}
		}
	}
	inline void putperm(int x){
		if(tp[x]==-1){
			perm[++ps]=x;
		}else for(int i=0,n=son[x].size();i<n;putperm(son[x][i++]));
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("matrix.in","r",stdin);
	freopen("matrix.out","w",stdout);
#endif
	int n=ni;
	T::rt=T::n=n+1;
	T::tp[T::rt]=0;
	for(int i=1;i<=n;i++){
		T::tp[i]=-1;
		T::son[T::rt].push_back(i);
	}
	try{
		for(int i=1;i<=n;i++){
			scanf("%s",(s=mat[i])+1);
			T::rt=T::dfs(T::rt);
			T::tie(T::rt,3,T::rt);
		}
		puts("YES");
		T::putperm(T::rt);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				putchar(mat[i][perm[j]]);
			}
			putchar('\n');
		}
	}catch(int err){
		puts("NO");
	}
	return 0;
}
