#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
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
const int N=210;
bool col[N];
int main(){
	int n;
	bool row,cur;
	for(int tot=ni();tot--;){
		memset(col,0,sizeof(col));
		row=true;
		n=ni();
		for(int i=0;i<n;i++){
			cur=false;
			for(int j=0;j<n;j++){
				if(ni()==1){
					cur=true;
					col[j]=true;
				}
			}
			if(!cur){
				row=false;
			}
		}
		if(row){
			row=false;
			for(int i=0;i<n;i++){
				if(!col[i]){
					row=true;
					break;
				}
			}
			if(row){
				puts("No");
			}else{
				puts("Yes");
			}
		}else{
			puts("No");
		}
	}
}
