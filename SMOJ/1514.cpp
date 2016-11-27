#include <iostream>
#include <cstdio>
#include <cstring>
#define N 100010
using namespace std;
char job[N][15];
bool face[N];//0:in  1:out
int main(){
	freopen("1514.in","r",stdin);
	freopen("1514.out","w",stdout);
	int n,m,d,a,s,p=0;
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++){
		scanf("%d%s",&d,job[i]);
		face[i]=d==1;
	}
	while(m--){
		scanf("%d%d",&a,&s);//a==0:left a==1:right
		if(a==0){
			s=-s;
		}
		if(face[p]){
			s=-s;
		}
		p=((p+s)%n+n)%n;
	}
	printf("%s",job[p]);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
