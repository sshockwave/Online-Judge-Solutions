#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char from[15][25],to[15][25],a[25],b[25],froml[15],tol[15];
int ttop=0;
bool match(char *sub,char *tem){
	for(;(*sub)&&(*tem);sub++,tem++){
		if((*sub)!=(*tem)){
			return false;
		}
	}
	return (*tem)==0;
}
int dfs(char *s,int steps){
	if(strcmp(s,b)==0){
		return steps;
	}
	if(steps>10){
		return steps;
	}
	int mins=11,tmp;
	for(int i=0;s[i];i++){
		for(int j=0;j<ttop;j++){
			if(match(s+i,from[j])){
				char *c=new char[25];
				for(int k=0;k<i;k++){
					c[k]=s[k];
				}
				int k;
				for(k=0;to[j][k];k++){
					c[k+i]=to[j][k];
				}
				k+=i;
				for(int l=i+froml[j];s[l];l++,k++){
					c[k]=s[l];
				}
				c[k]=0;
				tmp=dfs(c,steps+1);
				if(tmp<mins){
					mins=tmp;
				}
				delete[] c;
			}
		}
	}
	return mins;
}
int main(){
	cin>>a>>b;
	for(;cin>>from[ttop]>>to[ttop];ttop++){
		froml[ttop]=strlen(from[ttop]);
		tol[ttop]=strlen(to[ttop]);
	}
	int tmp=dfs(a,0);
	if(tmp>10){
		cout<<"NO ANSWER!";
	}else{
		cout<<tmp;
	}
}
