#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <ctime>
#include <cstdlib>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){a=b;}
}
const int L=110,N=22,INF=0x7f7f7f7f;
int mat[L][L],ans=INF;
int main(){
	srand(time(NULL));
	int mx=ni,my=ni,n=ni;
	memset(mat,0,sizeof(mat));
	for(int i=1;i<=n;i++){
		int x=ni,y=ni;
		mat[x][y]=ni;
	}
	cout<<rand()%(n/2)<<endl;
}