#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;
typedef long long lint;
typedef long double ld;
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
inline ld sqr(ld x){
	return x*x;
}
inline lint sqr(lint x){
	return x*x;
}
const int N=55;
const ld EPS=1e-9;
bool inque[N];
ld low[N],high[N];
queue<int>q;
struct Point{
	lint x,y;
	inline friend Point operator - (const Point &a,const Point &b){
		return (Point){a.x-b.x,a.y-b.y};
	}
	inline lint d2(){
		return x*x+y*y;
	}
}pt[N],s,t;
ld dis[N][N];
class CandyOnDisk{
	public:
	string ableToAchieve(vector<int>x,vector<int>y,vector<int>r,int sx,int sy,int tx,int ty){
		if(sx==tx&&sy==ty){
			return "YES";
		}
		int n=x.size();
		s.x=sx,s.y=sy;
		memset(inque,0,sizeof(inque));
		for(int i=0;i<n;i++){
			pt[i].x=x[i];
			pt[i].y=y[i];
			if((s-pt[i]).d2()<=(lint)r[i]*r[i]){
				q.push(i);
				inque[i]=true;
				low[i]=high[i]=sqrt((s-pt[i]).d2());
			}else{
				low[i]=high[i]=-1;
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				dis[i][j]=sqrt((pt[i]-pt[j]).d2());
			}
		}
		while(!q.empty()){
			int x=q.front();
			q.pop();
			assert(high[x]>-EPS&&low[x]>-EPS);
			for(int i=0;i<n;i++){
				if(pt[i].x==pt[x].x&&pt[i].y==pt[x].y){
					continue;
				}
				if(dis[i][x]+EPS<high[x]+r[i]){
					if(high[i]<-EPS||high[i]+EPS<min(dis[i][x]+r[x],(ld)r[i])){
						high[i]=min(dis[i][x]+r[x],(ld)r[i]);
						if(!inque[i]){
							inque[i]=true;
							q.push(i);
						}
					}
					if(low[i]<-EPS||low[i]-EPS>max(dis[i][x]-r[x],(ld)0)){
						low[i]=max(dis[i][x]-r[x],(ld)0);
						if(!inque[i]){
							inque[i]=true;
							q.push(i);
						}
					}
					bool flag=false;
					if(high[i]<-EPS||high[x]+EPS<min(dis[i][x]+r[i],(ld)r[x])){
						high[x]=min(dis[i][x]+r[i],(ld)r[x]);
						flag=true;
					}
					if(low[i]<-EPS||low[x]-EPS>max(dis[i][x]-r[i],(ld)0)){
						low[x]=max(dis[i][x]-r[i],(ld)0);
						flag=true;
					}
					if(flag){
						i=-1;
					}
				}
			}
			inque[x]=false;
		}
		for(int i=0;i<n;i++){
			double d=sqrt(sqr((lint)x[i]-tx)+sqr((lint)y[i]-ty));
			if(d>low[i]-EPS&&d<high[i]+EPS){
				return "YES";
			}
		}
		return "NO";
	}
};
vector<int>x,y,r;
int main(){
	x.push_back(0);
	y.push_back(0);
	r.push_back(1);
	cout<<CandyOnDisk().ableToAchieve(x,y,r,571,571,571,571)<<endl;
}