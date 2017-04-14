#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int N=300010;
struct Item{
	int a,b;
}item[N];
inline bool operator < (Item a,Item b){
	return a.a<b.a;
}
int a[N],b[N],ans[N],pre[N];
int main(){
	int n=ni();
	for(int i=1;i<=n;i++){
		scanf("%d%d",&item[i].a,&item[i].b);
	}
	sort(item+1,item+n+1);
	for(int i=1;i<=n;i++){
		a[i]=item[i].a,b[i]=item[i].b;
	}
	memset(ans,0,sizeof(ans));
	pre[0]=0;
	for(int i=n;i>=1;i--){
		for(int j=1;j<=i;j++){
			ans[i]+=a[j]*(j-1)+b[j];
			pre[j]=pre[j-1]+a[j];
		}
		int p=1,val=b[1];
		for(int j=2;j<=i;j++){
			if(a[j]*(j-1)+b[j]-pre[j]<val){
				p=j,val=a[j]*(j-1)+b[j]-pre[j];
			}
		}
		for(int j=p;j<i;j++){
			a[j]=a[j+1],b[j]=b[j+1];
		}
	}
	for(int i=1;i<=n;i++){
		printf("%d\n",ans[i]);
	}
}
