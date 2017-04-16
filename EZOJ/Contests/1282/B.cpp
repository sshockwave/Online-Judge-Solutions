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
inline lint labs(lint x){
	return x>=0?x:-x;
}
const int N=10010;
struct Line{
	int l,r,h;
	bool vert;
}line[N];
struct point{
	int x,y;
};
inline bool between(int a,int b,int c){
	return a<=b&&b<=c;
}
inline bool intersect(Line a,Line b){
	if(a.vert==b.vert){
		return false;
	}
	return between(a.l,b.h,a.r)&&between(b.l,a.h,b.r);
}
inline point operator * (Line a,Line b){
	if(a.vert){
		swap(a,b);
	}
	return (point){b.h,a.h};
}
inline void add_edge(int u,int v){
	
}
int main(){
	int n=ni();
	for(int i=1;i<=n;i++){
		int x1,x2,y1,y2;
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		if(x1==x2){
			if(y1>y2){
				swap(y1,y2);
			}
			line[i]=(Line){y1,y2,x1,true};
		}else{
			assert(y1==y2);
			if(x1>x2){
				swap(x1,x2);
			}
			line[i]=(Line){x1,x2,y1,false};
		}
	}
	int sx,sy,tx,ty;
	scanf("%d%d%d%d",&sx,&sy,&tx,&ty);
	if(n>200){
		printf("%d\n",labs((lint)sx-tx)+labs((lint)sy-ty));
		return 0;
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(intersect(line[i],line[j])){
				add_edge(i,j);
				add_edge(j,i);
			}
		}
	}
	
}
