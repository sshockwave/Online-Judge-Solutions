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
bool dfs(char *s,int rest){
	if(strcmp(s,b)==0){
		return true;
	}
	if(rest==0){
		return false;
	}
	rest--;
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
				if(dfs(c,rest)){
					return true;
				}
				delete[] c;
			}
		}
	}
	return false;
}
int main(){
	cin>>a>>b;
	for(;cin>>from[ttop]>>to[ttop];ttop++){
		froml[ttop]=strlen(from[ttop]);
		tol[ttop]=strlen(to[ttop]);
	}
	for(int i=0;i<=10;i++){
		if(dfs(a,i)){
			cout<<i;
			return 0;
		}
	}
	cout<<"NO ANSWER!";
}
