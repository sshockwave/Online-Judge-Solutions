#include <iostream>
#include <cstdio>
#include <cstring>
#define N 220
using namespace std;
bool rule[5][5]={
	{0,0,1,1,0},
	{1,0,0,1,0},
	{0,1,0,0,1},
	{0,0,1,0,1},
	{1,1,0,0,0}
};
int a[N],b[N];
int main(){
	int n,na,nb,cnta=0,cntb=0;
	scanf("%d%d%d",&n,&na,&nb);
	for(int i=0;i<na;i++){
		scanf("%d",a+na);
	}
	for(int i=0;i<nb;i++){
		scanf("%d",b+nb);
	}
	for(int i=0;i<n;i++){
		cnta+=rule[a[i%na]][b[i%nb]];
		cntb+=rule[b[i%nb]][a[i%na]];
	}
	printf("%d %d",cnta,cntb);
}
