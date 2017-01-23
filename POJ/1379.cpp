#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>
#define M 1010
#define G 30
#define EPS 1e-4
#define PI 3.1415926535898
using namespace std;
inline bool isNum(char c){
	return c>='0'&&c<='9';
}
inline int nextInt(){
	int i=0;char c;
	while(!isNum(c=getchar()));
	for(;isNum(c);i=i*10-'0'+c,c=getchar());
	return i;
}
int w,h,m;
inline double random(){
	return (double)rand()/(double)RAND_MAX;
}
inline void apmin(double &a,double b){
	if(a>b){
		a=b;
	}
}
struct coor{
	double x,y,d;
	bool valid(){
		return x>=0&&x<=w&&y>=0&&y<=h;
	}
	void cal();
	coor go(double delta){
		double theta=random()*2*PI;
		coor res;
		res.x=x+delta*cos(theta);
		res.y=y+delta*sin(theta);
		res.cal();
		return res;
	}
	coor iterate(double delta){
		coor res=*this,tmp;
		for(int i=0;i<G;i++){
			tmp=go(delta);
			if(tmp.valid()&&tmp.d>res.d){
				res=tmp;
			}
		}
		return res;
	}
}holes[M];
void coor::cal(){
	d=1e50;
	for(int i=0;i<m;i++){
		apmin(d,(holes[i].x-x)*(holes[i].x-x)+(holes[i].y-y)*(holes[i].y-y));
	}
}
inline coor anneal(){
	coor res;
	res.x=random()*w;
	res.y=random()*h;
	res.cal();
	for(double delta=max(w,h);delta>EPS;delta*=0.8){
		res=res.iterate(delta);
	}
	return res;
}
int main(){
	srand(time(0));
	for(int tot=nextInt();tot--;){
		w=nextInt(),h=nextInt(),m=nextInt();
		for(int i=0;i<m;i++){
			holes[i].x=nextInt(),holes[i].y=nextInt();
		}
		coor ans,tmp;
		ans.d=0;
		for(int i=0;i<G;i++){
			tmp=anneal();
			if(tmp.d>ans.d){
				ans=tmp;
			}
		}
		printf("The safest point is (%.1f, %.1f).\n",(double)round(ans.x*10)/10.0,(double)round(ans.y*10)/10.0);
	}
}
