#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 20000
using namespace std;
int f[N],stonepos[110];
bool stone[N];
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int main(){
	int l,s,t,m,last=0,space;
	cin>>l>>s>>t>>m;
	space=s/gcd(s,t)*t;
	memset(f,0,sizeof(f));
	memset(stone,0,sizeof(stone));
	for(int i=1;i<=m;i++){
		cin>>stonepos[i];
	}
	sort(stonepos,stonepos+m);
	for(int i=1;i<=m;i++){
		if(stonepos[i]-last>space){
			last+=space;
		}else{
			last+=stonepos[i]-stonepos[i-1];
		}
		stone[last]=true;
	}
	for(int i=0;i<=last;i++){
		
	}
	cout<<f[last];
}
