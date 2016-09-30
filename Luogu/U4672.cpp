#include <iostream>
#include <cstdio>
#include <cstring>
#define N 1010
using namespace std;
bool mat[N][N],reach[2][N][N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	memset(mat,0,sizeof(mat));
	memset(reach,0,sizeof(reach));
	int t,n,x,y;
	bool r=false;
	for(cin>>t;t--;){
		cin>>n;
		reach[r][1][1]=true;
		for(int i=0;i<2*n-2;i++,r=!r){
			memset(reach[!r],0,sizeof(reach[!r]));
			cin>>x>>y;
			for(int j=1;j<=n;j++){
				for(int k=1;k<=n;k++){
					if(reach[r][j][k]&&!mat[j][k]){
						reach[!r][j][k]=true;
						reach[!r][j+1][k]=true;
						reach[!r][j][k+1]=true;
						reach[!r][j-1][k]=true;
						reach[!r][j][k-1]=true;
					}
				}
			}
			mat[x][y]=true;
		}
		if(reach[r][n][n]){
			cout<<"Yes"<<endl;
		}else{
			cout<<"No"<<endl;
		}
	}
}
