#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int next_int(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	for(;is_num(c);i=i*10-'0'+c,c=getchar());
	return i;
}
inline void reset(){
	//todo
}
inline int ISAP(int s,int t){
	//todo
}
inline int new_node(){
	
}
inline void add_edge(int u,int v,int w,int c,bool org){
	
	if(org){
		add_edge()
	}
}
inline void problem(){
	reset();
	int s=new_node(),t=new_node(),m=next_int(),stcost=next_int(),;
	//todo
}
int main(){
	int tot=next_int();
	for(int i=1;i<=tot;i++){
		printf("%d\n",problem());
	}
}
