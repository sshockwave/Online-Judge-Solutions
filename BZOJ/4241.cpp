#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 100010
#define D (N*2)
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	for(;is_num(c);i=i*10-'0'+c,c=getchar());
	return i;
}
struct interval{
	int l,r,i;
}query[N];
bool operator < (interval a,interval b){
	if(a.l==b.l){
		return a.r<b.r;
	}
	return a.l<b.l;
}
struct point{
	int x,*bln;
}coor[N];
bool operator < (point a,point b){
	return a.x<b.x;
}
int day[N],ans[N];
int main(){
	int n=ni(),tot=ni();
	for(int i=1;i<=n;i++){
		coor[i].x=day[i]=ni();
		coor[i].bln=day+i;
	}
	sort(coor+1,coor+1+n);
	for(int i=1,last=-1,cur=0;i<=n;i++){
		if(coor[i].x!=last){
			last=coor[i].x;
			cur++;
		}
		*(coor[i].bln)=cur;
	}
	cout<<"Organized:";
	for(int i=1;i<=n;i++){
		cout<<day[i]<<" ";
	}
	cout<<endl;
	for(int i=0;i<tot;i++){
		query[i].l=ni(),query[i].r=ni(),query[i].i=i;
	}
	sort(query,query+tot);
	cout<<"Queries:";
	for(int i=0;i<tot;i++){
		cout<<"("<<query[i].l<<","<<query[i].r<<"):"<<query[i].i<<" ";
	}
	cout<<endl;
}
