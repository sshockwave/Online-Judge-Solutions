#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct person{
	int a,b;
}node[1010];
int digit[10010],cur[10010],ans[10010],dtop=1,ctop=0,atop=0;
inline void maintain(){
	for(int i=0;i<dtop;i++){
		digit[i+1]+=digit[i]/10;
		digit[i]%=10;
	}
	for(;digit[dtop];dtop++){
		digit[dtop+1]+=digit[dtop]/10;
		digit[dtop]%=10;
	}
}
bool diycmp(const person &a,const person &b){
	return a.a*a.b<b.a*b.b;
}
inline bool anscmp(){
	if(ctop==atop){
		for(int i=ctop;i>=0;i--){
			if(cur[i]!=ans[i]){
				return cur[i]>ans[i];
			}
		}
	}
	return ctop>atop;
}
int main(){
//	freopen("game.in","r",stdin);
//	freopen("game.out","w",stdout);
	int n,r;
	cin>>n;
	for(int i=0;i<=n;i++){
		cin>>node[i].a>>node[i].b;
	}
	sort(node+1,node+n+1,diycmp);
	memset(digit,0,sizeof(digit));
	digit[0]=node[0].a;
	maintain();
	for(int i=1;i<=n;i++){
		//divide
		r=0;
		for(int j=dtop-1;j>=0;j--){
			r=r*10+digit[j];
			cur[j]=r/node[i].b;
			r%=node[i].b;
		}
		for(ctop=dtop-1;ctop>=0&&!cur[ctop];ctop--);
		ctop++;
		if(anscmp()){
			//copy
			for(int j=0;j<ctop;j++){
				ans[j]=cur[j];
			}
			atop=ctop;
		}
		//multiply
		for(int j=0;j<dtop;j++){
			digit[j]*=node[i].a;
		}
		maintain();
	}
	while(atop--){
		cout<<ans[atop];
	}
}
