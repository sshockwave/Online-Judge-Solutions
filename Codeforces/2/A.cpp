#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int main(){
	int n;
	cin>>n;
	char name[n][35],op[n][35];
	int score[n],max=-2147483647,top,i,temp,opscore[n],mtop=0,optoid[n];
	bool exist,ismaxscore[n];
	memset(score,0,sizeof(score));
	memset(ismaxscore,0,sizeof(ismaxscore));
	for(top=0;top<n;top++){
		cin>>op[top];
		exist=false;
		for(i=0;i<mtop;i++){
			if(strcmp(name[i],op[top])==0){
				exist=true;
				break;
			}
		}
		if(!exist){
			strcpy(name[mtop++],op[top]);
		}
		cin>>opscore[top];
		score[i]+=opscore[top];
		optoid[top]=i;
	}
	for(int i=0;i<top;i++){
		if(score[i]>max){
			max=score[i];
		}
	}
	for(int i=0;i<top;i++){
		if(score[i]==max){
			ismaxscore[i]=true;
		}
	}
	int gettomaxround[mtop];
	memset(score,0,sizeof(score));
	for(int j=0;j<mtop;j++){
		gettomaxround[j]=-1;
	}
	for(int round=0;round<n;round++){
		i=optoid[round];
		if(ismaxscore[i]){
			score[i]+=opscore[round];
			if(score[i]>=max){
				if(gettomaxround[i]==-1){
					gettomaxround[i]=round;
				}
			}
		}
	}
	int mint=2000000000,minp;
	for(int p=0;p<mtop;p++){
		if(ismaxscore[p]){
			if(gettomaxround[p]<mint){
				mint=gettomaxround[p];
				minp=p;
			}
		}
	}
	cout<<name[minp];
}