#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#define M 55
#define N 1010
#define INF 0x7f7f7f7f
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
int res[M],need[N],_need[N],sum,n,m;
int dfs(int x,int extra,int ln,int li){
	if(x<0){
		return true;
	}
	if(extra<0){
		return false;
	}
	for(int i=ln==need[x]?li:0;i<m;i++){
		if(res[i]>need[x]){
			res[i]-=need[x];
			if(dfs(x-1,extra-(res[i]<need[0]?res[i]:0),need[x],i)){
				res[i]+=need[x];
				return true;
			}
			res[i]+=need[x];
		}
	}
	return false;
}
int main(){
	m=ni();
	sum=0;
	for(int i=0;i<m;i++){
		sum+=(res[i]=ni());
	}
	n=ni();
	for(int i=0,last=0;i<n;i++){
		last+=(need[i]=ni());
		_need[i]=last;
	}
	sort(res,res+m);
	sort(need,need+n);
	int l=0,r=n,mid;
	while(l<r){
		mid=((l+r)>>1)+1;
		if(dfs(mid-1,sum-_need[mid-1],INF,0)){
			l=mid;
		}else{
			r=mid-1;
		}
	}
	printf("%d",l);
}
