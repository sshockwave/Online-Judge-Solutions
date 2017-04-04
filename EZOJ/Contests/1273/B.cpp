#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
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
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
const int N=35;
struct Point{
	int x,y;
}pt[N],choose[N],stk[N];
bool operator < (Point a,Point b){
	if(a.x==b.x){
		return a.y<b.y;
	}
	return a.x<b.x;
}
Point operator - (Point a,Point b){
	return (Point){a.x-b.x,a.y-b.y};
}
inline int cross(Point a,Point b){
	return a.x*b.y-a.y*b.x;
}
inline bool turn_left(Point a,Point b,Point c){
	return cross(b-a,c-b)>=0;
}
inline int convex(int n,Point *pt){
	int stop1=0,stop2=0;
	for(int i=0;i<n;){
		if(stop1<2||turn_left(stk[stop1-2],stk[stop1-1],pt[i])){
			stk[stop1++]=pt[i++];
		}else{
			stop1--;
		}
	}
	for(int i=n-1;i>=0;){
		if(stop2<2||turn_left(stk[stop2-2],stk[stop2-1],pt[i])){
			stk[stop2++]=pt[i--];
		}else{
			stop2--;
		}
	}
	return stop1+stop2-2;
}
int main(){
	int n=ni(),ans=0;
	if(n<=3){
		printf("%d",n);
		return 0;
	}
	for(int i=0;i<n;i++){
		scanf("%d%d",&pt[i].x,&pt[i].y);
	}
	sort(pt,pt+n);
	for(int i=0,top=(1<<n),ctop;i<top;i++){
		ctop=0;
		for(int j=0;j<n;j++){
			if((i>>j)&1){
				choose[ctop++]=pt[j];
			}
		}
		apmax(ans,ctop<=3?ctop:convex(ctop,choose));
	}
	printf("%d",ans);
}
