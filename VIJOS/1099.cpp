#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n,code[26];
bool vis[26];
char a[30],b[30],c[30];
bool dfs(int x,int extra);
inline bool try3(int &x,int &c1,int &c2,int &c3,int &extra){
	if(code[c3]==-1){
		code[c3]=(code[c1]+code[c2]+extra)%n;
//		cout<<"\t\t\tcur:"<<(char)(c3+'A')<<"->"<<code[c3]<<endl;
		if(vis[code[c3]]){
//			cout<<"\t\t\tfail!"<<endl;
			code[c3]=-1;
			return false;
		}
		vis[code[c3]]=true;
//		cout<<"\t\t\tpass."<<endl;
		if(dfs(x-1,(code[c1]+code[c2]+extra)/n)){
			return true;
		}
		vis[code[c3]]=false;
		code[c3]=-1;
	}else{
//		cout<<"\t\t\tcur:"<<(char)(c3+'A')<<"->"<<code[c3]<<endl;
		if(code[c3]==(code[c1]+code[c2]+extra)%n){
//			cout<<"\t\t\tpass."<<endl;
			if(dfs(x-1,(code[c1]+code[c2]+extra)/n)){
				return true;
			}
		}
	}
	return false;
}
inline bool try2(int &x,int &c1,int &c2,int &c3,int &extra){
	if(code[c2]==-1){
//		cout<<"\t\tloop."<<endl;
		for(code[c2]=n-1;code[c2]>=0;code[c2]--){
			if(!vis[code[c2]]){
//				cout<<"\t\tcur:"<<(char)(c2+'A')<<"->"<<code[c2]<<endl;
				vis[code[c2]]=true;
				if(try3(x,c1,c2,c3,extra)){
					return true;
				}
				vis[code[c2]]=false;
			}
		}
		code[c2]=-1;
		return false;
	}else{
//		cout<<"\t\tcur:"<<(char)(c2+'A')<<"->"<<code[c2]<<endl;
		return try3(x,c1,c2,c3,extra);
	}
}
inline bool try1(int &x,int c1,int c2,int c3,int &extra){
	if(code[c1]==-1){
//		cout<<"\tloop."<<endl;
		for(code[c1]=n-1;code[c1]>=0;code[c1]--){
			if(!vis[code[c1]]){
//				cout<<"\tcur:"<<(char)(c1+'A')<<"->"<<code[c1]<<endl;
				vis[code[c1]]=true;
				if(try2(x,c1,c2,c3,extra)){
					return true;
				}
				vis[code[c1]]=false;
			}
		}
		code[c1]=-1;
		return false;
	}else{
//		cout<<"\tcur:"<<(char)(c1+'A')<<"->"<<code[c1]<<endl;
		return try2(x,c1,c2,c3,extra);
	}
}
bool dfs(int x,int extra){
	if(x<0&&!extra){
		return true;
	}
//	cout<<"Starting position "<<x<<":"<<endl;
	return try1(x,a[x]-'A',b[x]-'A',c[x]-'A',extra);
}
int main(){
	cin>>n>>a>>b>>c;
	memset(vis,0,sizeof(vis));
	memset(code,-1,sizeof(code));//Forgotten
	dfs(n-1,0);
	for(int i=0;i<n;i++){
		cout<<code[i]<<" ";
	}
}
