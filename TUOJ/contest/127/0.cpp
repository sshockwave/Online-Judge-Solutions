#include "sort.h"
#include <vector>
#define cout cerr
const int N=524288,K=16;
std::vector<int>son[N+1];
int que[K+1],lst[K];
void sort(int,int n,int k,int* a){
	son[n].clear();
	for(int i=0;i<n;i++){
		son[i].clear();
		son[n].push_back(i);
	}
	for(;!son[n].empty();){
		if(son[n].size()==1){
			a[0]=son[n][0];
			son[n]=son[a[0]];
			son[a[0]].clear();
			++a;
			continue;
		}
		int qh=0,qt=0;
		que[qt++]=n;
		for(;qh<qt;){
			const int x=que[qh++];
			for(;qt<=k&&!son[x].empty();son[x].pop_back()){
				que[qt++]=son[x].back();
			}
		}
		super_sort(que+1,qt-1,lst);
		for(int i=0;i<qt-1;i++){
			son[i?lst[i-1]:n].push_back(lst[i]);
		}
	}
}
