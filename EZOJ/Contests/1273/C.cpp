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
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
const int N=100010;
struct Operation{
	int delta,t;
}op[N];
bool operator < (Operation a,Operation b){
	return a.t<b.t;
}
bool igndown[N],ignup[N];
int main(){
	int n=ni(),mx=ni(),target=ni();
	for(int i=1;i<=n;i++){
		char c;
		while(c=getchar(),c!='+'&&c!='-');
		op[i].delta=(c=='+'?1:(-1));
		op[i].t=ni();
	}
	sort(op+1,op+n+1);
	int low=0,high=mx,hpile=1;
	memset(igndown,0,sizeof(igndown));
	memset(ignup,0,sizeof(ignup));
	for(int i=1;i<=n;i++){
		low+=op[i].delta;
		high+=op[i].delta;
		if(high>mx){
			high=mx;
			hpile=min(hpile+1,mx+1);
			ignup[i]=true;
			if(low>mx){
				low=mx;
			}
		}
		if(low<0){
			low=0;
			igndown[i]=true;
			if(high<0){
				high=0;
				hpile=mx+1;
			}
		}
	}
	if(low<=target&&target<=high){
		printf("infinity %d",target==high?mx:(mx-hpile-(high-target)+1));
	}
}
