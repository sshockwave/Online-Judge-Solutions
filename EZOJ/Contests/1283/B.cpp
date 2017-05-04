#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
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
inline lint nl(){
	lint i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int logN=85;
lint fib[logN],n,m,a,b;
inline bool aptry(const lint &da,const lint &db){
	if(a+da<=n&&b+db<=m){
		a+=da,b+=db;
		return true;
	}
	return false;
}
inline void approach(int i){
	if(i<2){
		if(aptry(1,2)){
			if(aptry(2,3)){
				if(i==1){
					aptry(2,3);
				}
			}
		}
	}else if(a+fib[i-2]>n||b+fib[i-1]>m){
		approach(i-2);
	}else{
		a+=fib[i-2],b+=fib[i-1];
		approach(i-1);
	}
}
lint diff,c;
inline int aptry2(const lint &da,const lint &db){
	assert(da<=db);
	if(c+db-da<=diff){
		a+=da,b+=db,c+=db-da;
		return true;
	}
}
inline void app2(int i){
	if(i<2){
		if(aptry2(1,2)){
			if(aptry2(2,3)){
				if(i==1){
					aptry2(2,3);
				}
			}
		}
	}else if(c+fib[i-2]>diff){
		a+=fib[i-1],b+=fib[i],c+=fib[i-2];
		app2(i-1);
	}else{
		app2(i-2);
	}
}
inline void getdiff(){
	if(diff==0){
		a=3,b=3;
		return;
	}
	if(diff==1){
		a=1,b=2;
		return;
	}
	int i=0;
	a=4,b=6,c=2;
	for(;c+fib[i]<diff;i++){
		a+=fib[i+1],b+=fib[i+2],c+=fib[i];
	}
	app2(i);
}
inline void solve(){
	a=b=1;
	int i=0;
	for(;a+fib[i]<=n&&b+fib[i+1]<=m;i++){
		a+=fib[i],b+=fib[i+1];
	}
	approach(i);
}
inline void brute(int n,int m){
	if((n==3&&m==3)||(n==1&&m==2)||(n==2&&m==1)){
		puts("NO");
		return;
	}
	if(n==1&&m==1){
		puts("YES 0 0");
		return;
	}
	int a[4]={0,2,1,3};
	if(n<m){
		printf("YES 0 %d\n",m-a[n]);
	}else{
		printf("YES %d 0\n",n-a[m]);
	}
}
int main(){
	fib[0]=3,fib[1]=5;
	for(int i=2;i<logN;i++){
		fib[i]=fib[i-1]+fib[i-2];
	}
	for(int tot=ni();tot--;){
		n=nl(),m=nl();
		if(n<=3||m<=3){
			brute(n,m);
			continue;
		}
		solve();
		if(a==n||b==m){
			if(a==n&&b==m){
				puts("NO");
			}else{
				printf("YES %lld %lld\n",n-a,m-b);
			}
			continue;
		}
		swap(n,m);
		solve();
		if(a==n||b==m){
			if(a==n&&b==m){
				puts("NO");
			}else{
				printf("YES %lld %lld\n",m-b,n-a);
			}
			continue;
		}
		bool flag;
		if(n>m){
			swap(n,m);
			flag=false;
		}else{
			flag=true;
		}
		diff=m-n;
		getdiff();
		if(flag){
			printf("YES %lld %lld\n",m-b,n-a);
		}else{
			printf("YES %lld %lld\n",n-a,m-b);
		}
	}
}
