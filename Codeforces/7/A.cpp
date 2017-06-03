#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
bool mat[8][8];
bool judge(int row,int column){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(mat[i][j]!=(((row>>i)&1)||((column>>j)&1))){
				return false;
			}
		}
	}
	return true;
}
int main(){
	memset(mat,0,sizeof(mat));
	char c;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			cin>>c;
			mat[i][j]=c=='B';
		}
	}
	int ti,tj,ans=20,cur;
	for(int i=0;i<256;i++){
		for(int j=0;j<256;j++){
			if(judge(i,j)){
				ti=i;
				tj=j;
				cur=0;
				while(ti>0){
					cur+=ti&1;
					ti=ti>>1;
				}
				while(tj>0){
					cur+=tj&1;
					tj=tj>>1;
				}
				ans=cur<ans?cur:ans;
			}
		}
	}
	cout<<ans;
}